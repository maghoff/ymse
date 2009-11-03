#include <cassert>
#include <cmath>
#include "vec.hpp"

namespace ymse {

template <int dim, typename T>
vec<dim, T>::vec() {
}

template <int dim, typename T>
vec<dim, T>::vec(T x, T y) {
	assert(dim == 2);
	v[0] = x;
	v[1] = y;
}

template <int dim, typename T>
vec<dim, T>::vec(T x, T y, T z) {
	assert(dim == 3);
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

template <int dim, typename T>
vec<dim, T>& vec<dim, T>::operator += (vec<dim, T> rhs) {
	for (int i=0; i<dim; ++i) v[i] += rhs[i];
	return *this;
}

template <int dim, typename T>
vec<dim, T>& vec<dim, T>::operator -= (vec<dim, T> rhs) {
	for (int i=0; i<dim; ++i) v[i] -= rhs[i];
	return *this;
}

template <int dim, typename T>
vec<dim, T>& vec<dim, T>::operator *= (T rhs) {
	for (int i=0; i<dim; ++i) v[i] *= rhs;
	return *this;
}

template <int dim, typename T>
T vec<dim, T>::length() const {
	T acc(0);
	for (int i=0; i<dim; ++i) acc += v[i] * v[i];
	return sqrt(acc);
}


template struct vec<2, float>;
template struct vec<3, float>;

}
