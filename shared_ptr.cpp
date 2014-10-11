#include <iostream>
#include <cassert>
using namespace std;

class Test
{
public:
    ~Test() { cout << "Test destructor" << endl; }
};

template <class T>
class obj
{
public:
    obj(T* t)
        :ptr(t), count(1)
    {}
    T* get() { count++; return ptr; }
    size_t put() { count--;  return count; }
    ~obj() { if (ptr) delete ptr; }
private:
    size_t count;
    T* ptr;
};
template <class T>
class shared_ptr
{
public:
    shared_ptr(T* t)
    {
        pObj = new obj<T>(t);
        assert(pObj);
    }
    shared_ptr(const shared_ptr& p)
    {
        copy(p);
    }
    shared_ptr& operator=(const shared_ptr& p)
    {
        copy(p);
        return *this;
    }
    ~shared_ptr()
    {
        cout << "shared_ptr destrctor" << endl;
        if (pObj->put() == 0) 
            delete pObj;
    }
private:
    obj<T>* pObj;
    void copy(const shared_ptr& p)
    {
        if (pObj == p.pObj)  //指向相同的对象
            return;
        pObj = p.pObj;
        pObj->get();
    }
};
int main(void)
{
    shared_ptr<Test> ptr(new Test()); 
    {
        shared_ptr<Test> pptr(ptr);
        shared_ptr<Test> ppptr(ptr);
    }
    cout << "program end" << endl;
    return 0;
}
