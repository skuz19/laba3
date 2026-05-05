#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

void table() {
    cout << "|   x   |    y    |" << endl;
    cout << "-------------------" << endl;
}

void printTable(float x, float y) {
    cout << "|" << setw(6) << fixed << setprecision(1) << x << " |"
         << setw(8) << fixed << setprecision(2) << y << " |" << endl;
}

void printEnd() {
    cout << "-------------------" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");

    float x, y;

    cout << "Таблица значений функции:\n";
    printEnd();
    table();

    // 1. Прямая: [-9; -3]
    for (x = -9; x <= -3; x++) {
        y = 0.5 * x + 1.5;
        printTable(x, y);
    }

    // 2. Экспонента: [-3; 1]
    for (; x <= 1; x++) {
        y = pow(3, x);
        printTable(x, y);
    }

    // 3. Полуокружность: [1; 5]
    for (; x <= 5; x++) {
        y = 3 - sqrt(4 - pow(x - 3, 2));
        printTable(x, y);
    }

    // 4. Прямая: [5; 8]
    for (; x <= 8; x++) {
        y = -x + 8;
        printTable(x, y);
    }

    printEnd();

    return 0;
}
