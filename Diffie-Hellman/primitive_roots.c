#include"primitive_roots.h"

int is_primitive_root(int a, int n) {
        return order(a, n) == phi(n);
}
