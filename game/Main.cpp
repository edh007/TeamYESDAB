#include "GentleIdiots.h"
#include <memory>

gi::Engine* g_pEngine = new gi::Engine;

class FiniteTimeBehavior : public gi::Behavior
{
public:
	FiniteTimeBehavior(gi::Entity* pOwner) : gi::Behavior(pOwner), m_duration(5.f), m_timer(0.f) {}
	~FiniteTimeBehavior(){}

	void SetDuration(float duration) { m_duration = duration; }
	float GetDuration() const { return m_duration; }

	virtual void Run(float dt)
	{
		m_timer += dt;

		//std::cout << "Update Finite Time Behavior\n";
		if(m_timer >= m_duration)
		{
			std::cout << "End Finite Time Behavior\n";
			m_active = false;
		}
	}

private:
	float m_duration;
	float m_timer;

	void HangAround(float dt)
	{
		auto pTransform = m_pOwner->GetComponentContainer().GetComponent<gi::ComponentTransform>();

		Vec3 rot = pTransform->GetRotationVec();


	}

};


class SampleScene : public gi::Scene
{
public:
	SampleScene(){}
	~SampleScene() override{}
	void Load() override{}
	void Init() override{}
	void Update(float) override{}
	void Shutdown() override{}
	void Unload() override{}
};
class TestObject : public gi::Entity
{
public:
	TestObject(const std::string& name):gi::Entity(nullptr, name){}
	~TestObject() override{}

};

int main(int argc, char *argv[])
{
	argc; argv;

	// TODO(JIN) : Test Code////////////////////////////////////////
	//SampleScene* pScene = new SampleScene;
	//TestObject* pObj = new TestObject("Test");

	/*gi::ComponentTransform* pTransform = gi::ComponentTransform::CreateComponentTransform(pObj);

	pObj->GetComponentContainer().AddComponent(pTransform, gi::ComponentTransform::COMPONENT_ID);

	gi::ComponentTransform* pTestComponent = 
	pObj->GetComponentContainer().GetComponent<gi::ComponentTransform>();

	pTestComponent->GetPositionVec();*/
	/////////////////////////////////////////////////////////


	g_pEngine->Initialize();

	g_pEngine->GetSpace()->AddEntity(new TestObject("Test"));
	TestObject* pObj = dynamic_cast<TestObject*>(g_pEngine->GetSpace()->FindEntity("Test"));
	pObj->GetComponentContainer().AddComponent(gi::ComponentTransform::CreateComponentTransform(pObj), gi::ComponentTransform::COMPONENT_ID);
	
	gi::ComponentTransform* pTestComponent = pObj->GetComponentContainer().GetComponent<gi::ComponentTransform>();
	pTestComponent->GetPositionVec();

	pObj->GetBehaviorContainer().AddBehavior(new FiniteTimeBehavior(pObj), true);
	


	/*gi::FiniteTimeBehavior* test = new gi::FiniteTimeBehavior();

	gi::Behavior* pBehavior = dynamic_cast<gi::Behavior*>(test);
	
	pBehavior->Run(0);

	pBehavior = nullptr;

	delete test;*/

	g_pEngine->Run();

	delete g_pEngine;
	g_pEngine = nullptr;

	// TODO(JIN) : Test Code////////////////////////////////////////

	//pObj->GetComponentContainer().RemoveComponent(gi::ComponentTransform::COMPONENT_ID);
	//pTestComponent = nullptr;
	//delete pScene;
	//pScene = nullptr;
	//delete pObj;
	//pObj = nullptr;
	/////////////////////////////////////////////////////////

	return 0;
}