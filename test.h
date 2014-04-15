#include <algorithm>
#include <iostream>

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
class Widget
{
	public:
		/*explicit*/ Widget(int val);
		~Widget();
		Widget(const Widget &r);
		Widget &operator= (Widget const &r);
		static GamePlayer* GetGamePlayer();
		void Swap(Widget &r);
	private:
		Bitmap *pb;  //处理包含Widget内的所有数据,这样在交换数据时可以不用整个交换数据，而只要交换指针就可以了
};
namespace std
{
	template <>
	void swap<Widget>(Widget &a, Widget &b)
	{
		std::cout << "swap<Widget> call" << std::endl;
		a.Swap(b);	
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
		virtual void Show();
	private:
		int val;
		UseGP& operator= (UseGP const &r);  //只声明，不定义，这样就屏蔽了赋值函数
		UseGP(UseGP const &r);  //只声明，不定义，这样就屏蔽了拷贝构造函数
};
class HUseGP : public UseGP
{
	public:
		HUseGP(int lVal);
		void Show();
};

