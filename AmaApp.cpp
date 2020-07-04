#include <cstring>
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

#include "AmaApp.h"
#include "Utilities.h"

using namespace std;

namespace ama{
    AmaApp::AmaApp(const char* filename){
        strncpy(m_filename, filename, 256);
        m_products[0]= nullptr;
        m_noOfProducts=0;
        loadProductRecords();
    }
    
    AmaApp::~AmaApp(){
        for (int i = 0; i<m_noOfProducts;i++){
            delete m_products[i];
            m_products[i]=nullptr;
        }
    }
    
    int AmaApp::run(){
        int selection;
        int done=0;
        cin.setstate(ios::goodbit);
        while(done==0){
            selection = menu();
            switch (selection){
                case 1:
                    loadProductRecords();
		    listProducts();
                    cout<<endl;
                    pause();
                    break;
                case 2:
                    char charSku[max_length_sku+1];
                    cout<<"Please enter the product SKU: ";
                    cin>>charSku;
                    cout<<endl;
                    if(find(charSku)!=nullptr){
                        find(charSku)->write(cout, write_human);
                        cout<<endl;
                    }else{
                        cout<<"No such product!"<<endl;// Think I fixed
                    }
                    cin.ignore();
                    pause();
                    break;
                case 3:
                    addProduct('N');
                    break;
                case 4:
                    addProduct('P');
                    break;
                case 5:
                    cout<<"Please enter the product SKU: ";
                    cin>>charSku;
                    cout<<endl;
                    if(find(charSku)!=nullptr){
                        addQty(find(charSku));
                        cout<<endl;
                    }else{
                        cout<<"No such product!"<<endl;
                        cout<<endl;
                    }
                    break;
                case 6://Do nothing
                    break;
                case 7://Do nothing
                    break;
                case 0:
                    cout<<"Goodbye!"<<endl;
                    done = 1;
                    break;
                default:
                    cout<<"~~~Invalid selection, try again!~~~"<<endl;
                    cin.ignore();
                    pause();
                    break;
            }
        }
        return 0;
    }
    
    void AmaApp::pause() const{
        cout<<"Press Enter to continue...";
        cin.ignore(5000,'\n');
        cout<<endl;
    }
    
    int AmaApp::menu() const{
        int selection;
        cout<<"Disaster Aid Supply Management Program"<<endl;
        cout<<"--------------------------------------"<<endl;
        cout<<"1- List products"<<endl;
        cout<<"2- Search product"<<endl;
        cout<<"3- Add non-perishable product"<<endl;
        cout<<"4- Add perishable product"<<endl;
        cout<<"5- Add to product quantity"<<endl;
        cout<<"6- Delete product"<<endl;
        cout<<"7- Sort products"<<endl;
        cout<<"0- Exit program"<<endl;
        cout<<"> ";
        cin>>selection;
        if(selection>=0&&selection<=7){
            return selection;
        }
        return -1;
    }
    
    void AmaApp::loadProductRecords(){
        int readIndex=0;
        char tag;
        ifstream file;
        file.open(m_filename,ios::in);
        if(file.is_open()){
            while(file){
                file>>tag;
                if (createInstance(tag)!=nullptr){
                    m_products[readIndex]=createInstance(tag);
                    file.ignore();
                    m_products[readIndex]->read(file,false);
                    readIndex++;
                }
            }
            m_noOfProducts=readIndex-1;
        }
        file.close();
    }
    
    void AmaApp::saveProductRecords() const{
        ofstream file;
        file.open(m_filename,ios::out);
        for (int i =0; i<m_noOfProducts; i++){
            m_products[i]->write(file, write_condensed);
            file<<endl;
        }
    }
    
    void AmaApp::listProducts() const{
        double total=0;
        cout<<"------------------------------------------------------------------------------------------------"<<endl;
        cout<<"| Row |     SKU | Product Name     | Unit       |   Price | Tax |   QtyA |   QtyN | Expiry     |"<<endl;
        cout<<"|-----|---------|------------------|------------|---------|-----|--------|--------|------------|"<<endl;
        for (int i=0; i<m_noOfProducts;i++){
            cout.setf(ios::right);
            cout<<"|";
            cout.width(4);
            cout<<(i+1);
            cout<<" |";
            cout.unsetf(ios::right);
            m_products[i]->write(cout, write_table);
            cout<<"\n";
            total+=m_products[i]->total_cost()*m_products[i]->qtyAvailable();
        }
        cout<<"------------------------------------------------------------------------------------------------"<<endl;
        cout<<"|                                                      Total cost of support ($): | ";
        cout.width(10);
        cout.precision(2);
        cout.setf(ios::right);//Maybe Remove?
        cout.setf(ios::fixed);
        cout<<total<<" |"<<endl;
        cout.unsetf(ios::right);
        cout.unsetf(ios::fixed);
        cout<<"------------------------------------------------------------------------------------------------"<<endl;
        cin.ignore();
    }
    
    iProduct* AmaApp::find(const char* sku) const{
        for (int i=0;i<m_noOfProducts;i++){
            if(*m_products[i]==sku){
                return m_products[i];
            }
        }
        return nullptr;
    }
    
    void AmaApp::addQty(iProduct* product){
        int qty;
        product->write(cout, write_human);
        cout<<endl;
        cout<<endl;
        cout<<"Please enter the number of purchased items: ";
        cin>>qty;
        if(cin.fail()){
            cout<<"Invalid quantity value!"<<endl;
            cin.clear();
            cin.ignore(500000000000,'\n');
        }else{
            if(qty<=(product->qtyNeeded()-product->qtyAvailable())){
                product->operator+=(qty);
                saveProductRecords();
                cout<<endl;
                cout<<"Updated!"<<endl;
            }else{
                cout<<"Too many items; only "<< product->qtyNeeded()-product->qtyAvailable() <<" is needed. Please return the extra "<< qty-(product->qtyNeeded()-product->qtyAvailable()) <<" items."<<endl;
                product->operator+=(qty-(qty-(product->qtyNeeded()-product->qtyAvailable())));
                saveProductRecords();
                cout<<endl;
                cout<<"Updated!"<<endl;
            }
        }
    }
    
    void AmaApp::addProduct(char tag){
        m_products[m_noOfProducts]=createInstance(tag);
        if(m_products[m_noOfProducts]!=nullptr){
            m_products[m_noOfProducts]->read(cin, true);
            if(cin.fail()){
                cout<<endl;
                cout<<*m_products[m_noOfProducts]<<endl;
                cout<<endl;
                cin.ignore(100000000, '\n');
                cin.clear();
                cin.ignore(500000000000,'\n');
            }else{
                m_noOfProducts++;
                saveProductRecords();
                cout<<endl;
                cout<<"Success!"<<endl;
                cout<<endl;
            }
        }
    }
    
}
