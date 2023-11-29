#pragma once
namespace Utils {
	const int WINDOW_WIDTH = 1920;
	const int WINDOW_HEIGHT = 1080;
	const int PADDLE_WIDTH = 10;
	const int PADDLE_HEIGHT = 100;
	const int BALL_WIDTH = 15;
	const int BALL_HEIGHT = 15;
	const float PADDLE_SPEED = 1.0f;
	const float BALL_SPEED = 1.0f;
	enum class CollisionType {
		None,
		Top,
		Middle,
		Bottom
	};

	struct Contact {
		CollisionType type;
		float penetration;
	};
}