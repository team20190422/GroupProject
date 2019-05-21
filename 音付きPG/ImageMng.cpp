#include"DxLib.h"
#include "ImageMng.h"

//-----‰æ‘œ“o˜^(1–‡‚à‚Ì)
//void ImageMng::SetID(std::string idName, std::string fileName)
const int& ImageMng::SetID(std::string fileName)
{
	//map”z—ñ‚ÅŠù‚É“o˜^Ï‚©‚Ç‚¤‚©‚ğƒ`ƒFƒbƒN‚µ‚Ä
	//“o˜^‚ª‚È‚¯‚ê‚ÎLoadGraph‚µ‚½ID‚ğmap”z—ñ‚É’Ç‰Á
	//std::map<std::string,int>imgDivMap;

	if (imgMap.find(fileName) == imgMap.end())
	{
		imgMap[fileName] = LoadGraph(fileName.c_str());
	}
	return imgMap[fileName]; //“o˜^‚µ‚½ID‚ğ•Ô‚·(¸”s‚Í-1)

}
//-----‰æ‘œ“o˜^(ƒAƒjƒ[ƒVƒ‡ƒ“)
const VEC_INT& ImageMng::SetID(std::string idName, std::string fileName, VECTOR2 divSize, VECTOR2 divNum)
{
	//map”z—ñ‚ÅŠù‚É“o˜^Ï‚©‚Ç‚¤‚©‚ğƒ`ƒFƒbƒN‚µ‚Ä
	//“o˜^‚ª‚È‚¯‚ê‚ÎLoadGraph‚µ‚½ID‚ğmap”z—ñ‚É’Ç‰Á
	//std::map<std::string,std::vector<int>>imgDivMap;

	if (imgDivMap.find(idName) == imgDivMap.end())
	{
		//“®“I‚È—v‘f”‚ğİ’è(vectorŒ^”z—ñ)
		imgDivMap[idName].resize(divNum.x*divNum.y);

		LoadDivGraph(fileName.c_str(), divNum.x*divNum.y,
					divNum.x, divNum.y, 
					divSize.x, divSize.y, 
					&imgDivMap[idName][0], true);
	}
	return imgDivMap[idName];
}

//-----‰æ‘œ•`‰æ(1–‡‚à‚Ì)
void ImageMng::DrawImage(std::string idName, int x, int y, bool flag)
{
	//•`‰æ—v‹‚Ì‚ ‚Á‚½ID‚ğ’T‚µ‚Ä
	//“o˜^‚ª‚È‚¯‚ê‚Î–³‹A‚ ‚ê‚Î•`‰æ

	if (imgMap.find(idName) == imgMap.end()) 
	{
		return;
	}
	DrawGraph(x, y, imgMap[idName], flag);
}

//-----‰æ‘œ•`‰æ(ƒAƒjƒ[ƒVƒ‡ƒ“)
void ImageMng::DrawImage(std::string idName, int x, int y, int animNo, bool flag)
{
	//•`‰æ—v‹‚Ì‚ ‚Á‚½ID‚ğ’T‚µ‚Ä
	//“o˜^‚ª‚È‚¯‚ê‚Î–³‹A‚ ‚ê‚Î•`‰æ
	if (imgDivMap.find(idName) == imgDivMap.end())
	{
		return;
	}

	//animNo‚ª”z—ñ‚ÌƒTƒCƒY‚ğ’´‚¦‚Ä‚¢‚½‚çreturn
	if ((animNo<0) || imgDivMap[idName].size() <= animNo) {
		return;
	}

	DrawGraph(x, y, imgDivMap[idName][animNo], flag);
}


