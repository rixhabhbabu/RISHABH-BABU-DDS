#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<string.h>
// Define the stack structure
typedef struct {
    char *array;
    int top;
    unsigned capacity;
} Stack;

// Function to create a stack of given capacity
Stack* createStack(unsigned capacity) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char *)malloc(stack->capacity * sizeof(char));
    return stack;
}

// Stack utility functions
int isEmpty(Stack *stack) {
    return stack->top == -1;
}

char peek(Stack *stack) {
    return stack->array[stack->top];
}

char pop(Stack *stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return '$'; // $ denotes empty stack
}

void push(Stack *stack, char op) {
    stack->array[++stack->top] = op;
}

// Function to check if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

// Function to get precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// Function to convert infix expression to postfix expression
void infixToPostfix(char *exp) {
    Stack *stack = createStack(strlen(exp));
    int i, k;

    for (i = 0, k = -1; exp[i]; ++i) {
        // If the scanned character is an operand, add it to output
        if (isalnum(exp[i]))
            exp[++k] = exp[i];

        // If the scanned character is an '(', push it to the stack
        else if (exp[i] == '(')
            push(stack, exp[i]);

        // If the scanned character is an ')', pop and output from the stack
        // until an '(' is encountered
        else if (exp[i] == ')') {
            while (!isEmpty(stack) && peek(stack) != '(')
                exp[++k] = pop(stack);
            if (!isEmpty(stack) && peek(stack) != '(')
                return; // invalid expression
            else
                pop(stack);
        } else { // an operator is encountered
            while (!isEmpty(stack) && precedence(exp[i]) <= precedence(peek(stack)))
                exp[++k] = pop(stack);
            push(stack, exp[i]);
        }
    }

    // pop all the operators from the stack
    while (!isEmpty(stack))
        exp[++k] = pop(stack);

    exp[++k] = '\0';
    printf("Postfix expression: %s\n", exp);
}

// Main function to test above functions
int main() {
    char exp[100];
    printf("Enter infix expression: ");
    fgets(exp, 100, stdin);

    infixToPostfix(exp);

    return 0;
}
