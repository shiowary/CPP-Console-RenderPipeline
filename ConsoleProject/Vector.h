#pragma once
#include "math.h"
# define M_PI           3.14159265358979323846  /* pi */

using namespace std;
class Vector
{ 


public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;


	//for optimizations we store these values within the class to avoid recalculations
	float mag = 0.0f;
	float sqrmag = 0.0f;


	Vector(float x_ = 0.0f, float y_ = 0.0f, float z_ = 0.0f): x(x_),y(y_),z(z_) {
		mag = sqrt(x * x + y * y + z * z);
		sqrmag = x * x + y * y + z * z;
	};
	//Properties
	Vector Normalized() const;
	float magnitude() const;
	float sqrMagnitude() const;

	//Static Methods
	static float Angle(Vector from, Vector to);
	static Vector Cross(Vector lhs, Vector rhs); //Cross Product of two vectors.
	static float Distance(Vector a, Vector b);
	static Vector Dot(Vector a, Vector b);
	static Vector Reflect(Vector a, Vector plane); //Reflects a vector off the plane defined by a normal.
	static Vector RotateTowards(Vector current, Vector target, float maxRadiansDelta, float maxMagnitudeDelta); //Rotates a vector current towards target.
	static Vector MoveTowards(Vector current, Vector target, float maxDistanceDelta); //Calculate a position between the points specified by current and target, moving no farther than the distance specified by maxDistanceDelta.
	static float Clamp(float value, float min, float max);


	//Non Static Methods

	bool ApproxEqu(Vector a, Vector b, float margin);
	
	Vector RotateX(Vector v, float angle)
	{
		float rad = angle * (float)M_PI / 180.0f;
		float fcos = cos(rad);
		float fsin = sin(rad);
		return Vector(v.x, v.y * fcos - v.z * fsin, v.y * fsin + v.z * fcos);
	}

	Vector RotateY(Vector v, float angle)
	{
		float rad = angle * (float)M_PI / 180.0f;
		float fcos = cos(rad);
		float fsin = sin(rad);
		return Vector(v.x * fcos + v.z * fsin, v.y, -v.x * fsin + v.z * fcos);
	}

	Vector RotateZ(Vector v, float angle)
	{
		float rad = angle * (float)M_PI / 180.0f;
		float fcos = cos(rad);
		float fsin = sin(rad);
		return Vector(v.x * fcos - v.y * fsin, v.x * fsin + v.y * fcos, v.z);
	}

private:



};

bool   operator==(const Vector& a, const Vector& b);
bool   operator!=(const Vector& a, const Vector& b);
Vector operator+ (const Vector& a, const Vector& b);
Vector operator- (const Vector& a, const Vector& b);
Vector operator* (const Vector& a, float s);        
Vector operator/ (const Vector& a, float s);        