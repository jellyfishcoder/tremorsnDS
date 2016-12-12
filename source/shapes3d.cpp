#include "shapes3d.h"

// MARK: Shape3D Functions
Shape3D::Shape3D(MathVector3D<f32> _center, MathVector3D<f32> _scale) {
	this->center = _center;
	this->scale = _scale;
}

// Functions related to retrieving information
MathVector3D<f32> getScale::Shape3D() {
	return this->scale;
}

MathVector3D<f32> getCenter::Shape3D() {
	return this->center;
}

// Functions related to changing information
void setScale::Shape3D(MathVector3D<f32> _scale) {
	this->scale = _scale;
}

void setCenter::Shape3D(MathVector3D<f32> _center) {
	this->center = _center;
}

// MARK: RectPrism Functions
RectPrism::RectPrism(MathVector3D<f32> _center, MathVector3D<f32> _scale, MathVector3D<f32> _dimensions) {
	this->center = _center;
	this->scale = _scale;
	this->dimensions = _dimensions;
}

// Functions related to retrieving information
MathVector3D<f32> getDimensions::RectPrism() {
	return this->dimensions;


f32 getVolume::RectPrism() {
	return 

// Functions related to changing information
void setDimensions::RectPrism(MathVector3D<f32> _dimensions) {
	this->dimensions = _dimensions;
}
