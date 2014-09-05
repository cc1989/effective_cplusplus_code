#include <iostream>
using namespace std;

class A
{
public:
    explicit A(int a) { this->a = a; cout << "A constructor : a = " << a << endl; } 
    A(const A& x) { a = x.a; cout << "A copy constructor : a = " << a << endl; }
    A& operator=(const A& x)
    {
        a = x.a;
        cout << "A operator= : a = " << a << endl;
        return *this;
    }
    const A operator*(const A& x)
    {
        A y(a * x.a); 
        cout << "operator* &y = " << &y << endl;
        return y; //如果是用A(a * x.a),会优化
    }
    friend ostream& operator<<(ostream& cout, const A& x);
    ~A() {cout << "A destructor a = " << a << endl; }
private:
    int a;
};

ostream& operator<<(ostream& cout, const A& x)
{
    cout << x.a << " &x = " << &x;
    return cout;
}

int main(void)
{
    A a(10), b(20);
    //A c(a * b);
    cout << (a * b) << endl;
    return 0;
}
