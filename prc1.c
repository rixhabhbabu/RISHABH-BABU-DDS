#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100

// Define the stack structure
struct Stack {
    int arr[MAX_SIZE];
    int top;
};

// Initialize an empty stack
void initStack(struct Stack* stack) {
    stack->top = -1;
}

// Check if the stack is empty
bool isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Check if the stack is full
bool isFull(struct Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

// Push an element onto the stack
void push(struct Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Stack overflow! Cannot push.\n");
        return;
    }
    stack->arr[++stack->top] = value;
}

// Pop an element from the stack
int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow! Cannot pop.\n");
        return -1; // Return a sentinel value
    }
    return stack->arr[stack->top--];
}

// Peek at the top element without removing it
int peek(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return -1; // Return a sentinel value
    }
    return stack->arr[stack->top];
}

int main() {
    struct Stack myStack;
    initStack(&myStack);

    push(&myStack, 10);
    push(&myStack, 20);
    push(&myStack, 30);

    printf("Top element: %d\n", peek(&myStack));

    printf("Popped element: %d\n", pop(&myStack));
    printf("Popped element: %d\n", pop(&myStack));

    printf("Is stack empty? %s\n", isEmpty(&myStack) ? "Yes" : "No");

    return 0;
}
