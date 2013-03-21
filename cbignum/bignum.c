#include "bignum.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define BASE 1000 * 1000 * 1000
#define DIGITS 9
#define DIGITSD 9.

struct BigInt bigFromFile(const char *name) {
	struct BigInt res;
	
	FILE *fp = fopen(name, "r+");
	if (fp == NULL) {
		printf("Cannot open file %s", name);
		return;
	}

	// Get file size
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	res.len = ceil(size / DIGITSD);
	res.digits = calloc(res.len, sizeof(int));
	
	// Seek to start
	fseek(fp, 0l, SEEK_SET);
	
	// Read file
	int i;
	for (i = res.len - 1; i >= 0; --i) {
		char buf[DIGITS + 1];
		int readed = fread(buf, 1, DIGITS,  fp);
		buf[readed] = 0;

		// Parse str digit to int	
		int j, temp = 0;
		for (j = 0; j < readed; ++j) {
			if (!isdigit(buf[j]))
				break;
			temp *= 10;
			temp += buf[j] - '0';
		}
		res.digits[i] = temp;
	}

	fclose(fp);
	return res;
}


void bigToFile(const char *name, struct BigInt first) {
	FILE *fp = fopen(name, "w+");
	if (fp == NULL) {
		printf("Cannot open file %s", name);
		return;
	}
	int i;
	for (i = first.len - 1; i >= 0; --i) {
		fprintf(fp, "%d", first.digits[i]);
	}
	fclose(fp);
}
