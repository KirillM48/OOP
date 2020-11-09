#include <iostream>
#include <string>
using namespace  std;
//Задание 1
template <class Type>
class Pair1 {
private:
    Type n1;
    Type n2;
public:
    Pair1(const Type& f, const Type& s) : n1(f), n2(s) {}
    Type first()const { return n1; }
    Type second()const { return n2; }
};
//Задание 2
template <class Type1, class Type2>
class Pair {
private:
    Type1 n1;
    Type2 n2;
public:
    Pair(const Type1& f, const Type2& s) : n1(f), n2(s) {}
    Type1 first()const { return n1; }
    Type2 second()const { return n2; }
};
//Задание 3
template <class Type>
class Pair<string, Type> {
private:
    string n1;
    Type n2;
public:
    Pair(const string& f, const Type& s) :n1(f), n2(s) {}
    string first()const { return n1; }
    Type second()const { return n2; }
};
template <class Type>
class StringValuePair : public Pair<string, Type> {
public:
    StringValuePair(const string& f, const Type& s) : Pair<string, Type>(f, s) {}
    string first()const { return Pair<string, Type>::first(); }
    Type second()const { return Pair<string, Type>::second(); }
};
int main()
{
    //Задание 1
    Pair1<int> p1(6, 9);
    cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
    const Pair1<double> p2(3.4, 7.8);
    cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';
    //Задание 2
    Pair<int, double> p3(6, 7.8);
    cout << "Pair: " << p3.first() << ' ' << p3.second() << '\n';
    const Pair<double, int> p4(3.4, 5);
    cout << "Pair: " << p4.first() << ' ' << p4.second() << '\n';
    //Задание 3
    StringValuePair<int> svp("Amazing", 7);
    std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
}