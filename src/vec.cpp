#include <cmath>
#include "vec.hpp"

namespace ymse {

template <int dim, typename T>
vec<dim, T>::vec() {
}

template <int dim, typename T>
vec<dim, T>::vec(T x, T y) {
	v[0] = x;
	v[1] = y;
}

template <int dim, typename T>
vec<dim, T>& vec<dim, T>::operator += (vec<dim, T> rhs) {
	for (int i=0; i<dim; ++i) v[i] += rhs[i];
}

template <int dim, typename T>
vec<dim, T>& vec<dim, T>::operator -= (vec<dim, T> rhs) {
	for (int i=0; i<dim; ++i) v[i] -= rhs[i];
}

template <int dim, typename T>
vec<dim, T>& vec<dim, T>::operator *= (T rhs) {
	for (int i=0; i<dim; ++i) v[i] *= rhs;
}

template <int dim, typename T>
T vec<dim, T>::length() const {
	T acc(0);
	for (int i=0; i<dim; ++i) acc += v[i] * v[i];
	return sqrt(acc);
}


template struct vec<2, float>;

}
