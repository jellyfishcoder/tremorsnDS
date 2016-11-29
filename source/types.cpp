#include "types.h"

/* Do not place operator overrides here,
 * linking *will* fail. Place them in the
 * file the class/struct is defined in.   */

// MARK: MathVector2D Initialiser
template<class T>
	MathVector2D<T>::MathVector2D(T x, T y) {
		this->x = x;
		this->y = y;
	};

// MARK: MathVector3D Initialiser
template<class T>
	MathVector3D<T>::MathVector3D(T x, T y, T z) {
		this->x = x;
		this->y = y;
		this->z = z;
	};
