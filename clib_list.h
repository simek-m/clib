#ifndef CLIST_H
#define CLIST_H

#include <stddef.h> // size_t

#define CLIST_OK (0)

typedef struct node node_t;

typedef struct clist {
  node_t *head;
  node_t *tail;
  size_t len;
} clist_t;

// TODO: Varargs,
clist_t clist_new();

inline size_t clist_len(const clist_t *const list) { return list->len; }

int clist_push(clist_t *const list, void *data_ptr);

void *clist_pop(clist_t *const list);

typedef void (*clist_foreach_cb_t)(void *data);

void clist_foreach(clist_t *list, clist_foreach_cb_t cb);

typedef char* (*clist_printer_t)(const void *const data);

void clist_print(clist_t *list, clist_printer_t printer);

#endif // CLIST_H

