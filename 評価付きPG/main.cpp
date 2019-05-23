#include "DxLib.h"
#include "resource1.h"
#include "GameTask.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// ���я���
	GameTask::GetInstance().SystemInit();
	SetWindowIconID(IDI_ICON1);
	// ---------- �ް�ٰ��
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		GameTask::GetInstance().GameUpdate();

	}
	InitSoundMem();	//���ׂĂ��T�E���h�n���h�����폜����
	DxLib_End();
	return 0;
}