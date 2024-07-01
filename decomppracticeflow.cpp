// decomppracticeflow.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "histogram.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Ввод чисел
vector<double> input_numbers(size_t count) {
    vector<double> result(count);
    cout << "Enter the numbers: ";
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}

// Поиск наибольшего и наименьшего значения
void find_minmax(const vector<double>& numbers, double& min, double& max) {
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
vector<size_t> make_histogram(const vector<double>& numbers, size_t bin_count, double& min, double& max) {
    find_minmax(numbers, min, max);

    double bin_size = (max - min) / bin_count;
    vector<size_t> bins(bin_count, 0);

    for (size_t i = 0; i < numbers.size(); ++i) {
        size_t bin_index = (size_t)((numbers[i] - min) / bin_size);
        if (bin_index == bin_count) {
            bin_index--;
        }
        bins[bin_index]++;
    }
    return bins;
}

// Функция для вывода текста в SVG
void svg_text(ofstream& out, double left, double baseline, const string& text) {
    out << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>\n";
}

// Функция для вывода прямоугольника в SVG
void svg_rect(ofstream& out, double x, double y, double width, double height, const string& stroke = "black", const string& fill = "black") {
    out << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height
        << "' stroke='" << stroke << "' fill='" << fill << "' />\n";
}

// Функция для начала SVG
void svg_begin(ofstream& out, double width, double height) {
    out << "<?xml version='1.0' encoding='UTF-8'?>\n";
    out << "<svg width='" << width << "' height='" << height << "' viewBox='0 0 " << width << " " << height
        << "' xmlns='http://www.w3.org/2000/svg'>\n";
}

// Функция для завершения SVG
void svg_end(ofstream& out) {
    out << "</svg>\n";
}

// Генерация случайного цвета
string random_color() {
    string colors[] = { "red", "green", "blue", "orange", "purple", "pink", "yellow" };
    int index = rand() % 7;
    return colors[index];
}

// Отображение гистограммы
void show_histogram_svg(const vector<size_t>& bins, double min, double max, double bin_size) {
    const auto IMAGE_WIDTH = 500;
    const auto IMAGE_HEIGHT = 400;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 60;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const auto BIN_MARGIN = 10;

    ofstream out("histogram.svg");

    svg_begin(out, IMAGE_WIDTH, IMAGE_HEIGHT);

    double top = 0;
    for (size_t i = 0; i < bins.size(); ++i) {
        const double bin_width = BLOCK_WIDTH * bins[i];
        svg_text(out, TEXT_LEFT, top + TEXT_BASELINE, to_string(bins[i]));

        svg_rect(out, TEXT_WIDTH + 100, top, bin_width, BIN_HEIGHT, "black", random_color()); // Смещаем прямоугольники дальше вправо

        double bin_label = min + i * bin_size;
        top += TEXT_BASELINE; // Добавляем отступ для текста границ
        svg_text(out, TEXT_LEFT, top + TEXT_BASELINE, to_string(bin_label).substr(0, 4)); // Граница столбца

        top += BIN_HEIGHT + BIN_MARGIN; // Добавлен отступ между корзинами
    }

    svg_end(out);
    out.close();
}

int main() {
    size_t number_count;
    cout << "Enter number count: ";
    cin >> number_count;

    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cout << "Enter bin count: ";
    cin >> bin_count;

    double min, max;
    const auto bins = make_histogram(numbers, bin_count, min, max);
    double bin_size = (max - min) / bin_count;

    show_histogram_svg(bins, min, max, bin_size);

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
