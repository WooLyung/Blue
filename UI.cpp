#include "pch.h"
#include "UI.h"



UI::UI(Entity* owner, Vec2F pos, DIR dir, Camera *cam)
	:Component(owner), pos(pos), dir(dir), cam(cam)
{
}

UI::~UI()
{
}

void UI::OnUpdate(void)
{
	GetOwner()->SetScale(Vec2F(1 / cam->zoom, 1 / cam->zoom));

	if (dir == DIR::LEFT_BOTTOM || dir == DIR::LEFT_MIDDLE || dir == DIR::LEFT_TOP)
	{
		GetOwner()->pos.x = -cam->pos_.x + this->pos.x / cam->zoom - (1/cam->zoom - 1) * (LONG)App::GetInstance()->GetSettings()->windowWidth / 2;
	}
	else if (dir == DIR::MIDDLE_BOTTOM || dir == DIR::CENTER || dir == DIR::MIDDLE_TOP)
	{
		GetOwner()->pos.x = -cam->pos_.x + this->pos.x / cam->zoom + (LONG)App::GetInstance()->GetSettings()->windowWidth / 2;
	}
	else if (dir == DIR::RIGHT_BOTTOM || dir == DIR::RIGHT_MIDDLE || dir == DIR::RIGHT_TOP)
	{
		GetOwner()->pos.x = -cam->pos_.x + this->pos.x / cam->zoom + (LONG)App::GetInstance()->GetSettings()->windowWidth / 2 * (1 + 1 / cam->zoom);
	}

	if (dir == DIR::LEFT_TOP || dir == DIR::MIDDLE_TOP || dir == DIR::RIGHT_TOP)
	{
		GetOwner()->pos.y = -cam->pos_.y + this->pos.y / cam->zoom - (1 / cam->zoom - 1) * (LONG)App::GetInstance()->GetSettings()->windowHeight / 2;
	}
	else if (dir == DIR::LEFT_MIDDLE || dir == DIR::CENTER || dir == DIR::RIGHT_MIDDLE)
	{
		GetOwner()->pos.y = -cam->pos_.y + this->pos.y / cam->zoom + (LONG)App::GetInstance()->GetSettings()->windowHeight / 2;
	}
	else if (dir == DIR::LEFT_BOTTOM || dir == DIR::MIDDLE_BOTTOM || dir == DIR::RIGHT_BOTTOM)
	{
		GetOwner()->pos.y = -cam->pos_.y + this->pos.y / cam->zoom + (LONG)App::GetInstance()->GetSettings()->windowHeight / 2 * (1 + 1 / cam->zoom);
	}
}

