#include "pch.h"
#include "Stage3.h"
#include "Stage4.h"
#include "emblemParticle.h"

Stage3::Stage3(Data data)
{
#pragma region Default Setting
	blocks = new list<IBlock*>;
	particles = new list<Entity*>;
	this->data = data;
	endPos = 163.5f;
	isGiveup = false;
	isGameover = false;
	isNextstage = false;

	cam = new Camera(this);
	cam->SetZoom(0.16f);
	cam->SetRange(Rect(0, 0, 173 * 256, 256 * 31));
#pragma region BackGround
	background[0] = new Entity();
	background[0]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage3/layer1.png");
	background[0]->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam);
	AddChild(background[0]);

	background[1] = new Entity();
	background[1]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage3/layer2.png");
	background[1]->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam);
	AddChild(background[1]);

	background[2] = new Entity();
	background[2]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage3/layer2.png");
	background[2]->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam);
	AddChild(background[2]);

	background[3] = new Entity();
	background[3]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage3/layer3.png");
	background[3]->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam);
	AddChild(background[3]);

	background[4] = new Entity();
	background[4]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage3/layer3.png");
	background[4]->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam);
	AddChild(background[4]);
#pragma endregion

	player = new Player();
	AddChild(player);

	if (data.nowPuzzle == 1)
		player->SetPos(Vec2F(17 * 256, 3 * 256));
	else if (data.nowPuzzle == 2)
		player->SetPos(Vec2F(65 * 256, 14 * 256));
	else if (data.nowPuzzle == 3)
		player->SetPos(Vec2F(134 * 256, 12 * 256));
	else if (data.nowPuzzle == 4)
		player->SetPos(Vec2F(166 * 256, 20 * 256));
	else
		player->SetPos(Vec2F(8 * 256, 3 * 256));

	cam->Follow(player);
#pragma endregion
#pragma region File Input
	ifstream inFile("Map/Stage3.txt");
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
	portal *newPortal[10];
	IBlock *newBlock;

	emblem = new Entity();
	emblem->SetPos(Vec2F(71.5f * 256, 10 * 256));
	emblem->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Entities/emblem/honor.png");
	if (data.col3)
		emblem->SetScale(Vec2F(0, 0));
	AddChild(emblem);

#pragma region Puzzle 1
	newSwitch[0] = new lever(0, 0, BOTTOM);
	newSwitch[0]->isRelative = true;
	newSwitch[0]->relativePos = Vec2F(512, -256);
	AddChild(newSwitch[0]);
	blocks->push_back(newSwitch[0]);

	newSwitch[1] = new button(19 * 256, 15 * 256, BOTTOM, 1.f);
	AddChild(newSwitch[1]);
	blocks->push_back(newSwitch[1]);

	newSwitch[2] = new foothold(31 * 256, 10 * 256, RIGHT);
	AddChild(newSwitch[2]);
	blocks->push_back(newSwitch[2]);

	newSwitch[3] = new foothold(31 * 256, 6 * 256, TOP);
	AddChild(newSwitch[3]);
	blocks->push_back(newSwitch[3]);

	newSwitch[4] = new foothold(27 * 256, 6 * 256, TOP);
	AddChild(newSwitch[4]);
	blocks->push_back(newSwitch[4]);

	newSwitch[5] = new lever(39 * 256, 9 * 256, RIGHT);
	AddChild(newSwitch[5]);
	blocks->push_back(newSwitch[5]);

	newBlock = new door(256 * 20.f, 256 * 5.f, "Sprites/Blocks/staticBlock/block(3-1).png", Vec2F(256 * 20.f, 256 * 5.f), Vec2F(256 * 20.f, 256 * 16.f), 600.f);
	((door*)newBlock)->switchList->push_back(newSwitch[0]);
	((door*)newBlock)->switchList->push_back(newSwitch[1]);
	((door*)newBlock)->allActive = false;
	newSwitch[0]->owner = newBlock;
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 23.f, 256 * 6.f, "Sprites/Blocks/staticBlock/block(1-2).png", Vec2F(256 * 23.f, 256 * 6.f), Vec2F(256 * 23.f, 256 * 9.f), 600.f);
	((door*)newBlock)->switchList->push_back(newSwitch[2]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 32.f, 256 * 12.f, "Sprites/Blocks/staticBlock/block(1-4).png", Vec2F(256 * 32.f, 256 * 12.f), Vec2F(256 * 32.f, 256 * 17.f), 800.f);
	((door*)newBlock)->switchList->push_back(newSwitch[3]);
	((door*)newBlock)->switchList->push_back(newSwitch[4]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 40.f, 256 * 2.f, "Sprites/Blocks/staticBlock/block(1-3).png", Vec2F(256 * 40.f, 256 * 2.f), Vec2F(256 * 40.f, 256 * 4.f), 800.f);
	((door*)newBlock)->switchList->push_back(newSwitch[5]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newPortal[0] = new portal(44 * 256, 2 * 256);
	AddChild(newPortal[0]);
	blocks->push_back(newPortal[0]);
	newPortal[1] = new portal(61 * 256, 13 * 256);
	AddChild(newPortal[1]);
	blocks->push_back(newPortal[1]);
	newPortal[0]->target = newPortal[1];
#pragma endregion
#pragma region Puzzle 2
	newSwitch[6] = new lever(88 * 256, 5 * 256, TOP);
	AddChild(newSwitch[6]);
	blocks->push_back(newSwitch[6]);

	newSwitch[7] = new foothold(92 * 256, 9 * 256, BOTTOM);
	AddChild(newSwitch[7]);
	blocks->push_back(newSwitch[7]);

	newSwitch[8] = new foothold(105 * 256, 9 * 256, RIGHT);
	AddChild(newSwitch[8]);
	blocks->push_back(newSwitch[8]);

	newSwitch[9] = new lever(93 * 256, 2 * 256, LEFT);
	AddChild(newSwitch[9]);
	blocks->push_back(newSwitch[9]);

	newBlock = new door(256 * 85.f, 256 * 8.f, "Sprites/Blocks/staticBlock/block(2-1).png", Vec2F(256 * 85.f, 256 * 8.f), Vec2F(256 * 83.f, 256 * 8.f), 200.f);
	((door*)newBlock)->switchList->push_back(newSwitch[6]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 93.f, 256 * 6.f, "Sprites/Blocks/staticBlock/block(4-1).png", Vec2F(256 * 93.f, 256 * 6.f), Vec2F(256 * 89.f, 256 * 6.f), 200.f);
	((door*)newBlock)->switchList->push_back(newSwitch[7]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new movingBlock(256 * 103.f, 256 * 5.8f, "Sprites/Blocks/staticBlock/block(3-1).png", Vec2F(256 * 103.f, 256 * 5.8f), Vec2F(256 * 103.f, 256 * 9.f), movingBlock::DIR::POS1, 200.f);
	((movingBlock*)newBlock)->switchList->push_back(newSwitch[8]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new movingBlock(256 * 107.f, 256 * 6.f, "Sprites/Blocks/staticBlock/block(2-1).png", Vec2F(256 * 107.f, 256 * 6.f), Vec2F(256 * 107.f, 256 * 24.f), movingBlock::DIR::POS1, 500.f);
	((movingBlock*)newBlock)->switchList->push_back(newSwitch[8]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 114.f, 256 * 3.f, "Sprites/Blocks/staticBlock/block(1-3).png", Vec2F(256 * 114.f, 256 * 3.f), Vec2F(256 * 114.f, 0), 200.f);
	((door*)newBlock)->switchList->push_back(newSwitch[9]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newPortal[2] = new portal(117 * 256, 4 * 256);
	AddChild(newPortal[2]);
	blocks->push_back(newPortal[2]);
	newPortal[3] = new portal(129 * 256, 11 * 256);
	AddChild(newPortal[3]);
	blocks->push_back(newPortal[3]);
	newPortal[2]->target = newPortal[3];
#pragma endregion
#pragma region Puzzle 3
	newSwitch[10] = new lever(138 * 256, 13 * 256, BOTTOM);
	AddChild(newSwitch[10]);
	blocks->push_back(newSwitch[10]);

	newSwitch[11] = new lever(139 * 256, 4 * 256, LEFT);
	AddChild(newSwitch[11]);
	blocks->push_back(newSwitch[11]);

	newSwitch[12] = new lever(132 * 256, 17 * 256, BOTTOM);
	AddChild(newSwitch[12]);
	blocks->push_back(newSwitch[12]);

	newBlock = new door(256 * 139.f, 256 * 10.f, "Sprites/Blocks/staticBlock/block(10-1).png", Vec2F(256 * 139.f, 256 * 10.f), Vec2F(256 * 129.f, 256 * 10.f), 600.f);
	((door*)newBlock)->switchList->push_back(newSwitch[10]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 155.f, 256 * 8.f, "Sprites/Blocks/staticBlock/block(1-3).png", Vec2F(256 * 155.f, 256 * 8.f), Vec2F(256 * 155.f, 256 * 11.f), 200.f);
	((door*)newBlock)->switchList->push_back(newSwitch[11]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 139.f, 256 * 17.9f, "Sprites/Blocks/staticBlock/block(4-1).png", Vec2F(256 * 139.f, 256 * 17.9f), Vec2F(256 * 139.f, 256 * 28.f), 400.f);
	((door*)newBlock)->switchList->push_back(newSwitch[11]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 143.f, 256 * 17.9f, "Sprites/Blocks/staticBlock/block(10-1).png", Vec2F(256 * 143.f, 256 * 17.9f), Vec2F(256 * 143.f, 256 * 28.f), 400.f);
	((door*)newBlock)->switchList->push_back(newSwitch[11]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 164.f, 256 * 19.f, "Sprites/Blocks/staticBlock/block(1-3).png", Vec2F(256 * 164.f, 256 * 19.f), Vec2F(256 * 164.f, 256 * 22.f), 200.f);
	((door*)newBlock)->switchList->push_back(newSwitch[12]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newPortal[4] = new portal(156 * 256, 9 * 256);
	AddChild(newPortal[4]);
	blocks->push_back(newPortal[4]);
	newPortal[5] = new portal(129 * 256, 15 * 256);
	AddChild(newPortal[5]);
	blocks->push_back(newPortal[5]);
	newPortal[4]->target = newPortal[5];
#pragma endregion

#pragma endregion
#pragma region Default Setting 2
	blueEntity = new blue();
	blueEntity->pos.x = data.bluePos;
	AddChild(blueEntity);

	AddChild((new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256 / 52.70689655172414f, 256 / 52.70689655172414f))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage3/front.png")->GetOwner());
	darkness = new Entity();
	darkness->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage3/darkness.png");
	darkness->SetScale(Vec2F(5.5f, 5.5f));
	AddChild(darkness);

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
		text->GetComponent<TextRenderer>()->SetText("가끔은 포기해도 괜찮을거야");
	else if (data.nowPuzzle != 0)
		text->GetComponent<TextRenderer>()->SetText("좋아, 다시 해보는거야");
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
void Stage3::OnUpdate() {

	Stage::OnUpdate();
	cam->Update();

	blueEntity->pos.x += DT * 14;
	blueEntity->pos.y = -cam->pos_.y - (1 / cam->zoom - 1) * (LONG)App::GetInstance()->GetSettings()->windowHeight / 2;;

	darkness->pos = Vec2F(player->pos.x + 128 - 2880 * 5.5f, player->pos.y + 256 - 1620 * 5.5f);

	if (player->pos.x >= 171 * 256 && fadeTime == 0)
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
		&& !data.col3)
	{
		emblem->SetScale(Vec2F(0, 0));
		data.col3 = true;
		for (int i = 0; i < 25; i++)
		{
			Entity* newParticle = new emblemParticle(emblem->pos.x, emblem->pos.y, "Sprites/Entities/emblem/honor.png");
			float speed = Random(20.f, 35.f);
			float angle = Random(-PI, PI);
			float scale = Random(0.5f, 1.5f);
			newParticle->GetComponent<RigidBody>()->velocityX = cos(angle) * speed;
			newParticle->GetComponent<RigidBody>()->velocityY = sin(angle) * speed;
			newParticle->SetScale(Vec2F(scale, scale));
			AddChild(newParticle);
			particles->push_back(newParticle);
		}
	}
}

Stage3::~Stage3()
{
}

void Stage3::ChangeScene()
{
	RG2SceneManager->ChangeScene(new Stage4({ data.col1, data.col2, data.col3, data.col4, data.col5, 0, false, data.giveupCount, -3500, false }));
}

void Stage3::GiveUp()
{
	if (player->pos.x <= 49 * 256)
		RG2SceneManager->ChangeScene(new Stage3({ data.col1, data.col2, data.col3, data.col4, data.col5, 2, isGiveup, data.giveupCount, blueEntity->pos.x, false }));
	else if (player->pos.x <= 107 * 256)
		RG2SceneManager->ChangeScene(new Stage3({ data.col1, data.col2, data.col3, data.col4, data.col5, 3, isGiveup, data.giveupCount, blueEntity->pos.x, false }));
	else
		RG2SceneManager->ChangeScene(new Stage3({ data.col1, data.col2, data.col3, data.col4, data.col5, 4, isGiveup, data.giveupCount, blueEntity->pos.x, false }));
}

void Stage3::ReGame()
{
	if (player->pos.x <= 49 * 256)
		RG2SceneManager->ChangeScene(new Stage3({ data.col1, data.col2, data.col3, data.col4, data.col5, 1, isGiveup, data.giveupCount, blueEntity->pos.x, false }));
	else if (player->pos.x <= 107 * 256)
		RG2SceneManager->ChangeScene(new Stage3({ data.col1, data.col2, data.col3, data.col4, data.col5, 2, isGiveup, data.giveupCount, blueEntity->pos.x, false }));
	else
		RG2SceneManager->ChangeScene(new Stage3({ data.col1, data.col2, data.col3, data.col4, data.col5, 3, isGiveup, data.giveupCount, blueEntity->pos.x, false }));
}

bool Stage3::CanRegame()
{
	if (player->pos.x <= 49 * 256)
	{
		if (17 * 256 - blueEntity->pos.x > 3000 && blueEntity->pos > 0 || blueEntity->pos < 0)
			return true;
	}
	else if (player->pos.x <= 107 * 256)
	{
		if (65 * 256 - blueEntity->pos.x > 3000 && blueEntity->pos > 0 || blueEntity->pos < 0)
			return true;
	}
	else if (134 * 256 - blueEntity->pos.x > 3000 && blueEntity->pos > 0 || blueEntity->pos < 0)
		return true;
	return false;
}