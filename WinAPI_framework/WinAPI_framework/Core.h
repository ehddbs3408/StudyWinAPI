#pragma once
class Core
{
public:
	SINGLE(Core);
private:
	Core();
	~Core();
};

//class Core
//{
//public:
//	static Core* GetInst()
//	{
//		if (nullptr == g_plnst)
//		{
//			g_plnst = new Core;
//		}
//		return g_plnst;
//	}
//
//	static void Release()
//	{
//		delete g_plnst;
//		g_plnst = nullptr;
//	}
//private:
//	static Core* g_plnst;
//	Core();
//	~Core();
//}; //1锅 规过
// 
//class Core
//{
//public:
//	static Core* GetInst()
//	{
//		static Core core;
//		return &core;
//	}
//private:
//	Core();
//	~Core();
//};//滴锅掳 规过