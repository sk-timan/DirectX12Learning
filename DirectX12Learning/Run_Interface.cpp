#include "MyD3D12Learning.h"


int main(HINSTANCE hInstance)
{
	MyDirect3DApp theApp(hInstance);
	//theApp.Initialize();
	//theApp.LogAdpt();
	theApp.BuildAllUp();

	theApp.Run();
	
}