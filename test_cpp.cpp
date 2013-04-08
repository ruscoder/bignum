#include <cstring>
#include <cstdio>
#include "cppbignum/cppbignum.h"

using namespace std;
void compute(int argc, char **argv) {
	Big a, b, res;
	// Binary form
	if (argv[5] && strncmp(argv[5], "-b", 2) == 0) {
		a = Big(argv[1], true);
		b = Big(argv[3], true);
	} else {
		a = Big(argv[1]);
		b = Big(argv[3]);
	}
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
	if (argv[5] && strncmp(argv[5], "-b", 2) == 0) {
		if (argv[6]) {
			Big module = Big(argv[6], true);
			res = res % module; 
		}
	} else {
		if (argv[5]) {
			Big module = Big(argv[5], true);
			res = res % module; 
		}
	
	}


	res.toFile(argv[4]);
}
int main(int argc, char **argv) {
	if (argc < 5) {
		printf("Usage: %s <first_file> <+|-|^|*|/|mod> <second_file> <result_file> [-b] [module_file]", argv[0]);
		return 1;
	}
	compute(argc, argv);
	bigVersion();	

	return 0;
}

