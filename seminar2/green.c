#include <stdlib.h>
#include <ucontext.h>
#include <assert.h>
#include "green.h"

#define FALSE 0
#define TRUE 1
#define STACK_SIZE 4096

static ucontext_t main_cntx = {0};
static green_t main_green = {&main_cntx, NULL, NULL, NULL, NULL, FALSE};

static green_t *running = &main_green;

static green_t *queue = NULL

static void init() __attribute__((constructor));

void init(){
    getcontext(&main_cntx)
}

int green_create(green_t *new, void *(*fun)(void*), void *arg){
    ucontext_t *cntx = (ucontext_t*) malloc(sizeof(ucontext_t));
    getcontext(cntx);

    void *stack = malloc(STACK_SIZE);

    cntx->uc_stack.ss_sp = stack;
    cntx->uc_stack.ss_size = STACK_SIZE;

    makecontext(cntx, green_thread, 0)
    new->context = cntx;
    new->fun = fun;
    new->arg = arg;
    new->next = NULL;
    new->join = NULL;
    new->zombie = FALSE;

    //add new to the ready queue

    return 0;
}

void green_thread(){
    green_t *this = running;
    
    (*this->fun)(this->arg);

    //place waiting (joining) thread in ready queue

    //free alocated memory structure

    //we're a zombie

    //find the next thread to run

    running = next;

    setcontext(next->context);
}

int green_yield(){
    green_t * susp = running;
    //add susp to ready queue

    //select the enxt thread for execution

    running = next;
    swapcontext(susp->context, next->context)
    return 0;
}

int green_join(green_t *thread){

    if(thread->zombie)
        return 0;
    
    green_t *susp = running;
    //add to waiting threads

    //select the next thread for execution

    running = next;
    swapcontext(susp->context, next->context);

    return 0:
}

