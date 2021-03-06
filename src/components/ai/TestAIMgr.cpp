#include <components/ai/TestAIMgr.hpp>
#include <chrono>
#include <stdlib.h>

TestAIMgr::TestAIMgr()
{

}

TestAIMgr::~TestAIMgr()
{

}

void TestAIMgr::setUp()
{

    srand(std::chrono::system_clock::now().time_since_epoch().count());
	
}

void TestAIMgr::update(const uint32_t elapsed_time_ns, Entity& entity)
{

		if((entity._spatial._default._x-entity._ai._default._targetX)*
		   (entity._spatial._default._x-entity._ai._default._targetX)<0.25 &&
		   (entity._spatial._default._y-entity._ai._default._targetY)*
		   (entity._spatial._default._y-entity._ai._default._targetY)<0.25 &&
		   (entity._spatial._default._z-entity._ai._default._targetZ)*
		   (entity._spatial._default._z-entity._ai._default._targetZ)<0.25 )
		{
		    entity._ai._default._targetX = ((rand()-(RAND_MAX/2))/(float)RAND_MAX)*10;
	    	entity._ai._default._targetY = ((rand()-(RAND_MAX/2))/(float)RAND_MAX)*10;
		    entity._ai._default._targetZ = ((rand()-(RAND_MAX/2))/(float)RAND_MAX)*10;
		}
	
}

void TestAIMgr::tearDown()
{
	
}
