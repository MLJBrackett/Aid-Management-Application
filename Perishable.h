#ifndef Perishable_h
#define Perishable_h
#include "Product.h"
#include "Date.h"


namespace ama {
        class Perishable : public Product {
            Date expiryDate;
        public:
            Perishable(char pType = 'P');
            std::ostream& write(std::ostream& out, int writemode) const;
            std::istream& read(std::istream& in,bool interactive);
    };
}



#endif /* Perishable_h */
