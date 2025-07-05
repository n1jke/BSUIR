package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

func binpow(a, b, mod int64) int64 {
	var res int64 = 1
	for b > 0 {
		if b&1 == 1 {
			res = res * a % mod
		}
		a = a * a % mod
		b >>= 1
	}
	return res
}

func inverse(a, mod int64) int64 {
	return binpow(a, mod-2, mod)
}

func solve(n, m, k, mod int64) int64 {
	if k%mod == 0 {
		return 0
	}

	res := binpow(m, n, mod)
	invK := inverse(k, mod)
	res = res * invK % mod
	return res
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Split(bufio.ScanWords)

	var count, size, speed, mod int64
	if scanner.Scan() {
		count, _ = strconv.ParseInt(scanner.Text(), 10, 64)
	}
	if scanner.Scan() {
		size, _ = strconv.ParseInt(scanner.Text(), 10, 64)
	}
	if scanner.Scan() {
		speed, _ = strconv.ParseInt(scanner.Text(), 10, 64)
	}
	if scanner.Scan() {
		mod, _ = strconv.ParseInt(scanner.Text(), 10, 64)
	}

	fmt.Println(solve(count, size, speed, mod))
}
