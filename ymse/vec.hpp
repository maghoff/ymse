#ifndef YMSE_VEC_HPP
#define YMSE_VEC_HPP

namespace ymse {

template <int dim, typename T>
struct vec {
	typedef T value_type;

	T v[dim];
	T operator[] (int n) const { return v[n]; }
	T& operator[] (int n) { return v[n]; }

	vec();
	vec(T x, T y);
	vec(T x, T y, T z);

	vec<dim, T>& operator += (vec<dim, T>);
	vec<dim, T>& operator -= (vec<dim, T>);

	vec<dim, T>& operator *= (T);

	T length() const;
	T square_length() const;
};

extern template struct vec<2, float>;
extern template struct vec<3, float>;

typedef vec<2, float> vec2f;
typedef vec<3, float> vec3f;

}

#endif
