#include <stdio.h>
#include <string.h>
#include "cbignum/bignum.h"



int main(int argc, char **argv) {
	if (argc < 5) {
		printf("Usage: %s <first_file> <+|-|^|*|/|mod> <second_file> <result_file> [-b]", argv[0]);
		return 1;
	}

	//int *first, *second;
	// Binary form
	BigNum a = bigFromFile(argv[1]);
	BigNum b = bigFromFile(argv[3]);
	BigNum res;
/*	if (strncmp(argv[5], "-b", 2) ) {
		a = a;
	} else {
	
	}
	*/	
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
		res = bigPowMod(a, b, b);	
		break;
		
	}
	bigToFile(argv[4], res);
	bigFree(a);
	bigFree(b);
	bigFree(res);
	
	bigVersion();
	return 0;
}
