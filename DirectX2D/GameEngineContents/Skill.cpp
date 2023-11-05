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

