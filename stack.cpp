#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

struct Stack{
    int size;
    size_t capacity;
    int* data;

};

void Resize(Stack* stack, bool size_bigger_smaller) {
    /// if size_bigger_smaller is TRUE then we are increasing the size
    /// if size_bigger_smaller is FALSE then we decrease the size
    if (size_bigger_smaller) {
        realloc(stack -> data, (stack -> capacity) * 2);
        stack -> capacity = stack -> capacity * 2;
    } else {
        realloc(stack -> data, (stack -> capacity) / 2);
        stack -> capacity = stack -> capacity / 2;
    }


}

void StackConstructor(Stack* stack, int capacity) {

    assert((capacity > 0) && "The capacity of the stack should be positive");
    stack->capacity = capacity;
    stack->data = (int* )calloc(capacity, sizeof(int));

    printf("the pointer alloc: %p\n", stack->data);

    stack->size = 0;

}

void StackDestractor(Stack* stack) {

    assert((stack->data != NULL) && "This object has already been destroyed");

    memset(stack->data, 0XF0, stack->capacity);

    free(stack->data);
    stack->data = NULL;
    stack->size = -1;

    stack->capacity = -1;

}

void StackPush (Stack* stack, int data) {

    if (stack->size == stack->capacity) {
        Resize(stack, true);
    }

    stack->size += 1;
    stack->data[(stack->size) - 1] = data;

}

int StackPop(Stack *stack) {
    if (stack->size == 0) {
        puts("The stack is empty\n");
        return -20000000;
    }

    if (stack->size < stack->capacity/4) {
        Resize(stack, false);
    }

    int temporary = 0;
    temporary = stack->data[stack->size - 1];

    stack->data[stack->size - 1] = 0;
    stack->size--;

    return temporary;

}

int main() {

    Stack st;
    StackConstructor(&st, -1);

    StackPush(&st, 3);

    int popped = StackPop(&st);

    printf("popped: %d\n", popped);

    StackDestractor(&st);

    StackDestractor(&st);

    return 0;
}