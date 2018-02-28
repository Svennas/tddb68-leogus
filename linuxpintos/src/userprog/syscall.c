#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/init.h"
#include "filesys/filesys.h"
#include "filesys/file.h"

static void syscall_handler (struct intr_frame *);

void
syscall_init (void)
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f)
{
  printf ("system call!\n");

  /*determines syscall and arguments with intr_frame's esp field and calls it*/
  switch (*(int*)(f->esp)) {
    case SYS_HALT:
      halt();
      break;
    case SYS_CREATE:
      f->eax = create((char*)(f->esp+4), *(unsigned*)(f->esp+4*2));
      break;
    case SYS_OPEN:
      f->eax = open((char*)(f->esp+4));
      break;
    case SYS_CLOSE:
      close(*(char*)(f->esp+4));
      break;
    case SYS_READ:
      read(*(char*)(f->esp+4), (char*)(f->esp+4*2), *(char*)(f->esp+4*3));
      break;
    case SYS_WRITE:
      f->eax = write(*(char*)(f->esp+4), (char*)(f->esp+4*2), *(char*)(f->esp+4*3));
      break;
    case SYS_EXIT:
      exit(*(char*)(f->esp+4));
      break;
    default:
      printf("System call not accounted for.\n");
  }

  thread_exit();
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

    if (t->fd_int <= 129) {
      t->fd_int++;
      t->fd_list[t->fd_int] = file_open(file);
      return t->fd_int;
    }
    printf("%s\n", "Amount of opened files simultaneously permitted exceeded.\n");
    return -1;
  }
}

void close (int fd) {
  struct thread *t = thread_current();
  file_close(t->fd_list[fd]);
  t->fd_list[fd] = NULL;
}

int read (int fd, void *buffer, unsigned size) {
  struct thread *t = thread_current();
  struct file *f = t->fd_list[fd];

  /*different function(s) depending if fd is 0 or not*/
  if (fd == 0) {
    input_getc(buffer, size);
    return size;
  }
  else {
    if (file_open(f) == NULL) {
      return -1;
    }

    file_read(f, buffer, size);
  }

  /*determines return value (when file can be opened and fd != 0)*/
  if (size > sizeof(f)) {
    return sizeof(f);
  }
  else {
    return size;
  }
}

int write (int fd, const void *buffer, unsigned size) {
  printf("Welcome to write!\n");
  struct thread *t = thread_current();
  struct file *f = t->fd_list[fd];
  printf("fd: %d\n", fd);
  printf("size: %u\n", size);

  /*different function depending if fd is 1 or not*/
  if (fd == 1) {
    putbuf(buffer, size);
    return size;
  }
  else {
    if (file_open(f) == NULL) {
      return -1;
    }

    file_write(f, buffer, size);
  }

  /*determines return value (when file can be opened and fd != 1)*/
  if (size > sizeof(f)) {
    printf("bloop\n");
    return sizeof(f);
  }
  else {
    printf("blarp\n");
    return size;
  }
}

void exit (int status) {
  thread_exit();
}
