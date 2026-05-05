package main

import (
	"fmt"
	"math"
)

// вывод шапки таблицы
func table() {
	fmt.Println("|   x   |    y    |")
	fmt.Println("-------------------")
}

// вывод строки таблицы
func printTable(x float64, y float64) {
	fmt.Printf("|%6.1f |%8.2f |\n", x, y)
}

// конец таблицы
func printEnd() {
	fmt.Println("-------------------")
}

func main() {

	var x, y float64

	fmt.Println("Таблица значений функции:")
	printEnd()
	table()

	// 1. Прямая: [-9; -3]
	for x = -9; x <= -3; x++ {
		y = 0.5*x + 1.5
		printTable(x, y)
	}

	// 2. Экспонента: [-3; 1]
	for ; x <= 1; x++ {
		y = math.Pow(3, x)
		printTable(x, y)
	}

	// 3. Полуокружность: [1; 5]
	for ; x <= 5; x++ {
		y = 3 - math.Sqrt(4-math.Pow(x-3, 2))
		printTable(x, y)
	}

	// 4. Прямая: [5; 8]
	for ; x <= 8; x++ {
		y = -x + 8
		printTable(x, y)
	}

	printEnd()
}
