#ifndef AmaApp_h
#define AmaApp_h

#include "iProduct.h"

namespace ama{
    class AmaApp{
        char m_filename[256];
        iProduct* m_products[100];
        int m_noOfProducts;
    public:
        AmaApp(const char* );
        ~AmaApp();
        int run();
    private:
        void pause() const;
        int menu() const;
        void loadProductRecords();
        void saveProductRecords() const;
        void listProducts() const;
        iProduct* find(const char* sku) const;
        void addQty(iProduct* product);
        void addProduct(char tag);
    };
}


#endif /* AmaApp_h */
