package main

import (
	"fmt"
	"math"
	"math/rand"
	"time"
)

// вычисление 2^n
func powerOfTwo(n int) int {
	result := 1
	for i := 0; i < n; i++ {
		result *= 2
	}
	return result
}

// построение таблицы простых чисел меньше 500
func sieveEratosthenes(limit int) []int {
	isPrime := make([]bool, limit+1)
	for i := 0; i <= limit; i++ {
		isPrime[i] = true
	}

	isPrime[0] = false
	isPrime[1] = false

	for i := 2; i*i <= limit; i++ {
		if isPrime[i] {
			for j := i * i; j <= limit; j += i {
				isPrime[j] = false
			}
		}
	}

	primes := []int{}

	for i := 2; i <= limit; i++ {
		if isPrime[i] {
			primes = append(primes, i)
		}
	}

	return primes
}

// умножение по модулю без переполнения
func multiplyMod(a, b, mod int) int {
	result := 0
	a %= mod

	for b > 0 {
		if b%2 == 1 {
			if result >= mod-a {
				result = result - (mod - a)
			} else {
				result += a
			}
		}

		b /= 2

		if a >= mod-a {
			a = a - (mod - a)
		} else {
			a += a
		}
	}

	return result
}

// быстрое возведение в степень по модулю
func powerMod(base, degree, mod int) int {
	result := 1
	base %= mod

	for degree > 0 {
		if degree%2 == 1 {
			result = multiplyMod(result, base, mod)
		}

		base = multiplyMod(base, base, mod)
		degree /= 2
	}

	return result
}

// проверка условий теоремы Диемитко
func gostTest(p, q int) bool {
	n := (p - 1) / q

	return powerMod(2, p-1, p) == 1 &&
		powerMod(2, n, p) != 1
}

// проверка повторов
func containsNumber(numbers []int, value int) bool {
	for _, number := range numbers {
		if number == value {
			return true
		}
	}

	return false
}

// генерация простого числа по ГОСТ
func generateGostPrime(primes []int, bits int, rejected *int) int {
	lowerBound := powerOfTwo(bits - 1)
	upperBound := powerOfTwo(bits)

	suitableQ := []int{}

	// выбор подходящих q
	for _, q := range primes {
		if q >= powerOfTwo((bits+1)/2-1) &&
			q < powerOfTwo((bits+1)/2) {
			suitableQ = append(suitableQ, q)
		}
	}

	if len(suitableQ) == 0 {
		suitableQ = primes
	}

	// поиск числа p
	for {
		q := suitableQ[rand.Intn(len(suitableQ))]

		xi := rand.Float64()

		// вычисление N
		n := int(
			math.Floor(float64(lowerBound)/float64(q)) +
				math.Floor(float64(lowerBound)*xi/float64(q)),
		)

		if n%2 != 0 {
			n++
		}

		// перебор параметра u
		for u := 0; ; u += 2 {
			p := (n+u)*q + 1

			if p >= upperBound {
				*rejected++
				break
			}

			if p <= lowerBound {
				*rejected++
				continue
			}

			// проверка простоты
			if gostTest(p, q) {
				return p
			}

			*rejected++
		}
	}
}

// вывод таблицы результатов
func printTable(numbers []int, rejected []int) {
	fmt.Println("\nТаблица результатов")
	fmt.Println("+---+---------------+-------------------+----------------------+")
	fmt.Println("| № | Простое число | Результат проверки | rejected             |")
	fmt.Println("+---+---------------+-------------------+----------------------+")

	for i := 0; i < len(numbers); i++ {
		fmt.Printf(
			"| %d | %13d | %17s | %20d |\n",
			i+1,
			numbers[i],
			"true",
			rejected[i],
		)
	}

	fmt.Println("+---+---------------+-------------------+----------------------+")
}

func main() {
	rand.Seed(time.Now().UnixNano())

	var bits int

	fmt.Print("Введите bits: ")
	fmt.Scan(&bits)

	// построение таблицы простых
	primes := sieveEratosthenes(500)

	resultNumbers := []int{}
	rejectedValues := []int{}

	// получение 10 различных чисел
	for len(resultNumbers) < 10 {
		rejected := 0

		p := generateGostPrime(primes, bits, &rejected)

		if containsNumber(resultNumbers, p) {
			continue
		}

		resultNumbers = append(resultNumbers, p)
		rejectedValues = append(rejectedValues, rejected)
	}

	printTable(resultNumbers, rejectedValues)
}
