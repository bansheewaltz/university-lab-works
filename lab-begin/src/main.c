#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#define MIN_N_OF_ELEMENTS 1
#define MAX_N_OF_ELEMENTS 10
#define N_OF_ELEMENTS_LIMITS MIN_N_OF_ELEMENTS, MAX_N_OF_ELEMENTS
#define INT_LIMITS INT_MIN, INT_MAX

bool int_read(long long *n) {
    return scanf("%lld", n);
}
bool int_in_bounds(long long n, int left_bound, int right_bound) {
    return left_bound <= n && n <= right_bound;
}
bool read_number_of_elements(long long *n) {
    return int_read(n) && int_in_bounds(*n, N_OF_ELEMENTS_LIMITS);
}
void print_input_error(void) {
    printf("bad input");
}

int main(void) {
    long long n_elements_expected = 0;

    if (!read_number_of_elements(&n_elements_expected)) {
        print_input_error();
        return 0;
    }

    long long sum = 0;
    long long n_elements_read = 0;
    long long number = 0;

    while (int_read(&number) && int_in_bounds(number, INT_LIMITS)) {
        if (!int_in_bounds(sum + number, INT_LIMITS)) {
            printf("overflow");
            return 0;
        }

        sum += number;
        n_elements_read++;
        if (getchar() == '\n') {
            break;
        }
    }

    if (n_elements_expected != n_elements_read) {
        print_input_error();
        return 0;
    }

    printf("%lld", sum);
    return 0;
}
