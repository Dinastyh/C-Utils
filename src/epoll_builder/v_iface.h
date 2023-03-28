#ifndef V_IFACE_H
#define V_IFACE_H

#include "aliases.h"
#include "slice.h"

struct v_iface {
  int socket;
  unsigned epoll_event_type;
  void *context;
};

SLICE_DEF(struct v_iface, v_iface)

bool v_iface_init(struct v_iface *v_iface, int socket,
                  unsigned epoll_event_type, void *context,
                  void *(*allocate_ctx)(void));

void v_iface_del(struct v_iface *iface, bool close_socket,
                 void(free_ctx)(void *ctx));

#endif /* V_IFACE_H */
