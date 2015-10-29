#include "PhysicsComponent.h"
using namespace misc;

void PhysicsComponent::init()
{
	_bDef.type = b2_dynamicBody;
	_bDef.position.Set(_position.x, _position.y);
	_shape.SetAsBox(_size.x, _size.y);

	_body = core::Siika2D::UI()->_boxWorld->CreateBody(&_bDef);
	//_world->CreateBody();
	_fixtureDef.shape = &_shape;
	_fixtureDef.density = _density;
	_fixtureDef.friction = _friction;
	_fixtureDef.restitution = _restitution;
	_body->CreateFixture(&_fixtureDef);
};

void PhysicsComponent::applyForce(glm::vec2 _force, bool wake)
{
	b2Vec2 force = b2Vec2(_force.x, _force.y);
	_body->ApplyForce(force, _body->GetWorldCenter(), wake);
}

void PhysicsComponent::applyForce(glm::vec2 _force, glm::vec2 _point, bool wake)
{
	b2Vec2 force = b2Vec2(_force.x, _force.y);
	b2Vec2 point = b2Vec2(_point.x, _point.y);
	_body->ApplyForce(force, _body->GetWorldPoint(point), wake);
}

void PhysicsComponent::applyLinearForce(glm::vec2 _force, bool wake)
{
	b2Vec2 force = b2Vec2(_force.x, _force.y);
	_body->ApplyLinearImpulse(force, _body->GetWorldCenter(), wake);
}

void PhysicsComponent::applyLinearForce(glm::vec2 _force, glm::vec2 _point, bool wake)
{
	b2Vec2 force = b2Vec2(_force.x, _force.y);
	b2Vec2 point = b2Vec2(_point.x, _point.y);
	_body->ApplyLinearImpulse(force, _body->GetWorldPoint(point), wake);
}

void PhysicsComponent::applyTorgue(float32 torgue, bool wake)
{
	_body->ApplyTorque(torgue, wake);
}

void PhysicsComponent::applyAngularTorgue(float32 torgue, bool wake)
{
	_body->ApplyAngularImpulse(torgue, wake);
}

void PhysicsComponent::setGravityScale(float32 _scale)
{
	_body->SetGravityScale(_scale);
}