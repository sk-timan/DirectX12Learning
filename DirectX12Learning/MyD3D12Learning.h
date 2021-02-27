#pragma once

#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <iostream>
#include <d3dApp.h>


class MyDirect3DApp : public D3DApp
{
public:
	MyDirect3DApp(HINSTANCE hInstance);
	~MyDirect3DApp();

	virtual bool Initialize()override;

	void LogAdpt();

	void BuildMyDevice();

	void BuildMyFence();

	void Check4XMSAAsupport();

	void BuildCommandQueue();

private:

	//virtual void OnResize()override;
	virtual void Update(const GameTimer& gt)override;
	virtual void Draw(const GameTimer& gt)override;

};