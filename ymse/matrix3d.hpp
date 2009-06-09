#ifndef YMSE_MATRIX3D_HPP
#define YMSE_MATRIX3D_HPP

namespace ymse {

template <int Size, typename T>
struct sq_matrix;

typedef sq_matrix<3, float> matrix33f;


namespace matrix3d {

matrix33f identity();

matrix33f rotate_x(double);
matrix33f rotate_y(double);
matrix33f rotate_z(double);

}

}

#endif
