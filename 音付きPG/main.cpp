#include "DxLib.h"
#include "GameTask.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// ���я���
	GameTask::GetInstance().SystemInit();
	// ---------- �ް�ٰ��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();

		GameTask::GetInstance().GameUpdate();

		ScreenFlip();
		
	}
	InitSoundMem();	//���ׂĂ��T�E���h�n���h�����폜����
	DxLib_End();
	return 0;
}