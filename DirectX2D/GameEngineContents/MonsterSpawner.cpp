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
		std::shared_ptr<Monster> PrevMonster = nullptr;
		for (int i = 0; i < SpawnPoint.size(); i++)
		{
			std::shared_ptr<Monster> NewMonster = GetLevel()->CreateActor<Monster>(ActorOrder::Monster);
			NewMonster->Setting(CurMonsterString); 
			NewMonster->Transform.SetWorldPosition(SpawnPoint[i]);
			if (PrevMonster != nullptr)
			{
				NewMonster->Transform.SetWorldPosition(PrevMonster->Transform.GetWorldPosition() + float4(40.0f, 0.0f));
			}
			PrevMonster = NewMonster;
		}
		
		SpawnCoolTime = ResetCoolTimeValue;
	}
}
