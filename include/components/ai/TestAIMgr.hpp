#ifndef TESTAIMGR_HPP
#define TESTAIMGR_HPP

#include <vector>
#include <inttypes.h>

#include <vmath.h>
#include <ComponentMgr.hpp>

class TestAIMgr: public ComponentMgr
{

    public:

    TestAIMgr();
	~TestAIMgr();
    virtual void update(uint16_t elapsed_time, std::vector<Entity>& entities);
	
};

#endif //TESTAIMGR_HPP
