package main

import (
	"fmt"
	"sort"
)

func checkD(length, count int, slice []int) bool {
	cows := 1
	last_cow := slice[0]
	for _, v := range slice {
		if v-last_cow >= length {
			cows++
			last_cow = v
		}
	}
	return cows >= count
}

func solveD(count int, slice []int) int {
	sort.Slice(slice, func(i, j int) bool {
		return slice[i] < slice[j]
	})

	l := 1
	r := slice[len(slice)-1] - slice[0] + 1

	for r-l > 1 {
		m := int((l + r) / 2)
		if checkD(m, count, slice) {
			l = m
		} else {
			r = m
		}
	}
	return l
}

func main() {
	size, cows := 0, 0
	fmt.Scan(&size, &cows)

	slice := make([]int, size)
	for i := range slice {
		fmt.Scan(&slice[i])
	}

	fmt.Println(solveD(cows, slice))
}
