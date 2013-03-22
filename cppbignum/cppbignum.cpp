#include <string>
#include "cppbignum.h"
#include <cstdio>
Big::Big(const char* fileName) {
	num = bigFromFile(fileName);
	printf("maked %p\n", num.digits);
}

Big::~Big() {
	bigFree(num);
}

Big::Big(BigNum first) {
	printf("maked from bignum %p\n", first.digits);
	num = first;
}

Big::Big(const Big &first) {
	// Free memory of old num
	bigFree(num);
	// Copy new num
	num = bigCopy(first.getNum());
}

Big &Big::operator =(const Big &rightVal) {
	printf("=== %p to %p\n",num.digits, rightVal.getNum().digits);
	// Free memory of old num
	bigFree(num);
	// Copy new num
	num = bigCopy(rightVal.getNum());
	return *this;
}

BigNum Big::getNum() const {
	return num;
}

const Big Big::operator +(Big& rightVal) {
	return Big(bigPlus(num, rightVal.getNum()));
}

const Big Big::operator -(Big& rightVal) {
	return Big(bigMinus(num, rightVal.getNum()));
}

const Big Big::operator *(Big& rightVal) {
	return Big(bigMul(num, rightVal.getNum()));
}

void Big::toFile(const char * fileName) {
	bigToFile(fileName, num);
}
