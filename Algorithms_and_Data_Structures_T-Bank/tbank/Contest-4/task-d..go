package main

import "fmt"

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func count(m, n, mid int) int {
	ans := 0
	for i := 1; i <= m; i++ {
		ans += min(n, int(mid/i))
	}
	return ans
}

/*
func binSearch(size, number int) int {
	left, right := 1, size*size
	mid := 1
	for right > left {
		mid = left + (right-left)/2
		if count(size, mid) < number {
			left = mid + 1
		} else {
			right = mid
		}
	}
	return right
}*/

func findKthNumber(m, n, number int) int {
	left, right := 1, m*n
	mid := 1
	if n == 1 {
		return number
	}
	for right > left {
		mid = left + (right-left)/2
		if count(m, n, mid) < number {
			left = mid + 1
		} else {
			right = mid
		}
	}
	return right
}

func main() {
	var m, n, number int
	fmt.Scan(&m, &n, &number)
	result := findKthNumber(m, n, number)
	fmt.Println(result)
}

/*
3 4 - 3 // 5 16 - 10
*/
