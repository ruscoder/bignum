#include "bignum.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

/*#define BASE 1000 * 1000 * 100
#define DIGITS 8
#define DIGITSD 8.
#define OUT_FORMAT "%.8d"
*/
#define BASE 10
#define DIGITS 1
#define DIGITSD 1.
#define OUT_FORMAT "%.1d"
#define false 0
#define true 1

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int newObjectsCount = 0,
	delObjectsCount = 0;


BigNum bigNewNum(int len) {
	newObjectsCount++;
	BigNum res;
	res.len = len;
	res.digits = calloc(len, sizeof(int)); 
	if (res.digits == NULL) {
		printf("Cannot allocate memory.\n");
		exit(1);
	}
	return res;
}

void bigFree(BigNum num) {
	delObjectsCount++;
	free(num.digits);
}

void bigVersion() {
	printf("Big Num Version 1.0\n");
	printf("New bignum's created: %d\n Deleted: %d", newObjectsCount, delObjectsCount);
}

BigNum bigCopy(BigNum src) {
	BigNum res = bigNewNum(src.len);
	memcpy(res.digits, src.digits, sizeof(int) * src.len);
	return res;
}


void bigExtend(BigNum *src, int len) {
	BigNum new = bigNewNum(src->len + len);
	memcpy(new.digits + len, src->digits, src->len * sizeof(int));
	bigFree(*src);
	*src = new;
}


BigNum removeLeadNulls(BigNum num) {
	int i;
	// Remove all nulls 
	for (i = num.len - 1; i >= 0; --i) {
		if (num.digits[i] == 0)
			num.len--;
		else
			break;
	}
	return num;
}

BigNum bigFromInt(int num) {
	int len = 1;
	if (num >= BASE)
		len = ceil(floor(log10(num) + 1) / DIGITSD);	

	BigNum res = bigNewNum(len);
	int i = 0;
	while (num) {
		div_t divRes = div(num, BASE);
		res.digits[i] = divRes.rem;
		num = divRes.quot;
		i++;
	}
	return removeLeadNulls(res);
}

BigNum bigFromFile(const char *name) {
	BigNum res;
	
	FILE *fp = fopen(name, "r+");
	if (fp == NULL) {
		printf("Cannot open file %s\n", name);
		exit(1);
	}

	// Get file size
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	res = bigNewNum(ceil(size / DIGITSD));
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
	return removeLeadNulls(res);
}


void bigToFile(const char *name, BigNum first) {
	FILE *fp = fopen(name, "w+");
	if (fp == NULL) {
		printf("Cannot open file %s\n", name);
		return;
	}
	if (first.len == 0) {
		fprintf(fp, "0");
	} else {
		int i;
		fprintf(fp, "%d", first.digits[first.len - 1]);
		for (i = first.len - 2; i >= 0; --i) {
			fprintf(fp, OUT_FORMAT, first.digits[i]);
		}
	}
	fclose(fp);
}

void bigOut(BigNum first) {
	if (first.len == 0) {
		printf("0");
	} else {
		int i;
		printf("%d", first.digits[first.len - 1]);
		for (i = first.len - 2; i >= 0; --i) {
			printf(OUT_FORMAT, first.digits[i]);
		}
	}
}

BigNum bigPlus(BigNum first, BigNum second) {
	BigNum res = bigNewNum(MAX(first.len, second.len) + 1);
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
	// Remove lead nulls
	if (res.digits[res.len - 1] == 0)
		res.len--;
	return res;
}

BigNum bigMinus(BigNum first, BigNum second) {
	// A >= B always
	BigNum res = bigNewNum(MAX(first.len, second.len));
	int i;
	for (i = 0; i < res.len; ++i) {
		int cur = first.digits[i] + res.digits[i];
		if (i < second.len) {
			if (cur < second.digits[i]) {
				cur += BASE;
				res.digits[i + 1] = -1;
			}
			cur -= second.digits[i];
		}
		res.digits[i] = cur;
		
	}
	res = removeLeadNulls(res);	
	return res;
}


BigNum bigMul(BigNum first, BigNum second) {
	BigNum res = bigNewNum(first.len + second.len);
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
 
BigNum bigDiv(BigNum first, BigNum second) {
	// TODO: second == 0
	if (bigCmp(first, second) == -1) {
		return bigFromInt(0);
	}
	BigNum res = bigNewNum(first.len - second.len + 1);
	int pos = 0,
		posSecond = res.len - 1,
		leadNulls = true; 
	BigNum part = bigFromInt(0); 
	for (pos = first.len - 1; pos >= 0; --pos) {
		// Extend 
		bigExtend(&part, 1);
		part.digits[0] = first.digits[pos];
		int l = 0, 
			r = BASE, 
			x = 0;
		BigNum	secondx,
				old;
		while (l <= r) {
			int m = (l + r) >> 1;
			// Search x: second*x <= part
			BigNum bigM = bigFromInt(m);
			secondx = bigMul(second, bigM);
			bigFree(bigM);
			if (bigCmp(secondx, part) <= 0) {
				x = m;
				l = m + 1;
			} else {
				r = m - 1;
			}
			bigFree(secondx);
		}
		BigNum bigX = bigFromInt(x);
		secondx = bigMul(second, bigX);
		old = part;
		part = bigMinus(part, secondx);
		bigFree(old);
		bigFree(secondx);
		bigFree(bigX);
		if (x > 0)
			leadNulls = false;
		if (!leadNulls)
			res.digits[posSecond--] = x;
		
	}
	bigFree(part);
	return res;
}

int bigCmp(BigNum first, BigNum second) {
	/** returns: 
	 -1 - first < second
	  0 - equal
	  1 - first > second
	**/
	if (first.len > second.len) 
		return 1;
	if (first.len < second.len)
		return -1;
	int i;
	for (i = first.len - 1; i >= 0; --i) {
		if (first.digits[i] > second.digits[i])
			return 1;
		if (first.digits[i] < second.digits[i])
			return -1;
	}
	
	return 0;
}

