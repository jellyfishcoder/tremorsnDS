#ifndef SHAPES3D_H
#define SHAPES3D_H

#include <nds.h>
#include "types.h"

class Shape3D {
	protected:
		MathVector3D<f32> center;	// X, Y, and Z center value as a fixed
		MathVector3D<f32> scale;	// X, Y, and Z scale value as a fixed
	public:
		// Functions related to updating properties
		void setCenter(MathVector3D<int> _center);
		void setScale(MathVector3D<int> _scale);
		// Functions related to retriving information
		MathVector3D<f32> getCenter();
		MathVector3D<f32> getScale();
		Shape3D(MathVector3D<f32> _center, MathVector3D<f32> _scale);
};

class RectPrism: protected Shape3D {
	protected:
		MathVector3D<f32> size;		// Size, NOT scale, scale multiplies by size before rendering
	public:
		RectPrism(MathVector3D<f32> _center, MathVector3D<f32> _scale, MathVector3D<f32> _dimensions);
		// Functions related to rendering
		void draw();
		//void setTexture(Texture _texture);
		// Functions to update properties
		void setDimensions(MathVector3D<f32> _dimensions);
		// Functions to retrive information
		MathVector3D<f32> getDimensions();
		f32 getVolume();		// Automatically use scale when calculating volume, returns a FIXED
};
