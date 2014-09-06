#include <iostream>
using namespace std;

class A
{
public:
    A()
    :a(5)
    {
    }
    virtual void show()
    {
        a = 10;
        cout << "A show a = " << a << endl; 
    }
    int get()
    {
        return a; 
    }
private:
    int a;
};

class B : public A
{
public:
    virtual void show()   
    {
        //A::show();  //正确的调用父类的函数，static_cast<A>(*this).show()这种方式只是改变了父类的一个副本而已
        static_cast<A>(*this).show();
        cout << "B show a = "  << get() << endl;
    }
};
int main(void)
{
    B b;
    A *pa = &b;
    pa->show();
    return 0;
}
