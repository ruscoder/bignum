extern "C" {
#include "../cbignum/bignum.h"
};

class Big {
public:
	Big(const std::string);
	const Big operator +(Big&);
	const Big operator -(Big&);
	Big(struct BigNum);
	struct BigNum getNum();
	void toFile(const std::string);

private:
	struct BigNum num;
};
