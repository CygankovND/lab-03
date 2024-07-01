// decomppracticeflow.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <vector>

// Ввод чисел
std::vector<double> input_numbers(size_t count) {
    std::vector<double> result(count);
    std::cerr << "Enter the numbers: ";
    for (size_t i = 0; i < count; i++) {
        std::cin >> result[i];
    }
    return result;
}

// Поиск наибольшего и наименьшего значения
void find_minmax(const std::vector<double>& numbers, double& min, double& max) {
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

// Расчет гистограммы
std::vector<size_t> make_histogram(const std::vector<double>& numbers, size_t bin_count) {
    double min, max;
    find_minmax(numbers, min, max);

    double bin_size = (max - min) / bin_count;
    std::vector<size_t> bins(bin_count, 0);

    for (size_t i = 0; i < numbers.size(); ++i) {
        size_t bin_index = std::min(static_cast<size_t>((numbers[i] - min) / bin_size), bin_count - 1);
        bins[bin_index]++;
    }
    return bins;
}

// Отображение гистограммы
void show_histogram_text(const std::vector<size_t>& bins, double min, double max) {
    const size_t SCREEN_WIDTH = 80;
    const size_t LABEL_WIDTH = 3;
    const size_t AXIS_WIDTH = 1;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - LABEL_WIDTH - AXIS_WIDTH;

    size_t max_bin_count = bins[0];
    for (size_t i = 1; i < bins.size(); ++i) {
        if (bins[i] > max_bin_count) {
            max_bin_count = bins[i];
        }
    }

    double scaling_factor = (max_bin_count > MAX_ASTERISK) ? static_cast<double>(MAX_ASTERISK) / max_bin_count : 1.0;
    double bin_size = (max - min) / bins.size();

    for (size_t i = 0; i < bins.size(); ++i) {
        std::cout << (bins[i] < 10 ? "  " : (bins[i] < 100 ? " " : "")) << bins[i] << "|";
        size_t stars = static_cast<size_t>(bins[i] * scaling_factor);
        for (size_t j = 0; j < stars; ++j) {
            std::cout << "*";
        }
        std::cout << std::endl;

        double lo = min + i * bin_size;
        std::cout << " " << lo << std::endl;
    }
    double hi = min + bins.size() * bin_size;
    std::cout << " " << hi << std::endl;
}

int main() {
    size_t number_count;
    std::cerr << "Enter number count: ";
    std::cin >> number_count;

    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    std::cerr << "Enter bin count: ";
    std::cin >> bin_count;

    const auto bins = make_histogram(numbers, bin_count);

    double min, max;
    find_minmax(numbers, min, max);

    show_histogram_text(bins, min, max);

    return 0;
}



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
