#include "DxLib.h"
#include "resource1.h"
#include "GameTask.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// ｼｽﾃﾑ処理
	GameTask::GetInstance().SystemInit();
	SetWindowIconID(IDI_ICON1);
	// ---------- ｹﾞｰﾑﾙｰﾌﾟ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		GameTask::GetInstance().GameUpdate();

	}
	InitSoundMem();	//すべておサウンドハンドルを削除する
	DxLib_End();
	return 0;
}