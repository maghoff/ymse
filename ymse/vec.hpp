#ifndef YMSE_VEC_HPP
#define YMSE_VEC_HPP

namespace ymse {

template <int Dim, typename T>
struct vec {
	typedef T value_type;

	T v[Dim];
	T operator[] (int n) const { return v[n]; }
	T& operator[] (int n) { return v[n]; }

	vec();
	vec(T x, T y);
	vec(T x, T y, T z);

	vec<Dim, T>& operator += (vec<Dim, T>);
	vec<Dim, T>& operator -= (vec<Dim, T>);

	vec<Dim, T>& operator *= (T);

	T length() const;
	T square_length() const;
};

template <int Dim, typename T>
ymse::vec<Dim, T> operator + (const ymse::vec<Dim, T>&, const ymse::vec<Dim, T>&);

template <int Dim, typename T>
ymse::vec<Dim, T> operator * (const ymse::vec<Dim, T>&, T);

template <int Dim, typename T>
ymse::vec<Dim, T> operator * (T, const ymse::vec<Dim, T>&);

extern template struct vec<2, float>;
extern template struct vec<3, float>;

extern template struct vec<2, int>;

typedef vec<2, float> vec2f;
typedef vec<3, float> vec3f;

typedef vec<2, int> vec2i;

}

#endif
