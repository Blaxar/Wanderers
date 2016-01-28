#include <components/physics/TestPhysicsMgr.hpp>
#include <chrono>
#include <vmath.h>

#include <math.h>

#include <iostream>

#define PI 3.14159265

#define WANDERER_FORWARD_STEP 1.0
#define WANDERER_ROT_VELO 10.0

TestPhysicsMgr::TestPhysicsMgr()
{

}

TestPhysicsMgr::~TestPhysicsMgr()
{

}

void TestPhysicsMgr::setUp(){}

void TestPhysicsMgr::update(const uint32_t elapsed_time_ns, Entity& entity)
{

	//Compute linear velocity based on current facing direction
	vmath::mat4 next_velo =	
    vmath::rotate<float>(entity._spatial._default._rotX,
			             entity._spatial._default._rotY,
		                 entity._spatial._default._rotZ)
	    
	*vmath::translate<float>(0, 0, WANDERER_FORWARD_STEP);

	//Update linear velocity
	entity._physics._default._velocityX = next_velo[3][0];
	entity._physics._default._velocityY = next_velo[3][1];
	entity._physics._default._velocityZ = next_velo[3][2];

	float aimX = entity._ai._default._targetX - entity._spatial._default._x;
	float aimY = entity._ai._default._targetY - entity._spatial._default._y;
    float aimZ = entity._ai._default._targetZ - entity._spatial._default._z;
		
	//Compute new angles to aim for
	float aimRotX = atan2(aimY,aimZ) - atan2(next_velo[3][1],next_velo[3][2]);
	float aimRotY = atan2(aimZ,aimX) - atan2(next_velo[3][2],next_velo[3][0]);
	//float aimRotZ = atan2(aimX,aimY) - atan2(next_velo[3][0],next_velo[3][1]);
    if(aimRotX > PI) aimRotX -= 2*PI;
	if(aimRotX < PI) aimRotX += 2*PI;
	if(aimRotY > PI) aimRotY -= 2*PI;
	if(aimRotY < PI) aimRotY += 2*PI;
	//if(aimRotZ > PI) aimRotZ -= 2*PI;
	//if(aimRotZ < PI) aimRotZ += 2*PI;
	aimRotX *= (180.0 / PI);
	aimRotY *= (180.0 / PI);
	//aimRotZ *= (180.0 / PI);
	if(aimRotX > 180) aimRotX = aimRotX-360;
	if(aimRotY > 180) aimRotY = aimRotY-360;
	//if(aimRotZ > 180) aimRotZ = aimRotZ-360;
	if(aimRotX < -180) aimRotX += 360;
	if(aimRotY < -180) aimRotY += 360;
	//if(aimRotZ < -180) aimRotZ += 360;

	//Adjust angular velocity to aim for the good direction
	entity._physics._default._angularVelocityX = -aimRotX;
	entity._physics._default._angularVelocityY = -aimRotY;
	//entity._physics._default._angularVelocityZ = -aimRotZ;

	//Apply new angular velocity to rotation proportionally to elapsed time
	entity._spatial._default._rotX += entity._physics._default._angularVelocityX*(elapsed_time_ns/1000000000.0);
	entity._spatial._default._rotY += entity._physics._default._angularVelocityY*(elapsed_time_ns/1000000000.0);
	entity._spatial._default._rotZ += entity._physics._default._angularVelocityZ*(elapsed_time_ns/1000000000.0);
	if(entity._spatial._default._rotX < 0) entity._spatial._default._rotX += 360;
	if(entity._spatial._default._rotX >= 360.0) entity._spatial._default._rotX -= 360;
	if(entity._spatial._default._rotY < 0) entity._spatial._default._rotY += 360;
	if(entity._spatial._default._rotY >= 360.0) entity._spatial._default._rotY -= 360;
	if(entity._spatial._default._rotZ < 0) entity._spatial._default._rotZ += 360;
	if(entity._spatial._default._rotZ >= 360.0) entity._spatial._default._rotZ -= 360;

	//Compute new position using linear velocity proportionally to elapsed time
	vmath::mat4 next_pos =   
	vmath::translate<float>(entity._spatial._default._x,
							entity._spatial._default._y,
			                entity._spatial._default._z)
	*vmath::translate<float>(entity._physics._default._velocityX*(elapsed_time_ns/1000000000.0),
							 entity._physics._default._velocityY*(elapsed_time_ns/1000000000.0),
							 entity._physics._default._velocityZ*(elapsed_time_ns/1000000000.0));

	//Apply new linear velocity
	entity._spatial._default._x = next_pos[3][0];
	entity._spatial._default._y = next_pos[3][1];
	entity._spatial._default._z = next_pos[3][2];
	
}

void TestPhysicsMgr::tearDown(){}
