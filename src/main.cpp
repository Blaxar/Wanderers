#include <EntityMgr.hpp>
#include <chrono>
#include <thread>
#include <components/graphics/OpenGLMgr.hpp>
#include <components/ai/TestAIMgr.hpp>

using namespace std::chrono;
using namespace std::this_thread;

int main(int argc, char* argv[])
{

	Entity proto;
	proto._spatial._default={0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
	
	EntityMgr& entMgr = EntityMgr::getInstance();
	OpenGLMgr glMgr;
	TestAIMgr aiMgr;
	
	srand(system_clock::now().time_since_epoch().count());
	
	for(int i=0; i<1000; i++)
	{
		entMgr.create(proto);
		proto._spatial._default._x = ((rand()-(RAND_MAX/2))/(float)RAND_MAX)*10;
		proto._spatial._default._y = ((rand()-(RAND_MAX/2))/(float)RAND_MAX)*10;
		proto._spatial._default._z = ((rand()-(RAND_MAX/2))/(float)RAND_MAX)*10;

		proto._spatial._default._rotX = ((rand()-(RAND_MAX/2))/(float)RAND_MAX)*180;
		proto._spatial._default._rotY = ((rand()-(RAND_MAX/2))/(float)RAND_MAX)*180;
	}
	
	entMgr.registerGraphicsMgr((ComponentMgr*) &glMgr);
	entMgr.registerAIMgr((ComponentMgr*) &aiMgr);

    std::chrono::milliseconds current, last = duration_cast< milliseconds >
                                             (system_clock::now().time_since_epoch());

	uint16_t elapsed, time_btw_frames = 1000/50;
	
	while(true)
	{
		
		current = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		elapsed = current.count()-last.count();
		
		if(elapsed > time_btw_frames)
		{
			entMgr.update(elapsed);
			last = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
		}
	    else
		{
			sleep_for(milliseconds(time_btw_frames/2));
		}
		
	}
		
	return 0;
	
}