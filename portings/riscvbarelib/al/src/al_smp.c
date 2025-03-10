/*
(C) 2014 EEMBC(R).  All rights reserved.

All EEMBC Benchmark Software are products of EEMBC
and are provided under the terms of the EEMBC Benchmark License Agreements.
The EEMBC Benchmark Software are proprietary intellectual properties of EEMBC and its Members
and is protected under all applicable laws, including all applicable copyright laws.
If you received this EEMBC Benchmark Software without having
a currently effective EEMBC Benchmark License Agreement, you must discontinue use.
Please refer to LICENSE.md for the specific license agreement that pertains to this Benchmark Software.
*/

/* File: mith/al/src/al_smp.c
	Abstraction layer implementation for thread API

	This file contains implementation prototypes using pthreads for all MITH API.
	Change the implementation of the functions in this file to use primitives applicabale to your target.
	Also see pthread documentation for expected behavior of this API which is a subset of pthreads API.
*/

#include <stdatomic.h>
#include "common/threads.h"
#include "common/spin_mutex.h"
#include "th_lib.h"
#include "al_smp.h"

#if (USE_SINGLE_CONTEXT!=1)
/* Function: al_mutex_init
	Initialize a mutex.
*/
int al_mutex_init(al_mutex_t *mutex) {
	spin_mutex_init(mutex);
	return 0;
}
/* Function: al_mutex_lock
	Lock a mutex.
*/
int al_mutex_lock(al_mutex_t *mutex) {
	spin_mutex_lock(mutex);
	return 0;
}
/* Function: al_mutex_trylock
	Non-blocking mutex lock.
*/
int al_mutex_trylock(al_mutex_t *mutex) {
	spin_mutex_trylock(mutex);
	return 0;
}
/* Function: al_mutex_unlock
	Unlock a mutex.
*/
int al_mutex_unlock(al_mutex_t *mutex) {
	spin_mutex_unlock(mutex);
	return 0;
}
/* Function: al_mutex_lock
	Destroy a mutex.
*/
int al_mutex_destroy(al_mutex_t *mutex) {
	spin_mutex_destroy(mutex);
	return 0;
}

/* Function: al_cond_init
	Initialize a cond variable.
*/
int al_cond_init(al_cond_t *cond) {
	al_mutex_init(&cond->lock);
	atomic_store(&cond->waiters, 0);
	return 0;
}
/* Function: al_cond_signal
	Signal on a cond variable.
*/
int al_cond_signal(al_cond_t *cond) {
	al_mutex_init(&cond->lock);
	if (atomic_load(&cond->waiters) > 0) {
		atomic_fetch_sub(&cond->waiters, 1);
	}
	al_mutex_unlock(&cond->lock);
	return 0;
}
/* Function: al_cond_broadcast
	Broadcast on a cond variable.
*/
int al_cond_broadcast(al_cond_t *cond) {
	al_mutex_init(&cond->lock);
	atomic_store(&cond->waiters, 0);
	al_mutex_unlock(&cond->lock);
	return 0;
}
/* Function: al_cond_wait
	Wait on a cond variable, releasing an associated mutex.
*/
int al_cond_wait(al_cond_t *cond, al_mutex_t *mutex) {
	atomic_fetch_add(&cond->waiters, 1);
	al_mutex_unlock(mutex);
	while (atomic_load(&cond->waiters) > 0) {
		cpu_delay(1000);
	}
	al_mutex_lock(mutex);
	return 0;
}
/* Function: al_cond_destroy
	Destroy a cond variable.
*/
int al_cond_destroy(al_cond_t *cond) {
	al_mutex_destroy(&cond->lock);
}

/* Function: al_thread_create
	Create a new thread

	Parameters:
	thread - pointer to a thread structure
	start_routine - pointer to the function to invoke for the new thread
	arg - argument to pass to the start_routine
*/
int al_thread_create(al_thread_t * thread, void *(*start_routine)(void *), void * arg) {
	return thread_create(thread, start_routine, arg);
}
/* Function: al_thread_join
	Wait for a thread to complete.
*/
int al_thread_join(al_thread_t thread, void **thread_return) {
	int ret = thread_join(&thread);

	if (ret == 0) {
		if (thread_return) {
			*thread_return = thread.ret;
		}
		return 0;
	}

	return ret;
}
#endif

void al_set_hardware_info(char *pdescription) {
	e_s32 tmp;
	th_parse_buf_flag(pdescription,"cores=",&tmp);
	hardware_info.num_processors=tmp;
	hardware_info.description_string=pdescription;
}

hardware_info_t hardware_info={1,NULL};

/* Function: al_thread_create_ex
	Create a new thread, using extra information to set specific hardware related parameters.
	This function is used by some work items to allow affinity on sub threads created by the work item.

	Parameters:
	thread - pointer to a thread structure
	start_routine - pointer to the function to invoke for the new thread
	arg - argument to pass to the start_routine
	tex - extra information for thread create extensions.

	Default implementation:
	Use the extra information to set thread affinity such that each sub item with id>0 is assigned
	affinity to a specific processor.
	* Default implementation will only set affinity if PTHREAD_SETAFFINITY_NP is enabled.
*/
int al_thread_create_ex(al_thread_t * pThread, void *(*start_routine)(void *), void * arg, mith_textend *tex) {
	int retval=al_thread_create(pThread,start_routine,arg);
	if (tex!=NULL)
		retval*=1;
	return retval;
}

/* Function: al_setaffinity
	Description:
	If affinity is supported, can potentially use affinity to set specific work items to specific affinity.
	This function controls the way affinity is assigned to new work items being executed.

	Parameters:
	Item identifiers - kernel and instance (unique) as well as serial item id,
	and context_id representing the harness view of items running in parallel.

	Default implementation:
	Assign different affinity to each context created by the harness up to num_processors.

	Porting:
	This function needs to be ported if affinity for work items is desired.
	This affects the work item affinity at the harness level, since this function is
	called before each work item starts initialization and processing.
*/
int al_item_setaffinity(int kernel_id, int instance_id, int item_id, e_u32 context_id) {
	int retval=kernel_id+instance_id+item_id+context_id;
	return retval;
}
