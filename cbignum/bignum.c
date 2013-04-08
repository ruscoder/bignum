/* TODO
 * Make comments documentation 
 */
#include "bignum.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define BASEDEC 1000 * 1000 * 100
#define DIGITSDEC 8
#define DIGITSDECF 8.
#define OUT_FORMATDEC "%.8d"

#define BASEBIN 0x1000000
#define DIGITSBIN 3
#define OUT_FORMATBIN "%.3X"

#define false 0
#define true 1

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int newObjectsCount = 0,
	delObjectsCount = 0;

int computeLen(int num, unsigned int base) {
	// Compute len
	int len = 1;
	if (base != BASEBIN && num >= base) {
		len = ceil(floor( log10(abs(num)) + 1) / DIGITSDECF);	
	}
	return len;
}

BigNum bigNewNum(int len, unsigned int base) {
	newObjectsCount++;
	BigNum res;
	res.len = len;
	res.allocated = len;
	res.base = base;
	// Positive
	res.sign = 0;
	res.digits = calloc(len, sizeof(int)); 
	if (res.digits == NULL) {
		printf("Cannot allocate memory.\n");
		exit(1);
	}
	return res;
}

BigNum bigNone() {
	BigNum res;
	res.len = res.allocated = res.sign = 0;
	res.digits = NULL;
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
	BigNum res = bigNewNum(src.len, src.base);
	memcpy(res.digits, src.digits, sizeof(int) * src.len);
	res.allocated = src.allocated;
	res.sign = src.sign;
	return res;
}


void bigExtend(BigNum *src, int num) {
	src->len++;
	if (src->len > src->allocated) {
		printf("Wrong using of bigExtend!\n");
		exit(1);
	}
	int i;
	for (i = src->len - 1; i >= 1; --i) {
		src->digits[i] = src->digits[i - 1];
	}
	src->digits[0] = num;
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

BigNum bigFromInt(int num, unsigned int base) {
	int len = computeLen(num, base);
	BigNum res = bigNewNum(len, base);
	// Negative nums
	if (num < 0) {
		num = -num;
		res.sign = 1;
	}
	// Parse
	int i = 0;
	while (num) {
		lldiv_t divRes = lldiv(num, res.base);
		res.digits[i] = divRes.rem;
		num = divRes.quot;
		i++;
	}
	return removeLeadNulls(res);
}

BigNum bigFromFileBin(const char *name) {
	BigNum res;

	FILE *fp = fopen(name, "rb+");
	if (fp == NULL) {
		printf("Cannot open file %s\n", name);
		exit(1);
	}

	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	res = bigNewNum(ceil(size / DIGITSBIN), BASEBIN);
	int i;
	for (i = 0; i < res.len; ++i) {
		fread(&res.digits[i], DIGITSBIN, 1, fp);
	}
	fclose(fp);
	return removeLeadNulls(res);
}

BigNum bigFromFileDec(const char *name) {
	BigNum res;
	
	FILE *fp = fopen(name, "r+");
	if (fp == NULL) {
		printf("Cannot open file %s\n", name);
		exit(1);
	}
	
	// Get sign (first byte)
	char signBuf;
	fread(&signBuf, 1, 1, fp);
	int sign = (signBuf == '-'); // 0 or 1
	// Get file size
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp) - sign;
	res = bigNewNum(ceil(size / DIGITSDECF), BASEDEC);
	// Set sign
	res.sign = sign;
	// Seek to start
	fseek(fp, sign, SEEK_SET);
	// Read file
	char buf[DIGITSDEC + 1];
	int i, 
		offset = size % DIGITSDEC,
		count = 0;
	
	for (i = res.len - 1; i >= 0; --i) {
		if (offset == 0) {
			// Read full num
			count = DIGITSDEC;
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


void bigToFileBin(const char *name, BigNum first) {
	FILE *fp = fopen(name, "wb+");
	if (fp == NULL) {
		printf("Cannot open file %s\n", name);
		return;
	}
	if (first.len == 0) {
		// Write 0
		char buf = '\0';
		fwrite(&buf, 1, 1, fp);
	} else {
		int i;
		for (i = 0; i < first.len; ++i) {
			fwrite(&first.digits[i], DIGITSBIN, 1, fp);
		}
	}
	fclose(fp);
}


void bigToFileDec(const char *name, BigNum first) {
	FILE *fp = fopen(name, "w+");
	if (fp == NULL) {
		printf("Cannot open file %s\n", name);
		return;
	}
	if (first.len == 0) {
		fprintf(fp, "0");
	} else {
		// Put sign
		if (first.sign) {
			fprintf(fp, "-");
		}
		int i;
		fprintf(fp, "%d", first.digits[first.len - 1]);
		for (i = first.len - 2; i >= 0; --i) {
			fprintf(fp, OUT_FORMATDEC, first.digits[i]);
		}
	}
	fclose(fp);
}

void bigToFile(const char *name, BigNum first) {
	if (first.base == BASEDEC) {
		bigToFileDec(name, first);
	} else {
		bigToFileBin(name, first);
	}
}

void bigOutBin(BigNum first) {
	if (first.len == 0) {
		printf("0");
	} else {
		int i;
		printf("%X", first.digits[0]);
		for (i = 1; i < first.len; ++i) {
			printf(OUT_FORMATBIN, first.digits[i]);
		}
	}
}

void bigOutDec(BigNum first) {
	if (first.len == 0) {
		printf("0");
	} else {
		if (first.sign) {
			printf("-");
		}
		int i;
		printf("%d", first.digits[first.len - 1]);
		for (i = first.len - 2; i >= 0; --i) {
			printf(OUT_FORMATDEC, first.digits[i]);
		}
	}
}

void bigOut(BigNum first) {
	if (first.base == BASEDEC) 
		bigOutDec(first);
	else
		bigOutBin(first);
}

BigNum bigNegative(BigNum num) {
	num.sign = !num.sign;
	return num;
}

int bigIsEven(BigNum num) {
	if (num.digits[num.len - 1] % 2 == 0)
		return 1;
	return 0;
}

BigNum bigPlus(BigNum first, BigNum second) {
	// a + (-b) = a - b
	if (!first.sign && second.sign) {
		return bigMinusUnsigned(first, second);
	}
	// (-a) + b = b - a
	if (first.sign && !second.sign) {
		return bigMinusUnsigned(second, first);
	}
	// (-a) + (-b) = -(a + b)
	if (first.sign && second.sign) {
		return bigNegative(bigPlusUnsigned(first, second));
	}
	// Default a + b
	return bigPlusUnsigned(first, second);
}



BigNum bigPlusUnsigned(BigNum first, BigNum second) {
	BigNum res = bigNewNum(MAX(first.len, second.len) + 1, first.base);
	int i;
	unsigned int cur = 0;
	for (i = 0; i < res.len; ++i) {
		if (i < first.len)
			cur += first.digits[i];
		if (i < second.len)
			cur += second.digits[i];
		lldiv_t divRes = lldiv(cur, res.base);
		res.digits[i] = divRes.rem; // %
		cur = divRes.quot; // div
	}
	// Remove lead nulls
	if (res.digits[res.len - 1] == 0)
		res.len--;
	return res;
}

BigNum bigMinus(BigNum first, BigNum second) {
	// a - (-b) = a + b
	if (!first.sign && second.sign) {
		return bigPlusUnsigned(first, second);
	}
	// (-a) - b = -(a + b)
	if (first.sign && !second.sign) {
		return bigNegative(bigPlusUnsigned(second, first));
	}
	// (-a) - (-b) = (-a) + b = b - a
	if (first.sign && second.sign) {
		return bigMinusUnsigned(second, first);
	}
	// Default a - b
	return bigMinusUnsigned(first, second);
}

BigNum bigMinusUnsigned(BigNum first, BigNum second) {
	if (bigCmpUnsigned(first, second) == -1) {
		return bigNegative(bigMinusUnsignedFromLargest(second, first));
	}
	return bigMinusUnsignedFromLargest(first, second);
}

BigNum bigMinusUnsignedFromLargest(BigNum first, BigNum second) {
	// A >= B always
	BigNum res = bigNewNum(MAX(first.len, second.len), first.base);
	int i;
	for (i = 0; i < res.len; ++i) {
		long long cur = (long long)first.digits[i] + res.digits[i];
		if (i < second.len) {
			if (cur < second.digits[i]) {
				cur += res.base;
				res.digits[i + 1] = -1;
			}
			cur -= second.digits[i];
		}
		res.digits[i] = cur;
		
	}
	res = removeLeadNulls(res);	
	return res;
}

// For bigDiv functions
void bigMinusUnsignedFromFirst(BigNum *first, BigNum second) {
	// A >= B always
	int i;
	for (i = 0; i < first->len; ++i) {
		unsigned long long cur = first->digits[i];
		if (i < second.len) {
			if (cur < second.digits[i]) {
				cur += first->base;
				first->digits[i + 1]--;
			}
			cur -= second.digits[i];
		}
		first->digits[i] = cur;
	}	
	
	*first = removeLeadNulls(*first);
}

BigNum bigMul(BigNum first, BigNum second) {
	BigNum res = bigNewNum(first.len + second.len, first.base);
	// Select sign
	res.sign = first.sign ^ second.sign;  
	int i;
	for (i = 0; i < first.len; ++i) {
		unsigned long long cur = 0;
		int j;
		for (j = 0; j < second.len || cur; ++j) {
			unsigned long long mul = first.digits[i];
			if (j < second.len)
				mul *= second.digits[j];
			else
				mul = 0;
			cur += mul + res.digits[i + j];
			lldiv_t divRes = lldiv(cur, res.base);
			res.digits[i + j] = divRes.rem; // %
			cur = divRes.quot; //v
		}
	}
	return removeLeadNulls(res);	
}

BigNum bigMulOnInt(BigNum first, int second) {
	char secondSign = 0;
	if (second < 0) {
		second = -second;
		secondSign = 1;
	}
	// Compute len of second
	int len = computeLen(second, first.base);
	BigNum res = bigNewNum(first.len + len, first.base);
	// Select sign
	res.sign = first.sign ^ secondSign;  
	int i;
	for (i = 0; i < first.len; ++i) {
		unsigned long long cur = (unsigned long long)first.digits[i] * second; 
		int j;
		for (j = 0; cur; ++j) {
			cur += res.digits[i + j];
			lldiv_t divRes = lldiv(cur, res.base);
			res.digits[i + j] = divRes.rem; // %
			cur = divRes.quot; // div
		}
	}
	return removeLeadNulls(res);	
}

BigNum bigDivOnInt(BigNum first, int second) {
	char secondSign = 0;
	if (second < 0) {
		second = -second;
		secondSign = 1;
	}
	// Compute len of second
	int len = computeLen(second, first.base);
	BigNum res = bigNewNum(first.len - len + 1, first.base);
	// Select sign
	res.sign = first.sign ^ secondSign;  
	int i;
	unsigned long long cur = 0;
	for (i = first.len - 1; i >= 0; --i) {
		cur = cur * res.base + first.digits[i];
		lldiv_t divRes = lldiv(cur, second);
		res.digits[i] = divRes.quot; // div
		cur = divRes.rem; // %
	}
	
	return removeLeadNulls(res);
}


BigNum bigDiv(BigNum first, BigNum second) {
	// 0 if a < b (nor=t signed)	
	if (bigCmpUnsigned(first, second) == -1) {
		return bigFromInt(0, first.base);
	}
	// if second == 0
	if (second.len == 0) {
		printf("Division by zero.");
		exit(1);
	}
	BigNum res = bigNewNum(first.len - second.len + 1, first.base);
	// Select sign
	res.sign = first.sign ^ second.sign;  
	int pos = 0,
		leadNulls = true; 
	BigNum part = bigNewNum(second.len + 1, first.base); 
	part.len = 0;
	for (pos = first.len - 1; pos >= 0; --pos) {
		// Extend 
		bigExtend(&part, first.digits[pos]);
		unsigned int l = 0, 
			r = res.base, 
			x = 0;
		BigNum	secondx;
		while (l <= r) {
			unsigned int m = (l + r) >> 1;
			// Search x: second*x <= part
			secondx = bigMulOnInt(second, m);
			if (bigCmpUnsigned(secondx, part) <= 0) {
				x = m;
				l = m + 1;
			} else {
				r = m - 1;
			}
			bigFree(secondx);
		}
		secondx = bigMulOnInt(second, x);
		bigMinusUnsignedFromFirst(&part, secondx);
		bigFree(secondx);
		// Before first null (set res.len)
		if (x > 0 && leadNulls) {
			leadNulls = false;
			res.len = pos + 1;
		}
		// Remove lead nulls
		if (!leadNulls)
			res.digits[pos] = x;
	}
	bigFree(part);
	return res;
}

BigNum bigMod(BigNum first, BigNum second) {
	// optimized a%b=a, if a<b (if not signed)
	if (!first.sign && !second.sign) {	
		if (bigCmpUnsigned(first, second) == -1) { 
			return bigCopy(first);
		}
	}
	// if second == 0
	if (second.len == 0) {
		printf("Division by zero.");
		exit(1);
	}
	
	BigNum part = bigNewNum(second.len + 1, first.base); 
	// Part = 0
	part.len = 0;
	int pos = 0;
	for (pos = first.len - 1; pos >= 0; --pos) {
		// Extend 
		bigExtend(&part, first.digits[pos]);
		unsigned int l = 0, 
			r = part.base, 
			x = 0;
		BigNum	secondx;
		while (l <= r) {
			unsigned int m = (l + r) >> 1;
			// Search x: second*x <= part
			secondx = bigMulOnInt(second, m);
			if (bigCmpUnsigned(secondx, part) <= 0) {
				x = m;
				l = m + 1;
			} else {
				r = m - 1;
			}
			bigFree(secondx);
		}
		secondx = bigMulOnInt(second, x);
		bigMinusUnsignedFromFirst(&part, secondx);
		bigFree(secondx);
	}
	part = removeLeadNulls(part);
	// Select sign and modify result
	// part != 0 !!!
	// a < 0 and b > 0 OR a > 0 and b < 0
	if (part.len != 0 && first.sign ^ second.sign) {
		// part = second - part 
		BigNum old = part;
		part = bigMinusUnsigned(second, part);
		bigFree(old);
	}
	// result sign such as b sign
	part.sign = second.sign;
	return part;
}


BigNum bigPowMod(BigNum first, BigNum second, BigNum module) {
	// Only second >= 0
	if (second.sign) {
		printf("BigPowMod only for b >= 0");
		exit(1);
	}
	// a ^ 0 == 1
	if (second.len == 0) {
		return bigFromInt(1, first.base);
	}
	BigNum res = bigFromInt(1, first.base), 
		cur = bigCopy(first),
		one = bigFromInt(1, first.base),
		st = bigCopy(second),
		old;
	while (st.len != 0) {
		if (!bigIsEven(st)) {
			bigMinusUnsignedFromFirst(&st, one);
			// res *= cur
			old = res;
			res = bigMul(res, cur);
			bigFree(old);
			// res = res % module
			if (module.digits != NULL) {
				old = res;
				res = bigMod(res, module);
				bigFree(old);
			}
		} else {
			// cur = cur * cur
			old = cur;
			cur = bigMul(cur, cur);
			bigFree(old);
			// cur = cur % module
			if (module.digits != NULL) {
				old = cur;
				cur = bigMod(cur, module);
				bigFree(old);
			}
			// st = st / 2
			old = st;
			st = bigDivOnInt(st, 2);
			bigFree(old);
		}
	}
	bigFree(one);
	bigFree(st);
	bigFree(cur);
	return res;
}

// Signed cmp
int bigCmp(BigNum first, BigNum second) {
	int res = bigCmpUnsigned(first, second);
	return res;
	if (!first.sign && !second.sign) 
		return -res;
	if (res == 1 && first.sign && !second.sign) 
		return -res;
	if (res == -1 && !first.sign && second.sign) 
		return -res;
	return res;
}

int bigCmpUnsigned(BigNum first, BigNum second) {
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

