#ifndef THREADS_SYNCH_H
#define THREADS_SYNCH_H
#include <list.h>
#include <stdbool.h>

struct semaphore 
  {
    unsigned value;            
    struct list waiters;        
  };

void sema_init (struct semaphore *, unsigned value);
void sema_down (struct semaphore *);
bool sema_try_down (struct semaphore *);
void sema_up (struct semaphore *);
void sema_self_test (void);

/* Lock. */
struct lock 
  {
    struct thread *holder;   
    struct semaphore semaphore; 
    bool is_donated;            
  };

void lock_init (struct lock *);
void lock_acquire (struct lock *);
bool lock_try_acquire (struct lock *);
void lock_release (struct lock *);
bool lock_held_by_current_thread (const struct lock *);


struct condition 
  {
    struct list waiters;        
  };

void cond_init (struct condition *);
void cond_wait (struct condition *, struct lock *);
void cond_signal (struct condition *, struct lock *);
void cond_broadcast (struct condition *, struct lock *);

bool compare_sema(struct list_elem *l1, struct list_elem *l2,void *aux);


#define barrier() asm volatile ("" : : : "memory")

#endif /* threads/synch.h */
