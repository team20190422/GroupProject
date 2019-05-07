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
	virtual float &GetSpeed();			//スクロール用	ｽﾋﾟｰﾄの値ﾞを取得する
	virtual bool SetFlag(bool flag);	//スクロール用	ﾌﾗｸﾞを取得する
	virtual double &GetAngle();			//スクロール用	角度の値を取得する
	const VECTOR2& GetSize(void);
	void SetSize(const VECTOR2& divSize);
	bool SetPos(VECTOR3 pos);
	const VECTOR3& GetPos(void);
	
	
private:
	VECTOR2 divSize = { 0,0 };			//	描画ﾁｯﾌﾟのｻｲｽﾞ
	VECTOR2 divCnt = { 0,0 };			//	描画ﾁｯﾌﾟの数
	VECTOR2 chipOffset = { 0,0 };			//	描画ﾁｯﾌﾟのｲﾒｰｼﾞIDの開始位置
	RECT rect;								//当たり判定の矩形の大きさ
	int flag;
protected:
	virtual void SetMove(void);
	std::string imageName;
	VECTOR3 pos = { 0,0 };			//	描画位置
	VECTOR2 drawOffset;
	float speed;						//	ｽﾋﾟｰﾄﾞ
	double angel;						//角度
};

