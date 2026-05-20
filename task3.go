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

	// защита от деления на ноль
	if denominator == 0 {
		return "error"
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

func main() {

	var a, b int

	fmt.Print("Введите a и b: ")
	_, err := fmt.Scan(&a, &b)

	// проверка корректности ввода
	if err != nil {
		return
	}

	// проверка диапазона
	if a < 1 || a > 10 || b < 1 || b > 10 {
		return
	}

	// вычисление результата
	result := calculateSum(uint(a), uint(b))

	// вывод результата
	fmt.Println("Результат:", result)
}
