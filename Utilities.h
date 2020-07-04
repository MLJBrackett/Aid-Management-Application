#ifndef Utilities_h
#define Utilities_h
#include "Product.h"
#include "iProduct.h"
namespace ama {
	double & operator+=(double& total, const iProduct& prod);
	std::ostream& operator<<(std::ostream& os, const iProduct& ref);
	std::istream& operator>>(istream&in, iProduct& prod);
    iProduct* createInstance(char tag);
}



#endif

