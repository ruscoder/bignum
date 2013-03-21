struct BigNum {
	int * digits;
	int len;
};

struct BigNum newBigNum(int);
void bigFree(struct BigNum);

struct BigNum bigFromFile(const char *);
void bigToFile(const char *, struct BigNum);
struct BigNum bigPlus(struct BigNum, struct BigNum);
struct BigNum bigMinus(struct BigNum, struct BigNum);
struct BigNum bigMul(struct BigNum, struct BigNum);

