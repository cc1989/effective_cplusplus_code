#include <iostream>
using namespace std;

class A
{
public:
    A(int a) { this->a = a; }
    operator int() const  //隐式类型转化
    {
        return a; 
    }
private:
    int a;
};
int main(void)
{
    A a = 10;
    cout << a << endl;  //用到了隐式类型转化
    return 0;
}
