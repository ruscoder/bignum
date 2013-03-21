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
	struct BigInt a = bigFromFile("jjj");
	
	if (strncmp(argv[5], "-b", 2) ) {
		a = a;
	} else {
	
	}
		
	switch (argv[2][0]) {
	case '+':
		//bigPlus();	
		break;
		
	}
	
	return 0;
}
