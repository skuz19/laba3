package main

import (
	"fmt"
)

// функция определения победителя
func determineWinner(n int, m int, a []int) int {

	pavelScore := 0
	vikaScore := 0

	pavelLast := -1
	vikaLast := -1

	pavelTurn := true

	// пока есть числа
	for len(a) > 0 {

		bestK := -1
		bestSum := -1000000000

		currentSum := 0

		// перебираем сколько элементов взять
		for k := 1; k <= m && k <= len(a); k++ {

			currentSum += a[k-1]

			// проверка ограничения варианта 1
			if pavelTurn && k == pavelLast {
				continue
			}
			if !pavelTurn && k == vikaLast {
				continue
			}

			// выбираем максимум, при равенстве — минимальный k
			if currentSum > bestSum {
				bestSum = currentSum
				bestK = k
			}
		}

		// начисление очков
		if pavelTurn {
			pavelScore += bestSum
			pavelLast = bestK
		} else {
			vikaScore += bestSum
			vikaLast = bestK
		}

		// удаляем выбранные элементы
		a = a[bestK:]

		// смена хода
		pavelTurn = !pavelTurn
	}

	// определяем победителя
	if pavelScore > vikaScore {
		return 1
	}
	return 0
}

func main() {

	var n, m int

	fmt.Print("Введите n и m: ")
	fmt.Scan(&n, &m)

	numbers := make([]int, n)

	fmt.Print("Введите числа: ")
	for i := 0; i < n; i++ {
		fmt.Scan(&numbers[i])
	}

	result := determineWinner(n, m, numbers)

	fmt.Println("Результат:", result)
}
