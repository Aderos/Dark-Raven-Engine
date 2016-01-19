#include "FBO.h"

FBO::FBO(OpenGL* m_OpenGL)
{
	this->m_OpenGL = m_OpenGL;
	this->gFBO = 0;
	this->gRenderedTexture = 0;
	this->gDepthRenderBuffer = 0;
}

FBO::~FBO()
{
}

void FBO::Initialize()
{
	m_OpenGL->glGenFramebuffers(1, &gFBO);
	m_OpenGL->glBindFramebuffer(GL_FRAMEBUFFER, gFBO);
}

void FBO::ColorBuffer()
{
	glGenTextures(1, &gColorTexture);
	glBindTexture(GL_TEXTURE_2D, gColorTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_OpenGL->GetScreenWidth(), m_OpenGL->GetScreenHeight(), 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	m_OpenGL->glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, gColorTexture, 0);

	m_OpenGL->glDrawBuffers(1, new GLenum { GL_COLOR_ATTACHMENT0 });
}

void FBO::DepthBuffer()
{
	glGenTextures(1, &gDepthTexture);
	glBindTexture(GL_TEXTURE_2D, gDepthTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, m_OpenGL->GetScreenWidth(), m_OpenGL->GetScreenHeight(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	m_OpenGL->glGenRenderbuffers(1, &gDepthRenderBuffer);
	m_OpenGL->glBindRenderbuffer(GL_RENDERBUFFER, gDepthRenderBuffer);
	m_OpenGL->glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_OpenGL->GetScreenWidth(), m_OpenGL->GetScreenHeight());
	m_OpenGL->glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, gDepthRenderBuffer);

	m_OpenGL->glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, gDepthTexture, 0);

	m_OpenGL->glDrawBuffers(1, new GLenum{ GL_COLOR_ATTACHMENT0 });
}

void FBO::CheckBuffer()
{
	GLenum Status = m_OpenGL->glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (Status != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("FB error, status: 0x%x\n", Status);
	}
}

GLuint FBO::GetTexture()
{
	return this->gRenderedTexture;
}

GLuint FBO::GetColorTexture()
{
	return this->gColorTexture;
}

GLuint FBO::GetDepthTexture()
{
	return this->gDepthTexture;
}

void FBO::Begin()
{
	m_OpenGL->glBindFramebuffer(GL_FRAMEBUFFER, gFBO);
	glViewport(0, 0, m_OpenGL->GetScreenWidth(), m_OpenGL->GetScreenHeight());
}

void FBO::End()
{
	m_OpenGL->glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, m_OpenGL->GetScreenWidth(), m_OpenGL->GetScreenHeight());
}