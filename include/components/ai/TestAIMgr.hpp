#ifndef TESTAIMGR_HPP
#define TESTAIMGR_HPP

#include <vector>
#include <inttypes.h>

#include <ComponentMgr.hpp>

class TestAIMgr: public ControlMgr

{

    public:

    TestAIMgr();
	~TestAIMgr();

    void setUp(void);
    void update(const uint32_t elapsed_time_ns, ControlComponent& ent, size_t id);
    void tearDown(void);
	
};

#endif //TESTAIMGR_HPP
