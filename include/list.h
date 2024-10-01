//
// Created by zhkag on 24-10-1.
//

#ifndef OS_LIST_H
#define OS_LIST_H
#include <stddef.h>

struct os_list {
    struct os_list *prev;
    struct os_list *next;
};

#define OS_LIST_INIT(ptr)  static struct os_list ptr = { &ptr, &ptr };
#define CONTAINER_OF(ptr, type, member) \
  ((type *)((char *)(ptr) - offsetof(type, member)))

static __inline void os_list_init(struct os_list *list){
  list->prev = list->next = list;
};

static __inline void os_list_insert_after(struct os_list *list, struct os_list *node){
  node->next = list->next;
  node->prev = list;
  list->next->prev = node;
  list->next = node;
}

static __inline void os_list_insert_before(struct os_list *list, struct os_list *node){
  node->next = list;
  node->prev = list->prev;
  list->prev->next = node;
  list->prev = node;
}

static __inline void os_list_del(struct os_list *node){
  node->prev->next = node->next;
  node->next->prev = node->prev;
  node->prev = node->next = node;
}

static __inline struct os_list *os_list_next_entry(struct os_list *node){
  return node->next;
}

static __inline struct os_list *os_list_prev_entry(struct os_list *node){
  return node->prev;
}

//static __inline struct os_list *os_list_first_entry(struct os_list *node){
//  struct os_list *head = node;
//  while (head->prev != head){
//    head = head->prev;
//  }
//  return head;
//}
//
//static __inline struct os_list *os_list_last_entry(struct os_list *node){
//  struct os_list *last = node;
//  while(last->next != last){
//    last = last->next;
//  }
//  return last;
//}

static __inline int os_list_len(struct os_list *list){
  int len = 0;
  struct os_list *head = list;
  while (head->next != head){
    head = head->next;
    len++;
  }
  return len;
}

static __inline int os_list_is_empty(struct os_list *list){
  return list->next == list;
}

#endif //OS_LIST_H
