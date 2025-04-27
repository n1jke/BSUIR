package main

import (
	"fmt"
)

func check(maxSum, k int, slice []int) bool {
	count := 1
	temp := 0
	for _, v := range slice {
		if v > maxSum {
			return false
		}
		if temp+v > maxSum {
			count++
			temp = v
			if count > k {
				return false
			}
		} else {
			temp += v
		}
	}
	return true
}

func solve(slice []int, count int) int {
	if len(slice) < count {
		return -1
	}
	l := slice[0]
	for _, v := range slice {
		if v > l {
			l = v
		}
	}
	r := 0
	for _, v := range slice {
		r += v
	}
	for l < r {
		m := int((l + r) / 2)
		if check(m, count, slice) {
			r = m
		} else {
			l = m + 1
		}
	}
	return l
}

func main() {
	var size, count int
	fmt.Scan(&size, &count)
	slice := make([]int, size)
	for i := range slice {
		fmt.Scan(&slice[i])
	}

	fmt.Println(solve(slice, count))
}
