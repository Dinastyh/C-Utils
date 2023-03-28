#include "epoll_builder.h"
#include "log.h"

#include <errno.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <unistd.h>

#ifndef MAX_EVENTS
#define MAX_EVENTS 128
#endif

static bool epoll_init(struct epoll_builder_parameters *parameters) {
  struct v_iface *v_ifaces = parameters->v_ifaces.data;
  size_t v_ifaces_size = parameters->v_ifaces.len;

  for (size_t i = 0; i < v_ifaces_size; i++) {
    struct epoll_event event = {0};
    struct v_iface *v_iface = v_ifaces + i;
    event.events = v_iface->epoll_event_type;
    event.data.ptr = v_iface;

    if (epoll_ctl(parameters->instance, EPOLL_CTL_ADD, v_iface->socket,
                  &event)) {
      LOG(L_EMERGENCY, "Fail to add socket to epoll");
      return true;
    }
  }
  return false;
}

bool epoll_builder_run(struct epoll_builder_parameters *parameters) {
  if (epoll_init(parameters))
    goto error_epoll_init;

  int epoll_instance = parameters->instance;

  if (parameters->before_loop)
    if (parameters->before_loop(parameters)) {
      LOG(L_EMERGENCY, "Before_loop failed");
      goto error_before_loop;
    }

  while (!*(parameters->condition_to_leave)) {
    struct epoll_event events[MAX_EVENTS];
    int event_count = epoll_wait(epoll_instance, events, MAX_EVENTS, 0);

    if (event_count == -1) {
      switch (errno) {
      case EBADF:
      case EFAULT:
      case EINVAL:
        LOG(L_EMERGENCY, "Epoll_wait: %d", errno);
        goto error_event_count;
        break;
      case EINTR:
        continue;
      default:
        LOG(L_WARNING, "Epoll Wait");
        continue;
      }
    }

    for (int i = 0; i < event_count; i++) {
      struct v_iface *v_iface = events[i].data.ptr;

      if (events[i].events & EPOLLIN) {
        if (parameters->epollin(v_iface)) {
          LOG(L_EMERGENCY, "Epollin failed");
          goto error_epollin;
        }
      }

      if (events[i].events & EPOLLOUT)
        if (parameters->epollout(v_iface)) {
          LOG(L_EMERGENCY, "Epollout failed");
          goto error_before_loop;
        }
    }

    if (parameters->after_event)
      if (parameters->after_event(parameters)) {
        LOG(L_EMERGENCY, "After_event failed");
        goto error_after_event;
      }
  }

  if (parameters->after_loop)
    if (parameters->after_loop(parameters)) {
      LOG(L_EMERGENCY, "After_loop failed");
      goto error_after_loop;
    }

  if (parameters->close_instance)
    close(epoll_instance);
  return false;

error_after_loop:
error_after_event:
error_epollin:
error_event_count:
error_before_loop:
error_epoll_init:
  if (parameters->close_instance)
    close(epoll_instance);
  *parameters->condition_to_leave = true;
  return true;
}
