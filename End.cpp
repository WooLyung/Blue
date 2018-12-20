#include "pch.h"
#include "End.h"
#include "MouseListener.h"
#include "StartButton.h"
#include "EndButton.h"
#include "Mainmenu.h"

End::End(Data data)
{
	fadeTime = 1.4f;

	cam = new Camera(this);
	
	imgEntity[0] = (new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256.f / 40, 256.f / 40))->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam)->GetOwner();
	imgEntity[1] = (new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256.f / 40, 256.f / 40))->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam)->GetOwner();
	imgEntity[2] = (new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256.f / 40, 256.f / 40))->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam)->GetOwner();
	imgEntity[3] = (new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256.f / 40, 256.f / 40))->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam)->GetOwner();
	imgEntity[4] = (new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256.f / 40, 256.f / 40))->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam)->GetOwner();
	imgEntity[5] = (new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256.f / 40, 256.f / 40))->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam)->GetOwner();
	imgEntity[6] = (new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256.f / 40, 256.f / 40))->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam)->GetOwner();
	imgEntity[7] = (new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256.f / 40, 256.f / 40))->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam)->GetOwner();
	imgEntity[8] = (new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256.f / 40, 256.f / 40))->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam)->GetOwner();
	imgEntity[9] = (new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256.f / 40, 256.f / 40))->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam)->GetOwner();
	imgEntity[10] = (new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256.f / 40, 256.f / 40))->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam)->GetOwner();

	imgEntity[0]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 1)))->SetEnabled(true);
	imgEntity[1]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 0)))->SetEnabled(true);
	imgEntity[2]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 0)))->SetEnabled(true);
	imgEntity[3]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 0)))->SetEnabled(true);
	imgEntity[4]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 0)))->SetEnabled(true);
	imgEntity[5]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 0)))->SetEnabled(true);
	imgEntity[6]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 0)))->SetEnabled(true);
	imgEntity[7]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 0)))->SetEnabled(true);
	imgEntity[8]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 0)))->SetEnabled(true);
	imgEntity[9]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 0)))->SetEnabled(true);
	imgEntity[10]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 0)))->SetEnabled(true);

	if (data.isGameover)
	{
		imgEntity[0]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/badEnding.png");
		rank = 'x';
	}
	else
	{
		if (data.col1) imgEntity[0]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/_Emblem_dream/true.png");
		else imgEntity[0]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/_Emblem_dream/false.png");

		if (data.col2) imgEntity[1]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/_Emblem_friendship/true.png");
		else imgEntity[1]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/_Emblem_friendship/false.png");

		if (data.col3) imgEntity[2]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/_Emblem_honor/true.png");
		else imgEntity[2]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/_Emblem_honor/false.png");

		if (data.col4) imgEntity[3]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/_Emblem_love/true.png");
		else imgEntity[3]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/_Emblem_love/false.png");

		if (data.giveupCount <= 3)
		{
			if (data.col1 + data.col2 + data.col3 + data.col4 >= 2)
				rank = 'a';
			else if (data.col1 + data.col2 + data.col3 + data.col4 >= 0)
				rank = 'b';
		}
		else if (data.giveupCount <= 8)
		{
			if (data.col1 + data.col2 + data.col3 + data.col4 >= 4)
				rank = 'b';
			else if (data.col1 + data.col2 + data.col3 + data.col4 >= 2)
				rank = 'c';
			else if (data.col1 + data.col2 + data.col3 + data.col4 >= 0)
				rank = 'd';
		}
		else
		{
			if (data.col1 + data.col2 + data.col3 + data.col4 >= 4)
				rank = 'd';
			else if (data.col1 + data.col2 + data.col3 + data.col4 >= 2)
				rank = 'e';
			else if (data.col1 + data.col2 + data.col3 + data.col4 >= 0)
				rank = 'f';
		}

		if (rank == 'a')
		{
			imgEntity[4]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/A/1.png");
			imgEntity[5]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/A/2.png");
			imgEntity[6]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/A/3.png");
			imgEntity[7]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/A/4.png");
			imgEntity[8]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/A/5.png");
		}
		else if (rank == 'b')
		{
			imgEntity[4]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/B/1.png");
			imgEntity[5]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/B/2.png");
			imgEntity[6]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/B/3.png");
			imgEntity[7]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/B/4.png");
		}
		else if (rank == 'c')
		{
			imgEntity[4]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/C/1.png");
			imgEntity[5]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/C/2.png");
			imgEntity[6]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/C/3.png");
			imgEntity[7]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/C/4.png");
			imgEntity[8]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/C/5.png");
			imgEntity[9]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/C/6.png");;
		}
		else if (rank == 'd')
		{
			imgEntity[4]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/D/1.png");
			imgEntity[5]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/D/2.png");
			imgEntity[6]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/D/3.png");
			imgEntity[7]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/D/4.png");
		}
		else if (rank == 'e')
		{
			imgEntity[4]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/E/1.png");
			imgEntity[5]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/E/2.png");
			imgEntity[6]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/E/3.png");
			imgEntity[7]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/E/4.png");
			imgEntity[8]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/E/5.png");
		}
		else if (rank == 'f')
		{
			imgEntity[4]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/F/1.png");
			imgEntity[5]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/F/2.png");
			imgEntity[6]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Ending/F/3.png");
		}

	}

	AddChild(imgEntity[0]);
	AddChild(imgEntity[1]);
	AddChild(imgEntity[2]);
	AddChild(imgEntity[3]);
	AddChild(imgEntity[4]);
	AddChild(imgEntity[5]);
	AddChild(imgEntity[6]);
	AddChild(imgEntity[7]);
	AddChild(imgEntity[8]);
	AddChild(imgEntity[9]);
	AddChild(imgEntity[10]);

	fade = new Entity();
	fade->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/fade.png");
	fade->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam);
	fade->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, 0.f)))->SetEnabled(true);
	AddChild(fade);

	RG2SoundManager->Stop(SoundID::BGMmain);
}

End::~End()
{
}

void End::OnUpdate()
{
	Scene::OnUpdate();
	cam->Update();

	if (RG2Input->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
	{
		if (rank == 'a' && img == 8
			|| rank == 'b' && img == 7
			|| rank == 'c' && img == 9
			|| rank == 'd' && img == 7
			|| rank == 'e' && img == 8
			|| rank == 'f' && img == 6
			|| rank == 'x')
		{
			img++;
			fadeTime = -1.4f;
		}
		else if (rank == 'a' && img < 8
			|| rank == 'b' && img < 7
			|| rank == 'c' && img < 9
			|| rank == 'd' && img < 7
			|| rank == 'e' && img < 8
			|| rank == 'f' && img < 6)
		{
			img++;
			imgAppear[img - 1] = 0;
		}
	}

	for (int i = 1; i <= 10; i++)
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
			RG2SceneManager->ChangeScene(new Mainmenu());

		fade->GetComponent<Effect>()->PopEffectInfo()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, fadeTime + 1.4f)))->SetEnabled(true);
	}
}