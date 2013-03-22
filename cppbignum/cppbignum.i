%module cppbignum

%{
#define SWIG_FILE_WITH_INIT
#include "cppbignum.h"
%}

class Big {
public:
	Big(const char *);
	~Big();
	Big(const Big&);
	Big(Big &);

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

