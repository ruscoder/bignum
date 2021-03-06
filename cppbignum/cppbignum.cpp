#include <string>
#include "cppbignum.h"
#include <cstdio>

Big::Big(const char* fileName) {
	num = bigFromFileDec(fileName);
}

Big::Big() {
	num = bigNone();
}

Big::Big(const char* fileName, bool binary = false) {
	if (binary) 
		num = bigFromFileBin(fileName);
	else
		num = bigFromFileDec(fileName);
}

Big::~Big() {
	if (num.digits)
		bigFree(num);
}

Big::Big(const BigNum &first) {
	num = first;
}

Big::Big(const Big &first) {
	// Make Copy for new num
	num = bigCopy(first.getNum());
}

Big &Big::operator =(const Big &rightVal) {
	if (this == &rightVal)
		return *this;
	// Free memory of old num
	bigFree(num);
	// Copy new num
	num = bigCopy(rightVal.getNum());
	return *this;
}

const BigNum &Big::getNum() const {
	return num;
}

const Big Big::operator +(Big &rightVal) {
	return Big(bigPlus(num, rightVal.getNum()));
}

const Big Big::operator -(Big &rightVal) {
	return Big(bigMinus(num, rightVal.getNum()));
} 
Big Big::operator -() {
	return Big(bigNegative(bigCopy(num)));
}

const Big Big::operator *(Big &rightVal) {
	return Big(bigMul(num, rightVal.getNum()));
}

const Big Big::operator /(Big &rightVal) {
	return Big(bigDiv(num, rightVal.getNum()));
}

const Big Big::operator %(Big &rightVal) {
	return Big(bigMod(num, rightVal.getNum()));
}

const Big Big::operator ^(Big &rightVal) {
	return Big(bigPowMod(num, rightVal.getNum(), bigNone()));
}

bool Big::operator ==(const Big &second) {
	if (bigCmp(second.getNum(), num) == 0) 
		return true;
	else
		return false;
}

bool Big::operator >(const Big &second) {
	if (bigCmp(num, second.getNum()) == 1) 
		return true;
	else
		return false;
}

bool Big::operator <(const Big &second) {
	if (bigCmp(num, second.getNum()) == -1) 
		return true;
	else
		return false;
}
bool Big::operator <=(const Big &second) {
	if (bigCmp(num, second.getNum()) <= 0) 
		return true;
	else
		return false;
}
bool Big::operator >=(const Big &second) {
	if (bigCmp(num, second.getNum()) >= 0) 
		return true;
	else
		return false;
}

void Big::toFile(const char * fileName) {
	bigToFile(fileName, num);
}

void Big::out() {
	bigOut(num);
}
