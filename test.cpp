#include "test.h"
#include <iostream>
#include <vector>
#include <string.h>
#include <exception>
#include <stdexcept>
#include <typeinfo>
#include <memory>
#include <tr1/memory>

GamePlayer* Widget::GetGamePlayer()
{
	return (new GamePlayer("wgp"));
}
Widget::Widget()
{
	pb = new Bitmap();
	pb->a = 10;
}
Widget& Widget::operator= (Widget const &r)
{
	std::cout << pb->a << std::endl;
	delete pb;
	pb = r.pb;
	std::cout << pb->a << std::endl;
	return *this;
}
HUseGP::HUseGP(int lVal)
	: UseGP(lVal)
{
}
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
	Show();
}
void HUseGP::Show()
{
	std::cout << typeid(*this).name() << std::endl;
}
void UseGP::Show()
{
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
GamePlayer& GamePlayer::operator*(GamePlayer const &r)
{
	std::cout << this->name << " * " << r.name << std::endl; 
	return (*this);
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
	//ugpp = ugp;

	{
		GamePlayer gpv("gpv");
		std::vector<GamePlayer> gpVec(10, gpv);
	}
	std::cout << typeid(vec).name() << std::endl;

	Widget wg;
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
	GamePlayer *strPtr1 = new GamePlayer("strgp"); 
	GamePlayer *strPtr2 = new GamePlayer[100];
	delete strPtr1;
	delete [] strPtr2;

	std::cout << "program endl" << std::endl;
	return 0;
}
