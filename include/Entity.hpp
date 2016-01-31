#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <inttypes.h>

enum EntityType
{

	None = 0,
	Wanderer
	
};

struct VoidComponent{};

//Spatial Components

union SpatialComponent
{

struct DefaultSpatialComponent
{

double _x;
double _y;
double _z;

float _rotX;
float _rotY;
float _rotZ;	
	
} _default;

struct VoidComponent _void;

};
	
//Physics Components

union PhysicsComponent
{

struct DefaultPhysicsComponent{

	float _weight;
	
	float _velocityX;
	float _velocityY;
	float _velocityZ;
	
	float _angularVelocityX;
	float _angularVelocityY;
	float _angularVelocityZ;
	
} _default;

struct VoidComponent _void;
	
};

//Graphics Components

union GraphicsComponent
{

struct DefaultGraphicsComponent{} _default;
struct VoidComponent _void;

};

//Sound Components

union SoundComponent
{

struct DefaultSoundComponent{} _default;
struct VoidComponent _void;

};

//AI Components

union ControlComponent
{

struct DefaultControlComponent{

	double _targetX;
	double _targetY;
	double _targetZ;

} _default;
struct VoidComponent _void;

};

//Entity

struct Entity
{

	EntityType _type;
	SpatialComponent _spatial;
	PhysicsComponent _physics;
	GraphicsComponent _graphics;
    SoundComponent _sound;
    ControlComponent _control;
	
};

#endif //ENTITY_HPP
