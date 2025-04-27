package main

import (
	"bufio"
	"fmt"
	"os"
)

// Функция для быстрого чтения числа из bufio.Reader
func readInt(reader *bufio.Reader) int {
	num := 0
	neg := false
	b, err := reader.ReadByte()
	for ; b < '0' || b > '9'; b, err = reader.ReadByte() {
		if b == '-' {
			neg = true
		}
		if err != nil {
			break
		}
	}
	for ; b >= '0' && b <= '9'; b, err = reader.ReadByte() {
		num = num*10 + int(b-'0')
		if err != nil {
			break
		}
	}
	if neg {
		return -num
	}
	return num
}

func buildPrefixSum(matrix [][]int, n, m int) [][]int {
	prefix := make([][]int, n+1)
	for i := range prefix {
		prefix[i] = make([]int, m+1)
	}

	for i := 1; i <= n; i++ {
		for j := 1; j <= m; j++ {
			prefix[i][j] = matrix[i-1][j-1] +
				prefix[i-1][j] +
				prefix[i][j-1] -
				prefix[i-1][j-1]
		}
	}
	return prefix
}

func getRectangleSum(prefix [][]int, y1, x1, y2, x2 int) int {
	return prefix[y2][x2] -
		prefix[y2][x1-1] -
		prefix[y1-1][x2] +
		prefix[y1-1][x1-1]
}

func main() {
	reader := bufio.NewReader(os.Stdin)

	// Читаем n, m, k
	n := readInt(reader)
	m := readInt(reader)
	k := readInt(reader)

	// Читаем матрицу
	matrix := make([][]int, n)
	for i := range matrix {
		matrix[i] = make([]int, m)
		for j := range matrix[i] {
			matrix[i][j] = readInt(reader)
		}
	}

	prefix := buildPrefixSum(matrix, n, m)

	for i := 0; i < k; i++ {
		y1 := readInt(reader)
		x1 := readInt(reader)
		y2 := readInt(reader)
		x2 := readInt(reader)
		result := getRectangleSum(prefix, y1, x1, y2, x2)
		fmt.Println(result)
	}
}
