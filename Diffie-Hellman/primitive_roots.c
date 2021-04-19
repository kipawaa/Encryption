#include<stdio.h>
#include<stdlib.h>
#include<order.h>
#include<coprime.h>

int primitive_root(int a, int n) {
        return order(a, n) == phi(n);
}
