#include "Utilities.h"
#include "Product.h"
#include "Perishable.h"
namespace ama {
	double& operator+=(double& total, const iProduct& prod) {
		return total += (prod.total_cost())*(prod.qtyAvailable());
	}
	std::ostream &operator<<(std::ostream &os, const iProduct &prod) {
		return prod.write(os,2);
	}
	std::istream &operator>>(std::istream &is, iProduct &prod) {
		return prod.read(is, true);
	}
    iProduct* createInstance(char tag){
        iProduct *pe = nullptr;
        if (tag=='N'||tag=='n'){
            pe = new Product();
        }else if (tag=='P'||tag=='p'){
            pe = new Perishable();
        }
        return pe;
    }
}
