#include "test.h"
#include <iostream>
#include <vector>
#include <string.h>
#include <exception>
#include <stdexcept>
#include <typeinfo>
#include <memory>
#include <tr1/memory>


template <typename T>
bool BPtr<T>::put()
{
	count--;
	if (count == 0)
	{
		delete ptr;
		return false;
	}
	return true;
}
template <typename T>
T* BPtr<T>::get()
{
	count++;
	return ptr;
}
template <typename T>
BPtr<T>::~BPtr()
{
}
template <typename T>
BPtr<T>::BPtr(T *lPtr)
	:ptr(lPtr), count(0)
{}
template <typename T>
template <typename U>
SmartPtr<T>::SmartPtr(SmartPtr<U> const& r)
{
	imPtr = (BPtr<T> *)r.GetPtr();
	imPtr->get();
}
template <typename T>
BPtr<T>* SmartPtr<T>::GetPtr()
{
	return imPtr;
}
template <typename T>
template <typename U>
SmartPtr<T>& SmartPtr<T>::operator=(SmartPtr<U> & r)
{
	if (imPtr != (BPtr<T> *)r.GetPtr())
	{
		SmartPtr<T> temp(*this);	
		imPtr->put();
		imPtr = (BPtr<T> *)r.GetPtr();
		//imPtr = (BPtr<T> *)r.imPtr;
		imPtr->get();
	}
	return *this;
}
template <typename T>
SmartPtr<T>::SmartPtr(T *realPtr)
{
	imPtr = new BPtr<T>(realPtr);
	imPtr->get();
}
template <typename T>
SmartPtr<T>::~SmartPtr()
{
	if (imPtr->put() == false)
		delete imPtr;
}

template <typename T>
void Rectangle<T>::draw()
{
	a = 1;  
	std::cout << "a = " << a << std::endl;
}
template <typename T>
void Ellipse<T>::draw()
{
	a = 2;
	std::cout << "a = " << a << std::endl;
}

//纯虚函数也可以被定义
template <typename T>
void Shape<T>::draw()
{
}
xxxx* Widget::GetXXXX()
{
	return NULL;
}
const int& UseGP::GetVal() const
{
	return val;
}
int Bitmap::Get() const
{
	return a;
}
Bitmap::Bitmap()
	: a(0)
{}
Bitmap& Bitmap::operator= (const Bitmap &r)
{
	a = r.a;
	return *this;
}
Bitmap::Bitmap(const Bitmap &r)
	: a(r.a)
{}
Bitmap::Bitmap(int val)
{
	a = val;
}
UseGP::operator int() const  //显示的类型转换
{
	std::cout << val << " operator int" << std::endl;
	return val;
}
GamePlayer* Widget::GetGamePlayer()
{
	return (new GamePlayer("wgp"));
}
Widget::Widget(int val)
{
	pb = new Bitmap(val);
	std::cout << val << " : Widget constructor : " << pb << std::endl;
}
void Widget::swap(Widget &r)
{
	//using std::swap;
	std::swap(pb, r.pb);
}
Widget::~Widget()
{
	std::cout << pb->Get() << " : Widget deconstructor " << pb << std::endl;
	if (pb)
		delete pb;
}
Widget::Widget(const Widget &r)
{
	std::cout << "Widget copy constructor : ";
	pb = new Bitmap(r.pb->Get());
	std::cout << pb->Get() << "(" << pb << ")" << " = " << r.pb->Get() << "(" << r.pb << ")" << std::endl;
}
Widget& Widget::operator= (Widget const &r)
{
	//copy and swap策略保证异常安全性
	Widget temp(r);  //用swap处理同一对象的情况
	//using std::swap;
	std::swap(*this, temp);
	std::cout << temp.pb->Get() << "(" << temp.pb << ")" << " = " << pb->Get() << "(" << pb << ")" << std::endl;
	return *this;
}
HUseGP::HUseGP(int lVal)
	: UseGP(lVal)
{}
GamePlayer::GamePlayer()
{}
GamePlayer::~GamePlayer()
{
	std::cout << name << " : GamePlayer deconstructor : ";
	std::overflow_error oe("overflow");
	try
	{
		throw oe;
	}
	catch (std::exception &ex)	
	{
		std::cout << "catch exception : " << ex.what() <<  std::endl;	
	}
}
UseGP::UseGP(int lVal)
	:val(lVal)
{
	std::cout << "UseGP instructor : " << val << std::endl;
	Show();
}
void HUseGP::Show(int lVal)
{
	std::cout << "val = " << GetVal() << " ";
	std::cout << typeid(*this).name() << std::endl;
}
void UseGP::Show()
{
	std::cout << "val = " << GetVal() << " ";
	std::cout << typeid(*this).name() << std::endl;
}
void GamePlayer::ShowName() const
{
	std::cout << name << std::endl;
}
GamePlayer& UseGP::GetGP()
{
	static GamePlayer gp("lgp");  //函数第一个被调用时初始化

	return gp;
}
void GamePlayer::GetName(char *name) const 
{
	//this->name[0] = 'c';
	strcpy(name, this->name);
}
const char& GamePlayer::operator[] (unsigned position) const  //是一个只读函数，只能读取，不能修改成员变量，只能调用const函数
{
	char name[10];

	this->name[0] = 'C';  //这是非法的, 但是如果成员变量是用mutable修饰的话是可以改的
	GetName(name);
	//name[0] = 'C';
	std::cout << name << " const [] " << std::endl;
	return name[position];
}
char& GamePlayer::operator[] (unsigned position)
{
	std::cout << this->name << " [] " << std::endl;

	//const_cast将const类型转换为非const类型
	//static_cast强制类型转换,可以将类型转换为const, 与dynamic_cast不同，dynamic_cast不能将将类型转换为const
	return const_cast<char&>(static_cast<GamePlayer const&>(*this)[position]); 
}

GamePlayer& GamePlayer::operator= (GamePlayer const &r)
{
	std::cout << this->name << " = " << r.name << std::endl;
	char name[10];
	strncpy(name, r.name, 10);  //处理同一对象的情况
	strncpy(this->name, name, 10);
	return *this;
}
GamePlayer::GamePlayer(GamePlayer const &r)
{
	strcpy(this->name, r.name);
	std::cout << this->name << " copy constructor " << r.name << std::endl;
}
GamePlayer::GamePlayer(char *name)
{
	std::cout << name << " : GamePlayer constructor" << std::endl;
	strcpy(this->name, name);
}
GamePlayer GamePlayer::operator*(GamePlayer const &r)
{
	std::cout << this->name << " * " << r.name << std::endl; 
	char name[10];
	strncpy(name, this->name, 10);
	strcat(name, r.name);
	GamePlayer temp(name);
	return temp;
}
const int  GamePlayer::NumTruns;

void Show(GamePlayer *gp)
{
	std::cout << "GamePlayer Show" << std::endl;
	delete gp;
}
int main(int argc, char **argv)
{
	std::vector<int> vec;
	GamePlayer gp("gp"), gpp("gpp"), gppp("gppp");
	const GamePlayer cgp("cgp");  //只能调用const函数

	for (int i = 0; i < 10; i++)
		vec.push_back(i);
	for (std::vector<int>::iterator iter = vec.begin(); iter != vec.end(); iter++)
		std::cout << *iter << std::endl;

	gp = gp * gpp * gppp;
	cgp[0];
	gp[0];
	cgp.ShowName();

	HUseGP ugp(1);// ugpp(ugp);
	ugp.GetGP();
	ugp.UseGP::Show();  //子类函数把父类同名函数隐藏了,不过参数是否相同,为了能调用被隐藏的父类函数，必须指定该函数的作用域在父类中
	//ugp.GetVal() = 2;  //通过const来防止被修改 
	ugp.Show(1);
	//ugpp = ugp;

	{
		GamePlayer gpv("gpv");
		std::vector<GamePlayer> gpVec(10, gpv);
	}
	std::cout << typeid(vec).name() << std::endl;

	Widget wg(1);
	wg = wg;

	//智能指针
	std::tr1::shared_ptr<GamePlayer> sGP2;
	{
		std::auto_ptr<GamePlayer> pGP(Widget::GetGamePlayer());	
		std::auto_ptr<GamePlayer> pGP2(pGP);
		std::cout << pGP.get() << ", " << pGP2.get() << std::endl;
		std::tr1::shared_ptr<GamePlayer> sGP(Widget::GetGamePlayer(), Show);
		sGP2 = sGP;
		std::cout << sGP.get() << ", " << sGP2.get() << std::endl;
	}

	//new和delete要匹配
/*	GamePlayer *strPtr1 = new GamePlayer("strgp"); 
	GamePlayer *strPtr2 = new GamePlayer[100];
	delete strPtr1;
	delete [] strPtr2;*/

	//显示类型转换
	UseGP ugp1(1), ugp2(2);
	std::cout << ugp1 + ugp2 << std::endl;

	//swap的使用
	Widget wgg(2);
	wg = wgg;

	//wg = 3;  //如果构造函数没有explicit就可以通过隐身类型转换
	wg = Widget(3);  //只有显示的强制类型转换,因为构造函数设置了explicit
	wg = static_cast<Widget>(3);  //只有显示的强制类型转换,因为构造函数设置了explicit

	Rectangle<int> rtg;
	rtg.draw();

	//成员函数模板化
	SmartPtr<UseGP> sp(new UseGP(100));
	SmartPtr<HUseGP> sph(new HUseGP(101));
	sp = sph;

	std::cout << Factorial<10>::value << std::endl;
	std::cout << "program endl" << std::endl;
	return 0;
}
