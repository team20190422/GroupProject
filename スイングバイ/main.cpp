#include "DxLib.h"
#include "GameTask.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// ºΩ√—èàóù
	GameTask::GetInstance().SystemInit();

	// ---------- πﬁ∞—Ÿ∞Ãﬂ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		GameTask::GetInstance().GameUpdate();

	}
	DxLib_End();
	return 0;
}