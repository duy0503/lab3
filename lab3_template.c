/*
  CPSC 223C
  Spring 2015
  CSU Fullerton

  Lab 3: structures and dynamic memory

  Authors: Kevin Wortman (kwortman@csu.fullerton.edu) (REPLACE THIS
  WITH YOUR NAMES AND CSUF EMAIL ADDRESSES)

*/ 

#include <assert.h>  // for assert()
#include <stdio.h>   // for printf()
#include <stdlib.h>  // for malloc() and free()

/* The following declares the types and functions for a data structure
   implementing a queue of integers. You should leave these
   declarations alone. */

struct Queue;
struct NODE;

/* Allocate and return a pointer to an empty queue, or return NULL if
   allocation failed. */
struct Queue* queue_make();

/* Free a queue and all its contents. The queue pointer must be
   valid. */
void queue_free(struct Queue* queue);

/* Return the number of elements in a queue. The queue pointer must be valid. */
int queue_length(struct Queue* queue);

/* Push a new element at the front of the queue. The queue pointer
   must be valid. Returns a true value on success and false if
   allocation failed. */
int queue_push_front(struct Queue* queue, int data);

/* Push a new element at the back of the queue. The queue pointer must
   be valid. Returns a true value on success and false if allocation
   failed. */
int queue_push_back(struct Queue* queue, int data);

/* Return the element at the front of the queue. The queue pointer
   must be valid and the queue must not be empty. */
int queue_front(struct Queue* queue);

/* Return the element at the front of the queue. The queue pointer
   must be valid and the queue must not be empty. */
int queue_back(struct Queue* queue);

/* Remove the element at the front of the queue. The queue pointer
   must be valid and the queue must not be empty. */
void queue_pop_front(struct Queue* queue);

/* Remove the element at the back of the queue. The queue pointer must
   be valid and the queue must not be empty. */
void queue_pop_back(struct Queue* queue);

/* Remove all elements from the queue. The queue pointer must be
   valid. */
void queue_clear(struct Queue* queue);

/* Print the queue and its contents to standard output in a
   human-readable format for debugging purposes. */
void queue_print(struct Queue* queue);

/********** START OF CODE TO MODIFY **********/

#define QUEUE_CAPACITY 100000 // one hundred thousand

/* This is a poor implementation of the queue interface based upon a
   fixed-size array. The array approach has two big flaws: it is
   limited to QUEUE_CAPACITY elements, and pushing an element to the
   front takes O(n) time, which is slow.

   Your mission is to refactor (rewrite) this code to implement the
   queue with a proper doubly-linked list.

   The doubly-linked list approach is more complex, but solves both
   these problems. It can handle any number of elements, limited only
   by computer memory, and pushing an element to the front is O(1),
   which is fast.

   I expect that you will need to modify the Queue struct to have some
   kind of head and/or tail pointer instead of a data array, and
   create another struct called Node or something like that. The
   definitions of all the queue functions will probably need to be
   rewritten. However the definitions (interfaces) should stay the
   same.
*/

 struct Queue {
  int n;
  struct Queue *front;
  struct Queue *back;
};

struct NODE {
  int data;
  struct NODE *previous;
  struct NODE *next;
};
struct Queue* queue_make() {
  struct Queue* queue;

  queue = malloc(sizeof(struct Queue));
  if (queue == NULL)
    return NULL;
  queue->n = 0;
  queue->front = NULL;
  queue->back = NULL;

  return queue;
}

void queue_free(struct Queue* queue) {
  assert(queue != NULL);
  free(queue);
}
  
int queue_length(struct Queue* queue) {
  assert(queue != NULL);
  return queue->n;
}

int queue_push_front(struct Queue* queue, int data) {
  int i;
  assert(queue != NULL);
  struct NODE *newNode;
  newNode = malloc(sizeof(struct NODE));
  newNode->data = data;
  newNode->previous = NULL;
  newNode->next = NULL;
  if(queue->front == NULL) queue->front = newNode;
  else{
    newNode->next = front;
    front = newNode->previous;
  }

  /*for (i = QUEUE_CAPACITY - 1; i > 0; i--)
    queue->data[i] = queue->data[i-1];

    queue->data[0] = data;*/

  queue->n++;

  return 1;
}

int queue_push_back(struct Queue* queue, int data) {
  assert(queue != NULL);
  //assert(queue->n < QUEUE_CAPACITY);
  struct NODE *newNode;
  newNode = malloc(sizeof(struct NODE));
  newNode->data = data;
  newNode->previous = NULL;
  newNode->next = NULL;
  if(queue-> back == NULL) queue->back = newNode;
  else{
    newNode->previous = back;
    back = newNode -> next;
  }
  queue->n++;
  return 1;
}

int queue_front(struct Queue* queue) {
  assert(queue != NULL);
  assert(queue_length(queue) > 0);

  return front->data;
}

int queue_back(struct Queue* queue) {
  assert(queue != NULL);
  assert(queue_length(queue) > 0);

  return back->data;
}

void queue_pop_front(struct Queue* queue) {
  int i;

  assert(queue != NULL);
  assert(queue_length(queue) > 0);

  /*for (i = 1; i < QUEUE_CAPACITY; i++)
    queue->data[i - 1] = queue->data[i];*/
  front = front->next;
  free(front->previous);
  queue->n--;
}

void queue_pop_back(struct Queue* queue) {
  assert(queue != NULL);
  assert(queue_length(queue) > 0);
  back = back->previous;
  free(back->next);
  queue->n--;
}

void queue_clear(struct Queue* queue) {
  assert(queue != NULL);

  queue->n = 0;
  while(front != back){
    back = back->previous;
    free(back->next);
  }
  front = back = NULL;
}

void queue_print(struct Queue* queue) {
  int i;

  assert(queue != NULL);

  printf("queue:");

  struct NODE *ptr;
  ptr = front;
  while(ptr != back->next) printf("%d\t", ptr->data);

  printf("\n");
}

/********** END OF CODE TO MODIFY **********/

/* This main() function tests the correctness of your queue using the assert() macro. */

int main(void) {

  struct Queue* queue;
  int ok, i;

  /* Create a queue. */
  queue = queue_make();
  assert(queue != NULL);
  assert(queue_length(queue) == 0);
  queue_print(queue);

  /* Test basic operation: push elements, alternating somewhat
     randomly between the front and back. We assert correctness of the
     queue after each step. */

  ok = queue_push_front(queue, 1);
  assert(ok);
  assert(queue_length(queue) == 1);
  assert(queue_front(queue) == 1);
  assert(queue_back(queue) == 1);
  queue_print(queue);

  ok = queue_push_front(queue, 2);
  assert(ok);
  assert(queue_length(queue) == 2);
  assert(queue_front(queue) == 2);
  assert(queue_back(queue) == 1);
  queue_print(queue);

  ok = queue_push_back(queue, 3);
  assert(ok);
  assert(queue_length(queue) == 3);
  assert(queue_front(queue) == 2);
  assert(queue_back(queue) == 3);
  queue_print(queue);

  ok = queue_push_back(queue, 4);
  assert(ok);
  assert(queue_length(queue) == 4);
  assert(queue_front(queue) == 2);
  assert(queue_back(queue) == 4);
  queue_print(queue);

  ok = queue_push_front(queue, 5);
  assert(ok);
  assert(queue_length(queue) == 5);
  assert(queue_front(queue) == 5);
  assert(queue_back(queue) == 4);
  queue_print(queue);

  queue_pop_back(queue);
  assert(queue_length(queue) == 4);
  assert(queue_front(queue) == 5);
  assert(queue_back(queue) == 3);
  queue_print(queue);
  
  queue_pop_back(queue);
  assert(queue_length(queue) == 3);
  assert(queue_front(queue) == 5);
  assert(queue_back(queue) == 1);
  queue_print(queue);

  queue_pop_back(queue);
  assert(queue_length(queue) == 2);
  assert(queue_front(queue) == 5);
  assert(queue_back(queue) == 2);
  queue_print(queue);

  queue_pop_front(queue);
  assert(queue_length(queue) == 1);
  assert(queue_front(queue) == 2);
  assert(queue_back(queue) == 2);
  queue_print(queue);

  queue_pop_front(queue);
  assert(queue_length(queue) == 0);
  queue_print(queue);

  /* Moderate stress test: add a few thousand elements and make sure
     the queue holds together. The array implementation will be
     noticeably slow here, but should work. The list implementation
     should be much faster. */

  printf("30k stress test...\n");

  for (i = 0; i < 30000; i++) {
    queue_push_front(queue, i);
    assert(queue_front(queue) == i);
    assert(queue_back(queue) == 0);
  }
  assert(queue_length(queue) == 30000);

  /* Test queue_clear(). */

  queue_clear(queue);
  assert(queue_length(queue) == 0);

  /* Severe stress test: add 1 million elements. The array
     implementation will crash here, but the list implementation
     should work, if slowly. */

  printf("1M stress test...\n");

  for (i = 0; i < 1000000; i++) {
    queue_push_back(queue, i);
    assert(queue_front(queue) == 0);
    assert(queue_back(queue) == i);
  }
  assert(queue_length(queue) == 1000000);

  /* Free the queue. */
  queue_free(queue);

  return 0;
}
