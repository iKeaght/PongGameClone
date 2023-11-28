class Vector2 {
public:
	float x;
	float y;

	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(float x, float y) : x(x), y(y) {}

	//overriding operator
	Vector2 operator+ (Vector2 const& other) {
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator*(float other) {
		return Vector2(x * other, y * other);
	}

	Vector2 operator+=(Vector2 const& other) {
		x += other.x;
		y += other.y;
		return *this;
	}
};