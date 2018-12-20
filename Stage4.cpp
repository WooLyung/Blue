#include "pch.h"
#include "Stage4.h"
#include "emblemParticle.h"

Stage4::Stage4(Data data)
{
#pragma region Default Setting
	blocks = new list<IBlock*>;
	particles = new list<Entity*>;
	this->data = data;
	endPos = 160.5f;
	isGiveup = false;
	isGameover = false;
	isNextstage = false;

	cam = new Camera(this);
	cam->SetZoom(0.16f);
	cam->SetRange(Rect(0, 0, 173 * 256, 256 * 31));
#pragma region BackGround
	background[0] = new Entity();
	background[0]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage4/layer1.png");
	background[0]->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam);
	AddChild(background[0]);

	background[1] = new Entity();
	background[1]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage4/layer2.png");
	background[1]->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam);
	AddChild(background[1]);

	background[2] = new Entity();
	background[2]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage4/layer2.png");
	background[2]->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam);
	AddChild(background[2]);

	background[3] = new Entity();
	background[3]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage4/layer3.png");
	background[3]->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam);
	AddChild(background[3]);

	background[4] = new Entity();
	background[4]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage4/layer3.png");
	background[4]->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam);
	AddChild(background[4]);
#pragma endregion

	AddChild((new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256 / 52.70114942528736f, 256 / 52.70114942528736f))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage4/back.png")->GetOwner());

	player = new Player();
	AddChild(player);

	if (data.nowPuzzle == 1)
		player->SetPos(Vec2F(13 * 256, 21 * 256));
	else if (data.nowPuzzle == 2)
		player->SetPos(Vec2F(52 * 256, 23 * 256));
	else if (data.nowPuzzle == 3)
		player->SetPos(Vec2F(117 * 256, 28 * 256));
	else if (data.nowPuzzle == 4)
		player->SetPos(Vec2F(163 * 256, 15 * 256));
	else
		player->SetPos(Vec2F(8 * 256, 22 * 256));

	cam->Follow(player);
#pragma endregion
#pragma region File Input
	ifstream inFile("Map/Stage4.txt");
	int y = 0;
	while (!inFile.eof()) {
		char inputString[200];
		for (int i = 0; i < sizeof(inputString); i++)
			inputString[i] = -1;
		inFile.getline(inputString, 200);
		for (int x = 0; inputString[x] != -1; x++)
		{
			IBlock *newBlock;
			switch (inputString[x])
			{
				// . : 공백
				// 숫자 : 정사각형 블록
				// 알파벳 소문자 : 가로 블록
				// 알파벳 대문자 : 세로 블록
				// 특수 문자 : 옮길 수 있는 블럭

				// 옮길 수 있는 블록
			case '*':// 1 * 1
				newBlock = new moveableBlock(x * 256, y * 256, "Sprites/Blocks/moveableBlock/moveableBlock1.png");
				AddChild(newBlock);
				blocks->push_back(newBlock);
				break;
			case '-':// 2 * 2
				newBlock = new moveableBlock(x * 256, y * 256, "Sprites/Blocks/moveableBlock/moveableBlock2.png");
				AddChild(newBlock);
				blocks->push_back(newBlock);
				break;

				// 정사각형 블록
			case '1': // 1 * 1
				newBlock = new block(x * 256, y * 256, "Sprites/Blocks/staticBlock/block(1-1).png");
				AddChild(newBlock);
				blocks->push_back(newBlock);
				break;
			case '2': // 2 * 2
				newBlock = new block(x * 256, y * 256, "Sprites/Blocks/staticBlock/block(2-2).png");
				AddChild(newBlock);
				blocks->push_back(newBlock);
				break;
			case '3': // 3 * 3
				newBlock = new block(x * 256, y * 256, "Sprites/Blocks/staticBlock/block(3-3).png");
				AddChild(newBlock);
				blocks->push_back(newBlock);
				break;
			case '4': // 4 * 4
				newBlock = new block(x * 256, y * 256, "Sprites/Blocks/staticBlock/block(4-4).png");
				AddChild(newBlock);
				blocks->push_back(newBlock);
				break;
			case '5': // 5 * 5
				newBlock = new block(x * 256, y * 256, "Sprites/Blocks/staticBlock/block(5-5).png");
				AddChild(newBlock);
				blocks->push_back(newBlock);
				break;

				// 가로 블록
			case 'a': // 2 * 1
				newBlock = new block(x * 256, y * 256, "Sprites/Blocks/staticBlock/block(2-1).png");
				AddChild(newBlock);
				blocks->push_back(newBlock);
				break;
			case 'b': // 3 * 1
				newBlock = new block(x * 256, y * 256, "Sprites/Blocks/staticBlock/block(3-1).png");
				AddChild(newBlock);
				blocks->push_back(newBlock);
				break;
			case 'c': // 4 * 1
				newBlock = new block(x * 256, y * 256, "Sprites/Blocks/staticBlock/block(4-1).png");
				AddChild(newBlock);
				blocks->push_back(newBlock);
				break;
			case 'd': // 5 * 1
				newBlock = new block(x * 256, y * 256, "Sprites/Blocks/staticBlock/block(5-1).png");
				AddChild(newBlock);
				blocks->push_back(newBlock);
				break;
			case 'e': // 6 * 1
				newBlock = new block(x * 256, y * 256, "Sprites/Blocks/staticBlock/block(6-1).png");
				AddChild(newBlock);
				blocks->push_back(newBlock);
				break;
			case 'f': // 7 * 1
				newBlock = new block(x * 256, y * 256, "Sprites/Blocks/staticBlock/block(7-1).png");
				AddChild(newBlock);
				blocks->push_back(newBlock);
				break;
			case 'g': // 8 * 1
				newBlock = new block(x * 256, y * 256, "Sprites/Blocks/staticBlock/block(8-1).png");
				AddChild(newBlock);
				blocks->push_back(newBlock);
				break;
			case 'h': // 9 * 1
				newBlock = new block(x * 256, y * 256, "Sprites/Blocks/staticBlock/block(9-1).png");
				AddChild(newBlock);
				blocks->push_back(newBlock);
				break;
			case 'i': // 10 * 1
				newBlock = new block(x * 256, y * 256, "Sprites/Blocks/staticBlock/block(10-1).png");
				AddChild(newBlock);
				blocks->push_back(newBlock);
				break;

				// 세로 블록
			case 'A': // 1 * 2
				newBlock = new block(x * 256, y * 256, "Sprites/Blocks/staticBlock/block(1-2).png");
				AddChild(newBlock);
				blocks->push_back(newBlock);
				break;
			case 'B': // 1 * 3
				newBlock = new block(x * 256, y * 256, "Sprites/Blocks/staticBlock/block(1-3).png");
				AddChild(newBlock);
				blocks->push_back(newBlock);
				break;
			case 'C': // 1 * 4
				newBlock = new block(x * 256, y * 256, "Sprites/Blocks/staticBlock/block(1-4).png");
				AddChild(newBlock);
				blocks->push_back(newBlock);
				break;
			case 'D': // 1 * 5
				newBlock = new block(x * 256, y * 256, "Sprites/Blocks/staticBlock/block(1-5).png");
				AddChild(newBlock);
				blocks->push_back(newBlock);
				break;
			}
		}
		y++;
	}
	inFile.close();
#pragma endregion
#pragma region Create Objects
	switchs *newSwitch[21];
	portal *newPortal[14];
	IBlock *newBlock;

	emblem = new Entity();
	emblem->SetPos(Vec2F(112 * 256, 27 * 256));
	emblem->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Entities/emblem/love.png");
	if (data.col4)
		emblem->SetScale(Vec2F(0, 0));
	AddChild(emblem);

#pragma region Puzzle 1
	newSwitch[0] = new foothold(14 * 256, 21 * 256, BOTTOM);
	AddChild(newSwitch[0]);
	blocks->push_back(newSwitch[0]);

	newSwitch[1] = new foothold(12 * 256, 5 * 256, LEFT);
	AddChild(newSwitch[1]);
	blocks->push_back(newSwitch[1]);

	newSwitch[2] = new lever(27 * 256, 13 * 256, BOTTOM);
	AddChild(newSwitch[2]);
	blocks->push_back(newSwitch[2]);

	newSwitch[3] = new foothold(28 * 256, 13 * 256, BOTTOM);
	AddChild(newSwitch[3]);
	blocks->push_back(newSwitch[3]);

	newBlock = new door(256 * 10.f, 256 * 17.f, "Sprites/Blocks/staticBlock/block(5-1).png", Vec2F(256 * 10.f, 256 * 17.f), Vec2F(256 * 6.f, 256 * 17.f), 300.f);
	((door*)newBlock)->switchList->push_back(newSwitch[0]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 15.f, 256 * 9.f, "Sprites/Blocks/staticBlock/block(5-1).png", Vec2F(256 * 15.f, 256 * 9.f), Vec2F(256 * 20.f, 256 * 9.f), 400.f);
	((door*)newBlock)->switchList->push_back(newSwitch[2]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 35.f, 256 * 10.f, "Sprites/Blocks/staticBlock/block(1-4).png", Vec2F(256 * 35.f, 256 * 10.f), Vec2F(256 * 35.f, 256 * 14.f), 100.f);
	((door*)newBlock)->switchList->push_back(newSwitch[1]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new fan(256 * 34, 256 * 5, PI, 5, 21 * 256);
	((fan*)newBlock)->switchList->push_back(newSwitch[3]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new fan(256 * 34, 256 * 6, PI, 5, 21 * 256);
	((fan*)newBlock)->switchList->push_back(newSwitch[3]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new fan(256 * 34, 256 * 7, PI, 5, 21 * 256);
	((fan*)newBlock)->switchList->push_back(newSwitch[3]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new fan(256 * 34, 256 * 8, PI, 5, 21 * 256);
	((fan*)newBlock)->switchList->push_back(newSwitch[3]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newPortal[0] = new portal(31 * 256, 2 * 256);
	AddChild(newPortal[0]);
	blocks->push_back(newPortal[0]);

	newPortal[1] = new portal(18 * 256, 10 * 256);
	AddChild(newPortal[1]);
	blocks->push_back(newPortal[1]);
	newPortal[1]->target = newPortal[0];

	newPortal[2] = new portal(51 * 256, 22 * 256);
	AddChild(newPortal[2]);
	blocks->push_back(newPortal[2]);

	newPortal[3] = new portal(38 * 256, 11 * 256);
	AddChild(newPortal[3]);
	blocks->push_back(newPortal[3]);
	newPortal[3]->target = newPortal[2];
#pragma endregion
#pragma region Puzzle 2
	newSwitch[4] = new lever(61 * 256, 24 * 256, BOTTOM);
	AddChild(newSwitch[4]);
	blocks->push_back(newSwitch[4]);

	newSwitch[5] = new lever(59 * 256, 24 * 256, BOTTOM);
	AddChild(newSwitch[5]);
	blocks->push_back(newSwitch[5]);

	newSwitch[6] = new lever(51 * 256, 20 * 256, LEFT);
	AddChild(newSwitch[6]);
	blocks->push_back(newSwitch[6]);

	newSwitch[7] = new foothold(72 * 256, 24 * 256, BOTTOM);
	AddChild(newSwitch[7]);
	blocks->push_back(newSwitch[7]);

	newBlock = new fan(256 * 71, 256 * 20, PI, 7, 9 * 256);
	((fan*)newBlock)->switchList->push_back(newSwitch[4]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new fan(256 * 71, 256 * 19, PI, 7, 9 * 256);
	((fan*)newBlock)->switchList->push_back(newSwitch[4]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new fan(256 * 62, 256 * 21, -PI / 3, 12, 5 * 256);
	((fan*)newBlock)->switchList->push_back(newSwitch[5]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 65.f, 256 * 21.f, "Sprites/Blocks/staticBlock/block(3-1).png", Vec2F(256 * 65.f, 256 * 21.f), Vec2F(256 * 65.f, 256 * 25.f), 300.f);
	((door*)newBlock)->switchList->push_back(newSwitch[6]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new fan(256 * 75, 256 * 25, -PI / 4, 10, 5 * 256);
	((fan*)newBlock)->switchList->push_back(newSwitch[7]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new fan(256 * 83, 256 * 25, -PI * 3 / 4, 10, 5 * 256, true);
	((fan*)newBlock)->switchList->push_back(newSwitch[7]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newPortal[4] = new portal(52 * 256, 27 * 256);
	AddChild(newPortal[4]);
	blocks->push_back(newPortal[4]);

	newPortal[5] = new portal(82 * 256, 17 * 256);
	AddChild(newPortal[5]);
	blocks->push_back(newPortal[5]);
	newPortal[5]->target = newPortal[4];

	newPortal[6] = new portal(116 * 256, 26 * 256);
	AddChild(newPortal[6]);
	blocks->push_back(newPortal[6]);

	newPortal[7] = new portal(80 * 256, 27 * 256);
	AddChild(newPortal[7]);
	blocks->push_back(newPortal[7]);
	newPortal[7]->target = newPortal[6];
#pragma endregion
#pragma region Puzzle 3
	newSwitch[8] = new lever(129 * 256, 24 * 256, TOP);
	AddChild(newSwitch[8]);
	blocks->push_back(newSwitch[8]);

	newSwitch[9] = new foothold(129 * 256, 25 * 256, RIGHT);
	AddChild(newSwitch[9]);
	blocks->push_back(newSwitch[9]);

	newSwitch[10] = new foothold(115 * 256, 22 * 256, LEFT);
	AddChild(newSwitch[10]);
	blocks->push_back(newSwitch[10]);

	newSwitch[11] = new foothold(136 * 256, 22 * 256, LEFT);
	AddChild(newSwitch[11]);
	blocks->push_back(newSwitch[11]);

	newSwitch[12] = new foothold(136 * 256, 21 * 256, LEFT);
	AddChild(newSwitch[12]);
	blocks->push_back(newSwitch[12]);

	newSwitch[13] = new foothold(143 * 256, 28 * 256, LEFT);
	AddChild(newSwitch[13]);
	blocks->push_back(newSwitch[13]);

	newSwitch[14] = new foothold(155 * 256, 28 * 256, RIGHT);
	AddChild(newSwitch[14]);
	blocks->push_back(newSwitch[14]);

	newBlock = new movingBlock(256 * 122.f, 256 * 30.f, "Sprites/Blocks/staticBlock/block(3-1).png", Vec2F(256 * 122.f, 256 * 30.f), Vec2F(256 * 122.f, 256 * 19.5f), movingBlock::DIR::POS1, 200.f);
	((movingBlock*)newBlock)->switchList->push_back(newSwitch[8]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 125.f, 256 * 18.f, "Sprites/Blocks/staticBlock/block(1-5).png", Vec2F(256 * 125.f, 256 * 18.f), Vec2F(256 * 125.f, 256 * 23.f), 300.f);
	((door*)newBlock)->switchList->push_back(newSwitch[9]);
	((door*)newBlock)->switchList->push_back(newSwitch[10]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new movingBlock(256 * 145.f, 256 * 23.f, "Sprites/Blocks/staticBlock/block(3-1).png", Vec2F(256 * 145.f, 256 * 30.f), Vec2F(256 * 145.f, 256 * 19.5f), movingBlock::DIR::POS1, 300.f);
	((movingBlock*)newBlock)->switchList->push_back(newSwitch[11]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new fan(256 * 153, 256 * 29, -PI / 2, 10, 7 * 256);
	((fan*)newBlock)->switchList->push_back(newSwitch[12]);
	((fan*)newBlock)->switchList->push_back(newSwitch[13]);
	((fan*)newBlock)->switchList->push_back(newSwitch[14]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newPortal[8] = new portal(136 * 256, 19 * 256);
	AddChild(newPortal[8]);
	blocks->push_back(newPortal[8]);

	newPortal[9] = new portal(140 * 256, 25 * 256);
	AddChild(newPortal[9]);
	blocks->push_back(newPortal[9]);
	newPortal[9]->target = newPortal[8];

	newPortal[10] = new portal(116 * 256, 15 * 256);
	AddChild(newPortal[10]);
	blocks->push_back(newPortal[10]);

	newPortal[11] = new portal(156 * 256, 21 * 256);
	AddChild(newPortal[11]);
	blocks->push_back(newPortal[11]);
	newPortal[11]->target = newPortal[10];
	newPortal[10]->target = newPortal[11];
#pragma endregion

#pragma endregion
#pragma region Default Setting 2
	blueEntity = new blue();
	blueEntity->pos.x = data.bluePos;
	AddChild(blueEntity);

	AddChild((new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256 / 52.70114942528736f, 256 / 52.70114942528736f))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage4/front.png")->GetOwner());
	fade = new Entity();
	fade->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/fade.png");
	fade->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam);
	fade->SetScale(Vec2F(1 / 0.16f, 1 / 0.16f));
	fade->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, 1.f)))->SetEnabled(true);
	AddChild(fade);

	text = new Entity();
	text->AttachComponent<TextRenderer>(
		"Maps/DoHyeon-Regula.ttf", 35, 0.f,
		Color(1.f, 1.f, 1.f, 1.f),
		Color(1.f, 1.f, 1.f, 1.f), "");
	text->AttachComponent<UI>(Vec2F(30, -70), UI::DIR::LEFT_BOTTOM, cam);
	if (data.isGiveup)
	{
		int ran = Random(0, 5);
		if (ran == 0) text->GetComponent<TextRenderer>()->SetText("가끔은 포기해도 괜찮을거야");
		if (ran == 1) text->GetComponent<TextRenderer>()->SetText("내 탓이 아니야");
		if (ran == 2) text->GetComponent<TextRenderer>()->SetText("이번 한번만..");
		if (ran == 3) text->GetComponent<TextRenderer>()->SetText("힘들다면 피해야지");
		if (ran == 4) text->GetComponent<TextRenderer>()->SetText("어차피 가망은 없었어");
		if (ran == 5) text->GetComponent<TextRenderer>()->SetText("포기가 마음 편할지도 모르겠네");
	}
	else if (data.nowPuzzle != 0)
	{
		int ran = Random(0, 5);
		if (ran == 0) text->GetComponent<TextRenderer>()->SetText("좋아. 다시 해보는거야");
		if (ran == 1) text->GetComponent<TextRenderer>()->SetText("한번 더 도전해보자");
		if (ran == 2) text->GetComponent<TextRenderer>()->SetText("아직 실패한게 아니야");
		if (ran == 3) text->GetComponent<TextRenderer>()->SetText("잘 할 수 있을거야");
		if (ran == 4) text->GetComponent<TextRenderer>()->SetText("나는 나를 믿어");
		if (ran == 5) text->GetComponent<TextRenderer>()->SetText("계속 시도한다면..");
	}
	AddChild(text);


	fadeTime = 1.7f;

	debug = new Entity();
	debug->AttachComponent<TextRenderer>(
		"Maps/DoHyeon-Regula.ttf", 35, 0.f,
		Color(1.f, 1.f, 1.f, 1.f),
		Color(1.f, 1.f, 1.f, 1.f), "");
	debug->AttachComponent<UI>(Vec2F(30, -140), UI::DIR::LEFT_BOTTOM, cam);
	AddChild(debug);
#pragma endregion
}
void Stage4::OnUpdate() {

	Stage::OnUpdate();
	cam->Update();

	blueEntity->pos.x += DT * 14;
	blueEntity->pos.y = -cam->pos_.y - (1 / cam->zoom - 1) * (LONG)App::GetInstance()->GetSettings()->windowHeight / 2;;

	if (player->pos.x >= 166 * 256 && fadeTime == 0)
	{
		fadeTime = -1.3f;
		isGiveup = false;
		isNextstage = true;
	}
	if (player->pos.y >= 32 * 256 && fadeTime == 0)
	{
		fadeTime = -1.3f;
		isGiveup = false;
	}

	if (player->pos.x <= emblem->pos.x + 256
		&& player->pos.x + 256 >= emblem->pos.x
		&& player->pos.y <= emblem->pos.y + 256
		&& player->pos.y + 512 >= emblem->pos.y
		&& !data.col4)
	{
		emblem->SetScale(Vec2F(0, 0));
		data.col4 = true;
		for (int i = 0; i < 25; i++)
		{
			Entity* newParticle = new emblemParticle(emblem->pos.x, emblem->pos.y, "Sprites/Entities/emblem/love.png");
			float speed = Random(20.f, 35.f);
			float angle = Random(-PI, PI);
			float scale = Random(0.5f, 1.5f);
			newParticle->GetComponent<RigidBody>()->velocityX = cos(angle) * speed;
			newParticle->GetComponent<RigidBody>()->velocityY = sin(angle) * speed;
			newParticle->SetScale(Vec2F(scale, scale));
			AddChild(newParticle);
			particles->push_back(newParticle);
			RG2SoundManager->Play(SoundID::sEmblem, false, false);
		}
	}
}

Stage4::~Stage4()
{
}

void Stage4::ChangeScene()
{
	RG2SceneManager->ChangeScene(new End({ data.col1, data.col2, data.col3, data.col4, data.col5, 0, false, data.giveupCount, -3500, false }));
}

void Stage4::GiveUp()
{
	if (player->pos.x <= 40 * 256)
		RG2SceneManager->ChangeScene(new Stage4({ data.col1, data.col2, data.col3, data.col4, data.col5, 2, isGiveup, data.giveupCount, blueEntity->pos.x, false }));
	else if (player->pos.x <= 87 * 256)
		RG2SceneManager->ChangeScene(new Stage4({ data.col1, data.col2, data.col3, data.col4, data.col5, 3, isGiveup, data.giveupCount, blueEntity->pos.x, false }));
	else
		RG2SceneManager->ChangeScene(new Stage4({ data.col1, data.col2, data.col3, data.col4, data.col5, 4, isGiveup, data.giveupCount, blueEntity->pos.x, false }));
}

void Stage4::ReGame()
{
	if (player->pos.x <= 40 * 256)
		RG2SceneManager->ChangeScene(new Stage4({ data.col1, data.col2, data.col3, data.col4, data.col5, 1, isGiveup, data.giveupCount, blueEntity->pos.x, false }));
	else if (player->pos.x <= 87 * 256)
		RG2SceneManager->ChangeScene(new Stage4({ data.col1, data.col2, data.col3, data.col4, data.col5, 2, isGiveup, data.giveupCount, blueEntity->pos.x, false }));
	else
		RG2SceneManager->ChangeScene(new Stage4({ data.col1, data.col2, data.col3, data.col4, data.col5, 3, isGiveup, data.giveupCount, blueEntity->pos.x, false }));
}

bool Stage4::CanRegame()
{
	if (player->pos.x <= 40 * 256)
	{
		if (13 * 256 - blueEntity->pos.x > 3000 && blueEntity->pos > 0 || blueEntity->pos < 0)
			return true;
	}
	else if (player->pos.x <= 87 * 256)
	{
		if (52 * 256 - blueEntity->pos.x > 3000 && blueEntity->pos > 0 || blueEntity->pos < 0)
			return true;
	}
	else if (117 * 256 - blueEntity->pos.x > 3000 && blueEntity->pos > 0 || blueEntity->pos < 0)
		return true;
	return false;
}