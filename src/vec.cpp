#include <cassert>
#include <cmath>
#include "vec.hpp"

namespace ymse {

template <int Dim, typename T>
vec<Dim, T>::vec() :
	x(v[0]),
	y(v[1])
{
	assert(Dim >= 2);
}

template <int Dim, typename T>
vec<Dim, T>::vec(T x_, T y_) :
	x(v[0]),
	y(v[1])
{
	assert(Dim == 2);
	v[0] = x_;
	v[1] = y_;
}

template <int Dim, typename T>
vec<Dim, T>::vec(T x_, T y_, T z_) :
	x(v[0]),
	y(v[1])
{
	assert(Dim == 3);
	v[0] = x_;
	v[1] = y_;
	v[2] = z_;
}

template <int Dim, typename T>
vec<Dim, T>& vec<Dim, T>::operator += (vec<Dim, T> rhs) {
	for (int i=0; i<Dim; ++i) v[i] += rhs[i];
	return *this;
}

template <int Dim, typename T>
vec<Dim, T>& vec<Dim, T>::operator -= (vec<Dim, T> rhs) {
	for (int i=0; i<Dim; ++i) v[i] -= rhs[i];
	return *this;
}

template <int Dim, typename T>
vec<Dim, T>& vec<Dim, T>::operator /= (vec<Dim, T> rhs) {
	for (int i=0; i<Dim; ++i) v[i] /= rhs[i];
	return *this;
}

template <int Dim, typename T>
vec<Dim, T>& vec<Dim, T>::operator *= (T rhs) {
	for (int i=0; i<Dim; ++i) v[i] *= rhs;
	return *this;
}

template <int Dim, typename T>
T vec<Dim, T>::length() const {
	return sqrt(square_length());
}

template <int Dim, typename T>
T vec<Dim, T>::square_length() const {
	T acc(0);
	for (int i=0; i<Dim; ++i) acc += v[i] * v[i];
	return acc;
}

template <int Dim, typename T>
vec<Dim, T> operator + (const vec<Dim, T>& lhs, const vec<Dim, T>& rhs) {
	vec<Dim, T> r(lhs);
	r += rhs;
	return r;
}

template <int Dim, typename T>
vec<Dim, T> operator - (const vec<Dim, T>& lhs, const vec<Dim, T>& rhs) {
	vec<Dim, T> r(lhs);
	r -= rhs;
	return r;
}

template <int Dim, typename T>
vec<Dim, T> operator / (const ymse::vec<Dim, T>& lhs, const ymse::vec<Dim, T>& rhs)
{
	vec<Dim, T> r(lhs);
	r /= rhs;
	return r;
}


template <int Dim, typename T>
vec<Dim, T> operator * (const vec<Dim, T>& lhs, T rhs) {
	vec<Dim, T> r(lhs);
	r *= rhs;
	return r;
}

template <int Dim, typename T>
vec<Dim, T> operator * (T lhs, const vec<Dim, T>& rhs) {
	return rhs * lhs;
}

#define INSTANTIATE(name, dim, t) \
	template struct vec<dim, t>; \
	template name operator + (const name&, const name&); \
	template name operator * (const name&, t); \
	template name operator * (t, const name&); \
	template name operator - (const name&, const name&); \
	template name operator / (const name&, const name&);

INSTANTIATE(vec2f, 2, float);
INSTANTIATE(vec3f, 3, float);
INSTANTIATE(vec2i, 2, int);

}
