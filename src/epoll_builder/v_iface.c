#include "v_iface.h"
#include "log.h"
#include "unistd.h"

#include <stdlib.h>
bool v_iface_init(struct v_iface *v_iface, int socket,
                  unsigned epoll_event_type, void *context,
                  void *(*allocate_ctx)(void)) {

  if ((!context && !allocate_ctx) || (context && allocate_ctx)) {
    LOG(L_ERROR, "Invalid argument: context and allocate_ctx can't be null or "
                 "defined in the same time");
    goto error_parameter;
  }

  if (context)
    v_iface->context = context;
  else if ((context = allocate_ctx()) == NULL) {
    LOG(L_ERROR, "Fail to allocate v_iface");
    goto error_allocation_context;
  }

  v_iface->socket = socket;
  v_iface->epoll_event_type = epoll_event_type;

  return false;

error_allocation_context:
error_allocation_v_iface:
error_parameter:
  return true;
}

void v_iface_del(struct v_iface *v_iface, bool close_socket,
                 void(free_ctx)(void *ctx)) {
  if (!v_iface) {
    LOG(L_ERROR, "Invalid argument: Attempt to del a NULL v_iface pointer");
    return;
  }

  if (close_socket)
    close(v_iface->socket);

  if (free_ctx)
    free_ctx(v_iface->context);
}
