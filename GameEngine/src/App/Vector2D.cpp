#include <gepch.h>
#include "Vector2D.h"

namespace App
{
	Vector2D::Vector2D()
	{
		x = 0;
		y = 0;
	}

	Vector2D::Vector2D(double x, double y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2D& Vector2D::operator=(const Vector2D& other)
	{
		this->x = other.x;
		this->y = other.y;
		return *this;
	}

	Vector2D& Vector2D::operator+=(const Vector2D& other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	Vector2D Vector2D::operator+(const Vector2D& other)
	{
		Vector2D copy = Vector2D(*this);
		return copy += other;
	}

	Vector2D& Vector2D::operator-=(const Vector2D& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}

	Vector2D Vector2D::operator-(const Vector2D& other)
	{
		Vector2D copy = Vector2D(*this);
		return copy -= other;
	}

	Vector2D& Vector2D::operator*=(const Vector2D& other)
	{
		this->x *= other.x;
		this->y *= other.y;
		return *this;
	}

	Vector2D& Vector2D::operator*=(const double& fact)
	{
		this->x *= fact;
		this->y *= fact;
		return *this;
	}

	Vector2D Vector2D::operator*(const double& fact)
	{
		return Vector2D(this->x * fact, this->y * fact);
	}

	bool Vector2D::operator==(const Vector2D& other)
	{
		return other.x == this->x && other.y == this->y;
	}

	bool Vector2D::operator!=(const Vector2D& other)
	{
		return !(*this == other);
	}

	Vector2D& Vector2D::AddScaled(const Vector2D& other, double magnitude)
	{
		this->x += other.x * magnitude;
		this->y += other.y * magnitude;
		return *this;
	}

	double Vector2D::Angle()
	{
		return std::atan2(y, x);
	}

	double Vector2D::AngleBetween(const Vector2D& other)
	{
		Vector2D thisCopy = Vector2D(*this);
		Vector2D thatCopy = Vector2D(other);
		thisCopy.Normalize();
		thatCopy.Normalize();
		return std::acos(thisCopy.Dot(thatCopy));
	}

	double Vector2D::Dot(const Vector2D& other)
	{
		return x * other.x + y * other.y;
	}

	double Vector2D::Distance(const Vector2D& other)
	{
		return std::hypot(other.x - x, other.y - y);
	}

	Vector2D Vector2D::Project(const Vector2D& other)
	{
		Vector2D result = other;
		Vector2D copy = *this;
		copy.Dot(other);
		result *= copy;
		return result;
	}

	Vector2D& Vector2D::Normalize()
	{
		if (x == 0 && y == 0)
			return *this;
		double angle = Angle();
		x = std::cos(angle) * 1;
		y = std::sin(angle) * 1;
		return *this;
	}

	Vector2D& Vector2D::Rotate(const double& angle)
	{
		double tempx = this->x;
		x = x * std::cos(angle) - y * std::sin(angle);
		y = tempx * std::sin(angle) + y * std::cos(angle);;
		return *this;
	}

	Vector2D& Vector2D::Clamp(const double& magnitude)
	{
		double currentMagnitude = Magnitude();
		if (currentMagnitude == 0)
			return *this;
		x = x * magnitude / currentMagnitude;
		y = y * magnitude / currentMagnitude;
	}

	Vector2D Vector2D::Cartesian(double angle, double magnitude)
	{
		return Vector2D(std::cos(angle) * magnitude, std::sin(angle) * magnitude);
	}

	double Vector2D::Magnitude()
	{
		return std::hypot(x, y);
	}

}
