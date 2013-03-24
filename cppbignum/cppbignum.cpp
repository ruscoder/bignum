#include <string>
#include "cppbignum.h"
#include <cstdio>
Big::Big(const char* fileName) {
	num = bigFromFile(fileName);
}

Big::~Big() {
	printf("deleted %p\n", num.digits);
	bigFree(num);
}

Big::Big(const BigNum &first) {
	printf("maked this(none)=%p, arg=%p\n",num.digits, first.digits);
	num = first;
}

Big::Big(const Big &first) {
	// Make Copy for new num
	num = bigCopy(first.getNum());
	printf("copy arg=%p to new = %p\n", first.getNum().digits, num.digits);
}

Big &Big::operator =(const Big &rightVal) {
	if (this == &rightVal)
		return *this;
	printf("copy this(deleted)=%p, arg=%p\n",num.digits, rightVal.getNum().digits);
	// Free memory of old num
	bigFree(num);
	// Copy new num
	num = bigCopy(rightVal.getNum());
	printf("new memory created =%p\n", num.digits);
	return *this;
}

const BigNum &Big::getNum() const {
	return num;
}

const Big Big::operator +(Big& rightVal) {
	printf("plus this=%p, arg=%p\n",num.digits, rightVal.getNum().digits);
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

void Big::out() {
	printf("outed num = %p\n", num.digits);
	//bigPrint(num);
}
