#include "MyD3D12Learning.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::PackedVector;
using Microsoft::WRL::ComPtr;

MyDirect3DApp::MyDirect3DApp(HINSTANCE hInstance) : D3DApp(hInstance)
{

}

MyDirect3DApp::~MyDirect3DApp()
{
}

bool MyDirect3DApp::Initialize()
{
	if(!D3DApp::Initialize())
		return false;
	return true;
}

void MyDirect3DApp::LogAdpt()
{
	this->LogAdapters();
}

void MyDirect3DApp::BuildMyDevice()
{
#if defined(DEBUG) || defined(_DEBUG)
	//����D3D12 �ĵ��Բ�
	{
		ComPtr<ID3D12Debug> debugController;
		ThrowIfFailed(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)));
		debugController->EnableDebugLayer();
	}
#endif
	ThrowIfFailed(CreateDXGIFactory1(IID_PPV_ARGS(&mdxgiFactory)));

	//���Դ���Ӳ���豸
	HRESULT hardwareResult = D3D12CreateDevice(
		nullptr,	// Ĭ��������
		D3D_FEATURE_LEVEL_11_0,
		IID_PPV_ARGS(&md3dDevice)
	);

	// ������WARP�豸
	if (FAILED(hardwareResult))
	{
		ComPtr<IDXGIAdapter> pWarpAdapter;
		ThrowIfFailed(mdxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&pWarpAdapter)));

		ThrowIfFailed(D3D12CreateDevice(
			pWarpAdapter.Get(),
			D3D_FEATURE_LEVEL_11_0,
			IID_PPV_ARGS(&md3dDevice)
		));
	}


}

void MyDirect3DApp::BuildMyFence()
{
	ThrowIfFailed(md3dDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&mFence)));
	mRtvDescriptorSize = md3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	mDsvDescriptorSize = md3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	mCbvSrvUavDescriptorSize = md3dDevice->GetDescriptorHandleIncrementSize(
		D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

}

void MyDirect3DApp::Check4XMSAAsupport()
{
	D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS msQualityLevels;
	msQualityLevels.Format = mBackBufferFormat;
	msQualityLevels.SampleCount = 4;
	msQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
	msQualityLevels.NumQualityLevels = 0;
	ThrowIfFailed(md3dDevice->CheckFeatureSupport(
		D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS,
		&msQualityLevels,
		sizeof(msQualityLevels)
	));

	m4xMsaaQuality = msQualityLevels.NumQualityLevels;
	assert(m4xMsaaQuality > 0 && "Unexpected MSAA quality level.");

}

void MyDirect3DApp::BuildCommandQueue()
{
	//ComPtr<ID3D12CommandQueue> mCommandQueue;
	//ComPtr<ID3D12CommandAllocator> mCommandAlloc;
	//ComPtr<ID3D12GraphicsCommandList> mCommandList;
	
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

	ThrowIfFailed(md3dDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&mCommandQueue)));
	ThrowIfFailed(md3dDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(mDirectCmdListAlloc.GetAddressOf())));
	ThrowIfFailed(md3dDevice->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		mDirectCmdListAlloc.Get(),	// �������������
		nullptr,					// ��ʼ����ˮ��״̬
		IID_PPV_ARGS(mCommandList.GetAddressOf())
	));

	// ����Ҫ�������б����ڹر�״̬��������Ϊ�ڵ�һ�����������б�ʱ������Ҫ�����������ã�
	// ���ڵ������÷���ǰ�����Ƚ���ر�
	mCommandList->Close();

}

void MyDirect3DApp::Update(const GameTimer& gt)
{
}

void MyDirect3DApp::Draw(const GameTimer& gt)
{
}
