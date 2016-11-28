#ifndef TYPES_H
#define TYPES_H
#define pi 3.1415926535897932
#include <cereal/archives/binary.hpp>

// Two Dimensional Vector
template <class T>
	struct MathVector2D {
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

// Three Dimensional Vector
template <class T>
	struct MathVector3D {
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
