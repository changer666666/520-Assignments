#include "solutions.h"
#include <stdio.h>

static int sum = 0;

int running_total(int x) {
    sum += x;
    return sum;
}

void reverse_in_place(int arr[], int len) {
    int temp = 0;
    for (int i  = 0; i < len / 2; i++) {
        temp = arr[i];
        arr[i] = arr[len - i - 1];
        arr[len - i - 1] = temp;
    }

    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
}

int * reverse(int arr[], int len) {
    int * f = (int *) calloc(len, sizeof(int));
    for (int i = len - 1; i >= 0; i--) {
        f[len - i - 1] = arr[i];
    }
    return f;
}

int num_instances(int arr[], int len, int num) {
    int count = 0;
    for (int i = 0; i < len; i++) {
        if (arr[i] == num) {
            count++;
        }
    }
    return count;
}

Point * map(Point arr[], int len, Point(*f)(Point)) {
    Point * a = (Point *) calloc(len, sizeof(Point));
    for (int i = 0; i < len; i++) {
        a[i] = (*f)(arr[i]);
    }
    return a;
}