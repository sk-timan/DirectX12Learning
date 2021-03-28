#pragma once

#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <iostream>
#include <d3dApp.h>
#include <UploadBuffer.h>
#include <MathHelper.h>

using namespace DirectX;
using namespace Microsoft::WRL;

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
	virtual void Update(const GameTimer& gt) override;
	virtual void Draw(const GameTimer& gt) override;

	virtual void OnMouseDown(WPARAM btnState, int x, int y);
	virtual void OnMouseUp(WPARAM btnState, int x, int y);
	virtual void OnMouseMove(WPARAM btnState, int x, int y);



	void BuildDescriptorHeaps();
	void BuildConstantBuffers();
	void BuildRootSignature();
	void BuildShadersAndInputLayout();
	void BuildBoxGeometry();
	void BuildPSO();

private:

	ComPtr<ID3D12RootSignature> mRootSignature = nullptr;
	ComPtr<ID3D12DescriptorHeap> mCbvHeap = nullptr;

	std::unique_ptr<UploadBuffer<ObjectConstants>> mObjectCB = nullptr;
	std::unique_ptr<MeshGeometry> mBoxGeo = nullptr;

	ComPtr<ID3DBlob> mvsByteCode = nullptr;
	ComPtr<ID3DBlob> mpsByteCode = nullptr;
	
	std::vector<D3D12_INPUT_ELEMENT_DESC> mInputLayout;

	ComPtr<ID3D12PipelineState> mPSO = nullptr;

	float mRadius = 5.0f;
	float mPhi = XM_PIDIV4;
	float mTheta = 1.5f * XM_PI;

	XMFLOAT4X4 mWorld = MathHelper::Identity4x4();
	XMFLOAT4X4 mView = MathHelper::Identity4x4();
	XMFLOAT4X4 mProj = MathHelper::Identity4x4();

	POINT mLastMousePos;
};

void RunMyBox(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd);