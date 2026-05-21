#include <iostream>
#include <cmath>
#include <string>
#include <cstdint>  // для uint32_t

using namespace std;

// функция для нахождения НОД
uint32_t gcd(uint32_t a, uint32_t b) {
    while (b != 0) {
        uint32_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// вычисление суммы ряда
string calculateSum(uint32_t a, uint32_t b) {

    // проверка сходимости ряда
    if (b <= 1) {
        return "infinity";
    }

    uint32_t numerator = 0;
    uint32_t denominator = 1;

    // формулы суммы ряда
    switch (a) {

        case 1:
            numerator = b;
            denominator = (b - 1) * (b - 1);
            break;

        case 2:
            numerator = b * (b + 1);
            denominator = pow(b - 1, 3);
            break;

        case 3:
            numerator = b * (b * b + 4 * b + 1);
            denominator = pow(b - 1, 4);
            break;

        case 4:
            numerator = b * (b * b * b + 11 * b * b + 11 * b + 1);
            denominator = pow(b - 1, 5);
            break;

        // остальные случаи a = 5..10
        default: {

            double sum = 0.0;

            for (uint32_t n = 1; n <= 100000; n++) {
                sum += pow(n, a) / pow(b, n);
            }

            const uint32_t PRECISION = 1000000;

            numerator = round(sum * PRECISION);
            denominator = PRECISION;

            break;
        }
    }

    // защита от деления на ноль
    if (denominator == 0) {
        return "error";
    }

    // сокращение дроби
    uint32_t g = gcd(numerator, denominator);

    numerator /= g;
    denominator /= g;

    // формирование результата
    return to_string(numerator) + "/" + to_string(denominator);
}

int main() {

    int a, b;

    cout << "Введите a и b: ";
    cin >> a >> b;

    // проверка корректности ввода
    if (cin.fail()) {
        return 0;
    }

    // проверка диапазона
    if (a < 1 || a > 10 || b < 1 || b > 10) {
        return 0;
    }

    // вычисление результата
    string result = calculateSum((uint32_t)a, (uint32_t)b);

    // вывод результата
    cout << "Результат: " << result << endl;

    return 0;
}
