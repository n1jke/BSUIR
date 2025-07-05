package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

const mod = 1000000007

func binpow(a, b int) int {
	res := 1
	for b > 0 {
		if b&1 == 1 {
			res = res * a % mod
		}
		a = a * a % mod
		b >>= 1
	}
	return res
}

func inverse(a int) int {
	return binpow(a, mod-2)
}

func findC(n, k int) int {

	fact := make([]int, n+1)
	fact[0] = 1
	for i := 1; i <= n; i++ {
		fact[i] = fact[i-1] * i % mod
	}

	invK := inverse(fact[k])
	invNK := inverse(fact[n-k])

	res := fact[n] * invK % mod
	res = res * invNK % mod
	return res
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Split(bufio.ScanWords)

	var n, k int
	if scanner.Scan() {
		n, _ = strconv.Atoi(scanner.Text())
	}

	if scanner.Scan() {
		k, _ = strconv.Atoi(scanner.Text())
	}

	fmt.Println(findC(n, k))
}
