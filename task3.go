package main

import "fmt"

type Fraction struct {
	numerator   uint64
	denominator uint64
}

// НОД
func gcd(a, b uint64) uint64 {
	for b != 0 {
		temp := b
		b = a % b
		a = temp
	}

	return a
}

// сокращение дроби
func reduce(f Fraction) Fraction {
	g := gcd(f.numerator, f.denominator)

	f.numerator /= g
	f.denominator /= g

	return f
}

// сложение дробей
func add(a, b Fraction) Fraction {
	result := Fraction{
		numerator:   a.numerator*b.denominator + b.numerator*a.denominator,
		denominator: a.denominator * b.denominator,
	}

	return reduce(result)
}

// умножение дроби на целое число
func multiply(f Fraction, value uint64) Fraction {
	f.numerator *= value
	return reduce(f)
}

// деление дроби на целое число
func divide(f Fraction, value uint64) Fraction {
	f.denominator *= value
	return reduce(f)
}

// биномиальный коэффициент C(n, k)
func combination(n, k int) uint64 {
	var result uint64 = 1

	for i := 1; i <= k; i++ {
		result = result * uint64(n-i+1) / uint64(i)
	}

	return result
}

// вычисление суммы ряда
func calculateSum(a, b int) string {
	if b == 1 {
		return "infinity"
	}

	var sums [11]Fraction

	// сумма ряда 1 / b^n
	sums[0] = reduce(Fraction{
		numerator:   1,
		denominator: uint64(b - 1),
	})

	// вычисление сумм для степеней от 1 до a
	for k := 1; k <= a; k++ {
		current := Fraction{
			numerator:   1,
			denominator: 1,
		}

		for j := 0; j < k; j++ {
			term := multiply(sums[j], combination(k, j))
			current = add(current, term)
		}

		sums[k] = divide(current, uint64(b-1))
	}

	answer := reduce(sums[a])

	return fmt.Sprintf("%d/%d", answer.numerator, answer.denominator)
}

func main() {
	var a, b int

	fmt.Scan(&a, &b)

	if a < 1 || a > 10 || b < 1 || b > 10 {
		return
	}

	fmt.Println(calculateSum(a, b))
}
