#include "OpenGL.h"

OpenGL::OpenGL()
{
}

OpenGL::~OpenGL()
{
}

bool OpenGL::Initialize(int screenWidth, int screenHeight, float screenDepth, float screenNear, bool vsync)
{
	LoadExtensionList();
	glClearDepth(1.0f);

	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

void OpenGL::ExitGame(unsigned char key)
{
	if (key == 27)
		exit(0);
}

float OpenGL::GetScreenWidth()
{
	return (float)SCREEN_WIDTH;
}

float OpenGL::GetScreenHeight()
{
	return (float)SCREEN_HEIGHT;
}

float OpenGL::GetScreenDepth()
{
	return (float)SCREEN_DEPTH;
}

float OpenGL::GetScreenNear()
{
	return (float)SCREEN_NEAR;
}

GLenum OpenGL::GetTextureCubeMapPosX()
{
	return GL_TEXTURE_CUBE_MAP_POSITIVE_X;
}

GLenum OpenGL::GetTextureCubeMapNegX()
{
	return GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
}

GLenum OpenGL::GetTextureCubeMapPosY()
{
	return GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
}

GLenum OpenGL::GetTextureCubeMapNegY()
{
	return GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
}

GLenum OpenGL::GetTextureCubeMapPosZ()
{
	return GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
}

GLenum OpenGL::GetTextureCubeMapNegZ()
{
	return GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
}

GLenum OpenGL::GetBGR()
{
	return GL_BGR;
}

GLenum OpenGL::GetBGRA()
{
	return GL_BGRA;
}

GLenum OpenGL::GetRGB()
{
	return GL_RGB;
}

GLenum OpenGL::GetRGBA()
{
	return GL_RGBA;
}

GLenum OpenGL::GetLuminance()
{
	return GL_LUMINANCE;
}

GLuint OpenGL::GetUnsignedByte()
{
	return GL_UNSIGNED_BYTE;
}

void OpenGL::DrawTriangles(int From, int To)
{
	glDrawArrays(GL_TRIANGLES, From, To);
}

void OpenGL::DrawTrianglesStrip(int From, int To)
{
	glDrawArrays(GL_TRIANGLE_STRIP, From, To);
}

void OpenGL::DrawLines(int From, int To)
{
	glDrawArrays(GL_LINES, From, To);
}

void OpenGL::DrawPoints(int From, int To)
{
	glDrawArrays(GL_POINTS, From, To);
}

void OpenGL::DrawTess(int numberVertices, int From, int To)
{
	glPatchParameteri(GL_PATCH_VERTICES, numberVertices);
	glDrawArrays(GL_PATCHES, From, To);
}

void OpenGL::GenVertexArrays(GLuint* VertexArray)
{
	glGenVertexArrays(1, &*VertexArray);
}

void OpenGL::BindVertexArray(GLuint *VertexArray)
{
	glBindVertexArray(*VertexArray);
}

void OpenGL::ReleaseVertexArray(GLuint *VertexArray)
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &*VertexArray);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &*VertexArray);
}

void OpenGL::DisableVertexAttribArray(GLuint index)
{
	glDisableVertexAttribArray(index);
}

void OpenGL::BindBufferData(GLuint Buffer, GLuint Size, GLsizei Stride, GLvoid* Data, GLint Index, GLint Count)
{
	glGenBuffers(1, &Buffer);
	glBindBuffer(GL_ARRAY_BUFFER, Buffer);
	glBufferData(GL_ARRAY_BUFFER, Size * Stride, Data, GL_STATIC_DRAW);
	glEnableVertexAttribArray(Index);
	glVertexAttribPointer(Index, Count, GL_FLOAT, false, Stride, 0);
}

void OpenGL::BindTexture1D(GLuint& TextureID, GLuint width, GLubyte* Data)
{
	GLenum target = GL_TEXTURE_1D;

	glGenTextures(1, &TextureID);
	glBindTexture(target, TextureID);
	glTexImage1D(target, 0, GL_RGB, width, 0, GL_RGB, GL_UNSIGNED_BYTE, Data);
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
}

void OpenGL::BindTexture2D(GLuint& TextureID, GLuint level, GLuint internalFormat, GLuint width, GLuint height, GLuint border, GLuint format, GLuint type, unsigned char* data)
{
	GLenum target = GL_TEXTURE_2D;

	glGenTextures(1, &TextureID);
	glBindTexture(target, TextureID);
	glTexImage2D(target, level, internalFormat, width, height, border, format, type, data);

	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glGenerateMipmap(target);
}

void OpenGL::BindTextureCubeMap(GLuint& TextureID)
{
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, TextureID);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void OpenGL::BindPartTextureCubeMap(GLenum target, GLuint level, GLuint internalFormat, GLuint width, GLuint height, GLuint border, GLuint format, GLuint type, unsigned char* data)
{
	glTexImage2D(target, level, internalFormat, width, height, border, format, type, data);
}

void OpenGL::BindActiveTexture2D(GLuint TextureID)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureID);
}

void OpenGL::BindActiveShadowTexture2D(GLuint TextureID)
{
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TextureID);
}

void OpenGL::BindActiveNormalTexture2D(GLuint TextureID)
{
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TextureID);
}

void OpenGL::BindActiveHeightTexture2D(GLuint TextureID)
{
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, TextureID);
}

void OpenGL::BindActiveCubeMap(GLuint TextureID)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, TextureID);
}

void OpenGL::ReleaseTexture(GLuint &TextureID)
{
	glDeleteTextures(1, &TextureID);
}

void OpenGL::EnableWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void OpenGL::DisableWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void OpenGL::EnableBlend()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGL::DisableBlend()
{
	glDisable(GL_BLEND);
}

void OpenGL::EnableDepth()
{
	glEnable(GL_DEPTH_TEST);
}

void OpenGL::DisableDepth()
{
	glDisable(GL_DEPTH_TEST);
}

GLenum OpenGL::GetVertexShader()
{
	return GL_VERTEX_SHADER;
}

GLenum OpenGL::GetFragmentShader()
{
	return GL_FRAGMENT_SHADER;
}

GLenum OpenGL::GetGeometryShader()
{
	return GL_GEOMETRY_SHADER;
}

GLenum OpenGL::GetTessControlShader()
{
	return GL_TESS_CONTROL_SHADER;
}

GLenum OpenGL::GetTessEvaluationShader()
{
	return GL_TESS_EVALUATION_SHADER;
}

GLenum OpenGL::GetComputeShader()
{
	return GL_COMPUTE_SHADER;
}

void OpenGL::UseProgram(int index)
{
	glUseProgram(index);
}

void OpenGL::DeleteShaders(GLuint program, std::vector<GLuint> listShader)
{
	for (unsigned int i = 0; i < listShader.size(); i++)
	{
		glDetachShader(program, listShader[i]);
		glDeleteShader(listShader[i]);
	}
}

void OpenGL::DeleteProgram(GLuint program)
{
	glDeleteProgram(program);
}

void OpenGL::CreateShader(GLuint& shader, GLenum shaderType, const char* buffer)
{
	shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &buffer, NULL);
}

bool OpenGL::CompileShader(GLuint shader)
{
	int status;

	glCompileShader(shader);
	// Check to see if the  shader compiled successfully.
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != 1)
		return false;

	return true;
}

void OpenGL::AttachShaders(GLuint program, std::vector<GLuint> listShader)
{
	for (unsigned int i = 0; i < listShader.size(); glAttachShader(program, listShader[i++]));
}

char* OpenGL::GetProgramInfoLog(GLuint programId)
{
	int logSize;

	// Get the size of the string containing the information log for the failed shader compilation message.
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logSize);

	// Increment the size by one to handle also the null terminator.
	logSize++;

	char* info = new char[logSize];

	// Now retrieve the info log.
	glGetProgramInfoLog(programId, logSize, NULL, info);

	return info;
}

char* OpenGL::GetShaderInfoLog(GLuint shaderId)
{
	int logSize;

	// Get the size of the string containing the information log for the failed shader compilation message.
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logSize);

	// Increment the size by one to handle also the null terminator.
	logSize++;

	char* infoLog = new char[logSize];
	glGetShaderInfoLog(shaderId, logSize, NULL, infoLog);

	return infoLog;
}

void OpenGL::BlendEquation(GLenum mode)
{
	this->glBlendEquation(mode);
}

bool OpenGL::LinkProgram(GLuint program)
{
	int status;

	// Link the shader program.
	glLinkProgram(program);

	// Check the status of the link.
	glGetProgramiv(program, GL_LINK_STATUS, &status);

	if (status != 1)
		return false;

	return true;
}

void OpenGL::CreateProgram(GLuint& program)
{
	program = glCreateProgram();
}

void OpenGL::BeginScene(float red, float green, float blue, float alpha)
{
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	return;
}

void OpenGL::SetUniformMatrix4f(GLuint theProgram, const char* name, const float* matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(theProgram, name), 1, false, matrix);
}

void OpenGL::SetUniformVector4f(GLuint theProgram, const char* name, const float* vector)
{
	glUniform4fv(glGetUniformLocation(theProgram, name), 1, vector);
}

void OpenGL::SetUniformVector3f(GLuint theProgram, const char* name, const float* vector)
{
	glUniform3fv(glGetUniformLocation(theProgram, name), 1, vector);
}

void OpenGL::SetUniform1i(GLuint theProgram, const char* name, int value)
{
	glUniform1i(glGetUniformLocation(theProgram, name), value);
}

void OpenGL::SetUniform1f(GLuint theProgram, const char* name, float value)
{
	glUniform1f(glGetUniformLocation(theProgram, name), value);
}

void OpenGL::EndScene()
{
	glutSwapBuffers();
	glutPostRedisplay();
}

void OpenGL::Shutdown()
{
}

bool OpenGL::LoadExtensionList()
{
	glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	if (!glAttachShader) { return false; }

	glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)wglGetProcAddress("glBindFramebuffer");
	if (!glBindFramebuffer) { return false; }

	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	if (!glBindBuffer) { return false; }

	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
	if (!glBindVertexArray) { return false; }

	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	if (!glBufferData) { return false; }

	glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	if (!glCompileShader) { return false; }

	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	if (!glCreateProgram) { return false; }

	glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	if (!glCreateShader) { return false; }

	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
	if (!glDeleteBuffers) { return false; }

	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
	if (!glDeleteProgram) { return false; }

	glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
	if (!glDeleteShader) { return false; }

	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
	if (!glDeleteVertexArrays) { return false; }

	glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
	if (!glDetachShader) { return false; }

	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
	if (!glEnableVertexAttribArray) { return false; }

	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	if (!glGenBuffers) { return false; }

	glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)wglGetProcAddress("glGenFramebuffers");
	if (!glGenFramebuffers) { return false; }

	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
	if (!glGenVertexArrays) { return false; }

	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
	if (!glGetAttribLocation) { return false; }

	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
	if (!glGetProgramInfoLog) { return false; }

	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
	if (!glGetProgramiv) { return false; }

	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
	if (!glGetShaderInfoLog) { return false; }

	glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
	if (!glGetShaderiv) { return false; }

	glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	if (!glLinkProgram) { return false; }

	glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	if (!glShaderSource) { return false; }

	glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
	if (!glUseProgram) { return false; }

	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
	if (!glVertexAttribPointer) { return false; }

	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");
	if (!glBindAttribLocation) { return false; }

	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
	if (!glGetUniformLocation) { return false; }

	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
	if (!glUniformMatrix4fv) { return false; }

	glActiveTexture = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");
	if (!glActiveTexture) { return false; }

	glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
	if (!glUniform1i) { return false; }

	glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
	if (!glUniform1f) { return false; }

	glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
	if (!glGenerateMipmap) { return false; }

	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
	if (!glDisableVertexAttribArray) { return false; }

	glUniform3fv = (PFNGLUNIFORM3FVPROC)wglGetProcAddress("glUniform3fv");
	if (!glUniform3fv) { return false; }

	glGenRenderbuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenRenderbuffers");
	if (!glGenRenderbuffers) { return false; }

	glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)wglGetProcAddress("glBindRenderbuffer");
	if (!glBindRenderbuffer) { return false; }

	glDrawBuffers = (PFNGLDRAWBUFFERSPROC)wglGetProcAddress("glDrawBuffers");
	if (!glDrawBuffers) { return false; }

	glFramebufferTexture = (PFNGLFRAMEBUFFERTEXTUREEXTPROC)wglGetProcAddress("glFramebufferTexture");
	if (!glFramebufferTexture) { return false; }

	glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)wglGetProcAddress("glRenderbufferStorage");
	if (!glRenderbufferStorage) { return false; }

	glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)wglGetProcAddress("glFramebufferRenderbuffer");
	if (!glFramebufferRenderbuffer) { return false; }

	glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)wglGetProcAddress("glFramebufferTexture2D");
	if (!glFramebufferTexture2D) { return false; }

	glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)wglGetProcAddress("glCheckFramebufferStatus");
	if (!glCheckFramebufferStatus) { return false; }

	glUniform4fv = (PFNGLUNIFORM4FVPROC)wglGetProcAddress("glUniform4fv");
	if (!glUniform4fv) { return false; }

	glPatchParameteri = (PFNGLPATCHPARAMETERIPROC)wglGetProcAddress("glPatchParameteri");
	if (!glPatchParameteri) { return false; }

	glBlendEquation = (PFNGLBLENDEQUATIONPROC)wglGetProcAddress("glBlendEquation");
	if (!glBlendEquation) { return false; }

	glBindImageTexture = (PFNGLBINDIMAGETEXTUREPROC)wglGetProcAddress("glBindImageTexture");
	if (!glBindImageTexture) { return false; }

	glDispatchCompute = (PFNGLDISPATCHCOMPUTEPROC)wglGetProcAddress("glDispatchCompute");
	if (!glDispatchCompute) { return false; }

	glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)wglGetProcAddress("glBindBufferBase");
	if (!glBindBufferBase) { return false; }

	//glBindBuffersBase = (PFNGLBINDBUFFERSBASEPROC)wglGetProcAddress("glBindBuffersBase");
	//if (!glBindBuffersBase) { return false; }

	glMapBufferRange = (PFNGLMAPBUFFERRANGEPROC)wglGetProcAddress("glMapBufferRange");
	if (!glMapBufferRange) { return false; }

	//glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)wglGetProcAddress("glUnmapBuffer");
	//if (!glUnmapBuffer) { return false; }

	glVertexPointer = (PFNGLVERTEXPOINTERPROC)wglGetProcAddress("glVertexPointer");
	if (!glVertexPointer) { return false; }

	glEnableClientState = (PFNGLENABLESTATECLIENTPROC)wglGetProcAddress("glEnableClientState");
	if (!glEnableClientState) { return false; }

	glDisableClientState = (PFNGLDISABLESTATECLIENTPROC)wglGetProcAddress("glDisableClientState");
	if (!glDisableClientState) { return false; }

	glMemoryBarrier = (PFNGLMEMORYBARRIERPROC)wglGetProcAddress("glMemoryBarrier");
	if (!glMemoryBarrier) { return false; }

	return true;
}
