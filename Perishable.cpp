#include "Perishable.h"
#include <iostream>

using namespace std;

namespace ama{
    Perishable::Perishable(char pType) : Product(pType){
        //Product('P');
    }
    
    std::ostream& Perishable::write(std::ostream& out, int writemode)const{
        Product::write(out, writemode);
        if (!isClear()&&!isEmpty()){
            if(writemode==write_human){
                out.width(max_length_label);
                out.setf(ios::right);
                out<<"Expiry Date: ";
                out<<expiryDate<<endl;
            }else if (writemode==write_table){
                out<<" "<<expiryDate<<" |";
            }else{
                out<<","<<expiryDate;
            }
        }
        return out;
    }
    
    std::istream& Perishable::read(std::istream& in, bool interactive){
        Product::read(in, interactive);
        Date tempDate;
        if (interactive){
            cout.width(max_length_label);
            cout.setf(ios::right);
            cout<<"Expiry date (YYYY/MM/DD): ";
            in>>tempDate;
            if(tempDate.isGood()){
                expiryDate=tempDate;
            }else{
                cin.setstate(ios::failbit);
                if (tempDate.status()==error_year){
                    productObj.message("Invalid Year in Date Entry");
                }else if (tempDate.status()==error_mon){
                    productObj.message("Invalid Month in Date Entry");
                }else if (tempDate.status()==error_day){
                    productObj.message("Invalid Day in Date Entry");
                }else if (tempDate.status()==error_input){
                    productObj.message("Invalid Date Entry");
                    in.ignore(500000000000,'\n');
                }
            }
        }else{
            in.ignore();
            tempDate.read(in);
            expiryDate=tempDate;
            in.ignore();
        }
        return in;
    }
}
