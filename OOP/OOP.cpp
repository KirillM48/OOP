#include <iostream>
using namespace std;
const double pi = 3.1415926;
//Задание 1
class Figura {
protected:
    double s;
public:
    Figura() {}
    virtual void area() = 0;
    virtual ~Figura();
};
class Parallelogram : public Figura {
protected:
    int length;
    int height;
public:
    Parallelogram(int a) :length(a) { height = 0; }
    Parallelogram(int a, int b) : length(a), height(a) {}
    void area() { s = length * height; }
};
class Circle :public Figura {
private:
    int rad;
public:
    Circle(int a) : rad(a) {}
    void area() { s = pi * rad * rad; }
};
class Rectangle :public Parallelogram {
private:
    int width;
public:
    Rectangle(int a, int b) :width(a), Parallelogram(b) {}
    void area() { s = length * width; }
};
class Square :public Parallelogram {
public:
    Square(int a) :Parallelogram(a) {}
    void area() { s = length * length; }
};
class Rhombus :public Parallelogram {
public:
    Rhombus(int a, int b) : Parallelogram(a, b) {}
    void area() { s = length * height; }
};
//Задание 2
class Car {
protected:
    string company;
    string model;
public:
    Car() {}
    Car(string a, string b) :company(a), model(b) { cout << "Model: " << model << endl << "Company: " << company << endl; }
};
class PassengerCar :public Car {
public:
    PassengerCar() {}
    PassengerCar(string a, string b) : Car(a, b) { cout << "Model: " << model << endl << "Company: " << company << endl; }
};
class Bus :public Car {
public:
    Bus(string a, string b) : Car(a, b) { cout << "Model: " << model << endl << "Company: " << company << endl; }
};
class Minivan :public PassengerCar, Bus {
public:
    Minivan(string a, string b) : Bus(a, b) { cout << "Model: " << Bus::model << endl << "Company: " << Bus::company << endl; }
};
//Задание 3
class Fraction {
private:
    int ntr, dtr;
public:
    Fraction(int a, int b) {
        try {
            if (b == 0) throw std::runtime_error("Invalid fraction! Determinator = 0");
        }
        catch (std::runtime_error& e)
        {
            cout << e.what() << endl;;
        }
        ntr = a;
        dtr = b;
    }
    ~Fraction() { }
    friend Fraction operator+ (const Fraction& f1, const Fraction& f2);
    friend Fraction operator- (const Fraction& f1, const Fraction& f2);
    friend Fraction operator* (const Fraction& f1, const Fraction& f2);
    friend Fraction operator/ (const Fraction& f1, const Fraction& f2);
    Fraction operator- () const { return Fraction(-ntr, -dtr); }
    friend bool operator== (const Fraction& f1, const Fraction& f2);
    friend bool operator!= (const Fraction& f1, const Fraction& f2);
    friend bool operator< (const Fraction& f1, const Fraction& f2);
    friend bool operator> (const Fraction& f1, const Fraction& f2);
    friend bool operator<= (const Fraction& f1, const Fraction& f2);
    friend bool operator>= (const Fraction& f1, const Fraction& f2);
    void get() { cout << ntr << "/" << dtr << endl; }

};
Fraction operator+ (const Fraction& f1, const Fraction& f2) {
    if (f1.dtr == f2.dtr)
        return Fraction(f1.ntr + f2.ntr, f1.dtr);
    else return Fraction(f1.ntr * f2.dtr + f2.ntr * f1.dtr, f1.dtr * f2.dtr);
}
Fraction operator- (const Fraction& f1, const Fraction& f2) {
    if (f1.dtr == f2.dtr)
        return Fraction(f1.ntr + f2.ntr, f1.dtr);
    else return Fraction(f1.ntr * f2.dtr - f2.ntr * f1.dtr, f1.dtr * f2.dtr);
}
Fraction operator* (const Fraction& f1, const Fraction& f2) {
    return Fraction(f1.ntr * f2.ntr, f1.dtr * f2.dtr);
}
Fraction operator/ (const Fraction& f1, const Fraction& f2) {
    return Fraction(f1.ntr * f2.dtr, f1.dtr * f2.ntr);
}
bool operator== (const Fraction& f1, const Fraction& f2) {
    return(f1.ntr == f2.ntr && f1.dtr == f2.dtr);
}
bool operator!= (const Fraction& f1, const Fraction& f2) {
    return !(f1 == f2);
}
bool operator< (const Fraction& f1, const Fraction& f2) {
    if (f1.dtr == f2.dtr) return f1.ntr < f2.ntr;
    else return f1.ntr * f2.dtr < f2.ntr* f1.dtr;
}
bool operator<= (const Fraction& f1, const Fraction& f2) {
    if (f1.dtr == f2.dtr) return f1.ntr <= f2.ntr;
    else return f1.ntr * f2.dtr <= f2.ntr * f1.dtr;
}
bool operator> (const Fraction& f1, const Fraction& f2) {
    return !(f1 < f2);
}
bool operator>= (const Fraction& f1, const Fraction& f2) {
    return !(f1 <= f2);
}
// Задание 4
enum suits { diamonds, clubs, hearts, peaks };
enum values { one = 1, two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7, eight = 8, nine = 9, ten = 10, jack = 10, queen = 10, king = 10, ace = 1 };
class Card {
private:
    suits suit;
    values val;
    bool position;
public:
    Card() {}
    ~Card() {}
    void Flip() { position = !position; }
    int GetValue() { return suit; }


};
int main()
{
    Car a("Company 1", "model 1");
    PassengerCar b("Company 2", "model 2");
    Bus c("Company 3", "model 3");
    Minivan d("Company 4", "model 4");
    Fraction f1(3, 7);
    Fraction f2(1, 9);
    Fraction f3 = f1 + f2;
    f3.get();
    f3 = f2 - f1;
    f3.get();
    f3 = f2 * f1;
    f3.get();
    f3 = f1 / f2;
    f3.get();
    if (f1 != f2) cout << "fraction are not equale" << endl;
    if (f1 == f2) cout << "fraction are equale" << endl;
    if (f1 > f2) cout << "fraction f1 is greater fraction f2" << endl;
    if (f1 < f2) cout << "fraction f1 is less fraction f2" << endl;
    if (f1 >= f2) cout << "fraction f1 is greater or equale fraction f2" << endl;
    if (f1 <= f2) cout << "fraction f1 is less or equale fraction f2" << endl;
}