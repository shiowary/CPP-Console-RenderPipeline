#include "Vector.h"
#include "math.h"
using namespace std;

//Math Operators

inline bool operator==(const Vector& a, const Vector& b) {return a.x == b.x && a.y == b.y && a.z == b.z;}
inline bool operator!=(const Vector& a, const Vector& b) { return !(a == b); }
inline Vector operator+(const Vector& a, const Vector& b) { return { a.x + b.x, a.y + b.y, a.z + b.z }; }
inline Vector operator-(const Vector& a, const Vector& b) { return { a.x - b.x, a.y - b.y, a.z - b.z }; }
inline Vector operator*(const Vector& a, float s) { return { a.x * s, a.y * s, a.z * s }; }
inline Vector operator/(const Vector& a, float s) { return { a.x / s, a.y / s, a.z / s }; }

//Properties
float Vector::magnitude()  const   { return x * x + y * y + z * z; }
float Vector::sqrMagnitude() const { return sqrt(x * x + y * y + z * z); }

Vector Vector::Normalized() const { 
    return  mag / sqrmag;
};

//Static Methods
float Vector::Angle(Vector from, Vector to) {
	float angle = (from.magnitude() * to.magnitude()) / (from.sqrMagnitude() * to.sqrMagnitude());
	return angle;
};

Vector Vector::Cross(Vector lhs, Vector rhs)
{
    return Vector(
        lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x
    );
}
float Vector::Clamp(float value, float min, float max) {
    float val = value;
    if (val > max) {
        val = max;
    }
    else if (val < min) {
        val = min;
    }
    return val;
};


float Vector::Distance(Vector a, Vector b)
{
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    float dz = b.z - a.z;

    return sqrt(dx * dx + dy * dy + dz * dz);
}

Vector Vector::Dot(Vector a, Vector b)
{
    float dot = a.x * b.x + a.y * b.y + a.z * b.z;
    return Vector(dot, dot, dot);
}

Vector Vector::Reflect(Vector a, Vector plane)
{
    // Reflection formula:
    // R = V - 2 * dot(V, N) * N
    float dot = a.x * plane.x +
        a.y * plane.y +
        a.z * plane.z;

    return a - plane * (2.0f * dot);
}

Vector Vector::RotateTowards(Vector current,Vector target,float maxRadiansDelta,float maxMagnitudeDelta)
{
    float currentMagnitude = current.magnitude();
    float targetMagnitude = target.magnitude();
    float newMagnitude = currentMagnitude;

    if (currentMagnitude < targetMagnitude)
        newMagnitude = fmin(currentMagnitude + maxMagnitudeDelta,
            targetMagnitude);
    else
        newMagnitude = fmax(currentMagnitude - maxMagnitudeDelta,
            targetMagnitude);
    if (currentMagnitude <= 0.0f)
        return target.Normalized() * newMagnitude;

    if (targetMagnitude <= 0.0f)
    {
        return current.Normalized() * newMagnitude;
    }
    Vector currentDir = current / currentMagnitude;
    Vector targetDir = target / targetMagnitude;
    float dot = currentDir.x * targetDir.x +
        currentDir.y * targetDir.y +
        currentDir.z * targetDir.z;
    dot = Clamp(dot, -1.0f, 1.0f);
    float angle = acos(dot);
    if (angle <= 0.0f)
        return targetDir * newMagnitude;
    if (angle <= maxRadiansDelta)
        return targetDir * newMagnitude;
    Vector axis = Cross(currentDir, targetDir);
    float axisMagnitude = axis.magnitude();
    if (axisMagnitude <= 0.000001f)
    {
        Vector perpendicular;

        if (fabs(currentDir.x) < fabs(currentDir.y))
            perpendicular = Cross(currentDir, Vector(1.0f, 0.0f, 0.0f));
        else
            perpendicular = Cross(currentDir, Vector(0.0f, 1.0f, 0.0f));

        axis = perpendicular.Normalized();
    }
    else
    {
        axis = axis / axisMagnitude;
    }
    float theta = maxRadiansDelta;
    float cosTheta = cos(theta);
    float sinTheta = sin(theta);
    Vector rotated =
        currentDir * cosTheta +
        Cross(axis, currentDir) * sinTheta +
        axis * (Dot(currentDir, axis).x * (1.0f - cosTheta));

    return rotated.Normalized() * newMagnitude;
}

Vector Vector::MoveTowards(Vector current,Vector target,float maxDistanceDelta)
{
    Vector delta = target - current;
    float distance = delta.magnitude();
    if (distance <= maxDistanceDelta || distance <= 0.0f)
        return target;
    return current + delta * (maxDistanceDelta / distance);
}

bool Vector::ApproxEqu(Vector a, Vector b, float margin) {
    return fabs(a.x - b.x) < margin || fabs(a.y - b.y) < margin || fabs(a.z - b.z) < margin;
};
