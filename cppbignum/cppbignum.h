extern "C" {
#include "../cbignum/bignum.h"
};

class Big {
public:
	Big(const char *);
	~Big();
	Big(const Big&);
	Big &operator =(const Big &); 
	const Big operator +(Big&);
	const Big operator -(Big&);
	const Big operator *(Big&);
	Big(BigNum);
	BigNum getNum() const;
	void toFile(const char *);

private:
	BigNum num;
};
