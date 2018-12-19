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

	imgEntity[0] = (new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256.f / 40, 256.f / 40))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Intro/0.png")->GetOwner()->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam)->GetOwner();
	imgEntity[0]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 1)))->SetEnabled(true);
	imgEntity[1] = (new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256.f / 40, 256.f / 40))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Intro/1.png")->GetOwner()->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam)->GetOwner();
	imgEntity[1]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 0)))->SetEnabled(true);
	imgEntity[2] = (new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256.f / 40, 256.f / 40))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Intro/2.png")->GetOwner()->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam)->GetOwner();
	imgEntity[2]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 0)))->SetEnabled(true);
	imgEntity[3] = (new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256.f / 40, 256.f / 40))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Intro/3.png")->GetOwner()->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam)->GetOwner();
	imgEntity[3]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 0)))->SetEnabled(true);
	imgEntity[4] = (new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256.f / 40, 256.f / 40))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Intro/4.png")->GetOwner()->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam)->GetOwner();
	imgEntity[4]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 0)))->SetEnabled(true);
	imgEntity[5] = (new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256.f / 40, 256.f / 40))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Intro/5.png")->GetOwner()->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam)->GetOwner();
	imgEntity[5]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 0)))->SetEnabled(true);
	imgEntity[6] = (new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256.f / 40, 256.f / 40))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Intro/6.png")->GetOwner()->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam)->GetOwner();
	imgEntity[6]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 0)))->SetEnabled(true);
	imgEntity[7] = (new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256.f / 40, 256.f / 40))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Intro/7.png")->GetOwner()->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam)->GetOwner();
	imgEntity[7]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 0)))->SetEnabled(true);

	AddChild(imgEntity[0]);
	AddChild(imgEntity[1]);
	AddChild(imgEntity[2]);
	AddChild(imgEntity[3]);
	AddChild(imgEntity[4]);
	AddChild(imgEntity[5]);
	AddChild(imgEntity[6]);
	AddChild(imgEntity[7]);

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
			imgAppear[img - 1] = 0;
		}
	}

	for (int i = 1; i <= 7; i++)
	{
		if (imgAppear[i - 1] != -1)
		{
			imgAppear[i - 1] += DT * 1.6f;
			if (imgAppear[i - 1] > 1) imgAppear[i - 1] = 1;
			imgEntity[i]->GetComponent<Effect>()->PopEffectInfo()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, imgAppear[i - 1])))->SetEnabled(true);
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