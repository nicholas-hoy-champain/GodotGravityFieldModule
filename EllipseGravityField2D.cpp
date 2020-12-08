#include "EllipseGravityField2D.h"
#include <scene\2d\physics_body_2d.h>

void EllipseGravityField2D::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("setAxes", "a"), &EllipseGravityField2D::setAxes);
	ClassDB::bind_method(D_METHOD("getAxes"), &EllipseGravityField2D::getAxes);

	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "axes", PROPERTY_HINT_RANGE, "0,1024,0.001"), "setAxes", "getAxes");
}

Vector2 EllipseGravityField2D::calcForce(RigidBody2D* body)
{
	Vector2 diff = body->get_global_position() - get_global_position();
	diff = Vector2(diff.x / axes.x, diff.y / axes.y);
	diff.normalize();
	diff *= gravityScale * body->get_gravity_scale();
	return diff;
}

void EllipseGravityField2D::setAxes(Vector2 a)
{
	axes = a;
}

Vector2 EllipseGravityField2D::getAxes()
{
	return axes;
}