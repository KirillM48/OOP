#include <iostream>
using namespace std;
class Person {
protected:
    string name;
    int age, height;
    string gender;
public:

    Person(string n, int a, int h, string g) : name(n), age(a), height(h), gender(g) {}

    void setName(string n) { name = n; }
    void setAge(int n) { age = n; }
    void setHeight(int n) { height = n; }
    void setGender(char n) {
        cout << "Enter 'f' (female) or 'm' (male): ";
        do {
            switch (n)
            {
            case'f':gender = "female";
                break;
            case'm':gender = "male";
                break;

            default: cout << "Invalid input" << endl;
                break;
            }
        } while (n == 'f' or n == 'm');
    }
};
class Student : public Person {
private:
    int yearStudy;
public:
    static int count;
    Student(string n, int a, int h, string g, int y) :yearStudy(y), Person(n, a, h, g) { ++count; }
    ~Student() { --count; }
    void setYear(int n) { yearStudy = n; }
    void getStudent() const
    {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Height: " << height << endl;
        cout << "Gender: " << gender << endl;
        cout << "Year of study: " << yearStudy << endl;
    }

};
int Student::count = 0;
class Fruit {
protected:
    string name;
    string color;
public:
    Fruit() {}
    Fruit(string n, string c) :name(n), color(c) {}
    ~Fruit() {}
    string getName() { return name; }
    string getColor() { return color; }
};
class Apple :public Fruit {
public:
    Apple() { name = "apple"; color = "red"; }
    Apple(string c) : Fruit("apple", c) { }
    ~Apple() {}
};
class Banana :public Fruit {
public:
    Banana() { name = "banana"; color = "yellow"; }
    ~Banana() {}
};
class GrannySmith :public Apple {
public:
    GrannySmith() { name = "Granny smith apple"; color = "green"; }
    ~GrannySmith() {}
};
int main()
{
    Student st1("Ivan", 20, 67, "male", 2019);
    Student st2("Olya", 19, 60, "female", 2020);
    st2.getStudent();
    cout << Student::count << endl;
    Apple a("red");
    Banana b;
    GrannySmith c;
    cout << "My " << a.getName() << " is " << a.getColor() << endl;
    cout << "My " << b.getName() << " is " << b.getColor() << endl;
    cout << "My " << c.getName() << " is " << c.getColor() << endl;
}