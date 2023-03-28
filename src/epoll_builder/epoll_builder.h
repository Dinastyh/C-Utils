#ifndef EPOLL_BUILDER_H
#define EPOLL_BUILDER_H

#include <stdatomic.h>

#include "v_iface.h"

struct epoll_builder_parameters {
  struct slice_v_iface v_ifaces;

  bool (*before_loop)(struct epoll_builder_parameters *parameters);
  bool (*epollin)(struct v_iface *v_iface);
  bool (*epollout)(struct v_iface *v_iface);
  bool (*after_event)(struct epoll_builder_parameters *parameters);
  bool (*after_loop)(struct epoll_builder_parameters *parameters);
  atomic_bool *condition_to_leave;
  void *data;

  int instance;
  bool close_instance;
};

bool epoll_builder_run(struct epoll_builder_parameters *parameters);

#endif /* EPOLL_H */
