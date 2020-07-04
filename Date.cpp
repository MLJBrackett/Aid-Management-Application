#include "Date.h"
#include <iostream>
using namespace std;
namespace ama {
   Date temp; 
    int Date::mdays(int year, int month)const{
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = month >= 1 && month <= 12 ? month : 13;
        mon--;
        return days[mon] + int((mon == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }
    
    void Date::status(int newStatus){
        Status=newStatus;
    }
    
    Date::Date(){
        year=0000;
        month=00;
        day_of_month=0;
        status(0);
    }
    
    Date::Date(int u_year, int u_month, int u_day){
        if(u_year<min_year||u_year>max_year){
            *this=Date();
            status(1);
        }else if (u_month<1||u_month>12){
            *this=Date();
            status(2);
        }else if (u_day>mdays(u_year, u_month)||u_day<=0){
            *this=Date();
            status(3);
        }else{
            year=u_year;
            month=u_month;
            day_of_month=u_day;
            status(0);
        }
    }
    
    int Date::status() const{
        return Status;
    }
    
    void Date::clearError(){
        status(0);
    }
    
    bool Date::isGood() const{
        return (year>=min_year&&year<=max_year)&&(month<=12&&month>=1)&&(day_of_month<=mdays(year,month))&&(Status==no_error);
    }
    
    Date& Date::operator+=(int days){
        if (!isGood()){
            status(4);
        }else if (day_of_month+days<=mdays(year, month)&&(day_of_month+days)<0){
            status(4);
        }else{
            day_of_month+=days;
        }
        return *this;
    }
    
    Date& Date::operator++(){
        if(!isGood()){
            status(4);
        }else if ((1+day_of_month)>mdays(year, month)&&(1+day_of_month)<0){
            status(4);
        }else{
            day_of_month++;
        }
        return *this;
    }
    
    Date& Date::operator++(int day){
        if (day<=mdays(year,month)){
           temp = *this;
            *this+=1;
            return temp;
        }else{
            return *this;
        }
    }
    
    Date& Date::operator+(int day)const{
       	temp = *this;
            if (!isGood()){
                temp.status(4);
            }else if (day_of_month+(day+1)>mdays(year, month)){
                temp.status(4);
            }else{
                temp.day_of_month+=day;
            }
            return temp;
        }
    
    bool Date::operator==(const Date& rhs)const{
        return (rhs.year==year)&&(rhs.month==month)&&(rhs.day_of_month==day_of_month);
    }
    
    bool Date::operator!=(const Date &rhs)const{
        return (day_of_month != rhs.day_of_month) || (month != rhs.month) || (year != rhs.year);
    }
    
    bool Date::operator<(const Date& rhs)const{
        return (day_of_month<rhs.day_of_month)||(month<rhs.month)||(year<rhs.year);
    }
    
    bool Date::operator>(const Date& rhs)const{
        return (day_of_month>rhs.day_of_month)||(month>rhs.month)||(year>rhs.year);
    }
    
    bool Date::operator<=(const Date& rhs) const{
        return (day_of_month<=rhs.day_of_month)&&(month<=rhs.month)&&(year<=rhs.year);
    }
    bool Date::operator>=(const Date& rhs) const{
        return (day_of_month >= rhs.day_of_month)&&(month>=rhs.month)&&(year>=rhs.year);
    }
    
    std::istream& Date::read(std::istream& is){
        char character;
        is >> year >> character >> month >> character >> day_of_month;
        if (is.fail()){
            *this=Date();
            status(5);
        }
        else{
            *this=Date(year, month, day_of_month);
        }
        return is;
    }
    
    std::ostream& Date::write(std::ostream& os)const{
        char character = '/';
        os.fill('0');
        os.width(4);
        os << year << character;
        os.width(2);
        os.unsetf(ios::left);
        os.fill('0');
        os << month << character;
        os.width(2);
        os.unsetf(ios::left);
        os.fill('0');
        os << day_of_month;
        os.fill(' ');
        return os;
    }
    
    std::istream& operator>>(std::istream& is, Date& txtDate) {
        return txtDate.read(is);
    }
    
    std::ostream& operator<<(std::ostream& ostr, const Date& txtDate){
        return txtDate.write(ostr);
    }
}
