#include <EntityMgr.hpp>
#include <chrono>
#include <thread>
#include <components/graphics/OpenGLMgr.hpp>
#include <components/ai/TestAIMgr.hpp>
#include <components/physics/TestPhysicsMgr.hpp>

using namespace std::chrono;
using namespace std::this_thread;

int main(int argc, char* argv[])
{

	Entity proto;
	proto._physics._default={0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};

	TestAIMgr aiMgr;
	TestPhysicsMgr phyMgr;
	OpenGLMgr glMgr;

	EntityMgr& entMgr =
    EntityMgr::getInstance(&aiMgr, &phyMgr, &glMgr);

	srand(system_clock::now().time_since_epoch().count());
	
	for(int i=0; i<1000; i++)
	{
		proto._spatial._default._x = ((rand()-(RAND_MAX/2))/(float)RAND_MAX)*10;
		proto._spatial._default._y = ((rand()-(RAND_MAX/2))/(float)RAND_MAX)*10;
		proto._spatial._default._z = ((rand()-(RAND_MAX/2))/(float)RAND_MAX)*10;

		proto._spatial._default._rotX = ((rand()-(RAND_MAX/2))/(float)RAND_MAX)*180;
		proto._spatial._default._rotY = ((rand()-(RAND_MAX/2))/(float)RAND_MAX)*180;
		proto._spatial._default._rotZ = 0;

		proto._control._default._targetX = ((rand()-(RAND_MAX/2))/(float)RAND_MAX)*10;
		proto._control._default._targetY = ((rand()-(RAND_MAX/2))/(float)RAND_MAX)*10;
		proto._control._default._targetZ = ((rand()-(RAND_MAX/2))/(float)RAND_MAX)*10;
		entMgr.create(proto);
	}
	
    glMgr.setPov(entMgr[0]);
		
    nanoseconds current, last = duration_cast<nanoseconds>
                                             (system_clock::now().time_since_epoch());

	uint32_t elapsed, time_btw_frames = (1000/50)*1000000;

	while(true)
	{
		
		current = duration_cast<nanoseconds>(system_clock::now().time_since_epoch());
		elapsed = current.count()-last.count();
		
		if(elapsed > time_btw_frames)
		{
			//entMgr.update(elapsed);
			entMgr.update(elapsed);
			last = duration_cast<nanoseconds>(system_clock::now().time_since_epoch());
		}
	    else
		{
		    sleep_for(nanoseconds(time_btw_frames-elapsed));
		}
		
	}
		
	return 0;
	
}
