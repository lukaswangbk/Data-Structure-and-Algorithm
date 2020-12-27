#ifndef Queue_H_
#define SIMPLE_QUEUE_H_
#include <stdio.h>
#include <stdlib.h>

struct QueueNode {
  int val;
  QueueNode* next;
};

// SimpleQueue
struct SimpleQueue {
  int count;
  QueueNode* begin;
  QueueNode* end;
};

bool is_queue_empty(struct SimpleQueue* queue) {
  return queue->count == 0;
}

int queue_front(struct SimpleQueue* queue) {
  return queue->begin->val;
}

int queue_pop(struct SimpleQueue* queue) {
  int ret;
  struct QueueNode* tmp;
  ret = queue_front(queue);
  tmp = queue->begin;
  queue->begin = queue->begin->next;
  queue->count -= 1;
  free(tmp);
  tmp = NULL;
  return ret;
}

void queue_push(struct SimpleQueue* queue, int val) {
  struct QueueNode* new_node = (struct QueueNode*) malloc(sizeof(struct QueueNode));
  new_node->val = val;
  new_node->next = NULL;
  if (is_queue_empty(queue)) {
    queue->begin = new_node;
    queue->end = new_node;
    queue->count += 1;
  } else {
    queue->end->next = new_node;
    queue->count += 1;
    queue->end = new_node;
  }
}

struct SimpleQueue* create_queue() {
  struct SimpleQueue* queue = (struct SimpleQueue*) malloc(sizeof(struct SimpleQueue));
  queue->begin = NULL;
  queue->end = NULL;
  queue->count = 0;
  return queue;
}

void print_queue(struct SimpleQueue* queue) {
  struct QueueNode* node = queue->begin;
  printf("queue: ");
  while (node) {
    printf("%d ", node->val);
    node = node->next;
  }
  printf("\n");
}
#endif