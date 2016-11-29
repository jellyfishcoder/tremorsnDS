#ifndef TYPES_H
#define TYPES_H
#define pi 3.1415926535897932
#include <cereal/archives/binary.hpp>

/* * * * * * * * * * * * * * * * * * * * * * *
 * The operator overloads MUST be in the same*
 * file as the class definition, or wherever *
 * the operator is first defined. If the     *
 * operator overloads are placed in any other*
 * file, the linker will have problems and   *
 * there will be linking errors.             *
 * * * * * * * * * * * * * * * * * * * * * * */
 

// MARK: MathVector2D Structure
template <class T>
	struct MathVector2D {
		bool operator== (MathVector2D<T> other) const;

		T x;
		T y;
		// Initialisation
		explicit MathVector2D(T x, T y);
		MathVector2D() = default;
		// Serialisation
		template <class Archive>
			void serialize( Archive & ar ) {
				ar(x, y);
			}
	};

// MARK: MathVector2D Operators
template <class T>
	bool MathVector2D<T>::operator==(MathVector2D<T> other) const {
		if((other.x == x) && (other.y == y)) {
			return true;
		} else {
			return false;
		}
	}

// MARK: Three Dimensional Vector
template <class T>
	struct MathVector3D {
		bool operator== (const MathVector3D<T> other) const;

		T x;
		T y;
		T z;
		// Initialisation
		explicit MathVector3D(T x, T y, T z);
		MathVector3D() = default;
		// Serialisation
		template <class Archive>
			void serialize( Archive & ar ) {
				ar(x, y, z);
			}
	};

// MARK: MathVector3D Operators
template<class T>
	bool MathVector3D<T>::operator==(const MathVector3D<T> other) const {
		if((other.x == x) && (other.y == y) && (other.z == z)) {
			return true;
		} else {
			return false;
		}
	}

/*
struct SaveSlot {
	int curMap;
	MathVector3D<float> playerPos;
	bool discMaps[10];
	int maxHealth;
	int curHealth;
	int maxAura;
	int curAura;
};*/

#endif 
