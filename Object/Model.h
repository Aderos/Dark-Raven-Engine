#ifndef _MODEL_H_
#define _MODEL_H_

#include <vector>

#include "Math3D.h"

using Math::Vector2f;
using Math::Vector3f;

class Model
{
public:
	virtual bool Load(const char*, std::vector<Vector3f>&, std::vector<Vector2f>&, std::vector<Vector3f>&) = 0;

};

#endif