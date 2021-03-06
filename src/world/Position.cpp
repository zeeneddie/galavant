#include "Position.hpp"
#include <cmath>

namespace gv
{
const float POSITION_TOLERANCE = 0.1f;

Position::Position(float x, float y, float z) : X(x), Y(y), Z(z)
{
}

Position::Position(float floatArray[3]) : X(floatArray[0]), Y(floatArray[1]), Z(floatArray[2])
{
}

bool Position::Equals(const Position& otherPosition, float tolerance) const
{
	return (fabs(X - otherPosition.X) <= tolerance && fabs(Y - otherPosition.Y) <= tolerance &&
	        fabs(Z - otherPosition.Z) <= tolerance);
}

void Position::Reset()
{
	X = Y = Z = 0.f;
}

void Position::Set(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

float Position::ManhattanTo(const Position& otherPosition) const
{
	return fabs(X - otherPosition.X) + fabs(Y - otherPosition.Y) + fabs(Z - otherPosition.Z);
}

Position Position::GetSafeNormal(float tolerance) const
{
	float squareSum = X * X + Y * Y + Z * Z;

	if (squareSum == 1.f)
		return Position(X, Y, Z);
	else if (squareSum < tolerance)
		return Position(0.f, 0.f, 0.f);

	float scale = std::sqrt(squareSum);
	return Position(X * scale, Y * scale, Z * scale);
}

void Position::Scale(float scale)
{
	X *= scale;
	Y *= scale;
	Z *= scale;
}

Position::operator bool() const
{
	// Only return false if we're exactly zero (don't use tolerances)
	return !(X == 0.f && Y == 0.f && Z == 0.f);
}

float& Position::operator[](int index)
{
	switch (index)
	{
		case 0:
			return X;
		case 1:
			return Y;
		case 2:
			return Z;
	}
	return X;
}

Position Position::operator+(const Position& otherPosition) const
{
	Position newPosition(*this);
	newPosition.X += otherPosition.X;
	newPosition.Y += otherPosition.Y;
	newPosition.Z += otherPosition.Z;
	return newPosition;
}

Position Position::operator-(const Position& otherPosition) const
{
	Position newPosition(*this);
	newPosition.X -= otherPosition.X;
	newPosition.Y -= otherPosition.Y;
	newPosition.Z -= otherPosition.Z;
	return newPosition;
}

Position Position::operator*(const Position& otherPosition) const
{
	Position newPosition(*this);
	newPosition.X *= otherPosition.X;
	newPosition.Y *= otherPosition.Y;
	newPosition.Z *= otherPosition.Z;
	return newPosition;
}

Position Position::operator/(const Position& otherPosition) const
{
	Position newPosition(*this);
	newPosition.X /= otherPosition.X;
	newPosition.Y /= otherPosition.Y;
	newPosition.Z /= otherPosition.Z;
	return newPosition;
}

Position& Position::operator+=(const Position& otherPosition)
{
	X += otherPosition.X;
	Y += otherPosition.Y;
	Z += otherPosition.Z;
	return *this;
}

Position& Position::operator-=(const Position& otherPosition)
{
	X -= otherPosition.X;
	Y -= otherPosition.Y;
	Z -= otherPosition.Z;
	return *this;
}

Position& Position::operator*=(const Position& otherPosition)
{
	X *= otherPosition.X;
	Y *= otherPosition.Y;
	Z *= otherPosition.Z;
	return *this;
}

Position& Position::operator/=(const Position& otherPosition)
{
	X /= otherPosition.X;
	Y /= otherPosition.Y;
	Z /= otherPosition.Z;
	return *this;
}

bool Position::operator==(const Position& otherPosition) const
{
	return X == otherPosition.X && Y == otherPosition.Y && Z == otherPosition.Z;
}

GlobalPosition::GlobalPosition(Position& localPosition) : LocalPosition(localPosition)
{
}
}

template <>
gv::Logging::Record& gv::Logging::Record::operator<<<gv::Position>(const gv::Position& data)
{
	*this << "(" << data.X << ", " << data.Y << ", " << data.Z << ")";
	return *this;
}