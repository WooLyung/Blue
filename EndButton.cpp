#include "pch.h"
#include "EndButton.h"
#include"AABBCollider.h"
#include"SpriteRenderer.h"
#include"TextRenderer.h"
#include"MouseListener.h"
#include "Mainmenu.h"

EndButton::EndButton(Scene *mainmenu)
{
	this->mainmenu = mainmenu;

	auto sr = AttachComponent<SpriteRenderer>();
	sr->SetTexture("Sprites/UIs/Quit-non.png");

	AttachComponent<AABBCollider>();

	AttachComponent<MouseListener>()
		->SetOnEnterListener([=]() {
		GetComponent<SpriteRenderer>()->SetTexture("Sprites/UIs/Quit-selected.png");
	})
		->SetOnExitListener([=]() {
		GetComponent<SpriteRenderer>()->SetTexture("Sprites/UIs/Quit-non.png");
	})
		->SetOnClickListener([=]() {
		exit(0);
	});
}


EndButton::~EndButton()
{
}

void EndButton::SetOnClickListener(std::function<void()> callback)
{
	GetComponent<MouseListener>()->SetOnClickListener(callback);
}
