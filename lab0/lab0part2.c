#include <stdio.h>

struct list_item {
    int value;
    struct list_item * next;
};

void append(struct list_item *first, int x) {
   /* puts x at the end of the list */
  typedef struct list_item Node;
  Node *next_item = (Node*)malloc(sizeof(Node));
  next_item->value = x;
  next_item->next = NULL;
  while (first->next != NULL) {
    first = first->next;
  }
  first->next = next_item;
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
