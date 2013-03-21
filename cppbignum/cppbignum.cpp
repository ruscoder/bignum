#include <string>
#include "cppbignum.h"
extern "C" {
#include "../cbignum/bignum.h"
};

BigNum::BigNum(std::string fileName) {
	bigFromFile(fileName.c_str());
}


