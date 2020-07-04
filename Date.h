#ifndef Date_h
#define Date_h
#include <iostream>
namespace ama {
    const int min_year=2019;
    const int max_year=2028;
    const int no_error=0;
    const int error_year=1;
    const int error_mon=2;
    const int error_day=3;
    const int error_invalid_operation=4;
    const int error_input=5;
    class Date{
        int year;
        int month;
        int day_of_month;
        int Status;
        int mdays(int u_year,int u_month) const;
        void status(int newStatus);
    public:
        Date();
        Date(int u_year,int u_month,int u_day);
        int status() const;
        void clearError();
        bool isGood() const;
        Date& operator+= (int days);
        Date& operator++ ();
        Date& operator++ (int);
        Date& operator+ (int) const;
        bool operator==(const Date& rhs)const;
        bool operator!=(const Date& rhs)const;
        bool operator<(const Date& rhs)const;
        bool operator>(const Date& rhs)const;
        bool operator<=(const Date& rhs)const;
        bool operator>=(const Date& rhs)const;
        std::istream& read(std::istream& is = std::cin);
        std::ostream& write(std::ostream& os = std::cout)const;
    };
    std::istream& operator>>(std::istream& is, Date&);
    std::ostream& operator<<(std::ostream& ostr, const Date&);
}

#endif /* Date_h */
