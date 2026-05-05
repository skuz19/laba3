package main

import (
	"fmt"
)

// функция для нахождения НОД (алгоритм Евклида)
func gcd(a, b int64) int64 {
	for b != 0 {
		a, b = b, a%b
	}
	return a
}

// вычисление суммы ряда
func calculateSum(a, b int) string {

	// проверка сходимости ряда
	if b <= 1 {
		return "infinity"
	}

	var numerator int64   // числитель
	var denominator int64 // знаменатель

	// используем готовые формулы
	switch a {

	// a = 1
	case 1:
		numerator = int64(b)
		denominator = int64((b - 1) * (b - 1))

	// a = 2
	case 2:
		numerator = int64(b * (b + 1))
		denominator = int64((b - 1) * (b - 1) * (b - 1))

	// a = 3
	case 3:
		numerator = int64(b * (b*b + 4*b + 1))
		denominator = int64((b - 1) * (b - 1) * (b - 1) * (b - 1))

	// a = 4
	case 4:
		numerator = int64(b * (b*b*b + 11*b*b + 11*b + 1))
		denominator = int64((b - 1) * (b - 1) * (b - 1) * (b - 1) * (b - 1))

	default:
		return "не поддерживается"
	}

	// сокращаем дробь
	g := gcd(numerator, denominator)
	numerator /= g
	denominator /= g

	// формируем строку результата
	return fmt.Sprintf("%d/%d", numerator, denominator)
}

func main() {

	var a, b int

	fmt.Print("Введите a и b: ")
	fmt.Scan(&a, &b)

	// вычисление суммы
	result := calculateSum(a, b)

	// вывод результата
	fmt.Println("Результат:", result)
}
