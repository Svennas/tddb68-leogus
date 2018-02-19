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
      t->fd_list[fd_int] = file_open(file);
      return t->fd_int;
    }
  }
}

void close (int fd) {
  struct thread *t = thread_current();
  file_close(t->fd_list[fd]);
  t->fd_list[fd] = NULL;
}

int read (int fd, void *buffer, unsigned size) {
  struct thread t* = thread_current();
  struct file f* = t->fd_list[fd];

  if (file_open(f) == NULL) {
    return -1;
  }

  else {
    //different function(s) depending if fd is 0 or not
    if (fd == 0) {
      input_getc(buffer, size);
    }
    else {
      fgets(buffer, size, f);
      puts(buffer);
    }

    //determines return value
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
  struct file f* = t->fd_list[fd];

  if (file_open(f) == NULL) {
    return -1;
  }

  else {
    //different function depending if fd is 1 or not
    if (fd == 1) {
      putbuf(buffer, size);
    }
    else {
      fputs(buffer, f);
    }

    //determines return value
    if (size > sizeof(f)) {
      return sizeof(file);
    }
    else {
      return size;
    }
  }
}

void exit (int status) {
  thread_exit();
}
