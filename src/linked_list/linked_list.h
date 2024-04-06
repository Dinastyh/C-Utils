#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "aliases.h"
#include "log.h"
#include "stdlib.h"

#define LIST_DEF(TYPE, NAME)                                                   \
  struct list_##NAME##_node {                                                  \
    TYPE data;                                                                 \
    struct list_##NAME##_node *prev;                                           \
    struct list_##NAME##_node *next;                                           \
  };                                                                           \
                                                                               \
  struct list_##NAME {                                                         \
    size_t size;                                                               \
    struct list_##NAME##_node *start;                                          \
    struct list_##NAME##_node *end;                                            \
  };                                                                           \
                                                                               \
  static struct list_##NAME *list_##NAME##_create(void) {                      \
    struct list_##NAME *list = calloc(1, sizeof(struct list_##NAME));          \
    if (!list) {                                                               \
      LOG(L_ALERT, "Fail to allocate list_" #NAME);                            \
      return NULL;                                                             \
    }                                                                          \
    return list;                                                               \
  }                                                                            \
                                                                               \
  static bool list_##NAME##_push_front(struct list_##NAME *list, TYPE value) { \
    if (!list) {                                                               \
      LOG(L_ALERT, "Attempt to push_front in NULL list");                      \
      return false;                                                            \
    }                                                                          \
                                                                               \
    struct list_##NAME##_node *node =                                          \
        calloc(1, sizeof(struct list_##NAME##_node));                          \
    if (!list) {                                                               \
      LOG(L_ALERT, "Fail to allocate list_" #NAME##"_node");                   \
      return NULL;                                                             \
    }                                                                          \
  }                                                                            \
  \\Function not finished

#endif /* LINKED_LIST_H */
