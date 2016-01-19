#include <components/ai/TestAIMgr.hpp>
#include <chrono>
#include <stdlib.h>

#define WANDERER_FORWARD_STEP 0.01

TestAIMgr::TestAIMgr()
{

}

TestAIMgr::~TestAIMgr()
{

}
	
void TestAIMgr::update(uint16_t elapsed_time, std::vector<Entity>& entities)
{
	
	srand(std::chrono::system_clock::now().time_since_epoch().count());
	
	for(Entity& entity : entities)
	{

		entity._spatial._default._rotX += ((rand()-(RAND_MAX/2))/(float)RAND_MAX)*10;
		entity._spatial._default._rotY += ((rand()-(RAND_MAX/2))/(float)RAND_MAX)*10;
		//current orientation + random change
		
		vmath::mat4 next_pos =   
	    vmath::translate<float>(entity._spatial._default._x,
								entity._spatial._default._y,
			                    entity._spatial._default._z)
        *vmath::rotate<float>(entity._spatial._default._rotX,
			                 entity._spatial._default._rotY,
			                 entity._spatial._default._rotZ)

	    *vmath::translate<float>(0, 0, WANDERER_FORWARD_STEP);
		
		entity._spatial._default._x = next_pos[3][0];
		entity._spatial._default._y = next_pos[3][1];
		entity._spatial._default._z = next_pos[3][2];
		
	}
	
}

