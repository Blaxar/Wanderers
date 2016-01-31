#ifndef TESTPHYSICSMGR_HPP
#define TESTPHYSICSMGR_HPP

#include <vector>
#include <inttypes.h>

#include <ComponentMgr.hpp>

class TestPhysicsMgr: public PhysicsMgr

{

    public:

    TestPhysicsMgr();
	~TestPhysicsMgr();

    void setUp(void);
    void update(const uint32_t elapsed_time_ns, SpatialComponent& sCmp, PhysicsComponent& pCmp, size_t id);
	void tearDown(void);
	
};

#endif //TESTPHYSICSMGR_HPP
