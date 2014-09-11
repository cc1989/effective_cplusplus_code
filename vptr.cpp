#include <iostream>
#include <cstring>

using namespace std;

class A
{
public:
    virtual void show()
    {
        cout << "A" << endl;
    }
};

class B : public A
{
public:
    void show()
    {
        cout << "B" << endl;
    }
};
int main(void)
{
    B b;
    A &pb= b;
    memset(&b, 0, sizeof(B));
    pb.show();
    return 0;
}
