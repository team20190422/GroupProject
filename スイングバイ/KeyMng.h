#pragma once
#include"DxLib.h"
#include"VECTOR2.h"

enum KEY_CODE {
	P1_UP = 0,
	P1_DOWN,
	P1_RIGHT ,
	P1_LEFT,
	P1_SPACE,
	P1_ENTER,
	
	KEY_MAX
};

#define lpKeyMng KeyMng::GetInstance()

class KeyMng
{
private:
	KeyMng() { 
		Init();
	}
	KeyMng(const KeyMng&) {}
	KeyMng& operator=(const KeyMng& k) {}
	~KeyMng() {}

public:
	static KeyMng& GetInstance() {
		static KeyMng keyInst;
		return keyInst;
	}
	void Init(void);
	bool Update();	//キー情報更新

	int newKey[KEY_MAX];
	int trgKey[KEY_MAX];
	int oldKey[KEY_MAX];
	int upKey[KEY_MAX];
};