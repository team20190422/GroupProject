#pragma once
#include<map>
#include<vector>
#include"VECTOR2.h"


class ImageMng
{
private:
	ImageMng() {}
	ImageMng(const ImageMng&) {}
	ImageMng& operator=(const ImageMng&){}
	~ImageMng() {}

	//-----画像登録用map配列
	std::map<std::string, int>imgMap;	//1枚画像用
	std::map<std::string, std::vector<int>>imgDivMap;	//アニメーション用

	

public:
	static ImageMng& GetInstance() {
		static ImageMng imgInst;
		return imgInst;
	}

	//登録
	void SetID(std::string idName, std::string fileName);
	//const int& ImageMng::SetID(std::string idName, std::string fileName)

	//登録(アニメーション)
	void SetID(std::string idName, std::string fileName, VECTOR2 divSize, VECTOR2 divNum);

	//描画(1枚画像)
	void DrawImage(std::string idName, int x, int y, bool flag);
	//void DrawImage(std::string idName, int x, int y,int lr, bool flag);

	//描画(アニメーション)
	void DrawImage(std::string idName, int x, int y,int animNo, bool flag);

};