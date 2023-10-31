#include "PreCompile.h"
#include "Skill.h"
#include "Player.h"

Skill::Skill()
{
}

Skill::~Skill()
{
}

void Skill::FlipX(float _dir, std::shared_ptr<class GameEngineSpriteRenderer> _Renderer)
{
	if (_dir == 1)
	{
		_Renderer->Transform.SetLocalScale({ -1,1 });
	}
	else if (_dir == -1)
	{
		_Renderer->Transform.SetLocalScale({ 1,1 });
	}
}

void Skill::Start()
{
	SkillId = GameEngineRandom::GameEngineRandom().RandomInt(0, 99999999);
}

void Skill::Update(float _Delta)
{
	
}
