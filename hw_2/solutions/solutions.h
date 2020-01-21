#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include <stdlib.h>

 typedef struct {
   double x, y, z;
 } Point;

int running_total(int x);

void reverse_in_place(int arr[], int len);

int * reverse(int arr[], int len);

int num_instances(int arr[], int len, int num);

Point * map(Point arr[], int len, Point(*f)(Point));

#endif