#include "pch.h"
#include "Stage2.h"
#include "Stage3.h"
#include "emblemParticle.h"

Stage2::Stage2(Data data)
{
#pragma region Default Setting
	blocks = new list<IBlock*>;
	particles = new list<Entity*>;
	this->data = data;
	endPos = 115;
	isGiveup = false;
	isGameover = false;
	isNextstage = false;

	cam = new Camera(this);
	cam->SetZoom(0.16f);
	cam->SetRange(Rect(0, 0, 130 * 256, 256 * 42));
#pragma region BackGround
	background[0] = new Entity();
	background[0]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage2/layer1.png");
	background[0]->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam);
	AddChild(background[0]);

	background[1] = new Entity();
	background[1]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage2/layer2.png");
	background[1]->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam);
	AddChild(background[1]);

	background[2] = new Entity();
	background[2]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage2/layer2.png");
	background[2]->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam);
	AddChild(background[2]);

	background[3] = new Entity();
	background[3]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage2/layer3.png");
	background[3]->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam);
	AddChild(background[3]);

	background[4] = new Entity();
	background[4]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage2/layer3.png");
	background[4]->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam);
	AddChild(background[4]);
#pragma endregion
	AddChild((new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256.f / 70, 256.f / 70))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage2/back.png")->GetOwner());

	player = new Player();
	AddChild(player);

	if (data.nowPuzzle == 1)
		player->SetPos(Vec2F(17 * 256, 38 * 256));
	else if (data.nowPuzzle == 2)
		player->SetPos(Vec2F(46 * 256, 38 * 256));
	else if (data.nowPuzzle == 3)
		player->SetPos(Vec2F(90 * 256, 38 * 256));
	else if (data.nowPuzzle == 4)
		player->SetPos(Vec2F(117 * 256, 38 * 256));
	else
		player->SetPos(Vec2F(8 * 256, 38 * 256));

	cam->Follow(player);
#pragma endregion
#pragma region File Input
	ifstream inFile("Map/Stage2.txt");
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
	IBlock *ref;

	emblem = new Entity();
	emblem->SetPos(Vec2F(63 * 256, 37 * 256));
	emblem->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Entities/emblem/friendship.png");
	if (data.col2)
		emblem->SetScale(Vec2F(0, 0));
	AddChild(emblem);

#pragma region Puzzle 1
	newSwitch[0] = new lever(0, 0, BOTTOM, true);
	newSwitch[0]->isRelative = true;
	newSwitch[0]->relativePos = Vec2F(512, -256);
	AddChild(newSwitch[0]);
	blocks->push_back(newSwitch[0]);

	newSwitch[1] = new button(27 * 256, 38 * 256, BOTTOM, 1.f);
	AddChild(newSwitch[1]);
	blocks->push_back(newSwitch[1]);

	newSwitch[2] = new foothold(20 * 256, 7.95f * 256, TOP);
	AddChild(newSwitch[2]);
	blocks->push_back(newSwitch[2]);

	newSwitch[3] = new foothold(24 * 256, 7.95f * 256, TOP);
	AddChild(newSwitch[3]);
	blocks->push_back(newSwitch[3]);

	newBlock = new door(256 * 28.f, 256 * 39.f, "Sprites/Blocks/staticBlock/block(3-1).png", Vec2F(256 * 28.f, 256 * 13.f), Vec2F(256 * 28.f, 256 * 39.f), 600.f);
	((door*)newBlock)->switchList->push_back(newSwitch[0]);
	((door*)newBlock)->switchList->push_back(newSwitch[1]);
	((door*)newBlock)->allActive = false;
	newSwitch[0]->owner = newBlock;
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new moveableBlock(256 * 23, 256 * 17, "Sprites/Blocks/moveableBlock/moveableBlock2.png");
	AddChild(newBlock);
	blocks->push_back(newBlock);
	ref = newBlock;

	newBlock = new moveableBlock(0, 0, "Sprites/Blocks/moveableBlock/moveableBlock1.png");
	((moveableBlock*)newBlock)->isRelative = true;
	((moveableBlock*)newBlock)->relativePos = Vec2F(0, -256);
	((moveableBlock*)newBlock)->owner = ref;
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new moveableBlock(256 * 21, 256 * 11, "Sprites/Blocks/moveableBlock/moveableBlock2.png");
	AddChild(newBlock);
	blocks->push_back(newBlock);
	ref = newBlock;

	newBlock = new moveableBlock(0, 0, "Sprites/Blocks/moveableBlock/moveableBlock1.png");
	((moveableBlock*)newBlock)->isRelative = true;
	((moveableBlock*)newBlock)->relativePos = Vec2F(0, -256);
	((moveableBlock*)newBlock)->owner = ref;
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new moveableBlock(256 * 23, 256 * 26, "Sprites/Blocks/moveableBlock/moveableBlock2.png");
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 31.f, 256 * 36.f, "Sprites/Blocks/staticBlock/block(1-3).png", Vec2F(256 * 31.f, 256 * 36.f), Vec2F(256 * 31.f, 256 * 40.f), 50.f);
	((door*)newBlock)->switchList->push_back(newSwitch[2]);
	((door*)newBlock)->switchList->push_back(newSwitch[3]);
	AddChild(newBlock);
	blocks->push_back(newBlock);
#pragma endregion
#pragma region Puzzle 2
	newSwitch[4] = new lever(52 * 256, 33 * 256, LEFT);
	AddChild(newSwitch[4]);
	blocks->push_back(newSwitch[4]);

	newSwitch[5] = new lever(52 * 256, 24 * 256, LEFT);
	AddChild(newSwitch[5]);
	blocks->push_back(newSwitch[5]);

	newSwitch[6] = new foothold(61 * 256, 28 * 256, BOTTOM);
	AddChild(newSwitch[6]);
	blocks->push_back(newSwitch[6]);

	newSwitch[7] = new lever(58 * 256, 12 * 256, RIGHT);
	AddChild(newSwitch[7]);
	blocks->push_back(newSwitch[7]);

	newSwitch[8] = new foothold(72 * 256, 18 * 256, RIGHT);
	AddChild(newSwitch[8]);
	blocks->push_back(newSwitch[8]);

	newSwitch[9] = new foothold(69 * 256, 31 * 256, BOTTOM);
	AddChild(newSwitch[9]);
	blocks->push_back(newSwitch[9]);

	newSwitch[16] = new foothold(60 * 256, 38 * 256, BOTTOM);
	AddChild(newSwitch[16]);
	blocks->push_back(newSwitch[16]);

	newBlock = new door(256 * 65.f, 256 * 36.f, "Sprites/Blocks/staticBlock/block(1-3).png", Vec2F(256 * 65.f, 256 * 36.f), Vec2F(256 * 65.f, 256 * 40.f), 120.f);
	((door*)newBlock)->switchList->push_back(newSwitch[16]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new fan(256 * 58.f, 256 * 40.f, PI / -2.f, 52.f, 1000.f);
	((fan*)newBlock)->switchList->push_back(newSwitch[4]);
	AddChild(newBlock);
	blocks->push_back(newBlock); 

	newBlock = new movingBlock(256 * 56.f, 256 * 19.f, "Sprites/Blocks/staticBlock/block(3-1).png", Vec2F(256 * 56.f, 256 * 19.f), Vec2F(256 * 56.f, 256 * 31.f), movingBlock::DIR::POS1, 300.f);
	((door*)newBlock)->switchList->push_back(newSwitch[5]);
	((door*)newBlock)->switchList->push_back(newSwitch[6]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 65.f, 256 * 16.f, "Sprites/Blocks/staticBlock/block(1-3).png", Vec2F(256 * 65.f, 256 * 16.f), Vec2F(256 * 65.f, 256 * 20.f), 100.f);
	((door*)newBlock)->switchList->push_back(newSwitch[7]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 62.f, 256 * 27.f, "Sprites/Blocks/staticBlock/block(1-2).png", Vec2F(256 * 62.f, 256 * 27.f), Vec2F(256 * 62.f, 256 * 25.f), 100.f);
	((door*)newBlock)->switchList->push_back(newSwitch[7]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 73.f, 256 * 36.f, "Sprites/Blocks/staticBlock/block(1-3).png", Vec2F(256 * 73.f, 256 * 36.f), Vec2F(256 * 73.f, 256 * 40.f), 50.f);
	((door*)newBlock)->switchList->push_back(newSwitch[8]);
	((door*)newBlock)->switchList->push_back(newSwitch[9]);
	AddChild(newBlock);
	blocks->push_back(newBlock);
#pragma endregion
#pragma region Puzzle 3
	newSwitch[10] = new lever(0, 0, BOTTOM, true);
	newSwitch[10]->isRelative = true;
	newSwitch[10]->relativePos = Vec2F(256, -256);
	AddChild(newSwitch[10]);
	blocks->push_back(newSwitch[10]);

	newSwitch[11] = new button(95 * 256, 38 * 256, BOTTOM, 1.2f);
	AddChild(newSwitch[11]);
	blocks->push_back(newSwitch[11]);

	newSwitch[12] = new foothold(109 * 256, 2 * 256, RIGHT);
	AddChild(newSwitch[12]);
	blocks->push_back(newSwitch[12]);

	newSwitch[13] = new foothold(108 * 256, 27 * 256, BOTTOM);
	AddChild(newSwitch[13]);
	blocks->push_back(newSwitch[13]);

	newSwitch[14] = new foothold(92 * 256, 13 * 256, BOTTOM);
	AddChild(newSwitch[14]);
	blocks->push_back(newSwitch[14]);

	newBlock = new door(256 * 97.f, 256 * 39.1f, "Sprites/Blocks/staticBlock/block(7-1).png", Vec2F(256 * 97.f, 256 * 7.f), Vec2F(256 * 97.f, 256 * 39.1f), 1000.f);
	((door*)newBlock)->switchList->push_back(newSwitch[10]);
	((door*)newBlock)->switchList->push_back(newSwitch[11]);
	((door*)newBlock)->allActive = false;
	newSwitch[10]->owner = newBlock;
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 105.f, 256 * 35.f, "Sprites/Blocks/staticBlock/block(1-4).png", Vec2F(256 * 105.f, 256 * 35.f), Vec2F(256 * 105.f, 256 * 40.f), 50.f);
	((door*)newBlock)->switchList->push_back(newSwitch[12]);
	((door*)newBlock)->switchList->push_back(newSwitch[13]);
	((door*)newBlock)->switchList->push_back(newSwitch[14]);
	AddChild(newBlock);
	blocks->push_back(newBlock);
#pragma endregion
#pragma endregion
#pragma region Default Setting 2
	blueEntity = new blue();
	blueEntity->pos.x = data.bluePos;
	AddChild(blueEntity);

	AddChild((new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256.f / 70, 256.f / 70))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage2/front.png")->GetOwner());

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
void Stage2::OnUpdate() {

	Stage::OnUpdate();
	cam->Update();

	blueEntity->pos.x += DT * 15;
	blueEntity->pos.y = -cam->pos_.y - (1 / cam->zoom - 1) * (LONG)App::GetInstance()->GetSettings()->windowHeight / 2;;

	if (player->pos.x >= 128 * 256.f && fadeTime == 0)
	{
		fadeTime = -1.3f;
		isGiveup = false;
		isNextstage = true;
	}
	if (player->pos.y >= 42 * 256 && fadeTime == 0)
	{
		fadeTime = -1.3f;
		isGiveup = false;
	}

	if (player->pos.x <= emblem->pos.x + 256
		&& player->pos.x + 256 >= emblem->pos.x
		&& player->pos.y <= emblem->pos.y + 256
		&& player->pos.y + 512 >= emblem->pos.y
		&& !data.col2)
	{
		emblem->SetScale(Vec2F(0, 0));
		data.col2 = true;
		for (int i = 0; i < 25; i++)
		{
			Entity* newParticle = new emblemParticle(emblem->pos.x, emblem->pos.y, "Sprites/Entities/emblem/friendship.png");
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

Stage2::~Stage2()
{
}

void Stage2::ChangeScene()
{
	RG2SceneManager->ChangeScene(new Stage3({ data.col1, data.col2, data.col3, data.col4, data.col5, 0, false, data.giveupCount, -3000, false }));
}

void Stage2::GiveUp()
{
	if (player->pos.x <= 38 * 256)
		RG2SceneManager->ChangeScene(new Stage2({ data.col1, data.col2, data.col3, data.col4, data.col5, 2, isGiveup, data.giveupCount, blueEntity->pos.x, false }));
	else if (player->pos.x <= 74 * 256)
		RG2SceneManager->ChangeScene(new Stage2({ data.col1, data.col2, data.col3, data.col4, data.col5, 3, isGiveup, data.giveupCount, blueEntity->pos.x, false }));
	else
		RG2SceneManager->ChangeScene(new Stage2({ data.col1, data.col2, data.col3, data.col4, data.col5, 4, isGiveup, data.giveupCount, blueEntity->pos.x, false }));
}

void Stage2::ReGame()
{
	if (player->pos.x <= 38 * 256)
		RG2SceneManager->ChangeScene(new Stage2({ data.col1, data.col2, data.col3, data.col4, data.col5, 1, isGiveup, data.giveupCount, blueEntity->pos.x, false }));
	else if (player->pos.x <= 74 * 256)
		RG2SceneManager->ChangeScene(new Stage2({ data.col1, data.col2, data.col3, data.col4, data.col5, 2, isGiveup, data.giveupCount, blueEntity->pos.x, false }));
	else
		RG2SceneManager->ChangeScene(new Stage2({ data.col1, data.col2, data.col3, data.col4, data.col5, 3, isGiveup, data.giveupCount, blueEntity->pos.x, false }));
}

bool Stage2::CanRegame()
{
	if (player->pos.x <= 38 * 256)
	{
		if (17 * 256 - blueEntity->pos.x > 3000 && blueEntity->pos > 0 || blueEntity->pos < 0)
			return true;
	}
	else if (player->pos.x <= 74 * 256)
	{
		if (46 * 256 - blueEntity->pos.x > 3000 && blueEntity->pos > 0 || blueEntity->pos < 0)
			return true;
	}
	else if (90 * 256 - blueEntity->pos.x > 3000 && blueEntity->pos > 0 || blueEntity->pos < 0)
		return true;
	return false;
}