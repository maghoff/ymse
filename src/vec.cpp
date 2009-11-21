#include <cassert>
#include <cmath>
#include "vec.hpp"

namespace ymse {

template <int Dim, typename T>
vec<Dim, T>::vec() {
}

template <int Dim, typename T>
vec<Dim, T>::vec(T x, T y) {
	assert(Dim == 2);
	v[0] = x;
	v[1] = y;
}

template <int Dim, typename T>
vec<Dim, T>::vec(T x, T y, T z) {
	assert(Dim == 3);
	v[0] = x;
	v[1] = y;
	v[2] = z;
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


template struct vec<2, float>;
template struct vec<3, float>;

template struct vec<2, int>;

}
