#pragma once

#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <iostream>
#include <d3dApp.h>
#include <UploadBuffer.h>
#include <MathHelper.h>

struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};

//	绘制物体所用的常量数据
struct ObjectConstants
{
	XMFLOAT4X4 WorldViewProj = MathHelper::Identity4x4();
};

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

	void BuildSwapChain();

	void BuildDescriptorHeap();

	void BuildRenderTargetView();

	void BuildDepthStencilView();

	void UpdateViewPortTransform();

	void SetScissorRectangle();

	void BuildAllUp();

	void CreateIndexBuffer();

private:

	//virtual void OnResize()override;
	virtual void Update(const GameTimer& gt)override;
	virtual void Draw(const GameTimer& gt)override;

public:
	

};

class MyBox : public D3DApp
{
public:
	MyBox(HINSTANCE hInstance);
	MyBox(const MyBox& rhs) = delete;
	MyBox& operator=(const MyBox& rhs) = delete;
	~MyBox();

	virtual bool Initialize() override;

private:
	virtual void OnResize() override;









	void BuildDescriptorHeaps();
	void BuildConstantBuffers();
	void BuildRootSignature();

private:
	ComPtr<ID3D12RootSignature> mRootSignature = nullptr;
	ComPtr<ID3D12DescriptorHeap> mCbvHeap = nullptr;

	std::unique_ptr<UploadBuffer<ObjectConstants>> mObjectCB = nullptr;

	

};