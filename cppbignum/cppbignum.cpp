#include <string>
#include "cppbignum.h"
#include <cstdio>
Big::Big(const std::string fileName) {
	num = bigFromFile(fileName.c_str());
}

Big::~Big() {
	bigFree(num);
}

Big::Big(BigNum first) {
	num = first;
}

Big::Big(const Big &first) {
	printf("copy %p\n",num.digits);
}

Big &Big::operator =(const Big &rightVal) {
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

void Big::toFile(const std::string fileName) {
	bigToFile(fileName.c_str(), num);
}
