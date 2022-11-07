#pragma once

// ¸ÅÅ©·Î¶û enum class
//#define SINGLE(type) static type* GetInst() { static type mgr;	return &mgr; }
#define SINGLE(type) static type* GetInst()\
					{\
						static type mgr;\
						return &mgr;\
					}
#define WINDOW_NAME L"Game framework"

#define fDT TimeMgr::GetInst()->GetfDT()
#define DT TimeMgr::GetInst()->GetDT()

enum class KEY_STATE
{
	NONE, // ¾È´­¸²
	TAP,  // µü ´­·¶´Ù.
	HOLD, // ´©¸£´Â Áß
	AWAY, // ¶Ã´Ù.
};

enum class KEY
{
	LEFT, RIGHT, UP, DOWN,
	Q,W,E,R,T,Y,U,I,O,P,
	A,S,D,F,G,H,J,K,L,
	Z,X,C,V,B,N,M,
	ALT, LSHIFT, CTRL, SPACE,
	ENTER, ESC, LAST,
	// END=Å°°¡ ÀÖÀÝ¾Æ.
};

enum class GROUP_TYPE
{
	DEFAULT,
	PLAYER,
	MONSTER,
	BULLET,

	END = 30,
};
enum class SCENE_TYPE
{
	START, SCENE_01,
	SCENE_02,TOOL,
	END
};