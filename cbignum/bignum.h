typedef struct __BigNum {
	int *digits;
	char sign;
	int len;
	int allocated;
} BigNum;

BigNum newBigNum(int);
void bigFree(BigNum);

BigNum bigFromFile(const char *);
void bigToFile(const char *, BigNum);
BigNum bigPlus(BigNum, BigNum);
BigNum bigMinus(BigNum, BigNum);
BigNum bigMul(BigNum, BigNum);
BigNum bigDiv(BigNum, BigNum);
BigNum bigMod(BigNum, BigNum);
int bigCmp(BigNum, BigNum);


BigNum bigCopy(BigNum);
void bigExtend(BigNum *, int);
void bigVersion(); 
void bigOut(BigNum); 

