#ifndef TESTPHYSICSMGR_HPP
#define TESTPHYSICSMGR_HPP

#include <vector>
#include <inttypes.h>

#include <ComponentMgr.hpp>

class TestPhysicsMgr: public ComponentMgr
{

    public:

    TestPhysicsMgr();
	~TestPhysicsMgr();
    virtual void update(uint16_t elapsed_time, std::vector<Entity>& entities);
	
};

#endif //TESTPHYSICSMGR_HPP
