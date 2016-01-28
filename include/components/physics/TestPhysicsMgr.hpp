#ifndef TESTPHYSICSMGR_HPP
#define TESTPHYSICSMGR_HPP

#include <vector>
#include <inttypes.h>

#include <ComponentMgr.hpp>

class TestPhysicsMgr
#ifndef _CACHE_FRIENDLY
	: public ComponentMgr
#endif
{

    public:

    TestPhysicsMgr();
	~TestPhysicsMgr();

    void setUp(void);
    void update(const uint32_t elapsed_time_ns, Entity& ent);
	void tearDown(void);
	
};

#endif //TESTPHYSICSMGR_HPP
