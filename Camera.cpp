#include "pch.h"
#include "Camera.h"
#include"App.h"
#include"Scene.h"
Camera::Camera(Entity* scene)
	:target(nullptr),
	range(-(int)RG2Window->GetSize().width, -(int)RG2Window->GetSize().height, RG2Window->GetSize().width, RG2Window->GetSize().height),
	offset(RG2Window->GetSize().width/2, RG2Window->GetSize().height / 2),
	isSmoothFollowEnabled(true),
	smoothFollow(.15f),
	zoom(1.f),
	shakeDuration(0.f, 0.f),
	shakeScale(0.f, 0.f),
	scene_(scene),
	pos_(0,0)
{
}


Camera::~Camera()
{
}

Camera& Camera::Follow(Entity* target)
{
	this->target = target;
	return *this;
}

Camera& Camera::UnFollow()
{
	target = nullptr;
	return *this;
}
Camera& Camera::SetOffset(const Vec2F & offset)
{
	this->offset = offset;
	return *this;
}
Camera& Camera::SetRange(const Rect & range)
{
	this->range = range;
	return *this;
}
Camera& Camera::SetSmoothFollow(float smoothFollow)
{
	this->smoothFollow = smoothFollow;
	return *this;
}
Camera& Camera::SetSmoothFollowEnabled(bool flag)
{
	this->isSmoothFollowEnabled = flag;
	return *this;
}

Camera& Camera::SetZoom(float zoom)
{
	this->zoom = zoom;

	return *this;
}
Camera& Camera::Shake(float duration, const Vec2F& scale)
{
	shakeDuration.first = 0.f;
	shakeDuration.second = duration;
	shakeScale = scale;
	return *this;
}

void Camera::Update()
{
	if (target)
	{
		
		scene_->scale = Vec2F(zoom, zoom);
		scene_->scaleCenter = offset;

		if (isSmoothFollowEnabled)
			pos_ += (-(target->pos) + offset - pos_) * smoothFollow;
		else
			pos_ = (-target->pos + offset);

		Rect area = Rect(0, 0, RG2Settings->windowWidth/zoom, RG2Settings->windowHeight/zoom).Offset(offset - offset/zoom);

		pos_.x = Clamp(pos_.x, -range.right + area.right, -range.left + area.left);
		pos_.y = Clamp(pos_.y, -range.bottom + area.bottom, -range.top + area.top);
		scene_->pos = (pos_ );
	}

	
	if (shakeDuration.first < shakeDuration.second)
	{
		scene_->pos.x += Random(0.f, shakeScale.x) - shakeScale.x / 2;
		scene_->pos.y += Random(0.f, shakeScale.y) - shakeScale.y / 2;
		shakeDuration.first += DT;

	}

		
}
