#include <algorithm>
#include <iostream>
#include <cstring>
#include <hash_map>

class Bitmap{
	public:
		Bitmap();
		Bitmap(int val);
		Bitmap(const Bitmap &r);
		Bitmap& operator= (const Bitmap &r);
		int Get() const;
	private:
		int a;
};
class GamePlayer;  //类的声明
class xxxx;
class Widget
{
	public:
		explicit Widget(int val);
		~Widget();
		Widget(const Widget &r);
		Widget &operator= (Widget const &r);
		static GamePlayer* GetGamePlayer();
		void swap(Widget &r);
		xxxx* GetXXXX();
	private:
		Bitmap *pb;  //处理包含Widget内的所有数据,这样在交换数据时可以不用整个交换数据，而只要交换指针就可以了
};
namespace std
{
	template <>
	void swap<Widget>(Widget &a, Widget &b)
	{
		std::cout << "swap<Widget> call" << std::endl;
		a.swap(b);	
	}
}
class GamePlayer
{
	private:
		static const int NumTruns = 10; //这个只是声明
		//int scores[NumTurns];
		mutable char name[NumTruns];
	public:
		GamePlayer(char *name);
		//返回对象，而不是返回引用
		GamePlayer operator* (GamePlayer const&r);
		GamePlayer(GamePlayer const &r);
		GamePlayer& operator= (GamePlayer const &r);
		const char& operator[] (unsigned position) const;
		char& operator[] (unsigned position);
		void GetName(char *name) const;
		void ShowName() const;
		~GamePlayer();
		GamePlayer();
};

class UseGP
{
	public:
		GamePlayer& GetGP();
		explicit UseGP(int lVal);
		operator int() const;
		/*virtual*/ void Show();
		const int& GetVal() const;
	private:
		int val;
		UseGP& operator= (UseGP const &r);  //只声明，不定义，这样就屏蔽了赋值函数
		UseGP(UseGP const &r);  //只声明，不定义，这样就屏蔽了拷贝构造函数
};
class HUseGP : public UseGP
{
	public:
		//using UseGP::Show;  //让父类的函数Show在子类作用域中可见
		HUseGP(int lVal);
		void Show(int lVal);
};

template <typename T>
class Shape
{
	public:
		T a;
		virtual void draw() = 0;  //函数用const和不用const修饰都是纯虚函数，不同的是加了const会要求子类实现时也要加const，导致该函数不能修改成员变量

};

template <typename T>
class Rectangle : public Shape<T>
{
	public:
		using Shape<T>::a;  //声明a出现在templated的父类中
		void draw();	
};
template <typename T>
class Ellipse : public Shape<T>
{
	public:
		using Shape<T>::a;
		void draw();	
};

template <typename T>
class BPtr
{
	public:
		BPtr(T *lPtr = NULL);
		~BPtr();
		T *get();
		bool put();
	private:
		T *ptr;
		int count;
};
template <typename T>
class SmartPtr
{
	public:
		explicit SmartPtr(T *realPtr);  //以内置的指针完成初始化
		template <typename U>
		SmartPtr<T>& operator=(SmartPtr<U> & r);
		template <typename U>
		SmartPtr(SmartPtr<U> const& r);
		BPtr<T>* GetPtr();
		~SmartPtr();
	private:
		BPtr<T> *imPtr;
};
//template元编程
template<unsigned n>
struct Factorial
{
	enum{value = n * Factorial<n - 1>::value};
};
template<>
struct Factorial<0>
{
	enum{value = 1};
};
//仿函数
struct CharLess 
{
	public:
		bool operator()(const char*  _Left, const char* _Right) const
		{
			return (strcmp(_Left, _Right) == 0);
		}
};
//产生hash
struct CharHash
{
	size_t operator()(const char* str) const
	{
		return __gnu_cxx::__stl_hash_string(str);	
	}
};

//测试__STL_STATIC_TEMPLATE_MEMBER_BUG
template <typename T>
class testClass
{
	public:
		static int _data;
};
//测试__STL_CLASS_PARTIAL_SPECIALIZATION
template <class I, class O>
class testClass2
{
	public:
	testClass2(){std::cout << "I, O" << std::endl;}
};
//特殊化
template <class T>
class testClass2<T*, T*>
{
	public:
	testClass2(){std::cout << "T*, T*" << std::endl;}
};
template <class T>
class testClass2<const T*, T*>
{
	public:
	testClass2(){std::cout << "const T*, T*" << std::endl;}
};
class MyAlloc
{
};
template <class T, class Alloc = MyAlloc>
class MyVector
{
	public:
		void swap(MyVector<T, Alloc>&){std::cout << "swap()" << std::endl;}
};

namespace std
{
//#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER
template <class T, class Alloc>
void swap(MyVector<T, Alloc>& x, MyVector<T,	Alloc>& y){
	x.swap(y);
}
//#endif
}
class A
{
    public:
            A() { std::cout << "A default constructor" << std::endl; }
                A(const A& a) { std::cout << "A copy constructor" << std::endl; }
                    A& operator=(const A& a) { std::cout << "a operator=" << std::endl; }
};
class UseA
{
    public:
            UseA(const A& ca);
    private:
                A a;
};
