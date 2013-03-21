struct BigInt {
	int * digits;
	int len;
};

struct BigInt bigFromFile(const char *);
void bigToFile(const char *, struct BigInt);
