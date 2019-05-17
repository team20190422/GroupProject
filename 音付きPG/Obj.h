#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include "VECTOR2.h"
#include "KeyMng.h"
#include "VECTOR3.h"

class Obj
{
public:
	Obj();
	Obj(const int (&trgKey)[6], const int (&oldKey)[6]);
	~Obj();
	
	void init(std::string filname, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 chipOffset, float speed);
	virtual void Update(void);			//	更新処理
	virtual void Draw(void);			//	描画用

	virtual RECT &GetRect();			//当たり判定の矩形用

	virtual const int& GetTimer(void);	//時間取得用

	const VECTOR2& GetSize(void);		//サイズを返す
	void SetSize(const VECTOR2& divSize);	//サイズをセットする

	virtual bool SetPos(VECTOR3 pos);		//座標をセットする
	virtual const VECTOR3& GetPos(void);	//座標を取得する

	virtual bool SetAngle(float Angle);		//角度をセットする
	virtual const float& GetAngle(void);	//角度を取得する

	virtual bool SetDistance(float distance);	//距離をセットする
	virtual const float& GetDistance();			//距離を取得する

	virtual const VECTOR3 & GetVec();			//Vecを取得する
	virtual bool SetVec(VECTOR3 vec);			//Vecをセットする

	virtual bool& GetDeathFlag();
	virtual void SetDeathFlag(bool flag);

	const VECTOR3 & Normalize(VECTOR3,float);	//正規化

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
	float Angle;					//角度
	float distance;					//距離
	VECTOR3 Vec;
	bool DeathFlag;
};

