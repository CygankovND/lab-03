#include "histogram.h"
#include <cassert>
#include <vector>

void test_positive() {
    double min = 0;
    double max = 0;
    find_minmax({ 1, 2, 3 }, min, max);
    assert(min == 1);
    assert(max == 3);
}

void test_negative() {
    double min = 0;
    double max = 0;
    find_minmax({ -1, -2, -3 }, min, max);
    assert(min == -3);
    assert(max == -1);
}

void test_same() {
    double min = 0;
    double max = 0;
    find_minmax({ 5, 5, 5 }, min, max);
    assert(min == 5);
    assert(max == 5);
}

void test_single() {
    double min = 0;
    double max = 0;
    find_minmax({ 7 }, min, max);
    assert(min == 7);
    assert(max == 7);
}

void test_empty() {
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    // ќжидаем, что значени€ min и max не измен€тс€
    assert(min == 0);
    assert(max == 0);
}

void test_large_with_duplicates() {
    double min = 0;
    double max = 0;
    find_minmax({ 1, 2, 2, 3, 4, 5, 5, 5, 6, 6, 7, 8, 8, 9, 10, 10, 11, 12, 13, 14 }, min, max);
    assert(min == 1);
    assert(max == 14);
}

int main() {
    test_positive();
    test_negative();
    test_same();
    test_single();
    test_empty();
    test_large_with_duplicates();

    return 0;
}
