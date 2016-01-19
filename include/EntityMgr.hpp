#ifndef ENTITYMGR_HPP
#define ENTITYMGR_HPP

#include <vector>
#include <Entity.hpp>
#include <ComponentMgr.hpp>
#include <cstddef>

class EntityPtr;

class EntityMgr
{

public:

	static EntityMgr& getInstance()
	{

		static EntityMgr instance;
		return instance;
		
	}

	std::vector<EntityPtr> create(Entity proto, size_t number=1);
	void destroy(EntityPtr& entity);
	void update(uint32_t elapsed);

	void registerPhysicsMgr(ComponentMgr* component){_physicsMgr = component;}
	void registerGraphicsMgr(ComponentMgr* component){_graphicsMgr = component;}
	void registerSoundMgr(ComponentMgr* component){_soundMgr = component;}
    void registerAIMgr(ComponentMgr* component){_aiMgr = component;}

    Entity* operator [] (size_t i) {return &_entities[i];}

private:

	std::vector<size_t> _freeSlots;
	std::vector<Entity> _entities;

	ComponentMgr* _physicsMgr;
	ComponentMgr* _graphicsMgr;
	ComponentMgr* _soundMgr;
	ComponentMgr* _aiMgr;

	EntityMgr():_physicsMgr(NULL),_graphicsMgr(NULL),_soundMgr(NULL),_aiMgr(NULL){}
	
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

#endif //ENTITYMGR_HPP
