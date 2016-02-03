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
    vmath::rotate<float>(sCmp._default._rotX,
			             sCmp._default._rotY,
		                 sCmp._default._rotZ)
	    
	*vmath::translate<float>(0, 0, WANDERER_FORWARD_STEP);

	//Update linear velocity
    pCmp._default._velocityX = next_velo[3][0];
	pCmp._default._velocityY = next_velo[3][1];
	pCmp._default._velocityZ = next_velo[3][2];

	float aimX = ai._default._targetX - sCmp._default._x;
	float aimY = ai._default._targetY - sCmp._default._y;
    float aimZ = ai._default._targetZ - sCmp._default._z;
		
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
	pCmp._default._angularVelocityX = -aimRotX;
	pCmp._default._angularVelocityY = -aimRotY;
	//pCmp._default._angularVelocityZ = -aimRotZ;

	//Apply new angular velocity to rotation proportionally to elapsed time
	sCmp._default._rotX += pCmp._default._angularVelocityX*(elapsed_time_ns/1000000000.0);
	sCmp._default._rotY += pCmp._default._angularVelocityY*(elapsed_time_ns/1000000000.0);
	sCmp._default._rotZ += pCmp._default._angularVelocityZ*(elapsed_time_ns/1000000000.0);
	if(sCmp._default._rotX < 0) sCmp._default._rotX += 360;
	if(sCmp._default._rotX >= 360.0) sCmp._default._rotX -= 360;
	if(sCmp._default._rotY < 0) sCmp._default._rotY += 360;
	if(sCmp._default._rotY >= 360.0) sCmp._default._rotY -= 360;
	if(sCmp._default._rotZ < 0) sCmp._default._rotZ += 360;
	if(sCmp._default._rotZ >= 360.0) sCmp._default._rotZ -= 360;

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
