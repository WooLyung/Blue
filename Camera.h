#pragma once
#include"Math.h"
class Entity;
class Camera 
{
private:
	Entity* scene_;
public:
	Vec2F pos_;
	Entity* target;
	Rect range;
	Vec2F offset;
	bool isSmoothFollowEnabled;
	//0ÀÌ»ף
	float smoothFollow;
	std::pair<float, float> shakeDuration;
	Vec2F shakeScale;
	float zoom;

public:
	Camera(Entity* scene);
	~Camera();
	Camera& Follow(Entity* target);
	Camera& UnFollow();
	Camera& SetOffset(const Vec2F& offset);
	Camera& SetRange(const Rect& range);
	Camera& SetSmoothFollow(float smoothFollow);
	Camera& SetSmoothFollowEnabled(bool flag);
	Camera& SetZoom(float zoom);
	Camera& Shake(float duration, const Vec2F& scale);

	Vec2F GetOffset() const { return offset; }
	Rect GetRange() const { return range; }
	float GetSmoothFollow() const { return smoothFollow; }
	bool IsSmoothFollowEnabled() const { return isSmoothFollowEnabled; }
	float GetZoom() const { return zoom; }

	void Update();
};

