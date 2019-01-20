#pragma once

template <class T>
Vector3<T> operator*(T t, const Vector3<T> v) { return Vector3<T>(v.e[0] * t, v.e[1] * t, v.e[2] * t); }

template <class T>
Vector3<T> operator+(const Vector3<T> v1, const Vector3<T> v2) { return Vector3<T>(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]); }

template <class T>
Vector3<T> operator-(const Vector3<T> v1, const Vector3<T> v2) { return Vector3<T>(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]); }

template <class T>
T Vector3<T>::SquaredLength() const
{
	return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

template <class T>
void Vector3<T>::Normalize()
{
	auto lengthInverse = static_cast<T>(1.0) / Length();
	*this *= lengthInverse;
}

template <class T>
T Vector3<T>::dot(const Vector3<T> v1, const Vector3<T> v2)
{
	return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}