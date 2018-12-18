#include "pch.h"
#include "Intro.h"
#include "MouseListener.h"
#include "StartButton.h"
#include "EndButton.h"
#include "Stage1.h"

Intro::Intro()
{
	fadeTime = 1.4f;

	cam = new Camera(this);

	imgEntity = (new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256.f / 40, 256.f / 40))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Intro/0.png")->GetOwner()->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam)->GetOwner();
	AddChild(imgEntity);

	fade = new Entity();
	fade->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/fade.png");
	fade->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam);
	fade->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, 0.f)))->SetEnabled(true);
	AddChild(fade);
}

Intro::~Intro()
{
}

void Intro::OnUpdate()
{
	Scene::OnUpdate();
	cam->Update();

	if (RG2Input->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
	{
		if (img == 7)
		{
			img = 8;
			fadeTime = -1.4f;
		}
		else if (img <= 6)
		{
			img++;
			if (img == 1) imgEntity->GetComponent<SpriteRenderer>()->SetTexture("Sprites/Intro/1.png");
			if (img == 2) imgEntity->GetComponent<SpriteRenderer>()->SetTexture("Sprites/Intro/2.png");
			if (img == 3) imgEntity->GetComponent<SpriteRenderer>()->SetTexture("Sprites/Intro/3.png");
			if (img == 4) imgEntity->GetComponent<SpriteRenderer>()->SetTexture("Sprites/Intro/4.png");
			if (img == 5) imgEntity->GetComponent<SpriteRenderer>()->SetTexture("Sprites/Intro/5.png");
			if (img == 6) imgEntity->GetComponent<SpriteRenderer>()->SetTexture("Sprites/Intro/6.png");
			if (img == 7) imgEntity->GetComponent<SpriteRenderer>()->SetTexture("Sprites/Intro/7.png");
		}
	}

	if (fadeTime > 0)
	{
		fadeTime -= DT;
		if (fadeTime <= 0)
			fadeTime = 0;

		fade->GetComponent<Effect>()->PopEffectInfo()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, fadeTime)))->SetEnabled(true);
	}
	else if (fadeTime < 0)
	{
		fadeTime += DT;
		if (fadeTime >= 0)
			RG2SceneManager->ChangeScene(new Stage1({ false, false, false, false, false, 0, false, 0, -3500, false }));

		fade->GetComponent<Effect>()->PopEffectInfo()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, fadeTime + 1.4f)))->SetEnabled(true);
	}
}