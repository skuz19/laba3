#include <iostream>
#include <string>
#include <cstdint>

using namespace std;

struct Fraction {
    uint64_t numerator;
    uint64_t denominator;
};

// НОД
uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

// сокращение дроби
Fraction reduce(Fraction f) {
    uint64_t g = gcd(f.numerator, f.denominator);

    f.numerator /= g;
    f.denominator /= g;

    return f;
}

// сложение дробей
Fraction add(Fraction a, Fraction b) {
    Fraction result;

    result.numerator =
        a.numerator * b.denominator +
        b.numerator * a.denominator;

    result.denominator =
        a.denominator * b.denominator;

    return reduce(result);
}

// умножение дроби на целое число
Fraction multiply(Fraction f, uint64_t value) {
    f.numerator *= value;
    return reduce(f);
}

// деление дроби на целое число
Fraction divide(Fraction f, uint64_t value) {
    f.denominator *= value;
    return reduce(f);
}

// биномиальный коэффициент C(n, k)
uint64_t combination(int n, int k) {
    uint64_t result = 1;

    for (int i = 1; i <= k; i++) {
        result = result * (n - i + 1) / i;
    }

    return result;
}

// вычисление суммы ряда
string calculateSum(int a, int b) {
    if (b == 1) {
        return "infinity";
    }

    Fraction sums[11];

    // сумма ряда 1 / b^n
    sums[0] = reduce({1, static_cast<uint64_t>(b - 1)});

    // вычисление сумм для степеней от 1 до a
    for (int k = 1; k <= a; k++) {
        Fraction current = {1, 1};

        for (int j = 0; j < k; j++) {
            Fraction term = multiply(sums[j], combination(k, j));
            current = add(current, term);
        }

        sums[k] = divide(current, b - 1);
    }

    Fraction answer = reduce(sums[a]);

    return to_string(answer.numerator) + "/" + to_string(answer.denominator);
}

int main() {
    int a, b;

    cout << "Введите a и b: ";
    cin >> a >> b;

    if (cin.fail()) {
        return 0;
    }

    if (a < 1 || a > 10 || b < 1 || b > 10) {
        return 0;
    }

    cout << "Результат: " << calculateSum(a, b) << endl;

    return 0;
}
