#include <stdio.h>
#include <stdlib.h>

struct list_item {
    int value;
    struct list_item * next;
};

void append(struct list_item *first, int x) {
   /* puts x at the end of the list */
  struct list_item *next_item;
  next_item = malloc(sizeof(struct list_item));
  next_item->value = x;
  next_item->next = NULL;
  while (first->next != NULL) {
    first = first->next;
  }
  first->next = next_item;
}

/* puts x at the beginning of the list */
void prepend(struct list_item *first, int x) {
  struct list_item *second_item;
  second_item = malloc(sizeof(struct list_item));
  second_item->value = x;
  second_item->next = first->next;
  first->next = second_item;
}

/* prints all elements in the list */
void print(struct list_item *first) {
  first = first->next;
  while (first != NULL) {
    printf("%d\n", first->value);
    first = first->next;
  }
  printf("\n");
}


 /* input_sorted: find the first element in the list larger than x
  and input x right before that element */
void input_sorted(struct list_item *first, int x) {
  struct list_item *new_item;
  new_item = malloc(sizeof(struct list_item));
  new_item->value = x;
  while(first->next != NULL && x >= first->next->value) {
    first = first->next;
  }
  new_item->next = first->next;
  first->next = new_item;
}

/* free everything dynamically allocated */
void clear(struct list_item *first) {
  struct list_item *root;
  root = first;
  root = root->next;

  struct list_item *temp;
  temp = root;

  while (root != NULL) {
    temp = root->next;
    free(root);
    root = temp;
  }

  first->next = NULL;

}

int main(int argc, char ** argv) {
   struct list_item root;
   root.value = -1; /* This value is always ignored */
   root.next = NULL;
   append(&root, 5);
   prepend(&root, 4);
   input_sorted(&root, 6);
   append(&root, 3);
   prepend(&root, 1);
   input_sorted(&root, 4);
   print(&root);
   clear(&root);
   append(&root, 9);
   print(&root);
   clear(&root);
}
