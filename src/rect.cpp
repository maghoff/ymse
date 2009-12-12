#include <algorithm>
#include "rect.hpp"

namespace ymse {

template struct rect<float>;


template<>
rectf bounding_box(rectf a, rectf b) {
	rectf r = {
		x1: std::min(a.x1, b.x1), y1: std::min(a.y1, b.y1),
		x2: std::max(a.x2, b.x2), y2: std::max(a.y2, b.y2)
	};
	return r;
}

}
