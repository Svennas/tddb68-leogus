#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);

void
syscall_init (void)
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED)
{
  printf ("system call!\n");
  thread_exit ();
}

void halt(void) {
  power_off();
}

bool create(const char *file, unsigned initial_size) {
  return filesys_create(file, initial_size);
}

int open(const char *file) {
  if (file_open(file) == NULL) {
    return -1;
  }

  else {
    struct thread *t = thread_current();

    if (t->fd_int =< 129) {
      t->fd_int++;
      t->fd_list[fd] = file_open(file);
      return t->fd_int;
    }
  }
}

void close (int fd) {
  struct thread *t = thread_current();
  t->fd_list[fd] = NULL;
}

int read (int fd, void *buffer, unsigned size) {
  struct thread t* = thread_current();
  struct file f = t->fd_list[fd];

  if (file_open(f) == NULL) {
    return -1;
  }

  else {
    fgets(buffer, size, f);
    puts(buffer);

    if (size > sizeof(f)) {
      return sizeof(file);
    }
    else {
      return size;
    }
  }
}

int write (int fd, const void *buffer, unsigned size) {
  struct thread t* = thread_current();
  struct file f = t->fd_list[fd];

  if (file_open(f) == NULL) {
    return -1;
  }

  else {
    fputs(buffer, f)

    if (size > sizeof(f)) {
      return sizeof(file);
    }
    else {
      return size;
    }
  }
}

void exit (int status) {
  struct thread t* = thread_current;
  free(t);
}
