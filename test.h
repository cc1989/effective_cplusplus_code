class GamePlayer
{
	private:
		static const int NumTruns = 10; //这个只是声明
		//int scores[NumTurns];
		mutable char name[NumTruns];
	public:
		GamePlayer(char *name);
		GamePlayer& operator* (GamePlayer const&r);
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
		UseGP(int lVal);
		virtual void Show();
	private:
		int &val;
		UseGP& operator= (UseGP const &r);  //只声明，不定义，这样就屏蔽了赋值函数
		UseGP(UseGP const &r);  //只声明，不定义，这样就屏蔽了拷贝构造函数
};
class HUseGP : public UseGP
{
	public:
		HUseGP(int lVal);
		void Show();
};

class Bitmap{
	public:
		int a;
};
class Widget
{
	public:
		Widget();
		Widget &operator= (Widget const &r);
		static GamePlayer* GetGamePlayer();
	private:
		Bitmap *pb;
};
