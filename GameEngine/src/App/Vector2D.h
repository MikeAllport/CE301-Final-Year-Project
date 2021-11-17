#ifndef APP_VEC2D
#define APP_VEC2D

namespace App
{
	/**
	* Vector2D class used from CE213-Game Programmin module
	*/
	class Vector2D
	{
	public:
		Vector2D();
		Vector2D(double x, double y);
		Vector2D& operator=(const Vector2D& other);
		Vector2D& operator+=(const Vector2D& other);
		Vector2D operator+(const Vector2D& other);
		Vector2D& operator-=(const Vector2D& other);
		Vector2D operator-(const Vector2D& other);
		Vector2D& operator*=(const Vector2D& other);
		Vector2D& operator*=(const double& fact);
		Vector2D operator*(const double& fact);
		bool operator==(const Vector2D& other);
		bool operator!=(const Vector2D & other);
		Vector2D& AddScaled(const Vector2D& other, double magnitude);
		double Angle();
		double AngleBetween(const Vector2D& other);
		double Dot(const Vector2D& other);
		double Distance(const Vector2D& other);
		Vector2D Project(const Vector2D& other);
		Vector2D& Normalize();
		Vector2D& Rotate(const double& angle);
		Vector2D& Clamp(const double& magnitude);
		static Vector2D Cartesian(double angle, double magnitude);
		double Magnitude();
		double x, y;
	};
}
#endif // !APP_VEC2D
