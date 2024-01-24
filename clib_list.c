#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <clist.h>

typedef struct node_t {
  struct node_t *prev;
  struct node_t *next;
  void *data;
} node_t;

// TODO: Varargs.
clist_t clist_new() {
  return (clist_t){};
}

int clist_push(clist_t *const list, void *data_ptr) {
  // Allocate and initialize a new node.
  node_t *new_node = malloc(sizeof(node_t));
  if (new_node == nullptr)
    return ENOMEM;
  *new_node = (node_t){.data = data_ptr};

  // Link to a previous node if present.
  if (list->len > 0) {
    node_t *old_tail = list->tail;
    new_node->prev = old_tail;
    old_tail->next = new_node;
  } else {
	list->head = new_node;
  }

  // Link to the list.
  list->tail = new_node;
  list->len++;

  return CLIST_OK;
}

void *clist_pop(clist_t *const list) {
  if (!list->len)
    return nullptr;

  node_t *node = list->tail;
  list->tail = node->prev;
  list->len--;

  void *data_ptr = node->data;
  free(node);

  return data_ptr;
}

// TODO: Macro?
void clist_foreach(clist_t *list, clist_foreach_cb_t cb) {
	node_t *current_node = list->head;
	for (size_t i = 0; i < list->len; i++) {
		cb(current_node->data);
		current_node = current_node->next;
	}
}

void clist_print(clist_t *list, clist_printer_t printer) {
	// TODO: Print to a buffer.
	printf("%s", "[");
	node_t *current_node = list->head;
	for (size_t i = 0; i < list->len; i++) {
		char *str = printer(current_node->data);
		if (str == nullptr)
			continue;

		if (i != 0) {
			printf(", %s", str);
		} else {
			printf("%s", str);
		}
		free(str);
		current_node = current_node->next;
	}
	printf("%s\n", "]");
}

