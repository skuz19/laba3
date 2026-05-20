package main

import (
	"fmt"
	"math"
	"strconv"
)

// функция для нахождения НОД
func gcd(a uint, b uint) uint {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

// вычисление суммы ряда
func calculateSum(a uint, b uint) string {

	// проверка сходимости ряда
	if b <= 1 {
		return "infinity"
	}

	var numerator uint = 0
	var denominator uint = 1

	// формулы суммы ряда
	switch a {

	case 1:
		numerator = b
		denominator = (b - 1) * (b - 1)

	case 2:
		numerator = b * (b + 1)
		denominator = uint(math.Pow(float64(b-1), 3))

	case 3:
		numerator = b * (b*b + 4*b + 1)
		denominator = uint(math.Pow(float64(b-1), 4))

	case 4:
		numerator = b * (b*b*b + 11*b*b + 11*b + 1)
		denominator = uint(math.Pow(float64(b-1), 5))

	// остальные случаи a = 5..10
	default:

		sum := 0.0

		for n := uint(1); n <= 100000; n++ {
			sum += math.Pow(float64(n), float64(a)) /
				math.Pow(float64(b), float64(n))
		}

		const precision uint = 1000000

		numerator = uint(math.Round(sum * float64(precision)))
		denominator = precision
	}

	// сокращение дроби
	g := gcd(numerator, denominator)

	numerator /= g
	denominator /= g

	// формирование результата
	return strconv.FormatUint(uint64(numerator), 10) +
		"/" +
		strconv.FormatUint(uint64(denominator), 10)
}

// функция тестирования
func runTests() {

	fmt.Println("\nПроверка программы:\n")

	// тест из задания
	fmt.Println("Тест 1")
	fmt.Println("Ввод: 1 2")
	fmt.Println("Вывод:", calculateSum(1, 2))
	fmt.Println()

	// расходящийся ряд
	fmt.Println("Тест 2")
	fmt.Println("Ввод: 2 1")
	fmt.Println("Вывод:", calculateSum(2, 1))
	fmt.Println()

	// тест из задания
	fmt.Println("Тест 3")
	fmt.Println("Ввод: 3 4")
	fmt.Println("Вывод:", calculateSum(3, 4))
	fmt.Println()

	// проверка a > 4
	fmt.Println("Тест 4")
	fmt.Println("Ввод: 7 3")
	fmt.Println("Вывод:", calculateSum(7, 3))
	fmt.Println()

	// минимальные значения
	fmt.Println("Тест 5")
	fmt.Println("Ввод: 1 1")
	fmt.Println("Вывод:", calculateSum(1, 1))
	fmt.Println()

	// максимальные значения
	fmt.Println("Тест 6")
	fmt.Println("Ввод: 10 10")
	fmt.Println("Вывод:", calculateSum(10, 10))
	fmt.Println()
}

func main() {

	var a, b uint

	fmt.Print("Введите a и b: ")
	fmt.Scan(&a, &b)

	// проверка диапазона
	if a < 1 || a > 10 || b < 1 || b > 10 {
		fmt.Println("Ошибка ввода")
		return
	}

	// вычисление результата
	result := calculateSum(a, b)

	// вывод результата
	fmt.Println("Результат:", result)

	// запуск тестов
	runTests()
}
