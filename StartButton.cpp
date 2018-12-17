#include "pch.h"
#include "StartButton.h"
#include"AABBCollider.h"
#include"SpriteRenderer.h"
#include"TextRenderer.h"
#include"MouseListener.h"
#include "Mainmenu.h"

StartButton::StartButton(Scene *mainmenu)
{
	this->mainmenu = mainmenu;

	auto sr = AttachComponent<SpriteRenderer>();
	sr->SetTexture("Sprites/UIs/Start-non.png");

	AttachComponent<AABBCollider>();

	AttachComponent<MouseListener>()
		->SetOnEnterListener([=]() {
		GetComponent<SpriteRenderer>()->SetTexture("Sprites/UIs/Start-selected.png");
	})
		->SetOnExitListener([=]() {
		GetComponent<SpriteRenderer>()->SetTexture("Sprites/UIs/Start-non.png");
	})
		->SetOnClickListener([=]() {
		if (((Mainmenu*)mainmenu)->fadeTime == 0)
			((Mainmenu*)mainmenu)->fadeTime = -1.4f;
	});
}


StartButton::~StartButton()
{
}

void StartButton::SetOnClickListener(std::function<void()> callback)
{
	GetComponent<MouseListener>()->SetOnClickListener(callback);
}
