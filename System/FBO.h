#ifndef _FBO_H_
#define _FBO_H_

#include "OpenGL.h"

class FBO
{
public:
	FBO(OpenGL* m_OpenGL);
	~FBO();

	void Initialize();

	void ColorBuffer();
	void DepthBuffer();

	void CheckBuffer();

	void DisableDepth();

	void Begin();
	void End();

	GLuint GetColorTexture();
	GLuint GetDepthTexture();
	
	GLuint GetTexture();

private:
	OpenGL* m_OpenGL;

private:
	GLuint gFBO;
	GLuint gRenderedTexture;
	GLuint gDepthRenderBuffer;

	GLuint gColorTexture;
	GLuint gDepthTexture;

};

#endif