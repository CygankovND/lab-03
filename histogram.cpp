#include "histogram.h"

void find_minmax(const std::vector<double>& numbers, double& min, double& max) {
    if (numbers.empty()) {
        return;
    }
    min = numbers[0];
    max = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i) {
        if (numbers[i] < min) {
            min = numbers[i];
        }
        if (numbers[i] > max) {
            max = numbers[i];
        }
    }
}
