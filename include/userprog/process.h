#ifndef USERPROG_PROCESS_H
#define USERPROG_PROCESS_H

#include "threads/thread.h"

tid_t process_create_initd (const char *file_name);
tid_t process_fork (const char *name, struct intr_frame *if_);
int process_exec (void *f_name);
int process_wait (tid_t);
void process_exit (void);
void process_activate (struct thread *next);
/*----------------------------Project 2 arg passing -----------------------*/
void argument_stack(char **arg_list, int cnt, struct intr_frame *if_);
/*----------------------------Project 2 fd --------------------------------*/
int process_add_file(struct file *f);
struct file *process_get_file(int fd);

#endif /* userprog/process.h */
