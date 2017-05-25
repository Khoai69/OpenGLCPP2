#pragma once
#include "../Engine/IDrawObject.h"

class Skybox : public IDrawObject
{
public:
	Skybox();
	~Skybox();
	virtual void Draw();
private:

};

