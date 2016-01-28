#ifndef ENTITYMGR_HPP
#define ENTITYMGR_HPP

#include <vector>
#include <Entity.hpp>
#include <ComponentMgr.hpp>
#include <cstddef>

//#define _CACHE_FRIENDLY

class VoidMgr
	#ifndef _CACHE_FRIENDLY
	: public ComponentMgr
    #endif
{
	
    public:

	VoidMgr(){}
	~VoidMgr(){}
	
    inline void setUp(void){}
    inline void update(const uint32_t eapsed_time_ns, Entity& ent){}
	inline void tearDown(void){}
	
};

#ifdef _CACHE_FRIENDLY

template <class ControlMgrT, class PhysicsMgrT, class GraphicsMgrT, class SoundMgrT>
class EntityPtr;

template<class ControlMgrT, class PhysicsMgrT, class GraphicsMgrT, class SoundMgrT>
class EntityMgr
{

using TypedEntityPtr = EntityPtr<ControlMgrT, PhysicsMgrT, GraphicsMgrT, SoundMgrT>;
	
public:

	static EntityMgr<ControlMgrT, PhysicsMgrT, GraphicsMgrT, SoundMgrT>&
	getInstance(ControlMgrT& aiMgr, PhysicsMgrT& physicsMgr, GraphicsMgrT& graphicsMgr, SoundMgrT& soundMgr)
	{

		static EntityMgr<ControlMgrT, PhysicsMgrT, GraphicsMgrT, SoundMgrT> instance
			   (aiMgr, physicsMgr, graphicsMgr, soundMgr);
		return instance;
		
	}

	inline std::vector<TypedEntityPtr> create(Entity proto, size_t number=1)
    {

		std::vector<TypedEntityPtr> entities;
		size_t added_entities;

		//First, we search for available slots among already allocated ones
		for(added_entities = 0; added_entities < number && added_entities < _freeSlots.size(); added_entities++)
		{
			entities.push_back(TypedEntityPtr(*this, _entities.size()));
			_entities[_freeSlots[added_entities]] = proto;
		}

		//Then, if we still have entities left to create, we allocate space for them
		for(size_t i=added_entities; i<number; i++)
		{
			entities.push_back(TypedEntityPtr(*this, _entities.size()));
			_entities.push_back(proto);
		}
		
		return entities;
	
	}
	
	inline void destroy(TypedEntityPtr& entity)
	{

		_entities[entity._id]._type = None;
		_freeSlots.push_back(entity._id);
	
    }
	
	inline void update(uint32_t elapsed_time_ns)
	{

		_controlMgr.setUp();
		for(Entity& ent: _entities) _controlMgr.update(elapsed_time_ns, ent);
		_controlMgr.tearDown();

		_physicsMgr.setUp();
		for(Entity& ent: _entities) _physicsMgr.update(elapsed_time_ns, ent);
		_physicsMgr.tearDown();

		_graphicsMgr.setUp();
		for(Entity& ent: _entities) _graphicsMgr.update(elapsed_time_ns, ent);
		_graphicsMgr.tearDown();

		_soundMgr.setUp();
		for(Entity& ent: _entities) _soundMgr.update(elapsed_time_ns, ent);
		_soundMgr.tearDown();
	
	}
	
    Entity* operator [] (size_t i) {return &_entities[i];}

private:
	
	std::vector<size_t> _freeSlots;
	std::vector<Entity> _entities;
	
    ControlMgrT& _controlMgr;
	PhysicsMgrT& _physicsMgr;
    GraphicsMgrT& _graphicsMgr;
    SoundMgrT& _soundMgr;

	EntityMgr(ControlMgrT& aiMgr, PhysicsMgrT& physicsMgr, GraphicsMgrT& graphicsMgr, SoundMgrT& soundMgr):
		      _controlMgr(aiMgr), _physicsMgr(physicsMgr), _graphicsMgr(graphicsMgr), _soundMgr(soundMgr){}
	
	EntityMgr(EntityMgr const&) = delete;
	void operator = (EntityMgr const&) = delete;

	friend TypedEntityPtr;
	
};

template<class ControlMgrT, class PhysicsMgrT, class GraphicsMgrT, class SoundMgrT>
class EntityPtr
{

	using TypedEntityMgr = EntityMgr<ControlMgrT, PhysicsMgrT, GraphicsMgrT, SoundMgrT>;
	
    private:

    TypedEntityMgr& _entityMgr;
	size_t _id;
	
	EntityPtr(TypedEntityMgr& entityMgr, size_t id):_entityMgr(entityMgr), _id(id){}

    public:

	~EntityPtr(){}

	inline EntityType getType(){ return _entityMgr[_id]->_type; }

	friend TypedEntityMgr;
	
};

#else //_CACHE_FRIENDLY

class EntityPtr;

class EntityMgr
{
	
public:

	static EntityMgr&
	getInstance(ComponentMgr* aiMgr, ComponentMgr* physicsMgr, ComponentMgr* graphicsMgr, ComponentMgr* soundMgr)
	{

		static EntityMgr instance(aiMgr, physicsMgr, graphicsMgr, soundMgr);
		return instance;
		
	}

	std::vector<EntityPtr> create(Entity proto, size_t number=1);
	
	void destroy(EntityPtr& entity);
	
	void update(uint32_t elapsed_time_ns);
	
    Entity* operator [] (size_t i) {return &_entities[i];}

private:
	
	std::vector<size_t> _freeSlots;
	std::vector<Entity> _entities;
	
    ComponentMgr* _controlMgr;
    ComponentMgr* _physicsMgr;
    ComponentMgr* _graphicsMgr;
    ComponentMgr* _soundMgr;

	EntityMgr(ComponentMgr* aiMgr, ComponentMgr* physicsMgr, ComponentMgr* graphicsMgr, ComponentMgr* soundMgr):
		      _controlMgr(aiMgr), _physicsMgr(physicsMgr), _graphicsMgr(graphicsMgr), _soundMgr(soundMgr){}
	
	EntityMgr(EntityMgr const&) = delete;
	void operator = (EntityMgr const&) = delete;

	friend class EntityPtr;
	
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

#endif //_CACHE_FRIENDLY

#endif //ENTITYMGR_HPP
