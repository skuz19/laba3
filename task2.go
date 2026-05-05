package main

import (
	"fmt"
	"math"
	"math/rand"
	"time"
)

// инициализация генератора случайных чисел
func init() {
	rand.Seed(time.Now().UnixNano())
}

// случайное целое число
func getRandomInt(a, b int) int {
	return rand.Intn(b-a+1) + a
}

// случайное вещественное число
func getRandomDouble(a, b float64) float64 {
	return a + rand.Float64()*(b-a)
}

// решето Эратосфена
func sieve(n int) []int {
	prime := make([]bool, n+1)
	for i := range prime {
		prime[i] = true
	}
	prime[0], prime[1] = false, false

	for i := 2; i*i <= n; i++ {
		if prime[i] {
			for j := i * i; j <= n; j += i {
				prime[j] = false
			}
		}
	}

	var res []int
	for i := 2; i <= n; i++ {
		if prime[i] {
			res = append(res, i)
		}
	}
	return res
}

// быстрое возведение в степень по модулю
func modPow(a, b, mod int64) int64 {
	res := int64(1)
	a %= mod

	for b > 0 {
		if b%2 == 1 {
			res = (res * a) % mod
		}
		a = (a * a) % mod
		b /= 2
	}
	return res
}

// тест Миллера-Рабина
func millerRabinTest(n int, k int) bool {
	if n < 2 {
		return false
	}
	if n == 2 || n == 3 {
		return true
	}
	if n%2 == 0 {
		return false
	}

	d := n - 1
	s := 0
	for d%2 == 0 {
		d /= 2
		s++
	}

	for i := 0; i < k; i++ {
		a := getRandomInt(2, n-2)
		x := modPow(int64(a), int64(d), int64(n))

		if x == 1 || x == int64(n-1) {
			continue
		}

		composite := true
		for r := 1; r < s; r++ {
			x = modPow(x, 2, int64(n))
			if x == int64(n-1) {
				composite = false
				break
			}
		}
		if composite {
			return false
		}
	}
	return true
}

// генерация числа по ГОСТ
func generateGostPrime(primes []int, t int) int {

	maxIndex := 0
	for maxIndex < len(primes) && primes[maxIndex] < (1<<(t/2)) {
		maxIndex++
	}

	q := primes[getRandomInt(0, maxIndex-1)]

	for {
		xi := getRandomDouble(0, 1)

		A := math.Floor(math.Pow(2, float64(t-1)) / float64(q))
		B := math.Floor((math.Pow(2, float64(t-1)) * xi) / float64(q))

		N := int(A + B)

		if N%2 != 0 {
			N++
		}

		u := 0

		for {
			p := (N + u) * q + 1

			if p > (1 << t) {
				break
			}

			if modPow(2, int64(p-1), int64(p)) == 1 &&
				modPow(2, int64(N+u), int64(p)) != 1 {
				return p
			}

			u += 2
		}
	}
}

// вывод таблицы
func printTable(data [][2]int) {
	fmt.Println("\nРезультаты:")
	fmt.Println("+-----+------------+-----------+")
	fmt.Println("|  №  |   Число    | отклонено |")
	fmt.Println("+-----+------------+-----------+")

	for i, v := range data {
		fmt.Printf("| %3d | %10d | %9d |\n", i+1, v[0], v[1])
	}

	fmt.Println("+-----+------------+-----------+")
}

// проверка результатов
func fullCheck(results [][2]int, bits int) {

	fmt.Println("\nПроверка результатов")

	ok := true

	if len(results) == 10 {
		fmt.Println("Количество чисел корректно")
	} else {
		fmt.Println("Ошибка количества чисел")
		ok = false
	}

	for _, v := range results {
		p := v[0]

		if !(p > (1<<(bits-1)) && p < (1<<bits)) {
			fmt.Println("Число вне диапазона:", p)
			ok = false
		}

		if modPow(2, int64(p-1), int64(p)) != 1 {
			fmt.Println("Не выполнено первое условие для:", p)
			ok = false
		}

		if !millerRabinTest(p, 5) {
			fmt.Println("Число не является простым:", p)
			ok = false
		}
	}

	if ok {
		fmt.Println("Все проверки пройдены успешно")
	} else {
		fmt.Println("Обнаружены ошибки")
	}
}

func main() {

	var bits int
	fmt.Print("Введите разрядность (bits): ")
	fmt.Scan(&bits)

	primes := sieve(500)

	var results [][2]int
	rejected := 0

	for len(results) < 10 {

		p := generateGostPrime(primes, bits)

		duplicate := false
		for _, v := range results {
			if v[0] == p {
				duplicate = true
				break
			}
		}

		if duplicate {
			continue
		}

		results = append(results, [2]int{p, rejected})
		rejected = 0
	}

	printTable(results)
	fullCheck(results, bits)
}
