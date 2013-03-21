typedef struct __BigNum {
	int * digits;
	int len;
} BigNum;

BigNum newBigNum(int);
void bigFree(BigNum);

BigNum bigFromFile(const char *);
void bigToFile(const char *, BigNum);
BigNum bigPlus(BigNum, BigNum);
BigNum bigMinus(BigNum, BigNum);
BigNum bigMul(BigNum, BigNum);
BigNum bigCopy(BigNum);
