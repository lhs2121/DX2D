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
		if (GetLevel()->GetObjectGroup(200).size() > MaxCount)
		{
		     SpawnCoolTime = ResetCoolTimeValue;
			 return;
		}

		for (int i = 0; i < SpawnCount; i++)
		{
			std::shared_ptr<Monster> NewMonster = GetLevel()->CreateActor<Monster>(200);
			NewMonster->Setting(CurMonsterString); 
			NewMonster->Transform.SetWorldPosition(SpawnPoint[i]);
			NewMonster->Transform.AddWorldPosition({ 0,30.0f });
		}
		
		SpawnCoolTime = ResetCoolTimeValue;
	}
}
