#ifndef TESTAIMGR_HPP
#define TESTAIMGR_HPP

#include <vector>
#include <inttypes.h>

#include <ComponentMgr.hpp>

class TestAIMgr
#ifndef _CACHE_FRIENDLY
	: public ComponentMgr
#endif
{

    public:

    TestAIMgr();
	~TestAIMgr();

    void setUp(void);
    void update(const uint32_t elapsed_time_ns, Entity& ent);
    void tearDown(void);
	
};

#endif //TESTAIMGR_HPP
