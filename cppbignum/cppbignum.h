extern "C" {
#include "../cbignum/bignum.h"
};

class Big {
public:
	Big(const std::string);
	~Big();
	Big(const Big&);
	Big &operator =(const Big &); 
	const Big operator +(Big&);
	const Big operator -(Big&);
	const Big operator *(Big&);
	Big(BigNum);
	BigNum getNum() const;
	void toFile(const std::string);

private:
	BigNum num;
};
