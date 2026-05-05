#include <iostream>
#include <cmath>
#include <string>

using namespace std;

// функция для нахождения НОД (алгоритм Евклида)
long gcd(long a, long b) {
    while (b != 0) {
        long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// вычисление суммы ряда
string calculateSum(int a, int b) {

    // проверка сходимости ряда
    // ряд сходится только при b > 1
    if (b <= 1) {
        return "infinity";
    }

    long numerator = 0;     // числитель
    long denominator = 1;   // знаменатель

    // используем формулы для суммы ряда
    // сумма: sum(n^a / b^n)

    switch (a) {

        // a = 1
        case 1:
            numerator = b;
            denominator = (b - 1) * (b - 1);
            break;

        // a = 2
        case 2:
            numerator = b * (b + 1);
            denominator = (b - 1) * (b - 1) * (b - 1);
            break;

        // a = 3
        case 3:
            numerator = b * (b * b + 4 * b + 1);
            denominator = (b - 1) * (b - 1) * (b - 1) * (b - 1);
            break;

        // a = 4
        case 4:
            numerator = b * (b * b * b + 11 * b * b + 11 * b + 1);
            denominator = (b - 1) * (b - 1) * (b - 1) * (b - 1) * (b - 1);
            break;

        default:
            // по условию a от 1 до 10, но формулы даны до 4
            return "не поддерживается";
    }

    // сокращаем дробь
    long g = gcd(numerator, denominator);
    numerator /= g;
    denominator /= g;

    // формируем строку результата
    return to_string(numerator) + "/" + to_string(denominator);
}

int main() {

    int a, b;

    cout << "Введите a и b: ";
    cin >> a >> b;

    // вычисление результата
    string result = calculateSum(a, b);

    // вывод результата
    cout << "Результат: " << result << endl;

    return 0;
}
