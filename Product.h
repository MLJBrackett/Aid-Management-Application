#ifndef Product_h
#define Product_h
#include "ErrorState.h"
#include "iProduct.h"

namespace ama {
    class Product : public iProduct{
        const char productType;
		char productSku[max_length_sku + 1];
		char productUnit[max_length_unit + 1];
		char* productAdd;
		int productQty;
		int productReq;
		double productPrice;
		bool tax;
	protected:
        ErrorState productObj;
		void message(const char* pText);
		bool isClear() const;
	public:
        Product(char pType = 'N');
		Product(const char* prodSku, const char* prodName, const char* prodUnit, double prodPrice = 0, int qtyNeeded = 0, int qtyProd = 0, bool taxable = true);
		Product(const Product& copy);
		~Product();
		Product& operator = (const Product& copy);
		int operator+=(int cnt);
		bool operator==(const char* sku) const;
		bool operator>(const char* sku) const;
		bool operator>(const iProduct& other) const;
		int qtyAvailable() const;
		int qtyNeeded() const;
		double total_cost() const;
		bool isEmpty() const;
        const char* name() const;
		std::istream& read(std::istream& in, bool interactive);
		std::ostream& write(std::ostream& out, int writeMode) const;
	};

}



#endif
