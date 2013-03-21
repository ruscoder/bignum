#include <string>
#include "cppbignum.h"

Big::Big(const std::string fileName) {
	num = bigFromFile(fileName.c_str());
}

Big::Big(struct BigNum first) {
	num = first;
}

struct BigNum Big::getNum() {
	return num;
}

const Big Big::operator +(Big& rightVal) {
	return Big(bigPlus(num, rightVal.getNum()));
}

const Big Big::operator -(Big& rightVal) {
	return Big(bigMinus(num, rightVal.getNum()));
}

void Big::toFile(const std::string fileName) {
	bigToFile(fileName.c_str(), num);
}
