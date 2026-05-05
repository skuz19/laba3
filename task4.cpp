#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int determineWinner(int n, int m, vector<int> a) {

    int pavel_score = 0;
    int vika_score = 0;

    int pavel_last = -1;
    int vika_last = -1;

    bool pavel_turn = true;

    while (!a.empty()) {

        int best_k = -1;
        int best_sum = -1e9;

        int current_sum = 0;

        for (int k = 1; k <= m && k <= a.size(); k++) {

            current_sum += a[k - 1];

            // проверка ограничения
            if (pavel_turn && k == pavel_last) continue;
            if (!pavel_turn && k == vika_last) continue;

            // выбираем максимум, при равенстве — минимальный k
            if (current_sum > best_sum) {
                best_sum = current_sum;
                best_k = k;
            }
        }

        // начисляем очки
        if (pavel_turn) {
            pavel_score += best_sum;
            pavel_last = best_k;
        } else {
            vika_score += best_sum;
            vika_last = best_k;
        }

        // удаляем элементы
        a.erase(a.begin(), a.begin() + best_k);

        // смена хода
        pavel_turn = !pavel_turn;
    }

    return pavel_score > vika_score ? 1 : 0;
}

int main() {

    int n, m;
    cout << "Введите n и m: ";
    cin >> n >> m;

    vector<int> numbers(n);

    cout << "Введите числа: ";
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }

    int result = determineWinner(n, m, numbers);

    cout << "Результат: " << result << endl;

    return 0;
}
