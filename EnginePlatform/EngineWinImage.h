#pragma once
#include <Windows.h>
#include <EngineBase/EngineMath.h>

// �̳༮�� �̹��� ������ ����� �̴ϴ�.
// �̳༮�� �翬�� �ε嵵 �˴ϴ�.

// ���� : API �̹� ������ ������ �ٽ� Ŭ����
//       ���� Ŭ���� winapi���� �츮���� �������� ������ �Լ����� �����ϴµ�
//       �ٽ� �ڷ����� HDC�� ���� ���α׷��� ���忡�� �̰� �����ϰų� ��ġ��
//       private���� ���� �ʹ�.
//       UEngineWinImage => ���ο� Has a�� HDC
//       ImageDC �� ��������� ���� HDC�� �ǹ̰� ����.
class UEngineWinImage
{
public:
	// constrcuter destructer
	UEngineWinImage();
	~UEngineWinImage();

	// delete Function
	UEngineWinImage(const UEngineWinImage& _Other) = delete;
	UEngineWinImage(UEngineWinImage&& _Other) noexcept = delete;
	UEngineWinImage& operator=(const UEngineWinImage& _Other) = delete;
	UEngineWinImage& operator=(UEngineWinImage&& _Other) noexcept = delete;

	// void Load(std::string_view _Path);
	HDC GetDC()
	{
		return ImageDC;
	}
	
	// �̹� ������� DC�� ���ؼ� �̹����� ����� Ÿ��
	void Create(HDC _DC)
	{
		ImageDC = _DC;
	}

	void Create(UEngineWinImage* _TargetImage, FVector2D _Scale);

	void CopyToBit(UEngineWinImage* _TargetImage, const FTransform& _Pos);

protected:

private:
	// BMP �̹��� ���� �� ��ü����
	// FVector2D Size;
	HDC ImageDC = nullptr;
	HBITMAP hBitMap = nullptr;

	// �̹��� ���� ������
	BITMAP Info;
};
