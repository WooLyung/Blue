#pragma once
#include "pch.h"
#include "Stage.h"
#include "Particle.h"
#include "breakedBlock.h"

void Stage::OnUpdate()
{
	Scene::OnUpdate();
#pragma region Particle
	list<Entity*>::iterator iter;
	for (iter = particles->begin(); iter != particles->end(); iter++)
	{
		if ((*iter)->GetComponent<Particle>()->isDelete)
		{
			(*iter)->Destroy();
			particles->erase(iter);
			if (iter == particles->end())
				break;
		}
	}
#pragma endregion
#pragma region Block and PlayerInteraction
	player->moveState->isPush = false;
	player->moveState->isNextBlock = false;
	player->grappedBlock = NULL;
	Rect rect1 = player->GetComponent<AABBCollider>()->GetRectWithWorldPos();

	for each(IBlock *block in *blocks)
	{
		Rect rect2 = block->GetComponent<AABBCollider>()->GetRectWithWorldPos();

		if (block->type == LEVER) // 레버
		{
			if (rect1.bottom >= rect2.top
				&& rect2.bottom >= rect1.top
				&& rect1.right >= rect2.left
				&& rect2.right >= rect1.left)
			{
				if (RG2Input->GetKeyState(KeyCode::KEY_Z) == KeyState::KEYSTATE_ENTER)
				{
					((switchs*)block)->isActive = !((switchs*)block)->isActive;
				}
			}
		}
		else if (block->type == MOVEABLEBLOCK) // 옮길 수 있는 블럭
		{
			if (rect1.bottom - 200 >= rect2.top
				&& rect2.bottom >= rect1.top
				&& rect1.right + 10 >= rect2.left
				&& rect2.right + 10 >= rect1.left) // 플레이어가 블럭 옆일 때 (끌기)
			{
				if (player->pos.x >= block->pos.x && !player->moveState->isRightDir && player->moveState->isGrap
					|| player->pos.x <= block->pos.x && player->moveState->isRightDir && player->moveState->isGrap) // 닿아있는 면이 같고, 그 쪽을 바라보고 있을 때
				{
					player->moveState->isNextBlock = true;
					if (player->grappedBlock == NULL
						|| pow(player->pos.x - player->grappedBlock->pos.x, 2) + pow(player->pos.y - player->grappedBlock->pos.y + 256, 2)
						>= pow(player->pos.x - block->pos.x, 2) + pow(player->pos.y - block->pos.y + 256, 2))
						player->grappedBlock = block;
				}
			}
			if (rect1.bottom - 100 >= rect2.top
				&& rect2.bottom >= rect1.top
				&& rect1.right >= rect2.left
				&& rect2.right >= rect1.left) // 블럭과 플레이어가 겹쳐있을 때 (밀기)
			{
				if (player->pos.x <= block->pos.x && player->moveState->isRightDir
					|| player->pos.x >= block->pos.x && !player->moveState->isRightDir) // 닿아있는 면이 같고, 그 쪽을 바라보고 있을 때
					player->moveState->isPush = true;
			}
		}
		else if (block->type == JUMPER) // 점프대
		{
			if (rect1.bottom >= rect2.top
				&& rect2.bottom >= rect1.top
				&& rect1.right >= rect2.left
				&& rect2.right >= rect1.left)
			{
				{
					((jumper*)block)->cooltime = 1;
					player->GetComponent<RigidBody>()->velocityY = ((jumper*)block)->power;
				}
			}
		}
		else if (block->type == FAN && ((fan*)block)->isActive != ((fan*)block)->defaultValue) // 선풍기
		{
			float pos1_x = (rect2.left + rect2.right) / 2;
			float pos1_y = (rect2.top + rect2.bottom) / 2;

			float pos2_x = (rect1.left + rect1.right) / 2;
			float pos2_y = (rect1.top + rect1.bottom) / 2;

			if (Random(0, (int)(1 / DT)) < 10)
			{
				Entity* newParticle = new wind(
					block->pos.x + cos(((fan*)block)->angle) * abs(rect1.bottom - pos2_y),
					block->pos.y + sin(((fan*)block)->angle) * abs(rect1.bottom - pos2_y)
				);
				float angle = Random(((fan*)block)->angle - PI / 8, ((fan*)block)->angle + PI / 8);
				float speed = Random(((fan*)block)->power * 0.6f, ((fan*)block)->power * 1.2f);
				newParticle->GetComponent<RigidBody>()->velocityX = cos(angle) * speed;
				newParticle->GetComponent<RigidBody>()->velocityY = sin(angle) * speed;
				AddChild(newParticle);
				particles->push_back(newParticle);
			}

			if (pow(pos1_x - pos2_x, 2) + pow(pos1_y - pos2_y, 2)
				<= pow(abs(rect2.bottom - pos1_y) + abs(rect1.bottom - pos2_y) + ((fan*)block)->range, 2)) // 거리 체크
			{
				float angle = atan2(pos2_y - pos1_y, pos2_x - pos1_x);
				angle -= ((fan*)block)->angle;
				if (angle > PI)
					angle -= 2 * PI;
				else if (angle < -PI)
					angle += 2 * PI;
				if (abs(angle) <= ((pow(pos1_x - pos2_x, 2) + pow(pos1_y - pos2_y, 2) >= pow(512, 2)) ?
					PI / 12 : PI / 8)) // 각도 체크
				{
					if (((fan*)block)->angle != PI / 2.f && ((fan*)block)->angle != PI / -2.f) 
						player->GetComponent<RigidBody>()->velocityX = cos(((fan*)block)->angle) * ((fan*)block)->power;
					if (((fan*)block)->angle != 0 && ((fan*)block)->angle != PI && ((fan*)block)->angle != -PI && ((fan*)block)->angle != 2 * PI) 
						player->GetComponent<RigidBody>()->velocityY = sin(((fan*)block)->angle) * ((fan*)block)->power;
				}
			}

			for each(IBlock *block2 in *blocks)
			{
				if (block2->type == MOVEABLEBLOCK)
				{
					Rect rect1 = block2->GetComponent<AABBCollider>()->GetRectWithWorldPos();

					float pos2_x = (rect1.left + rect1.right) / 2;
					float pos2_y = (rect1.top + rect1.bottom) / 2;

					if (pow(pos1_x - pos2_x, 2) + pow(pos1_y - pos2_y, 2)
						<= pow(abs(rect2.bottom - pos1_y) + abs(rect1.bottom - pos2_y) + ((fan*)block)->range, 2)) // 거리 체크
					{
						float angle = atan2(pos2_y - pos1_y, pos2_x - pos1_x);
						angle -= ((fan*)block)->angle;
						if (angle > PI)
							angle -= 2 * PI;
						else if (angle < -PI)
							angle += 2 * PI;
						if (abs(angle) <= ((pow(pos1_x - pos2_x, 2) + pow(pos1_y - pos2_y, 2) >= pow(512, 2)) ?
							PI / 12 : PI / 8)) // 각도 체크
						{
							if (((fan*)block)->angle != PI / 2.f && ((fan*)block)->angle != PI / -2.f) 
								block2->GetComponent<RigidBody>()->velocityX = cos(((fan*)block)->angle) * ((fan*)block)->power;
							if (((fan*)block)->angle != 0 && ((fan*)block)->angle != PI && ((fan*)block)->angle != -PI && ((fan*)block)->angle != 2 * PI)
								block2->GetComponent<RigidBody>()->velocityY = sin(((fan*)block)->angle) * ((fan*)block)->power;
						}
					}
				}
			}
		}
		else if (block->type == PORTAL && ((portal*)block)->target != NULL)
		{
			float posPortal1_x = (rect2.left + rect2.right) / 2; // 현재 포탈
			float posPortal1_y = (rect2.top + rect2.bottom) / 2;

			Rect targetRect = ((portal*)block)->target->GetComponent<AABBCollider>()->GetRectWithWorldPos();
			float posPortal2_x = (targetRect.left + targetRect.right) / 2; // 대상 포탈
			float posPortal2_y = (targetRect.top + targetRect.bottom) / 2;

			float posPlayer_x = (rect1.left + rect1.right) / 2; // 플레이어
			float posPlayer_y = (rect1.top + rect1.bottom) / 2;

			if (pow(posPortal1_x - posPlayer_x, 2) + pow(posPortal1_y - posPlayer_y, 2)
				<= pow(abs(rect2.bottom - posPortal1_y) + abs(rect1.left - posPlayer_x), 2)) // 거리 체크
			{
				float distance = sqrt(pow(posPortal1_x - posPlayer_x, 2) + pow(posPortal1_y - posPlayer_y, 2)) + 10;
				float angle = atan2(posPortal1_y - posPlayer_y, posPortal1_x - posPlayer_x);
				player->pos.x = ((portal*)block)->target->pos.x + abs(posPlayer_x - rect1.left) + cos(angle) * distance;
				player->pos.y = ((portal*)block)->target->pos.y + abs(posPlayer_y - rect1.bottom) + sin(angle) * distance;
			}

			for each(IBlock *block2 in *blocks)
			{
				if (block2->type == MOVEABLEBLOCK)
				{
					Rect rect1 = block2->GetComponent<AABBCollider>()->GetRectWithWorldPos();

					float posBlock_x = (rect1.left + rect1.right) / 2; // 블럭
					float posBlock_y = (rect1.top + rect1.bottom) / 2;

					if (pow(posPortal1_x - posBlock_x, 2) + pow(posPortal1_y - posBlock_y, 2)
						<= pow(abs(rect2.bottom - posPortal1_y) + abs(rect1.left - posBlock_x), 2)) // 거리 체크
					{
						float distance = sqrt(pow(posPortal1_x - posBlock_x, 2) + pow(posPortal1_y - posBlock_y, 2)) + 10;
						float angle = atan2(posPortal1_y - posBlock_y, posPortal1_x - posBlock_x);
						block2->pos.x = ((portal*)block)->target->pos.x + abs(posBlock_x - rect1.left) + cos(angle) * distance;
						block2->pos.y = ((portal*)block)->target->pos.y + abs(posBlock_y - rect1.bottom) + sin(angle) * distance;
					}
				}	
			}
		}

		if (rect1.bottom - 100 < rect2.top
			&& rect1.bottom + 15 >= rect2.top // 작은 차이는 그냥 올라가기
			&& rect2.bottom >= rect1.top
			&& rect1.right >= rect2.left
			&& rect2.right >= rect1.left
			&& block->type != FOOTHOLD)
			player->pos.y -= DT * 23;
	}
#pragma endregion
#pragma region Change Scene
	if (fadeTime > 0)
	{
		fadeTime -= DT;
		if (fadeTime <= 0)
			fadeTime = 0;

		fade->GetComponent<Effect>()->PopEffectInfo()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, fadeTime)))->SetEnabled(true);
		text->GetComponent<TextRenderer>()->SetFillColor(Color(1, 1, 1, fadeTime));
	}
	else if (fadeTime < 0)
	{
		fadeTime += DT;
		if (fadeTime >= 0)
		{
			if (isNextstage)
			{
				ChangeScene();
			}
			else if (isGameover)
			{
				RG2SceneManager->ChangeScene(new End({ data.col1, data.col2, data.col3, data.col4, data.col5, 0, isGiveup, data.giveupCount, blueEntity->pos.x, true }));
			}
			else if (isGiveup)
			{
				data.giveupCount++;
				GiveUp();
			}
			else
			{
				ReGame();
			}
		}
		fade->GetComponent<Effect>()->PopEffectInfo()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1.f, 1.f, 1.f, 1.3f + fadeTime)))->SetEnabled(true);
	}
	else if (RG2Input->GetKeyState(KeyCode::KEY_R) == KeyState::KEYSTATE_ENTER && player->pos.x <= endPos * 256 && CanRegame())
	{
		fadeTime = -1.3f;
		isGiveup = false;
	}
	else if (RG2Input->GetKeyState(KeyCode::KEY_G) == KeyState::KEYSTATE_ENTER && player->pos.x <= endPos * 256)
	{
		fadeTime = -1.3f;
		isGiveup = true;
	}
#pragma endregion
#pragma region Blue
	for each(IBlock *block in *blocks)
	{
		if (block->type == MOVEABLEBLOCK && block->pos.x - blueEntity->pos.x <= 1400)
		{
			for (int i = 0; i < 15; i++)
			{
				Entity* newParticle = new breakedBlock(block->pos.x, block->pos.y);
				float speed = Random(30.f, 60.f);
				float angle = Random(-2 * PI / 3, 2 * PI / 3);
				float scale = Random(0.5f, 1.5f);
				newParticle->GetComponent<RigidBody>()->velocityX = cos(angle) * speed;
				newParticle->GetComponent<RigidBody>()->velocityY = sin(angle) * speed;
				newParticle->SetScale(Vec2F(scale, scale));
				AddChild(newParticle);
				particles->push_back(newParticle);
			}
			list<IBlock*>::iterator iter;
			for (iter = blocks->begin(); iter != blocks->end(); iter++)
			{
				if ((*iter) == block)
				{
					if (block == player->grappedBlock)
						player->grappedBlock = NULL;
					(*iter)->Destroy();
					blocks->erase(iter);
					if (iter == blocks->end())
						break;
				}
			}
		}
		else if (block->type == MOVEABLEBLOCK && abs(block->pos.x - blueEntity->pos.x) <= 2000)
		{
			block->pos.x -= DT * 400;
		}
		else if (block->type == MOVEABLEBLOCK && abs(block->pos.x - blueEntity->pos.x) <= 3000)
		{
			block->pos.x -= DT * 200;
		}
	}
	if (blueEntity->pos.x > 0 && player->pos.x - blueEntity->pos.x <= 1400 && fadeTime == 0)
	{
		fadeTime = -1.3f;
		isGameover = true;
	}
	else if (abs(player->pos.x - blueEntity->pos.x) <= 2000)
	{
		player->pos.x -= DT * 400;
	}
	else if (abs(player->pos.x - blueEntity->pos.x) <= 3000)
	{
		player->pos.x -= DT * 200;
	}
#pragma endregion
#pragma region BackGround
	float posX1 = (-cam->pos_.x * 0.16f * 0.4f);
	float posX2 = (-cam->pos_.x * 0.16f * 0.7f);
	while (posX1 >= 1280)
		posX1 -= 1280;
	while (posX2 >= 1280)
		posX2 -= 1280;

	background[1]->GetComponent<UI>()->pos.x = -posX1;
	background[2]->GetComponent<UI>()->pos.x = -posX1 + 1280;
	background[3]->GetComponent<UI>()->pos.x = -posX2;
	background[4]->GetComponent<UI>()->pos.x = -posX2 + 1280;
#pragma endregion

	debug->GetComponent<TextRenderer>()->SetText("");
}