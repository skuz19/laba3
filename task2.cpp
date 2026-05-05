#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <iomanip>
#include <algorithm>

using namespace std;

// генератор случайных чисел
mt19937 gen(random_device{}());

// случайное целое число
int getRandomInt(int a, int b) {
    return uniform_int_distribution<int>(a, b)(gen);
}

// случайное вещественное число
double getRandomDouble(double a, double b) {
    return uniform_real_distribution<double>(a, b)(gen);
}

// решето Эратосфена (получаем список простых чисел)
vector<int> sieve(int n) {
    vector<bool> prime(n + 1, true);
    prime[0] = prime[1] = false;

    for (int i = 2; i * i <= n; i++) {
        if (prime[i]) {
            for (int j = i * i; j <= n; j += i)
                prime[j] = false;
        }
    }

    vector<int> res;
    for (int i = 2; i <= n; i++)
        if (prime[i]) res.push_back(i);

    return res;
}

// быстрое возведение в степень по модулю
long long mod_pow(long long a, long long b, long long mod) {
    long long res = 1;
    a %= mod;

    while (b > 0) {
        if (b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

// тест Миллера-Рабина (для дополнительной проверки простоты)
bool millerRabinTest(int n, int k = 5) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;

    int d = n - 1, s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    for (int i = 0; i < k; i++) {
        int a = rand() % (n - 3) + 2;
        long long x = mod_pow(a, d, n);

        if (x == 1 || x == n - 1) continue;

        bool composite = true;
        for (int r = 1; r < s; r++) {
            x = mod_pow(x, 2, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

// генерация простого числа по ГОСТ
int generate_gost_prime(const vector<int>& primes, int t) {

    // выбираем случайное простое число q
    int maxIndex = 0;
    while (maxIndex < primes.size() && primes[maxIndex] < (1 << (t / 2)))
        maxIndex++;

    int q = primes[getRandomInt(0, maxIndex - 1)];

    while (true) {

        // случайное число из (0,1)
        double xi = getRandomDouble(0, 1);

        // вычисляем N по формуле ГОСТ
        double A = floor(pow(2, t - 1) / q);
        double B = floor((pow(2, t - 1) * xi) / q);

        int N = (int)(A + B);

        // делаем N четным
        if (N % 2 != 0) N++;

        int u = 0;

        // перебор значений u
        while (true) {
            int p = (N + u) * q + 1;

            // проверка выхода за диапазон
            if (p > (1 << t)) break;

            // условия теоремы Диемитко
            if (mod_pow(2, p - 1, p) == 1 &&
                mod_pow(2, N + u, p) != 1) {
                return p;
            }

            u += 2;
        }
    }
}

// вывод таблицы результатов
void print_table(const vector<pair<int,int>>& data) {
    cout << "\nРезультаты:\n";
    cout << "+-----+------------+-----------+\n";
    cout << "|  №  |   Число    | отклонено |\n";
    cout << "+-----+------------+-----------+\n";

    for (int i = 0; i < data.size(); i++) {
        cout << "| " << setw(3) << i+1
             << " | " << setw(10) << data[i].first
             << " | " << setw(9) << data[i].second
             << " |\n";
    }

    cout << "+-----+------------+-----------+\n";
}

// автоматическая проверка результатов
void full_check(const vector<pair<int,int>>& results, int bits) {

    cout << "\nПроверка результатов\n";

    bool ok = true;

    // проверка количества
    if (results.size() == 10)
        cout << "Количество чисел корректно\n";
    else {
        cout << "Ошибка количества чисел\n";
        ok = false;
    }

    // проверка каждого числа
    for (auto [p, rejected] : results) {

        // проверка диапазона
        if (!(p > (1 << (bits - 1)) && p < (1 << bits))) {
            cout << "Число вне диапазона: " << p << endl;
            ok = false;
        }

        // проверка первого условия
        if (mod_pow(2, p - 1, p) != 1) {
            cout << "Не выполнено первое условие для: " << p << endl;
            ok = false;
        }

        // дополнительная проверка простоты
        if (!millerRabinTest(p)) {
            cout << "Число не является простым: " << p << endl;
            ok = false;
        }
    }

    if (ok)
        cout << "Все проверки пройдены успешно\n";
    else
        cout << "Обнаружены ошибки\n";
}

int main() {

    int bits;
    cout << "Введите разрядность (bits): ";
    cin >> bits;

    // получаем список простых чисел
    vector<int> primes = sieve(500);

    vector<pair<int,int>> results;
    int rejected = 0;

    // генерируем 10 чисел
    while (results.size() < 10) {

        int p = generate_gost_prime(primes, bits);

        // проверка на повтор
        bool duplicate = any_of(results.begin(), results.end(),
            [p](const pair<int,int>& v){ return v.first == p; });

        if (duplicate) continue;

        results.push_back({p, rejected});
        rejected = 0;
    }

    print_table(results);

    // проверка корректности
    full_check(results, bits);

    return 0;
}
