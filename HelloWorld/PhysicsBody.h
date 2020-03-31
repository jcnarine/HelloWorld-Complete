#pragma once

#include "JSON.h"
#include "Vector.h"
#include "EntityIdentifier.h"
#include "Transform.h"

enum class BodyType
{
	BOX,
	CIRCLE,

	NUM_TYPES
};
class PhysicsBody
{
public:
	PhysicsBody() {};

	PhysicsBody(vec2 bottomLeft, vec2 topRight, vec2 centerOffset, unsigned int objectSpecifier, unsigned int collidesWith, bool isDynamic = false);
	PhysicsBody(float width, float height, vec2 centerOffset, unsigned int objectSpecifier, unsigned int collidesWith, bool isDynamic = false);
	PhysicsBody(float radius, vec2 centerOffset, unsigned int objectSpecifier, unsigned int collidesWith, bool isDynamic = false);
	/*
		SETTERS
	*/
	vec3 GetForce() const;
	vec3 GetAcceleration() const;

	float GetMaxVelo() const;
	vec3 GetVelocity() const;
	float GetFriction() const;

	static vec3 GetGravityAcceleration();

	bool GetGravity() const;

	float GetMass() const;

	BodyType GetBodyType() const;

	vec2 GetCenterOffset() const;

	vec2 GetBottomLeft() const;
	vec2 GetBottomRight() const;
	vec2 GetTopLeft() const;
	vec2 GetTopRight() const;

	float GetWidth() const;

	float GetHeight() const;

	float GetRadius() const;

	unsigned int GetBodyID() const;

	unsigned int GetCollideID() const;

	bool GetDynamic() const;

	/*
		SETTERS
	*/

	void SetForce(vec3 force);
	void SetAcceleration(vec3 accel);
	void SetMaxVelo(float velo);
	void SetVelocity(vec3 velo);

	void SetFriction(float fric);
	static void SetGravityAcceleration(vec3 grav);
	void SetGravity(bool grav);
	void SetMass(float mass);

	void SetBodyType(BodyType type);

	void SetCenterOffset(vec2 cent);

	void SetBottomLeft(vec2 BL);
	void SetBottomRight(vec2 BR);
	void SetTopLeft(vec2 TL);
	void SetTopRight(vec2 TR);

	void SetWidth(float width);
	void SetHeight(float height);
	void SetRadius(float radius);

	void SetBodyID(unsigned int bodyID);

	void SetCollideID(unsigned int collideID);

	void SetDynamic(bool isDynamic);

	void Update(Transform* trans, float dt);

	void ApplyForce(vec3 force);

private:

	vec3 m_appliedForce = vec3(0.f, 0.f, 0.f);

	vec3 m_frictionForce = vec3(0.f, 0.f, 0.f);

	vec3 m_netForce = vec3(0.f, 0.f, 0.f);

	vec3 m_acceleration = vec3(0.f, 0.f, 0.f);

	float m_maxVelo = 20.f;

	vec3 m_velocity = vec3(0.f, 0.f, 0.f);

	float m_friction = 0.35f;

	static vec3 m_gravityAcceleration;

	bool m_applyGravity = false;

	float m_mass = 1.f;

	BodyType m_bodyType = BodyType::CIRCLE;

	//how far from the center of the sprite is it
	vec2 m_centerOffset = vec2();

	//each corner
	vec2 m_bottomLeft = vec2();
	vec2 m_bottomRight = vec2();
	vec2 m_topLeft = vec2();
	vec2 m_topRight = vec2();
	//Width and height of the body
	float m_width = 0.f;
	float m_height = 0.f;

	float m_radius = 0.f;

	unsigned int m_bodyID;

	unsigned int m_collideID;

	bool m_dynamic = false;
};

class CollisionIDs 
{
	public:
		//Get the different IDs
		static unsigned int Player();
		static unsigned int Environment();
		static unsigned int Enemy();
	private:
		//Holds the different IDs
		static unsigned int m_playerID;
		static unsigned int m_environmentID;
		static unsigned int m_enemyID;
};

//Sends body TO json file
inline void to_json(nlohmann::json& j, const PhysicsBody& phys)
{
	//stores the bodytype
	j["BodyType"] = phys.GetBodyType();
	//Center offset
	j["CenterOffset"] = { phys.GetCenterOffset().x, phys.GetCenterOffset().y };
	//Stores corners
	j["BottomLeft"] = { phys.GetBottomLeft().x, phys.GetBottomLeft().y };
	j["BottomRight"] = { phys.GetBottomRight().x, phys.GetBottomRight().y };
	j["TopLeft"] = { phys.GetTopLeft().x, phys.GetTopLeft().y };
	j["TopRight"] = { phys.GetTopRight().x, phys.GetTopRight().y };
	//width and height 
	j["Width"] = phys.GetWidth();
	j["Height"] = phys.GetHeight();
	//Radius
	j["Radius"] = phys.GetRadius();

	//Max velocity
	j["MaxVelo"] = phys.GetMaxVelo();

	//Friction strength
	j["Friction"] = phys.GetFriction();

	//Gravity enabled?
	j["Gravity"] = phys.GetGravity();

	//Collision type (body ID) and what this body collides *with*
	j["BodyID"] = phys.GetBodyID();
	j["CollideID"] = phys.GetCollideID();

	//Wheter the object is moving 
	j["IsDynamic"] = phys.GetDynamic();
}

//Reads body in FROM json file
inline void from_json(const nlohmann::json& j, PhysicsBody& phys)
{
	//Sets body type
	phys.SetBodyType(j["BodyType"]);
	//Set the center offset
	phys.SetCenterOffset(vec2(j["CenterOffset"][0], j["CenterOffset"][1]));
	//Sets the corners
	phys.SetBottomLeft(vec2(j["BottomLeft"][0], j["BottomLeft"][1]));
	phys.SetBottomRight(vec2(j["BottomRight"][0], j["BottomRight"][1]));
	phys.SetTopLeft(vec2(j["TopLeft"][0], j["TopLeft"][1]));
	phys.SetTopRight(vec2(j["TopRight"][0], j["TopLeft"][1]));
	//Set the width and height 
	phys.SetRadius(j["Radius"]);

	//Sets Max velocity
	phys.SetMaxVelo(j["MaxVelo"]);

	//Sets friction strenght 
	phys.SetFriction(j["Friction"]);

	//Set does gravity affect this body?
	phys.SetGravity(j["Gravity"]);

	//Set collision type (body ID) and what this body collides *with*
	phys.SetBodyID(j["BodyID"]);
	phys.SetCollideID(j["CollideID"]);

	//Set wheter the object is moving 
	phys.SetDynamic(j["IsDynamic"]);
}