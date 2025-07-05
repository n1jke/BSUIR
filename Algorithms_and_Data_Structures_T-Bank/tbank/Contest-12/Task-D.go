package main

import "fmt"

func lastNonZero(num int) int {
	count2 := 0
	count5 := 0
	res := 1
	mod := 100000000000

	for i := 1; i <= num; i++ {
		x := i
		for x%2 == 0 {
			x /= 2
			count2++
		}

		for x%5 == 0 {
			x /= 5
			count5++
		}
		res *= x
		res %= mod
	}

	diff := count2 - count5
	if diff > 0 {
		for i := 0; i < diff; i++ {
			res *= 2
			res %= mod
		}
	}

	for res%10 == 0 {
		res /= 10
	}

	return res % 10
}

func main() {
	var num int
	fmt.Scan(&num)
	fmt.Println(lastNonZero(num))
}
