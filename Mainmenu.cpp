#include "pch.h"
#include "Mainmenu.h"
#include "MouseListener.h"
#include "StartButton.h"
#include "EndButton.h"
#include "Intro.h"

Mainmenu::Mainmenu()
{
	fadeTime = 1.4f;

	cam = new Camera(this);

	AddChild((new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256.f / 40, 256.f / 40))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Main.png")->GetOwner()->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam)->GetOwner());

	AddChild((new StartButton(this))->SetPos(Vec2F(1120, 320)));
	AddChild((new EndButton(this))->SetPos(Vec2F(1120, 400)));

	fade = new Entity();
	fade->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/fade.png");
	fade->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam);
	fade->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, 0.f)))->SetEnabled(true);
	AddChild(fade);

	RG2SoundManager->Load(SoundID::sDrag, "Audio/drag.ogg");
	RG2SoundManager->Load(SoundID::sJump, "Audio/jump.ogg");
	RG2SoundManager->Load(SoundID::sPush, "Audio/push.ogg");
	RG2SoundManager->Load(SoundID::sRun, "Audio/run.ogg");
	RG2SoundManager->Load(SoundID::sWalk, "Audio/walk.ogg");
	RG2SoundManager->Load(SoundID::sWind, "Audio/wind.ogg");
	RG2SoundManager->Load(SoundID::sForce, "Audio/force.ogg");
	RG2SoundManager->Load(SoundID::sEmblem, "Audio/emblem.ogg");
	RG2SoundManager->Load(SoundID::sButtonDown, "Audio/buttonDown.ogg");
	RG2SoundManager->Load(SoundID::sButtonUp, "Audio/buttonUp.ogg");
	RG2SoundManager->Load(SoundID::sLever, "Audio/lever.ogg");
	RG2SoundManager->Load(SoundID::BGMmain, "Audio/mainBGM.ogg");

	RG2SoundManager->Play(SoundID::BGMmain, true, false);
}

Mainmenu::~Mainmenu()
{
}

void Mainmenu::OnUpdate()
{
	Scene::OnUpdate();
	cam->Update();

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
			RG2SceneManager->ChangeScene(new Intro());

		fade->GetComponent<Effect>()->PopEffectInfo()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, fadeTime + 1.4f)))->SetEnabled(true);
	}
}