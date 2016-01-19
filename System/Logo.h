#ifndef _LOGO_H_
#define _LOGO_H_

#include "ShaderManager.h"
#include "Object2D.h"
#include "OpenGL.h"

class Logo
{
public:
	Logo(OpenGL* m_OpenGL, ShaderManager* m_Shader);
	~Logo();

	void Initialize(int, int, int, int, const char*);

	void Reshape(int, int);
	void Draw();
	
	void Shutdown();

private:
	Object2D* m_Obj2D;
	OpenGL* m_OpenGL;

};

#endif