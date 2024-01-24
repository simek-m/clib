#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <clist.h>

// TODO: 
static char *print_int_node(const void *const data) {
    if (data == nullptr)
	    return nullptr;

    int number = *((int *)data);
    
    // Allocate a buffer to of an exact size to fit the string.
    size_t length = snprintf(nullptr, 0, "%d", number) + 1;
    char *str = malloc(sizeof(char) * length);

    snprintf(str, length, "%d", number);
    
    return str;
}

// TODO: Array List.
// TODO: Growable string.
int main(void) {
  auto l = clist_new();
  printf("length: %zu\n", clist_len(&l));
  int first = 1;
  int second = 2;
  clist_push(&l, &first);
  clist_push(&l, &second);
  printf("length: %zu\n", clist_len(&l));
  clist_print(&l, print_int_node);
  int *elem2 = clist_pop(&l);
  printf("length: %zu\n", clist_len(&l));
  assert(elem2 != nullptr && *elem2 == 2);
  int *elem1 = clist_pop(&l);
  assert(elem1 != nullptr && *elem1 == 1);
}
