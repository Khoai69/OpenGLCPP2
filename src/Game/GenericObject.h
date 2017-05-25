#pragma once
#include "../Engine/IDrawObject.h"

class IDrawObject;

class GenericObject : public IDrawObject
{
public:
	GenericObject();
	~GenericObject();
	void Draw();

private:

};

