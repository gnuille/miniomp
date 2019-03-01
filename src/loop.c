#include "libminiomp.h"

// Declaratiuon of global variable for loop work descriptor
miniomp_loop_t miniomp_loop;

/* The *_next routines are called when the thread completes processing of 
   the iteration block currently assigned to it.  If the work-share 
   construct is bound directly to a parallel construct, then the iteration
   bounds may have been set up before the parallel.  In which case, this
   may be the first iteration for the thread.

   Returns true if there is work remaining to be performed; *ISTART and
   *IEND are filled with a new iteration block.  Returns false if all work
   has been assigned.  */

bool
GOMP_loop_dynamic_next (long *istart, long *iend) {
  printf("TBI: Asking for more iterations? I gave you all at the beginning, no more left ...\n");
  return(false);
}

/* The *_start routines are called when first encountering a loop construct
   that is not bound directly to a parallel construct.  The first thread 
   that arrives will create the work-share construct; subsequent threads
   will see the construct exists and allocate work from it.

   START, END, INCR are the bounds of the loop; CHUNK_SIZE is the
   scheduling parameter. 

   Returns true if there's any work for this thread to perform.  If so,
   *ISTART and *IEND are filled with the bounds of the iteration block
   allocated to this thread.  Returns false if all work was assigned to
   other threads prior to this thread's arrival.  */

bool
GOMP_loop_dynamic_start (long start, long end, long incr, long chunk_size,
                         long *istart, long *iend)
{
  printf("TBI: What a mess! Starting a non-static for worksharing construct and dont know what to do, I'll take it all\n");
  *istart = start;
  *iend = end;
  return(true);
}

/* The GOMP_loop_end* routines are called after the thread is told that
   all loop iterations are complete.  The first version synchronize
   all threads; the nowait version does not. */

void
GOMP_loop_end (void) {
  printf("TBI: Finishing a for worksharing construct with non static schedule\n");
}

void
GOMP_loop_end_nowait (void) {
  printf("TBI: Finishing a for worksharing construct with non static schedule, with nowait clause\n");
}

#if 0
// Only implement this if really needed, i.e. you find a case in which it is invoked

/* The GOMP_parallel_loop_* routines pre-initialize a work-share construct
   to avoid one synchronization once we get into the loop. The compiler 
   does not invoke the *_start routine for the work-share. And of course, 
   the compiler does not invoke GOMP_loop_end. These routines should create 
   the team of threads to execute the work-share in parallel */

void
GOMP_parallel_loop_dynamic (void (*fn) (void *), void *data,
                            unsigned num_threads, long start, long end,
                            long incr, long chunk_size, unsigned flags)
{
  printf("TBI: What another mess! Directly starting a parallel and a non-static for worksharing construct! I am lost!\n");
  // Here you should pre-initialize the work-sharing structures as done in 
  // GOMP_loop_dynamic_start; only the master thread is doing this, the other
  // threads in the team do not reach this point 
  GOMP_parallel (fn, data, num_threads, flags);
}
#endif
