#include"DxLib.h"
#include "ImageMng.h"

//-----画像登録(1枚もの)
//void ImageMng::SetID(std::string idName, std::string fileName)
const int& ImageMng::SetID(std::string fileName)
{
	//map配列で既に登録済かどうかをチェックして
	//登録がなければLoadGraphしたIDをmap配列に追加
	//std::map<std::string,int>imgDivMap;

	if (imgMap.find(fileName) == imgMap.end())
	{
		imgMap[fileName] = LoadGraph(fileName.c_str());
	}
	return imgMap[fileName]; //登録したIDを返す(失敗時は-1)

}
//-----画像登録(アニメーション)
const VEC_INT& ImageMng::SetID(std::string idName, std::string fileName, VECTOR2 divSize, VECTOR2 divNum)
{
	//map配列で既に登録済かどうかをチェックして
	//登録がなければLoadGraphしたIDをmap配列に追加
	//std::map<std::string,std::vector<int>>imgDivMap;

	if (imgDivMap.find(idName) == imgDivMap.end())
	{
		//動的な要素数を設定(vector型配列)
		imgDivMap[idName].resize(divNum.x*divNum.y);

		LoadDivGraph(fileName.c_str(), divNum.x*divNum.y,
					divNum.x, divNum.y, 
					divSize.x, divSize.y, 
					&imgDivMap[idName][0], true);
	}
	return imgDivMap[idName];
}

//-----画像描画(1枚もの)
void ImageMng::DrawImage(std::string idName, int x, int y, bool flag)
{
	//描画要求のあったIDを探して
	//登録がなければ無視、あれば描画

	if (imgMap.find(idName) == imgMap.end()) 
	{
		return;
	}
	DrawGraph(x, y, imgMap[idName], flag);
}

//-----画像描画(アニメーション)
void ImageMng::DrawImage(std::string idName, int x, int y, int animNo, bool flag)
{
	//描画要求のあったIDを探して
	//登録がなければ無視、あれば描画
	if (imgDivMap.find(idName) == imgDivMap.end())
	{
		return;
	}

	//animNoが配列のサイズを超えていたらreturn
	if ((animNo<0) || imgDivMap[idName].size() <= animNo) {
		return;
	}

	DrawGraph(x, y, imgDivMap[idName][animNo], flag);
}


