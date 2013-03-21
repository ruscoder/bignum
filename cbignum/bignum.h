struct BigNum {
	int * digits;
	int len;
};

struct BigNum bigFromFile(const char *);
void bigToFile(const char *, struct BigNum);
struct BigNum bigPlus(struct BigNum, struct BigNum);
struct BigNum bigMinus(struct BigNum, struct BigNum);

