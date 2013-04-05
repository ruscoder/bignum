%module cppbignum

%{
#define SWIG_FILE_WITH_INIT
#include "cppbignum.h"
%}

class Big {
public:
	Big(const char *);
	~Big();
	Big(const Big &);
	Big &operator =(const Big &); 
	const Big operator +(Big &);
	const Big operator -(Big &);
    const Big operator -(); 
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
