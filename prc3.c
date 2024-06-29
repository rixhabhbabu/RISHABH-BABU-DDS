#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Define the stack structure
typedef struct {
    int *array;
    int top;
    unsigned capacity;
} Stack;

// Function to create a stack of given capacity
Stack* createStack(unsigned capacity) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int *)malloc(stack->capacity * sizeof(int));
    return stack;
}

// Stack utility functions
int isEmpty(Stack *stack) {
    return stack->top == -1;
}

int peek(Stack *stack) {
    return stack->array[stack->top];
}

int pop(Stack *stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return -1; // Stack underflow
}

void push(Stack *stack, int op) {
    stack->array[++stack->top] = op;
}

// Function to evaluate postfix expression
int evaluatePostfix(char *exp) {
    Stack *stack = createStack(strlen(exp));
    int i;

    for (i = 0; exp[i]; ++i) {
        // If the character is a digit, push it to the stack
        if (isdigit(exp[i]))
            push(stack, exp[i] - '0');

        // If the character is an operator, pop two operands from stack,
        // perform the operation, and push the result back
        else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') {
            int val1 = pop(stack);
            int val2 = pop(stack);
            switch (exp[i]) {
                case '+': push(stack, val2 + val1); break;
                case '-': push(stack, val2 - val1); break;
                case '*': push(stack, val2 * val1); break;
                case '/': push(stack, val2 / val1); break;
            }
        }
    }
    // The final result is at the top of the stack
    int result = pop(stack);
    free(stack->array);
    free(stack);
    return result;
}

// Main function to test above functions
int main() {
    char exp[100];
    printf("Enter postfix expression: ");
    fgets(exp, 100, stdin);

    // Remove newline character if present
    if (exp[strlen(exp) - 1] == '\n')
        exp[strlen(exp) - 1] = '\0';

    int result = evaluatePostfix(exp);
    printf("Result: %d\n", result);

    return 0;
}
