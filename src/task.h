/* This structure describes a "task" to be run by a thread.  */
typedef struct {
    void (*fn)(void *);
    void (*data);
    // complete with additional field if needed
} miniomp_task_t;

typedef struct {
    int max_elements;
    int count;
    int finished_count;
    int head;
    int tail;
    int first;
    pthread_mutex_t lock_queue;
    pthread_mutex_t lock_operations;
    miniomp_task_t **queue;
    // complete with additional field if needed
} miniomp_taskqueue_t;

extern miniomp_taskqueue_t * miniomp_taskqueue;
#define MAXELEMENTS_TQ 2048

// funtions to implement basic management operations on taskqueue
bool is_empty(miniomp_taskqueue_t *task_queue);
bool is_full(miniomp_taskqueue_t *task_queue) ;
bool is_valid(miniomp_task_t *task_descriptor);
bool enqueue(miniomp_taskqueue_t *task_queue, miniomp_task_t *task_descriptor);
bool dequeue(miniomp_taskqueue_t *task_queue);
bool try_lock(miniomp_taskqueue_t *task_queue);
void lock(miniomp_taskqueue_t *task_queue);
void unlock(miniomp_taskqueue_t *task_queue);
miniomp_task_t *first(miniomp_taskqueue_t *task_queue); 
void init_task_queue(int max_elements);
