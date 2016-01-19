#ifndef _MODELOBJ_H_
#define _MODELOBJ_H_

#include <vector>

#include "Math3D.h"
#include "Model.h"

using Math::Vector2f;
using Math::Vector3f;

class ModelOBJ : Model
{
public:
	ModelOBJ();
	~ModelOBJ();

	bool Load(const char*, std::vector<Vector3f>&, std::vector<Vector2f>&, std::vector<Vector3f>&);

};

#endif