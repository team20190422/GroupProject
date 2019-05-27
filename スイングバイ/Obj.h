#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include "VECTOR2.h"
#include "KeyMng.h"
#include "VECTOR3.h"

constexpr unsigned int PLAYER_SIZE = 32;

class Obj
{
public:
	Obj();
	Obj(const int (&trgKey)[KEY_MAX], const int (&oldKey)[KEY_MAX]);
	~Obj();
	
	void init(std::string filname, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 chipOffset, float speed);
	virtual void Update(void);			//	更新処理
	virtual void Draw(void);			//	描画用

	virtual RECT &GetRect();			//当たり判定の矩形用

	virtual const int& GetTimer(void);

	const VECTOR2& GetSize(void);
	void SetSize(const VECTOR2& divSize);

	virtual bool SetPos(VECTOR3 pos);
	virtual const VECTOR3& GetPos(void);

	virtual bool SetAngle(float Angle);
	virtual const float& GetAngle(void);

	virtual bool SetDistance(float distance);
	virtual const float& GetDistance();

	virtual const VECTOR3 & GetVec();
	virtual bool SetVec(VECTOR3 vec);

	const VECTOR3 & Normalize(VECTOR3,float);


private:

	VECTOR2 divSize = { 0,0 };			//	描画ﾁｯﾌﾟのｻｲｽﾞ
	VECTOR2 divCnt = { 0,0 };			//	描画ﾁｯﾌﾟの数
	VECTOR2 chipOffset = { 0,0 };			//	描画ﾁｯﾌﾟのｲﾒｰｼﾞIDの開始位置
	RECT rect;								//当たり判定の矩形の大きさ

protected:
	virtual void SetMove(void);
	std::string imageName;

	VECTOR3 pos = { 0,0 };			//	描画位置
	VECTOR2 drawOffset;
	float speed;						//	ｽﾋﾟｰﾄﾞ
	float Angle;
	float distance;
	VECTOR3 Vec;
};

