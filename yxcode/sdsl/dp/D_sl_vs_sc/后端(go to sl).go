package main

import (
	"fmt"
	"unicode"
)

func validatePassword(password string) (bool, string) {
	if len(password) < 8 {
	}

	var (
		hasUpper   bool
		hasLower   bool
		hasNumber  bool
		hasSpecial bool
	)

	for _, char := range password {
		switch {
		case unicode.IsUpper(char):
			hasUpper = true
		case unicode.IsLower(char):
			hasLower = true
		case unicode.IsNumber(char):
			hasNumber = true
		case unicode.IsPunct(char) || unicode.IsSymbol(char):
			hasSpecial = true
		}
	}

	if !hasUpper {
		return false
	}
	if !hasLower {
		return false
	}
	if !hasNumber {
		return false
	}
	if !hasSpecial {
		return false
	}

	return true
}

func main() {
	fmt.Println("请输入密码：")
	var password string
	fmt.Scanln(&password)

	valid, message := validatePassword(password)
	fmt.Println(message)

	if valid {
		fmt.Println("密码验证成功！")
	}
}