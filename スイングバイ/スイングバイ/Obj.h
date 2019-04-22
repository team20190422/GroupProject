#pragma once
#include <string>
#include <vector>
#include <memory>
#include <map>
#include "VECTOR2.h"
#include "KeyMng.h"

class Obj
{
public:
	//Obj();
	Obj(const int (&trgKey)[6], const int (&oldKey)[6]);
	~Obj();
	
	void init(std::string filname, VECTOR2 divSize, VECTOR2 divCnt, VECTOR2 chipOffset, float speed);
	virtual bool Update(void);			//	更新処理
	virtual void Draw(void);			//	描画用

	const VECTOR2& GetSize(void);
	void SetSize(const VECTOR2& divSize);

	bool SetPos(VECTOR2 pos);
	const VECTOR2& GetPos(void);

private:
	std::string imageName;

	VECTOR2 divSize = { 0,0 };			//	描画ﾁｯﾌﾟのｻｲｽﾞ
	VECTOR2 divCnt = { 0,0 };			//	描画ﾁｯﾌﾟの数
	VECTOR2 chipOffset = { 0,0 };			//	描画ﾁｯﾌﾟのｲﾒｰｼﾞIDの開始位置

protected:
	virtual void SetMove(void);

	VECTOR2 pos = { 0,0 };			//	描画位置
	VECTOR2 drawOffset;
	float speed;						//	ｽﾋﾟｰﾄﾞ

};

