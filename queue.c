#include <stdio.h>
#include <string.h>
#define MAX_SIZE 100

struct Queue {
    char data[MAX_SIZE][100]; // Array to store strings
    int front;
    int rear;
};

void enqueue(struct Queue *queue, const char *value) {
    if (queue->rear < MAX_SIZE - 1) {
        queue->rear++;
        strcpy(queue->data[queue->rear], value);
    } else {
        printf("Queue is full!\n");
    }
}

void dequeue(struct Queue *queue) {
    if (queue->front <= queue->rear) {
        printf("Dequeued: %s\n", queue->data[queue->front]);
        queue->front++;
    } else {
        printf("Queue is empty!\n");
    }
}

int main() {
    struct Queue queue;
    queue.front = 0;
    queue.rear = -1;

    enqueue(&queue, "Hello");
    enqueue(&queue, "World");
    enqueue(&queue, "Queue");
    enqueue(&queue, "Example");

    dequeue(&queue); // Output: Dequeued: Hello
    dequeue(&queue); // Output: Dequeued: World

    return 0;
}
