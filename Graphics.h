#pragma once
#include"EffectType.h"
class Graphics 
{
private:
	friend class TextRenderer;

	ID2D1Factory1* factory_;
	IDWriteFactory* dwFactory_;
	ID2D1Device* d2dDevice_;
	ID2D1DeviceContext* deviceContext_;
	IDXGISwapChain1* swapChain_;
	ID2D1Bitmap1* targetBitmap_;

	ID2D1SolidColorBrush* outlineBrush_;
	ID2D1SolidColorBrush* fillBrush_;

	std::map<EffectType, ID2D1Effect* > effects_;
public:
	Graphics();
	~Graphics();
	
	void Render();
	ID2D1DeviceContext* GetDeviceContext() const { return deviceContext_; }
	ID2D1Effect* GetEffect(EffectType type) const { return effects_.at(type); }
	
};

