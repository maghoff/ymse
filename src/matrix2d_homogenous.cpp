#include "matrix3d.hpp"
#include "matrix2d_homogenous.hpp"

namespace ymse {
namespace matrix2d {
namespace homogenous {

matrix33f scale(double sx, double sy) {
	return matrix3d::scale(sx, sy, 1);
}

matrix33f translate(double dx, double dy) {
	matrix33f t = matrix3d::identity();
	t[0][2] = dx;
	t[1][2] = dy;
	return t;
}

} // namespace homogenous
} // namespace matrix2d
} // namespace ymse
