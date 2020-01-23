#include <stdio.h>
#include <math.h>

#include "rpn.h"

#define INITIAL_STACK_SIZE 100

static double * stack;
static int initialized = 0;
static int top = 0;
static RPN_ERROR error = OK;
static int stackSize = 0;

void rpn_show() {
    printf("--->\n");
    for ( int i=0; i<top; i++ ) {
        printf("  %lf\n", stack[i]);
    }
    printf("<---\n");
}

void rpn_init() {
  if ( ! initialized ) {
      stackSize = INITIAL_STACK_SIZE;
      stack = (double *) calloc(stackSize, sizeof(double));
      initialized = 1;
      top = 0;
      error = OK;
      printf("%u\n",stack);
  }
}

void rpn_push(double x) {
    if ( !initialized ) {
        error = NOT_INITIALIZED_ERROR;
    } else if (top < stackSize) {
        stack[top] = x;
        top++;
    } else {
        stackSize *= 2;
        stack = (double *) realloc(stack, stackSize * sizeof(double));
        printf("%u\n",stack);
    }
}

void rpn_add() {  
    if ( !initialized ) {
        error = NOT_INITIALIZED_ERROR;
    } else if ( top < 2 ) {
        error = BINARY_ERROR;
    } else {    
        double x = stack[top-1]+stack[top-2];
        if ( x == INFINITY ) {
            error = OVERFLOW_ERROR;
        } 
        top--;
        stack[top-1] = x;
    }
}

void rpn_negate() {
    if ( !initialized ) {
        error = NOT_INITIALIZED_ERROR;
    } else if ( top < 1 ) {
        error = UNARY_ERROR;
    } else {    
      stack[top-1] = -stack[top-1];
    }
}

void rpn_multiply() {
    if ( !initialized ) {
        error = NOT_INITIALIZED_ERROR;
    } else if ( top < 2 ) {
        error = BINARY_ERROR;
    } else {    
        double x = stack[top-1]*stack[top-2];
        if ( x == INFINITY || x == -INFINITY ) {
            error = OVERFLOW_ERROR;
        } 
        top--;
        stack[top-1] = x;
    }
}

double rpn_pop() { 
    if ( !initialized ) {
        error = NOT_INITIALIZED_ERROR;
        return 0;
    } else if ( top == 0 ) {
        error = POP_ERROR;
        return 0;        
    } else {
        double result = stack[top-1];
        top--;
        return result;
    }
 }

RPN_ERROR rpn_error() { return error; }

void rpn_free() {
    if ( initialized ) {
        free(stack);
        initialized = 0;
    }
    error = OK;
}

void rpn_div() {
    if ( !initialized ) {
        error = NOT_INITIALIZED_ERROR;
    } else if ( top < 2 ) {
        error = BINARY_ERROR;
    } else if (stack[top-1] == 0) {
        error = DIVIDE_BY_ZERO_ERROR;
    } else {    
        double x = stack[top-2] / stack[top-1];
        if ( x == INFINITY || x == -INFINITY ) {
            error = OVERFLOW_ERROR;
        } 
        top--;
        stack[top-1] = x;
    }
}

int getStackSize() {
    return stackSize;
}