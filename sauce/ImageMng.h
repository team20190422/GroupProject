#pragma once
#include<map>
#include<vector>
#include"VECTOR2.h"

#define IMAGE_ID(X) ImageMng::GetInstance().SetID(X)
using VEC_INT = std::vector<int>;

class ImageMng
{
private:
	ImageMng() {}
	ImageMng(const ImageMng&) {}
	ImageMng& operator=(const ImageMng&){}
	~ImageMng() {}

	//-----�摜�o�^�pmap�z��
	std::map<std::string, int>imgMap;	//1���摜�p
	std::map<std::string, std::vector<int>>imgDivMap;	//�A�j���[�V�����p

	

public:
	static ImageMng& GetInstance() {
		static ImageMng imgInst;
		return imgInst;
	}

	//�o�^
	const int& SetID(std::string fileName);
	//const int& ImageMng::SetID(std::string idName, std::string fileName)

	//�o�^(�A�j���[�V����)
	const VEC_INT& SetID(std::string idName, std::string fileName, VECTOR2 divSize, VECTOR2 divNum);

	//�`��(1���摜)
	void DrawImage(std::string idName, int x, int y, bool flag);
	//void DrawImage(std::string idName, int x, int y,int lr, bool flag);

	//�`��(�A�j���[�V����)
	void DrawImage(std::string idName, int x, int y,int animNo, bool flag);

};