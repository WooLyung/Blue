#include "pch.h"
#include "Stage1.h"
#include "Stage2.h"
#include "emblemParticle.h"

Stage1::Stage1(Data data)
{
#pragma region Default Setting
	blocks = new list<IBlock*>;
	particles = new list<Entity*>;
	this->data = data;
	endPos = 161.5f;
	isGiveup = false;
	isGameover = false;
	isNextstage = false;

	cam = new Camera(this);
	cam->SetZoom(0.16f);
	cam->SetRange(Rect(0, 0, 180 * 256, 256 * 31));
#pragma region BackGround
	background[0] = new Entity();
	background[0]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage1/layer1.png");
	background[0]->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam);
	AddChild(background[0]);

	background[1] = new Entity();
	background[1]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage1/layer2.png");
	background[1]->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam);
	AddChild(background[1]);

	background[2] = new Entity();
	background[2]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage1/layer2.png");
	background[2]->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam);
	AddChild(background[2]);

	background[3] = new Entity();
	background[3]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage1/layer3.png");
	background[3]->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam);
	AddChild(background[3]);

	background[4] = new Entity();
	background[4]->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage1/layer3.png");
	background[4]->AttachComponent<UI>(Vec2F(0, 0), UI::DIR::LEFT_TOP, cam);
	AddChild(background[4]);
#pragma endregion
	AddChild((new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256.f / 40, 256.f / 40))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage1/back.png")->GetOwner());

	player = new Player();
	AddChild(player);

	if (data.nowPuzzle == 1)
		player->SetPos(Vec2F(9 * 256, 28 * 256));
	else if (data.nowPuzzle == 2)
		player->SetPos(Vec2F(76 * 256, 28 * 256));
	else if (data.nowPuzzle == 3)
		player->SetPos(Vec2F(126 * 256, 28 * 256));
	else if (data.nowPuzzle == 4)
		player->SetPos(Vec2F(170 * 256, 28 * 256));
	else
		player->SetPos(Vec2F(8 * 256, 28 * 256));
	
	cam->Follow(player);
#pragma endregion
#pragma region File Input
	ifstream inFile("Map/Stage1.txt");
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
#pragma region Hint
	AddChild(hints[0] = (new Entity())->SetPos(Vec2F(30 * 256, 27 * 256))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/hint/hint2.png")->GetOwner());
	hints[0]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, 0.f)))->SetEnabled(true);
	AddChild(hints[1] = (new Entity())->SetPos(Vec2F(25 * 256, 28 * 256))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/hint/hint1.png")->GetOwner());
	hints[1]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, 0.f)))->SetEnabled(true);
	AddChild(hints[2] = (new Entity())->SetPos(Vec2F(43 * 256, 28 * 256))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/hint/hint1.png")->GetOwner());
	hints[2]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, 0.f)))->SetEnabled(true);
	AddChild(hints[3] = (new Entity())->SetPos(Vec2F(51 * 256, 28 * 256))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/hint/hint1.png")->GetOwner());
	hints[3]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, 0.f)))->SetEnabled(true);
	AddChild(hints[4] = (new Entity())->SetPos(Vec2F(51 * 256, 26 * 256))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/hint/hint2.png")->GetOwner());
	hints[4]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, 0.f)))->SetEnabled(true);
	AddChild(hints[5] = (new Entity())->SetPos(Vec2F(51 * 256, 25 * 256))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/hint/hint1.png")->GetOwner());
	hints[5]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, 0.f)))->SetEnabled(true);
	AddChild(hints[6] = (new Entity())->SetPos(Vec2F(51 * 256, 24 * 256))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/hint/hint1.png")->GetOwner());
	hints[6]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, 0.f)))->SetEnabled(true);
	AddChild(hints[7] = (new Entity())->SetPos(Vec2F(94 * 256, 22 * 256))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/hint/hint1.png")->GetOwner());
	hints[7]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, 0.f)))->SetEnabled(true);
	AddChild(hints[8] = (new Entity())->SetPos(Vec2F(94 * 256, 21 * 256))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/hint/hint1.png")->GetOwner());
	hints[8]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, 0.f)))->SetEnabled(true);
	AddChild(hints[9] = (new Entity())->SetPos(Vec2F(94 * 256, 20 * 256))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/hint/hint1.png")->GetOwner());
	hints[9]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, 0.f)))->SetEnabled(true);
	AddChild(hints[10] = (new Entity())->SetPos(Vec2F(94 * 256, 19 * 256))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/hint/hint1.png")->GetOwner());
	hints[10]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, 0.f)))->SetEnabled(true);
	AddChild(hints[11] = (new Entity())->SetPos(Vec2F(140 * 256, 16 * 256))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/hint/hint2.png")->GetOwner());
	hints[11]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, 0.f)))->SetEnabled(true);
	AddChild(hints[12] = (new Entity())->SetPos(Vec2F(140 * 256, 20 * 256))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/hint/hint1.png")->GetOwner());
	hints[12]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, 0.f)))->SetEnabled(true);
	AddChild(hints[13] = (new Entity())->SetPos(Vec2F(141 * 256, 20 * 256))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/hint/hint1.png")->GetOwner());
	hints[13]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, 0.f)))->SetEnabled(true);
	AddChild(hints[14] = (new Entity())->SetPos(Vec2F(151 * 256, 19 * 256))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/hint/hint2.png")->GetOwner());
	hints[14]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, 0.f)))->SetEnabled(true);
	AddChild(hints[15] = (new Entity())->SetPos(Vec2F(153 * 256, 19 * 256))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/hint/hint2.png")->GetOwner());
	hints[15]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, 0.f)))->SetEnabled(true);
	AddChild(hints[16] = (new Entity())->SetPos(Vec2F(151 * 256, 23 * 256))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/hint/hint1.png")->GetOwner());
	hints[16]->AttachComponent<Effect>()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, 0.f)))->SetEnabled(true);
#pragma endregion
#pragma region Create Objects
	switchs *newSwitch[21];
	portal *newPortal[10];
	IBlock *newBlock;

	emblem = new Entity();
	emblem->SetPos(Vec2F(164 * 256, 24 * 256));
	emblem->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Entities/emblem/dream.png");
	if (data.col1)
		emblem->SetScale(Vec2F(0, 0));
	AddChild(emblem);

#pragma region Puzzle 1
	newSwitch[0] = new foothold(256 * 25, 256 * 28, BOTTOM);
	AddChild(newSwitch[0]);
	blocks->push_back(newSwitch[0]);

	newSwitch[1] = new lever(256 * 41, 256 * 23, RIGHT);
	AddChild(newSwitch[1]);
	blocks->push_back(newSwitch[1]);

	newSwitch[2] = new button(256 * 30.f, 256 * 16.f, TOP, 1.5f);
	AddChild(newSwitch[2]);
	blocks->push_back(newSwitch[2]);

	newSwitch[3] = new foothold(256 * 40.f, 256 * 20, BOTTOM);
	AddChild(newSwitch[3]);
	blocks->push_back(newSwitch[3]);

	newSwitch[4] = new lever(256 * 53, 256 * 19, RIGHT);
	AddChild(newSwitch[4]);
	blocks->push_back(newSwitch[4]);

	newSwitch[5] = new foothold(256 * 43.f, 256 * 28, BOTTOM);
	AddChild(newSwitch[5]);
	blocks->push_back(newSwitch[5]);

	newBlock = new door(256 * 28.f, 256 * 26.f, "Sprites/Blocks/staticBlock/block(1-3).png", Vec2F(256 * 28, 256 * 26), Vec2F(256 * 28, 256 * 23), 3000.f);
	((door*)newBlock)->switchList->push_back(newSwitch[0]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new movingBlock(256 * 29.f, 256 * 30.f, "Sprites/Blocks/staticBlock/block(3-1).png", Vec2F(256 * 29.f, 256 * 30.f), Vec2F(256 * 29.f, 256 * 18.f), movingBlock::POS1, 1000.f);
	((movingBlock*)newBlock)->switchList->push_back(newSwitch[1]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new fan(256 * 35.f, 256 * 30.f, PI / -2.f, 40.f, 1500.f);
	((fan*)newBlock)->switchList->push_back(newSwitch[2]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 42.f, 256 * 16.f, "Sprites/Blocks/staticBlock/block(1-5).png", Vec2F(256 * 42, 256 * 16), Vec2F(256 * 42, 256 * 12), 600.f);
	((door*)newBlock)->switchList->push_back(newSwitch[3]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new movingBlock(256 * 43.f, 256 * 22.f, "Sprites/Blocks/staticBlock/block(2-1).png", Vec2F(256 * 43.f, 256 * 22.f), Vec2F(256 * 52.f, 256 * 16.f), movingBlock::POS1, 200.f, false);
	((movingBlock*)newBlock)->switchList->push_back(newSwitch[4]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new fan(256 * 51.f, 256 * 30.f, PI / -2.f, 40.f, 300.f);
	((fan*)newBlock)->switchList->push_back(newSwitch[5]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new jumper(256 * 44.f, 256 * 28.f, -55.f);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newPortal[0] = new portal(256 * 52.f, 256 * 14.f);
	AddChild(newPortal[0]);
	blocks->push_back(newPortal[0]);

	newPortal[1] = new portal(256 * 55.f, 256 * 26.f);
	AddChild(newPortal[1]);
	blocks->push_back(newPortal[1]);

	newPortal[0]->target = newPortal[1];
#pragma endregion
#pragma region Puzzle 2
	newSwitch[6] = new lever(256 * 103.f, 256 * 28, BOTTOM);
	AddChild(newSwitch[6]);
	blocks->push_back(newSwitch[6]);

	newSwitch[7] = new lever(256 * 105.f, 256 * 28, BOTTOM);
	AddChild(newSwitch[7]);
	blocks->push_back(newSwitch[7]);

	newSwitch[8] = new foothold(256 * 81.f, 256 * 19, LEFT);
	AddChild(newSwitch[8]);
	blocks->push_back(newSwitch[8]);

	newSwitch[9] = new lever(256 * 101.f, 256 * 28, BOTTOM);
	AddChild(newSwitch[9]);
	blocks->push_back(newSwitch[9]);

	newSwitch[10] = new foothold(256 * 89.f, 256 * 21.f, BOTTOM);
	AddChild(newSwitch[10]);
	blocks->push_back(newSwitch[10]);

	newBlock = new fan(256 * 105.f, 256 * 17.f, PI, 10.f, 11 * 256.f);
	((fan*)newBlock)->switchList->push_back(newSwitch[6]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new movingBlock(256 * 91.f, 256 * 23.f, "Sprites/Blocks/staticBlock/block(4-1).png", Vec2F(256 * 91.f, 256 * 23.f), Vec2F(256 * 91.f, 256 * 14.f), movingBlock::POS2, 400.f);
	((movingBlock*)newBlock)->switchList->push_back(newSwitch[7]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new fan(256 * 96.f, 256 * 13.f, PI, 100.f, 3 * 256.f);
	((fan*)newBlock)->switchList->push_back(newSwitch[6]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new movingBlock(256 * 81.f, 256 * 13.f, "Sprites/Blocks/staticBlock/block(1-4).png", Vec2F(256 * 81.f, 256 * 13.f), Vec2F(256 * 85.3f, 256 * 13.f), movingBlock::POS2, 400.f);
	((movingBlock*)newBlock)->switchList->push_back(newSwitch[9]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new movingBlock(256 * 88.f, 256 * 17.f, "Sprites/Blocks/staticBlock/block(1-5).png", Vec2F(256 * 82.f, 256 * 17.f), Vec2F(256 * 88.f, 256 * 17.f), movingBlock::POS1, 200.f);
	((movingBlock*)newBlock)->switchList->push_back(newSwitch[9]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new movingBlock(256 * 96.f, 256 * 23.f, "Sprites/Blocks/staticBlock/block(5-1).png", Vec2F(256 * 96.f, 256 * 23.f), Vec2F(256 * 96.f, 256 * 30.f), movingBlock::POS2, 400.f);
	((movingBlock*)newBlock)->switchList->push_back(newSwitch[8]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 106.f, 256 * 19.f, "Sprites/Blocks/staticBlock/block(1-5).png", Vec2F(256 * 106.f, 256 * 19.f), Vec2F(256 * 106.f, 256 * 23.f), 300.f);
	((door*)newBlock)->switchList->push_back(newSwitch[10]);
	AddChild(newBlock);
	blocks->push_back(newBlock);
#pragma endregion
#pragma region Puzzle 3
	newSwitch[11] = new lever(256 * 144.f, 256 * 28.f, BOTTOM);
	AddChild(newSwitch[11]);
	blocks->push_back(newSwitch[11]);

	newSwitch[12] = new lever(256 * 146.f, 256 * 28.f, BOTTOM);
	AddChild(newSwitch[12]);
	blocks->push_back(newSwitch[12]);

	newSwitch[13] = new lever(256 * 148.f, 256 * 28.f, BOTTOM);
	AddChild(newSwitch[13]);
	blocks->push_back(newSwitch[13]);

	newSwitch[14] = new lever(256 * 140.f, 256 * 28.f, BOTTOM);
	AddChild(newSwitch[14]);
	blocks->push_back(newSwitch[14]);

	newSwitch[15] = new lever(256 * 138.f, 256 * 28.f, BOTTOM);
	AddChild(newSwitch[15]);
	blocks->push_back(newSwitch[15]);

	newSwitch[16] = new lever(256 * 152.f, 256 * 28.f, BOTTOM);
	AddChild(newSwitch[16]);
	blocks->push_back(newSwitch[16]);

	newSwitch[17] = new lever(256 * 154.f, 256 * 28.f, BOTTOM);
	AddChild(newSwitch[17]);
	blocks->push_back(newSwitch[17]);

	newSwitch[18] = new foothold(256 * 140.f, 256 * 16.f, TOP);
	AddChild(newSwitch[18]);
	blocks->push_back(newSwitch[18]);

	newSwitch[19] = new foothold(256 * 140.f, 256 * 20.f, BOTTOM);
	AddChild(newSwitch[19]);
	blocks->push_back(newSwitch[19]);

	newSwitch[20] = new foothold(256 * 154.f, 256 * 19.f, TOP);
	AddChild(newSwitch[20]);
	blocks->push_back(newSwitch[20]);

	newSwitch[21] = new foothold(256 * 151.f, 256 * 23.f, BOTTOM);
	AddChild(newSwitch[21]);
	blocks->push_back(newSwitch[21]);

	newBlock = new door(256 * 142.f, 256 * 16.f, "Sprites/Blocks/staticBlock/block(1-2).png", Vec2F(256 * 142.f, 256 * 16.f), Vec2F(256 * 142.f, 256 * 24.f), 500.f);
	((door*)newBlock)->switchList->push_back(newSwitch[11]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 142.f, 256 * 19.f, "Sprites/Blocks/staticBlock/block(1-2).png", Vec2F(256 * 142.f, 256 * 19.f), Vec2F(256 * 142.f, 256 * 24.f), 500.f);
	((door*)newBlock)->switchList->push_back(newSwitch[12]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 142.f, 256 * 22.f, "Sprites/Blocks/staticBlock/block(1-2).png", Vec2F(256 * 142.f, 256 * 22.f), Vec2F(256 * 142.f, 256 * 24.f), 500.f);
	((door*)newBlock)->switchList->push_back(newSwitch[13]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 150.f, 256 * 16.f, "Sprites/Blocks/staticBlock/block(1-2).png", Vec2F(256 * 150.f, 256 * 16.f), Vec2F(256 * 150.f, 256 * 24.f), 500.f);
	((door*)newBlock)->switchList->push_back(newSwitch[11]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 150.f, 256 * 19.f, "Sprites/Blocks/staticBlock/block(1-2).png", Vec2F(256 * 150.f, 256 * 19.f), Vec2F(256 * 150.f, 256 * 24.f), 500.f);
	((door*)newBlock)->switchList->push_back(newSwitch[12]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 150.f, 256 * 22.f, "Sprites/Blocks/staticBlock/block(1-2).png", Vec2F(256 * 150.f, 256 * 22.f), Vec2F(256 * 150.f, 256 * 24.f), 500.f);
	((door*)newBlock)->switchList->push_back(newSwitch[13]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 143.f, 256 * 24.f, "Sprites/Blocks/staticBlock/block(3-1).png", Vec2F(256 * 143.f, 256 * 24.f), Vec2F(256 * 143.f, 256 * 18.f), 500.f);
	((door*)newBlock)->switchList->push_back(newSwitch[14]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 147.f, 256 * 24.f, "Sprites/Blocks/staticBlock/block(3-1).png", Vec2F(256 * 147.f, 256 * 24.f), Vec2F(256 * 147.f, 256 * 18.f), 500.f);
	((door*)newBlock)->switchList->push_back(newSwitch[14]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 143.f, 256 * 24.f, "Sprites/Blocks/staticBlock/block(3-1).png", Vec2F(256 * 143.f, 256 * 24.f), Vec2F(256 * 143.f, 256 * 21.f), 500.f);
	((door*)newBlock)->switchList->push_back(newSwitch[15]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 147.f, 256 * 24.f, "Sprites/Blocks/staticBlock/block(3-1).png", Vec2F(256 * 147.f, 256 * 24.f), Vec2F(256 * 147.f, 256 * 21.f), 500.f);
	((door*)newBlock)->switchList->push_back(newSwitch[15]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new fan(256 * 146.f, 256 * 17.f, 0, 10.f, 14 * 256.f, true);
	((fan*)newBlock)->switchList->push_back(newSwitch[17]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new fan(256 * 146.f, 256 * 20.f, 0, 10.f, 14 * 256.f, true);
	((fan*)newBlock)->switchList->push_back(newSwitch[17]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new fan(256 * 146.f, 256 * 23.f, 0, 10.f, 14 * 256.f, true);
	((fan*)newBlock)->switchList->push_back(newSwitch[17]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new fan(256 * 146.f, 256 * 17.f, 0, -10.f, 14 * 256.f);
	((fan*)newBlock)->switchList->push_back(newSwitch[17]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new fan(256 * 146.f, 256 * 20.f, 0, -10.f, 14 * 256.f);
	((fan*)newBlock)->switchList->push_back(newSwitch[17]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new fan(256 * 146.f, 256 * 23.f, 0, -10.f, 14 * 256.f);
	((fan*)newBlock)->switchList->push_back(newSwitch[17]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	//

	newBlock = new fan(256 * 146.f, 256 * 17.f, PI, 10.f, 14 * 256.f, true);
	((fan*)newBlock)->switchList->push_back(newSwitch[16]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new fan(256 * 146.f, 256 * 20.f, PI, 10.f, 14 * 256.f, true);
	((fan*)newBlock)->switchList->push_back(newSwitch[16]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new fan(256 * 146.f, 256 * 23.f, PI, 10.f, 14 * 256.f, true);
	((fan*)newBlock)->switchList->push_back(newSwitch[16]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new fan(256 * 146.f, 256 * 17.f, PI, -10.f, 14 * 256.f);
	((fan*)newBlock)->switchList->push_back(newSwitch[16]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new fan(256 * 146.f, 256 * 20.f, PI, -10.f, 14 * 256.f);
	((fan*)newBlock)->switchList->push_back(newSwitch[16]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new fan(256 * 146.f, 256 * 23.f, PI, -10.f, 14 * 256.f);
	((fan*)newBlock)->switchList->push_back(newSwitch[16]);
	AddChild(newBlock);
	blocks->push_back(newBlock);

	newBlock = new door(256 * 161.f, 256 * 26.f, "Sprites/Blocks/staticBlock/block(1-3).png", Vec2F(256 * 161.f, 256 * 26.f), Vec2F(256 * 161.f, 256 * 30.f), 1200.f);
	((door*)newBlock)->switchList->push_back(newSwitch[18]);
	((door*)newBlock)->switchList->push_back(newSwitch[19]);
	((door*)newBlock)->switchList->push_back(newSwitch[20]);
	((door*)newBlock)->switchList->push_back(newSwitch[21]);
	AddChild(newBlock);
	blocks->push_back(newBlock);
#pragma endregion

#pragma endregion
#pragma region Default Setting 2
	blueEntity = new blue();
	blueEntity->pos.x = data.bluePos;
	AddChild(blueEntity);

	AddChild((new Entity())->SetPos(Vec2F(0, 0))->SetScale(Vec2F(256 / 40.f, 256 / 40.f))->AttachComponent<SpriteRenderer>()->SetTexture("Sprites/Backgrounds/Stage1/front.png")->GetOwner());
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
void Stage1::OnUpdate() {

	Stage::OnUpdate();
	cam->Update();

	blueEntity->pos.x += DT * 20;
	blueEntity->pos.y = -cam->pos_.y - (1 / cam->zoom - 1) * (LONG)App::GetInstance()->GetSettings()->windowHeight / 2;;

	if (player->pos.x >= 178 * 256 && fadeTime == 0)
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
		&& !data.col1)
	{
		emblem->SetScale(Vec2F(0, 0));
		data.col1 = true;
		for (int i = 0; i < 25; i++)
		{
			Entity* newParticle = new emblemParticle(emblem->pos.x, emblem->pos.y, "Sprites/Entities/emblem/dream.png");
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

	if (RG2Input->GetKeyState(KeyCode::KEY_H) == KeyState::KEYSTATE_ENTER)
	{
		hint = !hint;
		for (int i = 0; i < 17; i++)
			hints[i]->GetComponent<Effect>()->PopEffectInfo()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, hint)))->SetEnabled(true);
	}
}

Stage1::~Stage1()
{
}

void Stage1::ChangeScene()
{
	RG2SceneManager->ChangeScene(new Stage2({ data.col1, data.col2, data.col3, data.col4, data.col5, 0, false, data.giveupCount, -3500, false }));
}

void Stage1::GiveUp()
{
	if (player->pos.x <= 58 * 256)
		RG2SceneManager->ChangeScene(new Stage1({ data.col1, data.col2, data.col3, data.col4, data.col5, 2, isGiveup, data.giveupCount, blueEntity->pos.x, false }));
	else if (player->pos.x <= 107 * 256)
		RG2SceneManager->ChangeScene(new Stage1({ data.col1, data.col2, data.col3, data.col4, data.col5, 3, isGiveup, data.giveupCount, blueEntity->pos.x, false }));
	else
		RG2SceneManager->ChangeScene(new Stage1({ data.col1, data.col2, data.col3, data.col4, data.col5, 4, isGiveup, data.giveupCount, blueEntity->pos.x, false }));
}

void Stage1::ReGame()
{
	if (player->pos.x <= 58 * 256)
		RG2SceneManager->ChangeScene(new Stage1({ data.col1, data.col2, data.col3, data.col4, data.col5, 1, isGiveup, data.giveupCount, blueEntity->pos.x, false }));
	else if (player->pos.x <= 107 * 256)
		RG2SceneManager->ChangeScene(new Stage1({ data.col1, data.col2, data.col3, data.col4, data.col5, 2, isGiveup, data.giveupCount, blueEntity->pos.x, false }));
	else
		RG2SceneManager->ChangeScene(new Stage1({ data.col1, data.col2, data.col3, data.col4, data.col5, 3, isGiveup, data.giveupCount, blueEntity->pos.x, false }));
}

bool Stage1::CanRegame()
{
	if (player->pos.x <= 58 * 256)
	{
		if (9 * 256 - blueEntity->pos.x > 3000 && blueEntity->pos > 0 || blueEntity->pos < 0)
			return true;
	}
	else if (player->pos.x <= 107 * 256)
	{
		if (76 * 256 - blueEntity->pos.x > 3000 && blueEntity->pos > 0 || blueEntity->pos < 0)
			return true;
	}
	else if (126 * 256 - blueEntity->pos.x > 3000 && blueEntity->pos > 0 || blueEntity->pos < 0)
		return true;
	return false;
}