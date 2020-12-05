#include "DiskGravityField.h"
#include <core\engine.h>
#include <scene\3d\physics_body.h>
#include <cmath>

Vector3 DiskGravityField::calcForce(RigidBody *body) {

	Vector3 ret;

	float innerRadius = radius - thickness / 2;

	Vector3 bodyPos = body->get_translation();
	Vector2 flatDiff = Vector2(get_translation().x - bodyPos.x, get_translation().y - bodyPos.y);
	if (flatDiff.length() <= innerRadius)
	{
		ret = Vector3(0, 0, get_translation().z - bodyPos.z);
	}
	else
	{
		flatDiff.normalize();
		flatDiff *= innerRadius;
		ret = (get_translation() - Vector3(flatDiff.x, flatDiff.y, 0)) - bodyPos;
	}

	ret.normalize();
	ret *= gravityScale * body->get_gravity_scale();
	return ret;
}

void DiskGravityField::setRadius(float rad) {
	radius = rad;
}
float DiskGravityField::getRadius() {
	return radius;
}
void DiskGravityField::setThickness(float thick) {
	thickness = thick;
}
float DiskGravityField::getThickness() {
	return thickness;
}

//Bind getters and setters and add paramters as property
void DiskGravityField::_bind_methods() {
	ClassDB::bind_method(D_METHOD("setRadius", "radius"), &DiskGravityField::setRadius);
	ClassDB::bind_method(D_METHOD("getRadius"), &DiskGravityField::getRadius);
	ClassDB::bind_method(D_METHOD("setThickness", "thickness"), &DiskGravityField::setThickness);
	ClassDB::bind_method(D_METHOD("getThickness"), &DiskGravityField::getThickness);

	ADD_PROPERTY(PropertyInfo(Variant::REAL, "radius", PROPERTY_HINT_RANGE, "-1024,1024,0.001"), "setRadius", "getRadius");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "thickness", PROPERTY_HINT_RANGE, "-1024,1024,0.001"), "setThickness", "getThickness");
}
