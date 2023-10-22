#include "PreCompile.h"
#include "Monster.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::Start()
{
	MonsterBase::Start();
	Setting("Octopus");
	{
		Transform.SetWorldPosition({ 800,300 });
	}
}
void Monster::Update(float _Delta)
{
	PhysicsActor::Update(_Delta);
	MonsterBase::Update(_Delta);
}
