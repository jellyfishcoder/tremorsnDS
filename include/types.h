#ifndef TYPES_H
#define TYPES_H
#define pi 3.1415926535897932

// Two Dimensional Vector
template <class T>
struct MathVector2D {
	T x;
	T y;
};

// Three Dimensional Vector
template <class T>
struct MathVector3D {
	T x;
	T y;
	T z;
};

struct SaveSlot {
	int curMap;
	MathVector3D<float> playerPos;
	bool discMaps[10];
	int maxHealth;
	int curHealth;
	int maxAura;
	int curAura;
};

#endif 
