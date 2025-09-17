#include <cstdio>
#include <example/span.h>


int sum(example::span<int> values) {
    int total = 0;
    for (auto elem : values) {
        total += elem;
    }
    return total;
}

int main() {
    int values[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    printf("total = %d\n", sum(values));
}
