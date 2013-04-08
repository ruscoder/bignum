#include <stdio.h>
#include <string.h>
#include "cbignum/bignum.h"



int main(int argc, char **argv) {
	if (argc < 5) {
		printf("Usage: %s <first_file> <+|-|^|*|/|%%> <second_file> <result_file> [-b] [module_file] ", argv[0]);
		return 1;
	}


	BigNum a, 
		b, 
		module = bigNone(), 
		res;
	// Binary form
	if (argv[5] && strncmp(argv[5], "-b", 2) == 0) {
		printf("bin");
		a = bigFromFileBin(argv[1]);
		b = bigFromFileBin(argv[3]);
		if (argv[6]) {
			module = bigFromFileBin(argv[6]);
		}
	} else {
		a = bigFromFileDec(argv[1]);
		b = bigFromFileDec(argv[3]);
		if (argv[5]) {
			module = bigFromFileDec(argv[5]);
		}
	
	}

	switch (argv[2][0]) {
	case '+':
		res = bigPlus(a, b);	
		break;
	case '-':
		res = bigMinus(a, b);
		break;
	case '*':
		res = bigMul(a, b);	
		break;
	case '/':
		res = bigDiv(a, b);	
		break;
	case '%':
		res = bigMod(a, b);	
		break;
	case '^':
		res = bigPowMod(a, b, module);	
		break;
		
	}
	// Module for * - / +
	if (module.digits && argv[2][0] != '^') {
		BigNum old = res;
		res = bigMod(res, module);
		bigFree(old);
	}
	bigToFile(argv[4], res);
	bigFree(a);
	bigFree(b);
	bigFree(res);
	if (argv[5] && strncmp(argv[5], "-b", 2) == 0) {
		if (argv[6]) {
			bigFree(module);
		}
	} else {
		if (argv[5])
		{
			bigFree(module);
		}
	}
	bigVersion();
	return 0;
}
