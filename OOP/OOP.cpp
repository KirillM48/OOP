#include <iostream>
using namespace std;

class Date{
private:
    int m_day, m_month, m_year;

public:
    Date(int d = 1, int m = 1, int y = 2020) : m_day(d), m_month(m), m_year(y){ }
    int getDay() { return m_day; }
    int getMonth() { return m_month; }
    int getYear() { return m_year; }
    friend ostream& operator<< (ostream& out, const Date& date);
    Date& operator= (const Date& d)
    {
        m_day = d.m_day;
        m_month = d.m_month;
        m_year = d.m_year;
        return *this;
    }
};
ostream& operator<< (ostream& out, const Date& date)
{
    return out << "Date: " << date.m_day << "." << date.m_month << "." << date.m_year << endl;
}
Date itsDate ( const unique_ptr<Date>& d1,  const unique_ptr<Date>& d2) {
    if (d1->getYear() > d2->getYear() ||
        d1->getYear() == d2->getYear() && d1->getMonth() > d2->getMonth() ||
        d1->getYear() == d2->getYear() && d1->getMonth() == d2->getMonth() && d1->getDay() > d2->getDay()) return *d1;
    else return *d2;
}
void revDate(unique_ptr<Date>& d1, unique_ptr<Date>& d2) {
    Date tmp = *d1;
    *d1 = *d2;
    *d2 = tmp;
}
int main()
{
    unique_ptr<Date> today(new Date(16, 11, 2020));
    cout << today->getDay() << endl;
    cout << *today;
    unique_ptr<Date> date(move(today));
    if (today) cout << "today not null" << endl;
    else cout << "today null" << endl;
    if (date) cout << "date not null" << endl;
    else cout << "date null" << endl;
    unique_ptr<Date> date1(new Date(17, 10, 2020));
    unique_ptr<Date> date2(new Date(16, 11, 2020));
    cout << itsDate(date1, date2);
    revDate(date1, date2);
    cout << *date1;
    cout << *date2;
    return 0;
}
