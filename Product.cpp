#include <cstring>
#include <iostream>
#include <string>
#include <cmath>
#include "ErrorState.h"
#include "Product.h"
#include "Utilities.h"
#include "iProduct.h"
using namespace std;

namespace ama {

	void Product::message(const char* pText) {
		productObj.message(pText);
    }

	bool Product::isClear() const {
		return productObj.operator bool();
	}

    Product::Product(char pType):productType(pType) {
		productSku[0] = '\0';
		productUnit[0] = '\0';
		productAdd = nullptr;
		productQty = 0;
		productReq = 0;
		productPrice = 0.0;
		tax = false;
	}


    Product::Product(const char* prodSku, const char* prodName, const char* prodUnit, double prodPrice, int qtyNeeded, int qtyProd, bool taxable):productType('N') {
		if (prodName != nullptr&&strlen(prodName)<=max_length_name) {
			
			//Product SKU Copy
			strncpy(productSku, prodSku, max_length_sku);
			//Product Name Copy
			if (prodName != nullptr){
				unsigned long length = strlen(prodName);
				productAdd = new char[length];
				for (unsigned int i = 0; i < length; ++i){
					productAdd[i] = prodName[i];
				}
				productAdd[length] = '\0';
			}
			//Product Unit Copy
			strncpy(productUnit, prodUnit, max_length_unit);
			//Product Price Copy
			productPrice = prodPrice;
			//Product Qty Needed Copy
			productReq = qtyNeeded;
			//Product qty avail copy
			productQty = qtyProd;
			//Tax Copy
			tax = taxable;
		}else {
			*this = Product();
		}
	}

	Product::Product(const Product& copy) : productType(copy.productType)  {
        unsigned long length = strlen(copy.productAdd);
		strncpy(productSku, copy.productSku, max_length_sku);
		productSku[max_length_sku] = '\0';
		strncpy(productUnit, copy.productUnit, max_length_unit);
		productUnit[max_length_unit] = '\0';
		productQty = copy.productQty;
		productReq = copy.productReq;
		productPrice = copy.productPrice;
		tax = copy.tax;
		if (copy.productAdd != nullptr) {
			productAdd = nullptr;
			productAdd = new char[length];
			for (unsigned int i = 0; i < length; i++) {
				productAdd[i] = copy.productAdd[i];
			}
			productAdd[strlen(copy.productAdd) + 1] = '\0';
		}else {
			productAdd = nullptr;
		}
	}

	Product::~Product() {
		productAdd = nullptr;
		delete[] productAdd;
	}

    Product &Product::operator = (const Product& copy){
		if (this != &copy) {
			strncpy(productSku, copy.productSku, max_length_sku);
			strncpy(productUnit, copy.productUnit, max_length_unit);
			productQty = copy.productQty;
			productReq = copy.productReq;
			productPrice = copy.productPrice;
			tax = copy.tax;
			if (copy.productAdd != nullptr) {
				unsigned long length = strlen(copy.productAdd);
				productAdd = new char[length];
				for (unsigned int i = 0; i < length; ++i) {
					productAdd[i] = copy.productAdd[i];
				}
				productAdd[length] = '\0';
			}
			else {
				productAdd = nullptr;
			}
		}
		return *this;
	}

	int Product::operator+=(int qty) {
		if (qty >= 0) {
            productQty=qtyAvailable()+qty;
		}
		return productQty;
	}

	bool Product::operator==(const char* sku) const {
		return strcmp(sku, this->productSku) == 0;
	}

	bool Product::operator>(const char* sku) const {
		return strcmp(productSku, sku) > 0;
	}

	bool Product::operator>(const iProduct& other) const {
		return strcmp(productAdd, other.name()) > 0;
	}

	int Product::qtyAvailable() const {
		return productQty;
	}

	int Product::qtyNeeded() const {
		return productReq;
	}

	double Product::total_cost() const {
		double total = productPrice;
		if (tax) {
			total += productPrice * tax_rate;
		}
		return total;
	}

	bool Product::isEmpty() const {
		return (productSku[0] == '\0');
	}
    const char* Product::name() const{
        return productAdd;
    }
	std::istream& Product::read(std::istream& in, bool interactive) {
		char temp;
		if (!interactive) {
            in.getline(productSku, max_length_sku, ',');
            productAdd = new char[max_length_name];
            in.getline(productAdd, max_length_name, ',');
            in.getline(productUnit, max_length_unit, ',');
            in >>productPrice;
            in >>temp;
            in >>tax;
            in >>temp;
            in >>productQty;
            in >>temp;
            in >>productReq;
            return in;
		}
        cout.setf(ios::right);
        cout.width(max_length_label);
        cout<<"Sku: ";
        cin>>productSku;
        cout.width(max_length_label);
        cout<<"Name (no spaces): ";
        productAdd=new char[max_length_name];
        cin>>productAdd;
        cout.width(max_length_label);
        cout<<"Unit: ";
        cin>>productUnit;
        cout.width(max_length_label);
        cout<<"Taxed? (y/n): ";
        cin>>temp;
        if (strncmp(&temp, "y", 1)==0||strncmp(&temp, "Y", 1)==0){
            tax=true;
        }else if(strncmp(&temp, "n", 1)==0||strncmp(&temp, "N", 1)==0){
            tax=false;
        }else{
            in.setstate(ios::failbit);
            productObj.message("Only (Y)es or (N)o are acceptable!");
        }
        if(!in.fail()){
            cout.width(max_length_label);
            cout<<"Price: ";
            cin>>productPrice;
            if(in.fail()){
                in.setstate(ios::failbit);
                productObj.message("Invalid Price Entry!");
            }
        }
        if(!in.fail()){
            cout.width(max_length_label);
            cout<<"Quantity on hand: ";
            cin>>productQty;
            if(in.fail()){
                in.setstate(ios::failbit);
                productObj.message("Invalid Quantity Available Entry!");
            }
        }
        if(!in.fail()){
            cout.width(max_length_label);
            cout<<"Quantity needed: ";
            cin>>productReq;
            if(in.fail()){
                in.setstate(ios::failbit);
                productObj.message("Invalid Quantity Needed Entry!");
            }
        }
        return in;
	}

	std::ostream& Product::write(std::ostream& out, int writeMode) const {
		if (productObj.message() != nullptr) {
			out << productObj.message();
		}
		else if(productAdd==nullptr){
			return out;
		}
		else {
			if (writeMode == write_condensed) {
				out << productType << "," << productSku << "," << productAdd << "," << productUnit << "," << productPrice<< ","<< tax << "," << productQty << "," << productReq;
			}else if (writeMode == write_table) {
				out << " ";
				out.width(max_length_sku);
				out.setf(ios::right);
				out << productSku << " | ";
				out.unsetf(ios::right);
				out.setf(ios::left);
				if (strlen(productAdd) > 16) {
					for (int i = 0; i < 13; i++) {
						out << productAdd[i];
					}
					out << ".";
					out << ".";
					out << ".";
				}
				else {
                    out.width(16);
					out << productAdd;
				}
				out << " | ";
				out.width(10);
				out.setf(ios::left);
				out << productUnit << " | ";
				out.width(7);
				out.setf(ios::right);
                out.setf(ios::fixed);
				out.precision(2);
				out << productPrice << " | ";
				out.width(3);
				out.setf(ios::right);
				if (tax) {
					out << "yes" << " | ";
				}
				else {
					out << "no" << " | ";
				}
				out.width(6);
				out << productQty << " | ";
				out.width(6);
                out << productReq << " |";
				out.unsetf(ios::right);
			}else {
				out.setf(ios::right);
                out.setf(ios::fixed);
                out.precision(2);
				out.width(max_length_label);
				out << "Sku: ";
				out << productSku << endl;
				out.width(max_length_label);
				out << "Name: ";
				out << productAdd << endl;
				out.width(max_length_label);
				out << "Price: ";
				out << productPrice << endl;
				out.width(max_length_label);
				out << "Price after Tax: ";
				out << total_cost() << endl;
				out.width(max_length_label);
				out << "Quantity Available: ";
				out << productQty<<" ";
				out << productUnit << endl;
				out.width(max_length_label);
				out << "Quantity Needed: ";
				out << productReq<<" ";
				out << productUnit << endl;
				out.unsetf(ios::right);
			}
		}
		return out;
	}


}
