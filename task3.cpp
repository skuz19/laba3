#include <iostream>
#include <cmath>
#include <string>

using namespace std;

// функция для нахождения НОД
uint gcd(uint a, uint b) {
    while (b != 0) {
        uint temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// вычисление суммы ряда
string calculateSum(uint a, uint b) {

    // проверка сходимости ряда
    if (b <= 1) {
        return "infinity";
    }

    uint numerator = 0;
    uint denominator = 1;

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

        // для остальных случаев используем численное вычисление
        default: {

            double sum = 0.0;

            for (uint n = 1; n <= 100000; n++) {
                sum += pow(n, a) / pow(b, n);
            }

            const uint PRECISION = 1000000;

            numerator = round(sum * PRECISION);
            denominator = PRECISION;

            break;
        }
    }

    // сокращение дроби
    uint g = gcd(numerator, denominator);

    numerator /= g;
    denominator /= g;

    // формирование результата
    return to_string(numerator) + "/" + to_string(denominator);
}

int main() {

    uint a, b;

    cout << "Введите a и b: ";
    cin >> a >> b;

    // проверка диапазона
    if (a < 1 || a > 10 || b < 1 || b > 10) {
        cout << "Ошибка ввода" << endl;
        return 0;
    }

    // вычисление результата
    string result = calculateSum(a, b);

    // вывод результата
    cout << "Результат: " << result << endl;

    return 0;
}
