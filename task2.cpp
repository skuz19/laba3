#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <algorithm>
#include <cmath>

using namespace std;

// генератор случайных чисел
mt19937 gen(random_device{}());

// получение случайного целого числа
int randomInt(int left, int right) {
    uniform_int_distribution<int> dist(left, right);
    return dist(gen);
}

// получение случайного числа из (0;1)
double randomDouble() {
    uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(gen);
}

// вычисление 2^n
int powerOfTwo(int n) {
    int result = 1;

    for (int i = 0; i < n; i++) {
        result *= 2;
    }

    return result;
}

// построение таблицы простых чисел
vector<int> sieveEratosthenes(int limit) {

    vector<bool> isPrime(limit + 1, true);
    vector<int> primes;

    isPrime[0] = false;
    isPrime[1] = false;

    for (int i = 2; i * i <= limit; i++) {
        if (isPrime[i]) {
            for (int j = i * i; j <= limit; j += i) {
                isPrime[j] = false;
            }
        }
    }

    for (int i = 2; i <= limit; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}

// умножение по модулю без переполнения
int multiplyMod(int a, int b, int mod) {

    int result = 0;
    a %= mod;

    while (b > 0) {

        if (b % 2 == 1) {

            if (result >= mod - a)
                result = result - (mod - a);
            else
                result += a;
        }

        b /= 2;

        if (a >= mod - a)
            a = a - (mod - a);
        else
            a += a;
    }

    return result;
}

// быстрое возведение в степень по модулю
int powerMod(int base, int degree, int mod) {

    int result = 1;
    base %= mod;

    while (degree > 0) {

        if (degree % 2 == 1)
            result = multiplyMod(result, base, mod);

        base = multiplyMod(base, base, mod);
        degree /= 2;
    }

    return result;
}

// проверка условий теоремы Диемитко
bool gostTest(int p, int q) {

    int n = (p - 1) / q;

    return
        powerMod(2, p - 1, p) == 1 &&
        powerMod(2, n, p) != 1;
}

// генерация кандидата в простые по ГОСТ
int generateGostPrime(
        const vector<int>& primes,
        int bits,
        int& rejected) {

    int lowerBound = powerOfTwo(bits - 1);
    int upperBound = powerOfTwo(bits);

    // выбор подходящих q
    vector<int> suitableQ;

    for (int q : primes) {

        if (
            q >= powerOfTwo((bits + 1) / 2 - 1) &&
            q < powerOfTwo((bits + 1) / 2)
        ) {
            suitableQ.push_back(q);
        }
    }

    // поиск числа p
    while (true) {

        if (suitableQ.empty())
            suitableQ = primes;

        int q =
            suitableQ[
                randomInt(
                    0,
                    suitableQ.size() - 1
                )
            ];

        double xi = randomDouble();

        // вычисление N
        int n =
            floor(
                (double)lowerBound / q
            ) +
            floor(
                (double)lowerBound * xi / q
            );

        if (n % 2 != 0)
            n++;

        // перебор параметра u
        for (int u = 0;; u += 2) {

            int p =
                (n + u) * q + 1;

            if (p >= upperBound) {
                rejected++;
                break;
            }

            if (p <= lowerBound) {
                rejected++;
                continue;
            }

            // проверка простоты
            if (gostTest(p, q))
                return p;

            rejected++;
        }
    }
}

// проверка повторов
bool containsNumber(
        const vector<int>& numbers,
        int value) {

    return
        find(
            numbers.begin(),
            numbers.end(),
            value
        )
        != numbers.end();
}

// вывод таблицы результатов
void printTable(
        const vector<int>& numbers,
        const vector<int>& rejected) {

    cout << "\nТаблица результатов\n";

    cout
    << "+---+---------------+-------------------+----------------------+\n";

    cout
    << "| № | Простое число | Результат проверки | rejected             |\n";

    cout
    << "+---+---------------+-------------------+----------------------+\n";

    for (int i = 0; i < numbers.size(); i++) {

        cout
        << "| "
        << i + 1
        << " | "
        << setw(13)
        << numbers[i]

        << " | true"

        << " | "
        << setw(20)
        << rejected[i]

        << " |\n";
    }

    cout
    << "+---+---------------+-------------------+----------------------+\n";
}

// основная программа
int main() {

    int bits;

    cout
    << "Введите bits: ";

    cin >> bits;

    // построение таблицы простых
    vector<int> primes =
        sieveEratosthenes(500);

    vector<int> resultNumbers;
    vector<int> rejectedValues;

    // получение 10 различных чисел
    while (
        resultNumbers.size()
        < 10
    ) {

        int rejected = 0;

        int p =
            generateGostPrime(
                primes,
                bits,
                rejected
            );

        if (
            containsNumber(
                resultNumbers,
                p
            )
        )
            continue;

        resultNumbers.push_back(p);
        rejectedValues.push_back(rejected);
    }

    // вывод результата
    printTable(
        resultNumbers,
        rejectedValues
    );

    return 0;
}
