#include <components/physics/TestPhysicsMgr.hpp>
#include <ComponentReader.hpp>
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

void TestPhysicsMgr::update(const uint32_t elapsed_time_ns, SpatialComponent& sCmp, PhysicsComponent& pCmp, size_t id)
{

	const ControlComponent ai = _cmpRdr->getControlComponent(id);
	
	//Compute linear velocity based on current facing direction
	vmath::mat4 next_velo =	
    vmath::rotate<float>(sCmp._default._roll,
			             sCmp._default._pitch,
		                 sCmp._default._yaw)
	    
	*vmath::translate<float>(WANDERER_FORWARD_STEP, 0, 0);

	//Update linear velocity
    pCmp._default._velocityX = next_velo[3][0];
	pCmp._default._velocityY = next_velo[3][1];
	pCmp._default._velocityZ = next_velo[3][2];

	float aimX = ai._default._targetX - sCmp._default._x;
	float aimY = ai._default._targetY - sCmp._default._y;
    float aimZ = ai._default._targetZ - sCmp._default._z;
		
	//Compute new angles to aim for
	//float aimRoll = atan2(aimY,aimZ) - atan2(next_velo[3][1],next_velo[3][2]);
	float aimPitch = atan2(aimZ,aimX) - atan2(next_velo[3][2],next_velo[3][0]);
	float aimYaw = atan2(aimX,aimY) - atan2(next_velo[3][0],next_velo[3][1]);
    //if(aimRoll > PI) aimRoll -= 2*PI;
	//if(aimRoll < PI) aimRoll += 2*PI;
	if(aimPitch > PI) aimPitch -= 2*PI;
	if(aimPitch < PI) aimPitch += 2*PI;
	if(aimYaw > PI) aimYaw -= 2*PI;
	if(aimYaw < PI) aimYaw += 2*PI;
	//aimRoll *= (180.0 / PI);
	aimPitch *= (180.0 / PI);
	aimYaw *= (180.0 / PI);
	//if(aimRoll > 180) aimRoll = aimRoll-360;
	if(aimPitch > 180) aimPitch = aimPitch-360;
	if(aimYaw > 180) aimYaw = aimYaw-360;
	//if(aimRoll < -180) aimRoll += 360;
	if(aimPitch < -180) aimPitch += 360;
	if(aimYaw < -180) aimYaw += 360;

	//Adjust angular velocity to aim for the good direction
	//pCmp._default._angularVelocityX = -aimRoll;
	pCmp._default._angularVelocityY = -aimPitch;
	pCmp._default._angularVelocityZ = -aimYaw;

	//Apply new angular velocity to rotation proportionally to elapsed time
	sCmp._default._roll += pCmp._default._angularVelocityX*(elapsed_time_ns/1000000000.0);
	sCmp._default._pitch += pCmp._default._angularVelocityY*(elapsed_time_ns/1000000000.0);
	sCmp._default._yaw += pCmp._default._angularVelocityZ*(elapsed_time_ns/1000000000.0);
	if(sCmp._default._roll < 0) sCmp._default._roll += 360;
	if(sCmp._default._roll >= 360.0) sCmp._default._roll -= 360;
	if(sCmp._default._pitch < 0) sCmp._default._pitch += 360;
	if(sCmp._default._pitch >= 360.0) sCmp._default._pitch -= 360;
	if(sCmp._default._yaw < 0) sCmp._default._yaw += 360;
	if(sCmp._default._yaw >= 360.0) sCmp._default._yaw -= 360;

	//Compute new position using linear velocity proportionally to elapsed time
	vmath::mat4 next_pos =   
	vmath::translate<float>(sCmp._default._x,
							sCmp._default._y,
			                sCmp._default._z)
	*vmath::translate<float>(pCmp._default._velocityX*(elapsed_time_ns/1000000000.0),
							 pCmp._default._velocityY*(elapsed_time_ns/1000000000.0),
							 pCmp._default._velocityZ*(elapsed_time_ns/1000000000.0));

	//Apply new linear velocity
	sCmp._default._x = next_pos[3][0];
	sCmp._default._y = next_pos[3][1];
	sCmp._default._z = next_pos[3][2];
	
}

void TestPhysicsMgr::tearDown(){}
