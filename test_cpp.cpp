#include <string>
#include <cstdio>
#include "cppbignum/cppbignum.h"

using namespace std;

int main(int argc, char **argv) {
	if (argc < 5) {
		printf("Usage: %s <first_file> <+|-|^|*|/|mod> <second_file> <result_file> [module_file] [-b]", argv[0]);
		return 1;
	}
	
	Big a = Big(argv[1]);
	Big b = Big(argv[3]);
	Big res = Big(argv[1]);
	// Binary form
/*	if (strncmp(argv[6], "-b", 2) ) {
		a = a;
	} else {
	
	}
	*/	
	switch (argv[2][0]) {
	case '+':
		res = a + b;
		break;
	case '-':
		res = a - b;
		break;
	case '*':
		res = a * b;
		break;
	case '/':
		res = a / b;
		break;
	case '%':
		res = a % b;
		break;
	case '^':
		res = a ^ b;
	}
	
	// If module
	if (argv[5]) {
		Big module = Big(argv[5]);
		res = res % module; 
	}

	res.toFile(argv[4]);
	return 0;
}

