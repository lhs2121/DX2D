#include "PreCompile.h"
#include "MonsterSpawner.h"
#include "Monster.h"

MonsterSpawner::MonsterSpawner()
{
}

MonsterSpawner::~MonsterSpawner()
{
}

void MonsterSpawner::Start()
{
}

void MonsterSpawner::Update(float _Delta)
{
	SpawnCoolTime -= _Delta;
	if (SpawnCoolTime < 0.0f)
	{

		for (int i = 0; i < 3; i++)
		{
			std::shared_ptr<Monster> NewMonster = GetLevel()->CreateActor<Monster>(ActorOrder::Monster);
			NewMonster->Setting(CurMonsterString); 
			NewMonster->Transform.SetWorldPosition(SpawnPoint[i]);
			NewMonster->Transform.AddWorldPosition({ 0,30.0f });
		}
		
		SpawnCoolTime = ResetCoolTimeValue;
	}
}
