#ifndef YMSE_VEC_HPP
#define YMSE_VEC_HPP

namespace ymse {

template <int dim, typename T>
struct vec {
	typedef T value_type;

	T v[dim];
	T& operator[] (int n) { return v[n]; }

	vec();
	vec(T x, T y);

	vec<dim, T>& operator += (vec<dim, T>);
	vec<dim, T>& operator -= (vec<dim, T>);

	vec<dim, T>& operator *= (T);

	T length() const;
};

extern template struct vec<2, float>;

typedef vec<2, float> vec2f;

}

#endif
