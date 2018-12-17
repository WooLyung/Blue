#include "pch.h"
#include "End.h"
#include "Mainmenu.h"

End::End(Data data)
{
	this->data = data;
	fadeTime = 1.4f;

	cam = new Camera(this);

	AddChild((new Entity())->SetPos(Vec2F(0, 0))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Ending/ending.png")->GetOwner()->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam)->GetOwner());
	fade = new Entity();
	fade->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/fade.png");
	fade->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam);
	fade->SetScale(Vec2F(1 / 0.16f, 1 / 0.16f));
	fade->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, 1.f)))->SetEnabled(true);
	AddChild(fade);
}

End::~End()
{
}

void End::OnUpdate()
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
	else if (fadeTime == 0)
	{
		if (RG2Input->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
			fadeTime = -1.4f;
	}
	else if (fadeTime < 0)
	{
		fadeTime += DT;
		if (fadeTime >= 0)
			RG2SceneManager->ChangeScene(new Mainmenu());

		fade->GetComponent<Effect>()->PopEffectInfo()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, fadeTime + 1.4f)))->SetEnabled(true);
	}
}