#include <stdio.h>

struct list_item {
    int value;
    struct list_item * next;
};

void append(struct list_item *first, int x) {
   /* puts x at the end of the list */
  while (first->next != NULL) {
    first = first->next;
  }
  struct list_item *last;
  last->value = x;
  last->next = NULL;
  first->next = last;
}

void prepend(struct list_item *first, int x) {
  /* puts x at the beginning of the list */
  struct list_item second;
  second.value = x;
  second.next = first->next;
  first->next = &second;
}

void print(struct list_item *first) {
  /* prints all elements in the list */
  while (first->next != NULL) {
    printf("%d", first->value);
    first = first->next;
  }
 }

void input_sorted(struct list_item *first, int x);
/* input_sorted: find the first element in the list larger than x
 and input x right before that element */
void clear(struct list_item *first); /* free everything dynamically allocated */

int main(int argc, char ** argv) {
   struct list_item root;
   root.value = -1; /* This value is always ignored */
   root.next = NULL;
   append(&root, 5);
   //append(&root, 3);
   //prepend(&root, 43);
   print(&root);
}
