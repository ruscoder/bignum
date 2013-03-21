#include "bignum.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define BASE 1000 * 1000 * 100
#define DIGITS 8
#define DIGITSD 8.
#define OUT_FORMAT "%.8d"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

struct BigNum newBigNum(int len) {
	struct BigNum res;
	res.len = len;
	res.digits = calloc(len, sizeof(int));
	return res;
}

void bigFree(struct BigNum num) {
	free(num.digits);
}

struct BigNum removeLeadNulls(struct BigNum num) {
	int i;
	for (i = num.len - 1; i >= 0; --i) {
		if (num.digits[i] == 0)
			num.len--;
		else
			break;
	}
	return num;
}

struct BigNum bigFromFile(const char *name) {
	struct BigNum res;
	
	FILE *fp = fopen(name, "r+");
	if (fp == NULL) {
		printf("Cannot open file %s\n", name);
		return;
	}

	// Get file size
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	res = newBigNum(ceil(size / DIGITSD));
	// Seek to start
	fseek(fp, 0l, SEEK_SET);
	// Read file
	char buf[DIGITS + 1];
	int i, 
		offset = size % DIGITS,
		count = 0;
	
	for (i = res.len - 1; i >= 0; --i) {
		if (offset == 0) {
			// Read full num
			count = DIGITS;
		} else {
			// Read first part
			count = offset;
			offset = 0;
		}
		int readed = fread(buf, 1, count,  fp);
		buf[readed] = 0;
		res.digits[i] = atoi(buf);
	}

	fclose(fp);
	return res;
}


void bigToFile(const char *name, struct BigNum first) {
	FILE *fp = fopen(name, "w+");
	if (fp == NULL) {
		printf("Cannot open file %s\n", name);
		return;
	}
	int i;
	fprintf(fp, "%d", first.digits[first.len - 1]);
	for (i = first.len - 2; i >= 0; --i) {
		fprintf(fp, OUT_FORMAT, first.digits[i]);
	}
	fclose(fp);
}

struct BigNum bigPlus(struct BigNum first, struct BigNum second) {
	struct BigNum res = newBigNum(MAX(first.len, second.len) + 1);
	int i;
	unsigned int cur = 0;
	for (i = 0; i < res.len; ++i) {
		if (i < first.len)
			cur += first.digits[i];
		if (i < second.len)
			cur += second.digits[i];
		ldiv_t divRes = ldiv(cur, BASE);
		res.digits[i] = divRes.rem; // %
		cur = divRes.quot; // div
	}
	if (res.digits[res.len - 1] == 0)
		res.len--;
	return res;
}

struct BigNum bigMinus(struct BigNum first, struct BigNum second) {
	// A >= B always
	struct BigNum res = newBigNum(MAX(first.len, second.len));
	int i;
	for (i = 0; i < res.len; ++i) {
		printf("f=%d, s=%d\n", first.digits[i], second.digits[i]);
		int cur = first.digits[i];
		if (i < second.len) {
			if (first.digits[i] < second.digits[i]) {
				cur += BASE;
				res.digits[i + 1] = -1;
			}
			cur -= second.digits[i];
		}
		res.digits[i] += cur;
	}
	res = removeLeadNulls(res);	
	return res;
}


struct BigNum bigMul(struct BigNum first, struct BigNum second) {
	struct BigNum res = newBigNum(first.len + second.len);
	int i;
	for (i = 0; i < first.len; ++i) {
		long long cur = 0;
		int j;
		for (j = 0; j < second.len || cur; ++j) {
			long long mul = first.digits[i];
			if (j < second.len)
				mul *= second.digits[j];
			else
				mul = 0;
			cur += mul + res.digits[i + j];
			lldiv_t divRes = lldiv(cur, BASE);
			res.digits[i + j] = divRes.rem; // %
			cur = divRes.quot; // div
		}
	}
	res = removeLeadNulls(res);	
	return res;
}

