#include "pch.h"
#include "Mainmenu.h"
#include "MouseListener.h"
#include "StartButton.h"
#include "EndButton.h"
#include "Stage1.h"

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
			RG2SceneManager->ChangeScene(new Stage1({ false, false, false, false, false, 0, false, 0, -3500, false }));

		fade->GetComponent<Effect>()->PopEffectInfo()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, fadeTime + 1.4f)))->SetEnabled(true);
	}
}