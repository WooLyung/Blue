#include"pch.h"
#include"App.h"

#include "Mainmenu.h"
#include "End.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "Stage4.h"

#if defined(_DEBUG)
int main()
#else
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#endif
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	RG2App->Init();

	RG2SceneManager->ChangeScene(new Mainmenu());

	RG2App->MainLoop();
	
	RG2App->Dispose();
	
	return 0;
}