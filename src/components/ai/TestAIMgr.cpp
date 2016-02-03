#include <components/ai/TestAIMgr.hpp>
#include <ComponentReader.hpp>
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

void TestAIMgr::update(const uint32_t elapsed_time_ns, ControlComponent& cmp, size_t id)
{

	const SpatialComponent spatial = _cmpRdr->getSpatialComponent(id);
	
		if((spatial._default._x-cmp._default._targetX)*
		   (spatial._default._x-cmp._default._targetX)<0.25 &&
		   (spatial._default._y-cmp._default._targetY)*
		   (spatial._default._y-cmp._default._targetY)<0.25 &&
		   (spatial._default._z-cmp._default._targetZ)*
		   (spatial._default._z-cmp._default._targetZ)<0.25 )
		{
		    cmp._default._targetX = ((rand()-(RAND_MAX/2))/(float)RAND_MAX)*10;
	    	cmp._default._targetY = ((rand()-(RAND_MAX/2))/(float)RAND_MAX)*10;
		    cmp._default._targetZ = ((rand()-(RAND_MAX/2))/(float)RAND_MAX)*10;
		}
	
}

void TestAIMgr::tearDown()
{
	
}
