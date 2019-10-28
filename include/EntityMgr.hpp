#ifndef ENTITYMGR_HPP
#define ENTITYMGR_HPP

#include <vector>
#include <Entity.hpp>
#include <ComponentMgr.hpp>
#include <cstddef>

class EntityPtr;

class VoidMgr: public ComponentMgr
{
	
    public:


    VoidMgr(){}
	  ~VoidMgr(){}
	
    inline void setUp(void){}
    inline void update(const uint32_t eapsed_time_ns, Entity& ent){}
	  inline void tearDown(void){}
	
};

class EntityMgr
{

    public:

	  static EntityMgr&
	  getInstance(ControlMgr* ctrlMgr = nullptr, PhysicsMgr* physicsMgr = nullptr, GraphicsMgr* graphicsMgr = nullptr, SoundMgr* soundMgr = nullptr) {

        static EntityMgr instance(ctrlMgr, physicsMgr, graphicsMgr, soundMgr);
        return instance;

	  }

	  std::vector<EntityPtr> create(Entity proto, size_t number=1);

    void destroy(EntityPtr& entity);

    void update(uint32_t elapsed_time_ns);

    Entity* operator [] (size_t i) {return &_entities[i];}

    private:

	  std::vector<size_t> _freeSlots;
    std::vector<Entity> _entities;

    ControlMgr* _controlMgr;
    PhysicsMgr* _physicsMgr;
    GraphicsMgr* _graphicsMgr;
    SoundMgr* _soundMgr;

	  EntityMgr(ControlMgr* ctrlMgr = nullptr,
              PhysicsMgr* physicsMgr = nullptr,
              GraphicsMgr* graphicsMgr = nullptr,
              SoundMgr* soundMgr = nullptr):
		      _controlMgr(ctrlMgr),
          _physicsMgr(physicsMgr),
          _graphicsMgr(graphicsMgr),
          _soundMgr(soundMgr) {}

	  EntityMgr(EntityMgr const&) = delete;
	  void operator = (EntityMgr const&) = delete;

	  friend class EntityPtr;
	  friend class ComponentReader;
	
};

class EntityPtr
{

    private:

    EntityMgr& _entityMgr;
	  size_t _id;

	  EntityPtr(EntityMgr& entityMgr, size_t id):_entityMgr(entityMgr), _id(id){}

    public:

	  ~EntityPtr(){}

	  EntityType getType(){ return _entityMgr[_id]->_type; }

	  friend class EntityMgr;

};

#endif //ENTITYMGR_HPP
