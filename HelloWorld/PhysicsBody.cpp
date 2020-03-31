#include "PhysicsBody.h"

unsigned int CollisionIDs::m_playerID	   = 0x1;
unsigned int CollisionIDs::m_environmentID = 0x10;
unsigned int CollisionIDs::m_enemyID       = 0x100;

unsigned int CollisionIDs::Player()
{
	return m_playerID;
}

unsigned int CollisionIDs::Environment()
{
	return m_environmentID;
}

unsigned int CollisionIDs::Enemy()
{
	return m_enemyID;
}

vec3 PhysicsBody::m_gravityAcceleration = vec3(0.f, -35.f, 0.f);

PhysicsBody::PhysicsBody(vec2 bottomLeft, vec2 topRight, vec2 centerOffset, unsigned int objectSpecifier, unsigned int collidesWith, bool isDynamic)
{

}

PhysicsBody::PhysicsBody(float width, float height, vec2 centerOffset, unsigned int objectSpecifier, unsigned int collidesWith, bool isDynamic)
{
	m_bodyType = BodyType::BOX;

	m_width = width;
	m_height = height;

	m_centerOffset = centerOffset;
	m_bottomLeft = vec2(centerOffset.x - (width / 2.f), centerOffset.y - (height / 2.f));
	m_bottomRight = vec2(centerOffset.x + (width / 2.f), centerOffset.y - (height / 2.f));
	m_topLeft = vec2(centerOffset.x - (width / 2.f), centerOffset.y + (height / 2.f));
	m_topRight = vec2(centerOffset.x + (width / 2.f), centerOffset.y + (height / 2.f));

	m_collideID = collidesWith;
	m_bodyID = objectSpecifier;

	m_dynamic = isDynamic;
}

PhysicsBody::PhysicsBody(float radius, vec2 centerOffset, unsigned int objectSpecifier, unsigned int collidesWith, bool isDynamic)
{
	m_bodyType = BodyType::CIRCLE;

	m_radius = radius;
	m_centerOffset = centerOffset;

	m_collideID = collidesWith;
	m_bodyID = objectSpecifier;

	m_dynamic = isDynamic;

}

vec3 PhysicsBody::GetForce() const
{
	return m_appliedForce;
}

vec3 PhysicsBody::GetAcceleration() const
{
	return vec3();
}

float PhysicsBody::GetMaxVelo() const
{
	return 0.0f;
}

vec3 PhysicsBody::GetVelocity() const
{
	return vec3();
}
float PhysicsBody::GetFriction() const
{
	return 0.0f;
}
vec3 PhysicsBody::GetGravityAcceleration()
{
	return vec3();
}

bool PhysicsBody::GetGravity() const
{
	return false;
}

float PhysicsBody::GetMass() const
{
	return 0.0f;
}

BodyType PhysicsBody::GetBodyType() const
{
	return BodyType();
}

vec2 PhysicsBody::GetCenterOffset() const
{
	return vec2();
}

vec2 PhysicsBody::GetBottomLeft() const
{
	return vec2();
}

vec2 PhysicsBody::GetBottomRight() const
{
	return vec2();
}

vec2 PhysicsBody::GetTopLeft() const
{
	return vec2();
}

vec2 PhysicsBody::GetTopRight() const
{
	return vec2();
}

float PhysicsBody::GetWidth() const
{
	return 0.0f;
}

float PhysicsBody::GetHeight() const
{
	return 0.0f;
}

float PhysicsBody::GetRadius() const
{
	return 0.0f;
}

unsigned int PhysicsBody::GetBodyID() const
{
	return 0;
}

unsigned int PhysicsBody::GetCollideID() const
{
	return 0;
}

bool PhysicsBody::GetDynamic() const
{
	return false;
}

void PhysicsBody::SetForce(vec3 force)
{
	m_appliedForce = force;
}

void PhysicsBody::SetAcceleration(vec3 accel)
{
}

void PhysicsBody::SetMaxVelo(float velo)
{
}

void PhysicsBody::SetVelocity(vec3 velo)
{
}

void PhysicsBody::SetFriction(float fric)
{
}

void PhysicsBody::SetGravityAcceleration(vec3 grav)
{
}

void PhysicsBody::SetGravity(bool grav)
{
}

void PhysicsBody::SetMass(float mass)
{
}

void PhysicsBody::SetBodyType(BodyType type)
{
}

void PhysicsBody::SetCenterOffset(vec2 cent)
{
}

void PhysicsBody::SetBottomLeft(vec2 BL)
{
}

void PhysicsBody::SetBottomRight(vec2 BR)
{
}

void PhysicsBody::SetTopLeft(vec2 TL)
{
}

void PhysicsBody::SetTopRight(vec2 TR)
{
}

void PhysicsBody::SetWidth(float width)
{
}

void PhysicsBody::SetHeight(float height)
{
}

void PhysicsBody::SetRadius(float radius)
{
}

void PhysicsBody::SetBodyID(unsigned int bodyID)
{
}

void PhysicsBody::SetCollideID(unsigned int collideID)
{
}

void PhysicsBody::SetDynamic(bool isDynamic)
{
}

void PhysicsBody::Update(Transform* trans, float dt)
{
	vec3 transposition = trans->GetPosition();

	if (m_velocity.GetMagnitude() > 0.f) {
	
		if (m_applyGravity) {
		
			m_frictionForce = vec3(-m_velocity.x, 0.f, 0.f) * m_friction;
		}
		else {
			m_frictionForce = -m_velocity * m_friction;
		}
	
	}
	m_netForce = m_appliedForce + m_frictionForce;
	m_acceleration = (m_netForce/m_mass);

	if (m_applyGravity) {
	
		if (m_dynamic) {
		
			m_acceleration = m_acceleration + (m_gravityAcceleration * m_mass);

		}
	}

	m_frictionForce = vec3(0.f, 0.f, 0.f);
	m_appliedForce = vec3(0.f, 0.f, 0.f);

	float tempX = m_velocity.x;
	float tempY = m_velocity.y;

	m_velocity = m_velocity + (m_acceleration * dt);

	if (abs(m_velocity.x) > abs(m_maxVelo)) {
		m_velocity.x = tempX;
	}

	if (abs(m_velocity.y) > abs(m_maxVelo)) {
		m_velocity.y= tempY;
	}

	transposition = transposition + (m_velocity * dt);

	trans->SetPosition(transposition);
}

void PhysicsBody::ApplyForce(vec3 force)
{
	m_appliedForce = m_appliedForce + force;
}
