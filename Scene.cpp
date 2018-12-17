#include "pch.h"
#include "Scene.h"
#include"Entity.h"
#include"Camera.h"
#include"Math.h"
#include"App.h"
#include"Collider.h"
#include"RigidBody.h"
#include"AABBCollider.h"
#include"CircleCollider.h"
bool Scene::isChanging_ = false;
std::vector<Entity*> Scene::tempEntities_(0);
std::vector<Entity*> Scene::tempCollidables_(0);

void Scene::RegisterEntity(Entity * e)
{
	if (Scene::isChanging_)
	{
		tempEntities_.push_back(e);
	}
	else
	{
		entities_.push_back(e);
	}
		
}

void Scene::UnregisterEntity(Entity * e)
{
	if (Scene::isChanging_)
	{
		auto i = std::find(tempEntities_.begin(), tempEntities_.end(), e);
		tempEntities_.erase(i);
	}
	else
	{
		auto i = std::find(entities_.begin(), entities_.end(), e);
		entities_.erase(i);
	}
}

void Scene::RegisterCollidable(Entity * e)
{
	if (Scene::isChanging_)
	{
		tempCollidables_.push_back(e);
	}
	else
	{
		collidables_.push_back(e);
	}
}

void Scene::UnregisterCollidable(Entity * e)
{
	if (Scene::isChanging_)
	{
		auto i = std::find(tempCollidables_.begin(), tempCollidables_.end(), e);
		tempCollidables_.erase(i);
	}
	else
	{
		auto i = std::find(collidables_.begin(), collidables_.end(), e);
		collidables_.erase(i);
	}
}

void Scene::Dispose()
{
	for (auto& i : children_)
		delete i;
	children_.clear();
	tempEntities_.clear();
	tempCollidables_.clear();
}

Scene::Scene()
	:Entity(false),
	camera(this)
{
	Scene::isChanging_ = true;
}


Scene::~Scene()
{
}


const std::vector<Entity*>& Scene::GetEntities(void) const
{
	return entities_;
}

void Scene::Render()
{
	matrix =
		matrix*
		D2D1::Matrix3x2F::Scale(scale.x, scale.y, scaleCenter);

	App::GetInstance()->GetGraphics()->GetDeviceContext()->SetTransform(matrix);

	for (auto i : components_)
	{
		if ((i.second)->IsEnabled())
		{
			(i.second)->OnRender();
		}
	}

	if (isAutoRenderEnabled)
	{
		for (auto i : children_)
		{
			if (i->IsEnabled())
				i->Render();
		}
	}

	OnRender();
}

void Scene::Update()
{

	matrix = D2D1::Matrix3x2F::Translation(pos.x - center.x, pos.y - center.y);
	for (auto i : components_)
	{
		if ((i.second)->IsEnabled())
		{
			(i.second)->OnUpdate();
		}
	}

	if (isAutoUpdateEnabled)
	{
		for (auto i : children_)
		{
			if (i->IsEnabled())
			{
				i->Update();
			}

		}
	}


	OnUpdate();



	children_.erase(std::remove_if(children_.begin(), children_.end(), [](Entity* element) {
		const LifeState tmp = element->GetLifeState();
		if (tmp == Destroyed)
		{
			delete element;
			return true;
		}
		else if (tmp == Detached)
		{
			element->parent_ = nullptr;
			element->lifeState_ = Alive;
			return true;
		}
		return false;
	}), children_.end());
}

void Scene::OnUpdate()
{
	Entity::OnUpdate();
	for (auto iter = collidables_.begin(); iter != collidables_.end(); ++iter)
	{
		if ((*iter)->GetComponent<RigidBody>())
		{
			(*iter)->GetComponent<RigidBody>()->isTouchingBottom = false;
			(*iter)->GetComponent<RigidBody>()->isTouchingTop = false;
			(*iter)->GetComponent<RigidBody>()->isTouchingLeft = false;
			(*iter)->GetComponent<RigidBody>()->isTouchingRight = false;
		}
	}

	for (auto iter = collidables_.begin(); iter != collidables_.end(); ++iter)
	{
		for (auto iter2 = next(iter); iter2 != collidables_.end(); ++iter2)
		{
			Collider* a = (*iter)->GetComponent<Collider>();
			Collider* b = (*iter2)->GetComponent<Collider>();
			if (!a || !b || !a->IsEnabled() || !b->IsEnabled()) continue;
			if (a->IsCollision(b))
			{
				a->onCollision_((*iter2));
				b->onCollision_((*iter));
				
			}
			else
				continue;

			RigidBody* ra = (*iter)->GetComponent<RigidBody>();
			RigidBody* rb = (*iter2)->GetComponent<RigidBody>();
			if (!ra || !rb || (ra->isFixed && rb->isFixed)) continue;

			//TODO:�����ڵ� �и�

			//�簢��-�簢��
			if(a->GetID() == typeid(AABBCollider) &&
				b->GetID() == typeid(AABBCollider))
			{
				const Rect& r1 = ((AABBCollider*)a)->GetRectWithWorldPos();
				const Rect& r2 = ((AABBCollider*)b)->GetRectWithWorldPos();
				//�������� ���Ѵ�.
				const Rect& intersection =r1.GetIntersection(r2);
				//X ���� �浹�� ��
				if (intersection.GetHeight() > intersection.GetWidth())
				{
					//r1�� ���ʿ� ���� �� 
					if (r1.GetCenterX() < r2.GetCenterX())
					{
						//�Ѵ� fixed�� �ƴҶ�
						if(!rb->ignore) ra->isTouchingRight = true;
						if(!ra->ignore) rb->isTouchingLeft = true;
						if (!ra->ignore && !rb->ignore)
						{
							if (!ra->isFixed && !rb->isFixed)
							{
								if (ra->velocityX > 0)
								{
									if (rb->velocityX < 0)
									{
										float a = ra->velocityX / 2;
										float b = rb->velocityX / 2;
										ra->velocityX += b;
										rb->velocityX += a;
									}
									else
									{
										ra->velocityX /= 2;
										rb->velocityX += ra->velocityX;
									}
								}
								else
								{
									rb->velocityX /= 2;
									ra->velocityX += rb->velocityX;
								}

								//�ݹݾ� ���ش�.
								//���ʿ��ִ°� -,�����ʿ��ִ°� +
								(*iter)->pos.x -= intersection.GetWidth() / 2;
								(*iter2)->pos.x += intersection.GetWidth() / 2;
							}
							//ra�� fixed�϶�
							else if (ra->isFixed)
							{
								//rb(iter2)�� ���ش�.
								(*iter2)->pos.x += intersection.GetWidth() / 2;
								if (rb->velocityX < 0)
									rb->velocityX = 0;
							}
							else if (rb->isFixed)
							{
								(*iter)->pos.x -= intersection.GetWidth() / 2;
								if (ra->velocityX > 0)
									ra->velocityX = 0;
							}
						}
					}
					//r1�� �����ʿ� ���� ��
					else
					{
						if (!ra->ignore) rb->isTouchingRight = true;
						if (!rb->ignore) ra->isTouchingLeft = true;
						if (!ra->ignore && !rb->ignore)
						{
							if (!ra->isFixed && !rb->isFixed)
							{
								if (rb->velocityX > 0)
								{
									if (ra->velocityX < 0)
									{
										float a = ra->velocityX / 2;
										float b = rb->velocityX / 2;
										ra->velocityX += b;
										rb->velocityX += a;
									}
									else
									{
										rb->velocityX /= 2;
										ra->velocityX += rb->velocityX;
									}
								}
								else
								{
									ra->velocityX /= 2;
									rb->velocityX += ra->velocityX;
								}

								(*iter)->pos.x += intersection.GetWidth() / 2;
								(*iter2)->pos.x -= intersection.GetWidth() / 2;
							}
							else if (ra->isFixed)
							{
								(*iter2)->pos.x -= intersection.GetWidth() / 2;
								if (rb->velocityX > 0)
									rb->velocityX = 0;
							}
							else if (rb->isFixed)
							{
								(*iter)->pos.x += intersection.GetWidth() / 2;
								if (ra->velocityX < 0)
									ra->velocityX = 0;
							}
						}
					}
				}
				//y���� �浹�� ��
				else
				{
					//r1�� ���ʿ� ���� ��
					if (r1.GetCenterY() < r2.GetCenterY())
					{
						if (!ra->ignore) rb->isTouchingTop = true;
						if (!rb->ignore) ra->isTouchingBottom = true;
						if (!ra->ignore && !rb->ignore)
						{

							if (!ra->isFixed && !rb->isFixed)
							{
								if (ra->velocityY > 0)
								{
									if (rb->velocityY < 0)
									{
										float a = ra->velocityY / 10;
										float b = rb->velocityY / 10;
										ra->velocityY += b;
										rb->velocityY += a;
									}
									else
									{
										ra->velocityY /= 2;
										rb->velocityY += ra->velocityY;
									}
								}
								else
								{
									rb->velocityY /= 2;
									ra->velocityY += rb->velocityY;
								}

								(*iter)->pos.y -= intersection.GetHeight() / 4;
								(*iter2)->pos.y += intersection.GetHeight() / 4;
							}
							else if (ra->isFixed)
							{
								(*iter2)->pos.y += intersection.GetHeight() / 3;
								if (rb->velocityY < 0)
									rb->velocityY = 0;
							}
							else if (rb->isFixed)
							{
								(*iter)->pos.y -= intersection.GetHeight() / 3;
								if (ra->velocityY > 0)
									ra->velocityY = 0;
							}
						}
					}
					//r1�� �Ʒ��ʿ� ���� ��
					else
					{
						if (!rb->ignore) ra->isTouchingTop = true;
						if (!ra->ignore) rb->isTouchingBottom = true;
						if (!ra->ignore && !rb->ignore)
						{
							if (!ra->isFixed && !rb->isFixed)
							{
								if (rb->velocityY > 0)
								{
									if (ra->velocityY < 0)
									{
										float a = ra->velocityY / 10;
										float b = rb->velocityY / 10;
										ra->velocityY += b;
										rb->velocityY += a;
									}
									else
									{
										rb->velocityY /= 2;
										ra->velocityY += rb->velocityY;
									}
								}
								else
								{
									ra->velocityY /= 2;
									rb->velocityY += ra->velocityY;
								}

								(*iter)->pos.y += intersection.GetHeight() / 4;
								(*iter2)->pos.y -= intersection.GetHeight() / 4;
							}
							else if (ra->isFixed)
							{
								(*iter2)->pos.y -= intersection.GetHeight() / 3;
								if (rb->velocityY > 0)
									rb->velocityY = 0;
							}
							else if (rb->isFixed)
							{
								(*iter)->pos.y += intersection.GetHeight() / 3;
								if (ra->velocityY < 0)
									ra->velocityY = 0;
							}
						}
					}
				}
			}
			//��-��
			else if (a->GetID() == typeid(CircleCollider) &&
				b->GetID() == typeid(CircleCollider))
			{
				const Circle& c1 = ((CircleCollider*)a)->GetCircleWithWorldPos();
				const Circle& c2 = ((CircleCollider*)b)->GetCircleWithWorldPos();
				float intersection = c1.radius + c2.radius - Distance(c1.center, c2.center);
				float angleC1C2 = Angle(c1.center, c2.center);
				float angleC2C1 = NormalizeDegree(angleC1C2 +180);

				if (!ra->isFixed && !rb->isFixed)
				{
					//�ݹݾ�
					(*iter)->pos -= Vec2F(intersection * Cos(angleC1C2),
									intersection * Sin(angleC1C2)) / 2;
					(*iter2)->pos -= Vec2F(intersection * Cos(angleC2C1),
									intersection * Sin(angleC2C1)) / 2;
				}
				else if (ra->isFixed)
				{
					(*iter2)->pos -= Vec2F(intersection * Cos(angleC2C1),
									intersection * Sin(angleC2C1));
					if (angleC2C1 > 0)
					{
						rb->velocityY *= (Sin(angleC2C1-180)+1);
					}
					else if (angleC2C1 < 0 && rb->velocityY < 0)
					{
						rb->velocityY = -rb->velocityY*(Sin(angleC2C1+180));
					}
				}
				else if (rb->isFixed)
				{
					(*iter)->pos -= Vec2F(intersection * Cos(angleC1C2),
						intersection * Sin(angleC1C2));
					if (angleC1C2 > 0)
					{
						ra->velocityY *= (Sin(angleC1C2-180)+1);
					}
					else if (angleC1C2 < 0 && ra->velocityY < 0)
					{
						ra->velocityY = -ra->velocityY*(Sin(angleC1C2+180));
					}
				}
			}
			//�� - �簢��
			else if((a->GetID() == typeid(CircleCollider) &&
				b->GetID() == typeid(AABBCollider)) ||
				(a->GetID() == typeid(AABBCollider) &&
				b->GetID() == typeid(CircleCollider)))
			{
				Circle circle;
				Rect rect;
				int circleNum = 0;
				//iter == 1 , iter2 == 2
				//int circleNum = 0;
				//int rectNum = 0;
				if (a->GetID() == typeid(CircleCollider))
				{
					circle = ((CircleCollider*)a)->GetCircleWithWorldPos();
					rect = ((AABBCollider*)b)->GetRectWithWorldPos();
					circleNum = 1;
				}
				else
				{
					circle = ((CircleCollider*)b)->GetCircleWithWorldPos();
					rect = ((AABBCollider*)a)->GetRectWithWorldPos();
					circleNum = 2;
				}
				Vec2F nearest(
					Clamp(circle.center.x, rect.left, rect.right),
					Clamp(circle.center.y, rect.top, rect.bottom));

				float angle12 = circleNum == 1 ? Angle(circle.center, nearest) : Angle(nearest, circle.center);
				float angle21 = NormalizeDegree(angle12 + 180);

				float intersection = circle.radius - Distance(nearest, circle.center);


				if (!ra->isFixed && !rb->isFixed)
				{
					(*iter)->pos -= Vec2F(intersection * Cos(angle12),
									intersection * Sin(angle12)) / 2;
					(*iter2)->pos -= Vec2F(intersection * Cos(angle21),
									intersection * Sin(angle21)) / 2;
				}
				else if (ra->isFixed)
				{

					(*iter2)->pos -= Vec2F(intersection * Cos(angle21),
									intersection * Sin(angle21));
					if ((int)angle21 == 90 && rb->velocityY > 0.f)
					{
						rb->velocityY = 0.f;
						rb->isTouchingBottom = true;
					}
					else if ((int)angle21 ==-90 && rb->velocityY < 0.f)
					{
						rb->velocityY = -rb->velocityY;
					}
						

				}
				else if (rb->isFixed)
				{

					(*iter)->pos -= Vec2F(intersection * Cos(angle12),
						intersection * Sin(angle12));
					if ((int)angle12 == 90 && ra->velocityY > 0.f)
					{
						ra->velocityY = 0.f;
						ra->isTouchingBottom = true;
					}
					else if ((int)angle12 == -90 && ra->velocityY < 0.f)
					{
						ra->velocityY = -ra->velocityY;
					}
						
				}
			}

		}
	}

	camera.Update();
}

Entity * Scene::FindEntity(Tag tag)
{
	auto iter = std::find_if(entities_.begin(), entities_.end(), [tag](Entity* entity)
	{
		return entity->tag == tag;
	});
	
	if (iter == entities_.end())
		return nullptr;
	else
		return *iter;
}

Entity * Scene::FindEntityIf(std::function<bool(Entity*)> pred)
{
	auto iter = std::find_if(entities_.begin(), entities_.end(), pred);

	if (iter == entities_.end())
		return nullptr;
	else
		return *iter;
}


