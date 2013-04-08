extern "C" {
#include "../cbignum/bignum.h"
};

class Big {
public:
	Big(const char *);
	Big(const char *, bool);
	~Big();
	Big(const Big &);
	Big &operator =(const Big &); 
	const Big operator +(Big &);
	const Big operator -(Big &);
	Big operator -();
	const Big operator *(Big &);
	const Big operator /(Big &);
	const Big operator %(Big &);
	const Big operator ^(Big &);

	bool operator ==(const Big &);
	bool operator <(const Big &);
	bool operator >(const Big &);
	bool operator <=(const Big &);
	bool operator >=(const Big &);

	Big(const BigNum &);
	const BigNum& getNum() const;
	void toFile(const char *);
	void out();
private:
	BigNum num;
};
