// ВНИМАНИЕ! Для решения данной задачи нужно использовать структуру данных стек!

// Дана последовательность, состоящая из символов '(' и ')'. Требуется определить, является \
ли данная последовательность правильной скобочной последовательностью. Длина исходной \
последовательности ≤ 800000.

#include <iostream>

#define OK 0

struct node_t {
    char value;
    struct node_t *next;
};

typedef struct {
    struct node_t *pointerStack;
    int length;
} stack_node_t;

void push(stack_node_t *stack, char element) {
    if (element == 0)
        return;
    node_t *newNode = (node_t *)malloc(sizeof(node_t));
    if (newNode) {
        newNode->value = element;
        newNode->next = stack->pointerStack;
        stack->pointerStack = newNode;
        stack->length += 1;
    }
}

char pop(stack_node_t *stack) {
    char element;
    if (stack->pointerStack != NULL) {
        element = stack->pointerStack->value;
        node_t *t = stack->pointerStack;
        stack->pointerStack = t->next;
        free(t);
        stack->length -= 1;
    }
    else {
        element = 0;
    }
    return element;
}

static void freeNode(struct node_t **node)
{
    (*node)->next = NULL;
    (*node)->value = 0;
    free(*node);
    *node = NULL;
}


void freeStack(stack_node_t *stack) {
    stack->length = 0;
    struct node_t *tmp = stack->pointerStack;
    while (tmp != NULL)
    {
        tmp = stack->pointerStack->next;
        freeNode(&(stack->pointerStack));
        stack->pointerStack = tmp;
    }
}

int main() {
    char ch = 1;
    char previous = 1;
    stack_node_t stack = { NULL, 0 };
    while (ch != 0 && ch != '\n' && ch != EOF) {
        scanf("%c", &ch);
        if (ch == ')') {
            previous = pop(&stack);
            if (previous != '(') {
                push(&stack, previous);
                push(&stack, ch);
            }
        }
        else if (ch == '(') {
            push(&stack, ch);
        }
    }
    if (stack.length == 0) {
        std::cout << "YES\n";
    }
    else {
        std::cout << "NO\n";
    }
    freeStack(&stack);
    return OK;
}
