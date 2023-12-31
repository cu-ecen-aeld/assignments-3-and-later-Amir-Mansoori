#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
//#define DEBUG_LOG(msg,...)
#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{

    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    //struct thread_data* thread_func_args = (struct thread_data *) thread_param;
    struct thread_data* thread_func_args = (struct thread_data *) thread_param;
    thread_func_args -> thread_complete_success = false;
    usleep(1000 * (thread_func_args -> obtain_ms));
    int lock_err = pthread_mutex_lock(thread_func_args -> thread_mutex);
    if(lock_err != 0) {
        printf("failed mutex lock\n");
        exit(-1);
    }
    usleep(1000 * (thread_func_args -> release_ms));
    int unlock_err = pthread_mutex_unlock(thread_func_args -> thread_mutex);
    if(unlock_err != 0) {
        printf("failed mutex unlock\n");
        exit(-1);
    }
    thread_func_args -> thread_complete_success = true;
    return thread_param;
    pthread_exit(NULL);
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.      *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */
    struct thread_data *thread_func_args = malloc(sizeof(struct thread_data));
    thread_func_args -> obtain_ms = wait_to_obtain_ms;
    thread_func_args -> release_ms = wait_to_release_ms;
    thread_func_args -> thread_mutex = mutex;
    int err = pthread_create(thread, NULL, threadfunc, thread_func_args);
    if(err != 0) {
        printf("thread creation failed!\n");
        return false;
    }
   else {
    return true;
   }
}

