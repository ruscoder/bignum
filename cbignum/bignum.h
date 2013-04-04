typedef struct __BigNum {
	int *digits;
	char sign;
	int len;
	int allocated;
} BigNum;

BigNum newBigNum(int);
BigNum bigCopy(BigNum);
void bigFree(BigNum);

BigNum bigFromFile(const char *);
void bigToFile(const char *, BigNum);

BigNum bigNegative(BigNum);

BigNum bigPlusUnsigned(BigNum, BigNum);
BigNum bigPlus(BigNum, BigNum);

BigNum bigMinusUnsignedFromLargest(BigNum, BigNum);
BigNum bigMinusUnsigned(BigNum, BigNum);
BigNum bigMinus(BigNum, BigNum);

BigNum bigMul(BigNum, BigNum);
BigNum bigMulOnInt(BigNum, int);

BigNum bigDiv(BigNum, BigNum);
BigNum bigDivOnInt(BigNum, int);

BigNum bigMod(BigNum, BigNum);

int bigCmp(BigNum, BigNum);
int bigCmpUnsigned(BigNum, BigNum);


void bigExtend(BigNum *, int);
void bigVersion(); 
void bigOut(BigNum); 

