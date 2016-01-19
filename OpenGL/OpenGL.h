#pragma once
#include <GL/glut.h>
#include <windows.h>
#include <vector>
//#include <GL/glew.h>

#include "Math3D.h"
#include "MatrixStack.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define FULL_SCREEN false
#define VSYNC_ENABLED true

#define SCREEN_DEPTH 100.0f
#define SCREEN_NEAR 0.1f

#pragma region OPENGL
#define GL_MAP_WRITE_BIT			   0x0002
#define GL_MAP_INVALIDATE_BUFFER_BIT   0x0008
#define GL_DEPTH_TEXTURE_MODE		   0x884B 
#define GL_TEXTURE_COMPARE_FUNC		   0x884D
#define GL_COMPARE_R_TO_TEXTURE		   0x884E
#define GL_TEXTURE_COMPARE_MODE		   0x884C
#define GL_FRAMEBUFFER_COMPLETE		   0x8CD5
#define GL_FRAMEBUFFER				   0x8D40
#define GL_DRAW_FRAMEBUFFER			   0x8CA9
#define GL_DEPTH_ATTACHMENT			   0x8D00
#define WGL_DRAW_TO_WINDOW_ARB         0x2001
#define WGL_ACCELERATION_ARB           0x2003
#define WGL_SWAP_METHOD_ARB            0x2007
#define WGL_SUPPORT_OPENGL_ARB         0x2010
#define WGL_DOUBLE_BUFFER_ARB          0x2011
#define WGL_PIXEL_TYPE_ARB             0x2013
#define WGL_COLOR_BITS_ARB             0x2014
#define WGL_DEPTH_BITS_ARB             0x2022
#define WGL_STENCIL_BITS_ARB           0x2023
#define WGL_FULL_ACCELERATION_ARB      0x2027
#define WGL_SWAP_EXCHANGE_ARB          0x2028
#define WGL_TYPE_RGBA_ARB              0x202B
#define WGL_CONTEXT_MAJOR_VERSION_ARB  0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB  0x2092
#define GL_ARRAY_BUFFER                0x8892
#define GL_STATIC_DRAW                 0x88E4
#define GL_FRAGMENT_SHADER             0x8B30
#define GL_VERTEX_SHADER               0x8B31
#define GL_GEOMETRY_SHADER			   0x8DD9
#define GL_TESS_EVALUATION_SHADER	   0x8E87
#define GL_TESS_CONTROL_SHADER		   0x8E88
#define GL_COMPILE_STATUS              0x8B81
#define GL_LINK_STATUS                 0x8B82
#define GL_INFO_LOG_LENGTH             0x8B84
#define GL_TEXTURE0                    0x84C0
#define GL_TEXTURE1					   0x84C1
#define GL_TEXTURE2					   0x84C2
#define GL_BGR						   0x80E0
#define GL_BGRA                        0x80E1
#define GL_ELEMENT_ARRAY_BUFFER        0x8893
#define GL_TEXTURE_3D				   0x806F
#define GL_TEXTURE_CUBE_MAP			   0x8513
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X 0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y 0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z 0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x851A
#define GL_CLAMP_TO_EDGE			   0x812F
#define GL_TEXTURE_WRAP_R			   0x8072
#define GL_TEXTURE_RECTANGLE		   0x84F5
#define GL_RENDERBUFFER                0x8D41
#define GL_COLOR_ATTACHMENT0           0x8CE0
#define GL_DEPTH_COMPONENT16           0x81A5
#define GL_DEPTH_COMPONENT24           0x81A6
#define GL_DEPTH_COMPONENT32           0x81A7
#define GL_PATCHES					   0x000E
#define GL_PATCH_VERTICES			   0x8E72
#define GL_R32F						   0x822E
#define GL_WRITE_ONLY				   0x88B9
#define GL_COMPUTE_SHADER			   0x91B9
#define GL_READ_WRITE				   0x88BA
#define GL_RGBA32F                     0x8814
#define GL_RGB32F                      0x8815
#define GL_RGBA16F                     0x881A
#define GL_RGB16F                      0x881B
#define GL_SHADER_STORAGE_BUFFER	   0x90D2
#define GL_SHADER_STORAGE_BARRIER_BIT  0x2000



typedef BOOL(WINAPI * PFNWGLCHOOSEPIXELFORMATARBPROC) (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
typedef HGLRC(WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int *attribList);
typedef BOOL(WINAPI * PFNWGLSWAPINTERVALEXTPROC) (int interval);
typedef void   (APIENTRY * PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader);
typedef void   (APIENTRY * PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer);
typedef void   (APIENTRY * PFNGLBINDFRAMEBUFFERPROC) (GLenum target, GLuint buffer);
typedef void   (APIENTRY * PFNGLBINDVERTEXARRAYPROC) (GLuint array);
typedef void   (APIENTRY * PFNGLBUFFERDATAPROC) (GLenum target, ptrdiff_t size, const GLvoid *data, GLenum usage);
typedef void   (APIENTRY * PFNGLCOMPILESHADERPROC) (GLuint shader);
typedef GLuint(APIENTRY * PFNGLCREATEPROGRAMPROC) (void);
typedef GLuint(APIENTRY * PFNGLCREATESHADERPROC) (GLenum type);
typedef void   (APIENTRY * PFNGLDELETEBUFFERSPROC) (GLsizei n, const GLuint *buffers);
typedef void   (APIENTRY * PFNGLDELETEPROGRAMPROC) (GLuint program);
typedef void   (APIENTRY * PFNGLDELETESHADERPROC) (GLuint shader);
typedef void   (APIENTRY * PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, const GLuint *arrays);
typedef void   (APIENTRY * PFNGLDETACHSHADERPROC) (GLuint program, GLuint shader);
typedef void   (APIENTRY * PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void   (APIENTRY * PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers);
typedef void   (APIENTRY * PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays);
typedef GLint(APIENTRY * PFNGLGETATTRIBLOCATIONPROC) (GLuint program, const char *name);
typedef void   (APIENTRY * PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufSize, GLsizei *length, char *infoLog);
typedef void   (APIENTRY * PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint *params);
typedef void   (APIENTRY * PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, char *infoLog);
typedef void   (APIENTRY * PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params);
typedef void   (APIENTRY * PFNGLLINKPROGRAMPROC) (GLuint program);
typedef void   (APIENTRY * PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const char* *string, const GLint *length);
typedef void   (APIENTRY * PFNGLUSEPROGRAMPROC) (GLuint program);
typedef void   (APIENTRY * PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer);
typedef void   (APIENTRY * PFNGLBINDATTRIBLOCATIONPROC) (GLuint program, GLuint index, const char *name);
typedef GLint(APIENTRY * PFNGLGETUNIFORMLOCATIONPROC) (GLuint program, const char *name);
typedef void   (APIENTRY * PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value);
typedef void   (APIENTRY * PFNGLACTIVETEXTUREPROC) (GLenum texture);
typedef void   (APIENTRY * PFNGLUNIFORM1IPROC) (GLint location, GLint v0);
typedef void   (APIENTRY * PFNGLUNIFORM1FPROC) (GLint location, GLfloat v0);
typedef void   (APIENTRY * PFNGLGENERATEMIPMAPPROC) (GLenum target);
typedef void   (APIENTRY * PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint index);
typedef void   (APIENTRY * PFNGLUNIFORM3FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void   (APIENTRY * PFNGLUNIFORM4FVPROC) (GLint location, GLsizei count, const GLfloat *value);
typedef void   (APIENTRY * PFNGLGENFRAMEBUFFERSPROC) (GLsizei n, GLuint *buffers);
typedef void   (APIENTRY * PFNGLGENRENDERBUFFERSPROC) (GLsizei n, GLuint *renderbuffers);
typedef void   (APIENTRY * PFNGLBLENDEQUATIONPROC) (GLenum mode);
typedef void   (APIENTRY * PFNGLPATCHPARAMETERIPROC) (GLenum pname, GLint value);

//typedef void (APIENTRY * PFNGLGENFRAMEBUFFERSEXTPROC)(GLsizei n, GLuint* ids);
//typedef void (APIENTRY * PFNGLDELETEFRAMEBUFFERSEXTPROC)(GLsizei n, const GLuint* ids);
//typedef void (APIENTRY * PFNGLBINDFRAMEBUFFEREXTPROC)(GLenum target, GLuint id);
typedef void (APIENTRY * PFNGLFRAMEBUFFERTEXTURE2DEXTPROC)(GLenum target, GLenum attachmentPoint, GLenum textureTarget, GLuint textureId, GLint  level);
typedef void (APIENTRY * PFNGLFRAMEBUFFERTEXTUREEXTPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level);
//typedef void (APIENTRY * PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);

typedef GLenum(APIENTRY * PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC)(GLenum target);

typedef void (APIENTRY * PFNGLBINDRENDERBUFFERPROC) (GLenum target, GLuint renderbuffer);
typedef void (APIENTRY * PFNGLRENDERBUFFERSTORAGEPROC) (GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
typedef void (APIENTRY * PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);

typedef void(APIENTRY * PFNGLDRAWBUFFERSPROC)(GLsizei n, const GLenum *bufs);

//typedef void (APIENTRY * PFNGLACTIVETEXTUREARBPROC)(GLenum texture);
//typedef void (APIENTRY * PFNGLCLIENTACTIVETEXTUREARBPROC)(GLenum texture);

typedef void (APIENTRY * PFNGLBINDIMAGETEXTUREPROC)(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
typedef void (APIENTRY * PFNGLDISPATCHCOMPUTEPROC)(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
typedef void (APIENTRY * PFNGLBINDBUFFERBASEPROC)(GLenum target, GLuint index, GLuint buffer);
typedef void (APIENTRY * PFNGLBINDBUFFERSBASEPROC)(GLenum target, GLuint index, GLuint size, const GLuint *buffer);
typedef void* (APIENTRY * PFNGLMAPBUFFERRANGEPROC)(GLenum target, GLint offset, GLsizei length, GLbitfield access);
//typedef void (APIENTRY * PFNGLUNMAPBUFFERPROC) (GLenum target);
typedef void (APIENTRY * PFNGLVERTEXPOINTERPROC) (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
typedef void (APIENTRY * PFNGLENABLESTATECLIENTPROC) (GLenum array);
typedef void (APIENTRY * PFNGLDISABLESTATECLIENTPROC) (GLenum array);
typedef void (APIENTRY * PFNGLMEMORYBARRIERPROC) (GLbitfield barriers);

#pragma endregion OPENGL

using namespace Math;

class OpenGL
{
public:
	OpenGL();
	~OpenGL();

	bool Initialize(int, int, float, float, bool);
	void Shutdown();

	void BeginScene(float, float, float, float);
	void EndScene();
	void ExitGame(unsigned char key);

	void BindBufferData(GLuint Buffer, GLuint Size, GLsizei Stride, GLvoid* Data, GLint Index, GLint Count);
	void BindVertexArray(GLuint *VertexArray);
	void GenVertexArrays(GLuint *VertexArray);

	void BindTexture1D(GLuint &TextureID, GLuint, GLubyte*);
	void BindTexture2D(GLuint &TextureID, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, unsigned char*);
	void BindTextureCubeMap(GLuint &TextureID);
	void BindPartTextureCubeMap(GLenum target, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, GLuint, unsigned char*);
	void BindActiveTexture2D(GLuint TextureID);
	void BindActiveNormalTexture2D(GLuint TextureID);
	void BindActiveHeightTexture2D(GLuint TextureID);
	void BindActiveShadowTexture2D(GLuint TextureID);
	void BindActiveCubeMap(GLuint TextureID);
	void ReleaseTexture(GLuint &TextureID);

	void EnableWireframe();
	void DisableWireframe();

	void BlendEquation(GLenum mode);

	void ReleaseVertexArray(GLuint *VertexArray);
	void DisableVertexAttribArray(GLuint);

	void EnableBlend();
	void DisableBlend();

	void EnableDepth();
	void DisableDepth();

	void DrawTriangles(int, int);
	void DrawTrianglesStrip(int, int);
	void DrawLines(int, int);
	void DrawPoints(int, int);
	void DrawTess(int, int, int);

	void UseProgram(int);
	void DeleteShaders(GLuint, std::vector<GLuint>);
	void DeleteProgram(GLuint);

	bool CompileShader(GLuint);
	void AttachShaders(GLuint, std::vector<GLuint>);

	void CreateProgram(GLuint&);
	void CreateShader(GLuint&, GLenum, const char*);

	char* GetProgramInfoLog(GLuint);
	char* GetShaderInfoLog(GLuint);

	bool LinkProgram(GLuint);

	void SetUniformMatrix4f(GLuint, const char*, const float*);
	void SetUniformVector4f(GLuint, const char*, const float*);
	void SetUniformVector3f(GLuint, const char*, const float*);
	void SetUniform1i(GLuint, const char*, int);
	void SetUniform1f(GLuint, const char*, float);

	float GetScreenWidth();
	float GetScreenHeight();
	float GetScreenDepth();
	float GetScreenNear();

	GLenum GetVertexShader();
	GLenum GetFragmentShader();
	GLenum GetGeometryShader();
	GLenum GetTessControlShader();
	GLenum GetTessEvaluationShader();
	GLenum GetComputeShader();

	GLenum GetRGB();
	GLenum GetRGBA();
	GLenum GetBGR();
	GLenum GetBGRA();
	GLenum GetLuminance();
	GLuint GetUnsignedByte();

	GLenum GetTextureCubeMapPosX();
	GLenum GetTextureCubeMapNegX();
	GLenum GetTextureCubeMapPosY();
	GLenum GetTextureCubeMapNegY();
	GLenum GetTextureCubeMapPosZ();
	GLenum GetTextureCubeMapNegZ();

private:
	bool LoadExtensionList();

public:
	PFNGLATTACHSHADERPROC glAttachShader;
	PFNGLBINDBUFFERPROC glBindBuffer;
	PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
	PFNGLBUFFERDATAPROC glBufferData;
	PFNGLCREATESHADERPROC glCreateShader;
	PFNGLDELETEBUFFERSPROC glDeleteBuffers;
	PFNGLDELETEPROGRAMPROC glDeleteProgram;
	PFNGLDELETESHADERPROC glDeleteShader;
	PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
	PFNGLCOMPILESHADERPROC glCompileShader;
	PFNGLCREATEPROGRAMPROC glCreateProgram;
	PFNGLUNIFORM3FVPROC glUniform3fv;
	PFNGLUNIFORM4FVPROC glUniform4fv;
	PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
	PFNGLDETACHSHADERPROC glDetachShader;
	PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
	PFNGLGENBUFFERSPROC glGenBuffers;
	PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
	PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
	PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
	PFNGLGETPROGRAMIVPROC glGetProgramiv;
	PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
	PFNGLGETSHADERIVPROC glGetShaderiv;
	PFNGLLINKPROGRAMPROC glLinkProgram;
	PFNGLSHADERSOURCEPROC glShaderSource;
	PFNGLUSEPROGRAMPROC glUseProgram;
	PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
	PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
	PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
	PFNGLACTIVETEXTUREPROC glActiveTexture;
	PFNGLUNIFORM1IPROC glUniform1i;
	PFNGLUNIFORM1FPROC glUniform1f;
	PFNGLPATCHPARAMETERIPROC glPatchParameteri;

	PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
	PFNGLGENBUFFERSPROC glGenRenderbuffers;
	PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer;
	PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage;

	PFNGLFRAMEBUFFERTEXTURE2DEXTPROC glFramebufferTexture2D;
	PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC glCheckFramebufferStatus;
	PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer;
	PFNGLFRAMEBUFFERTEXTUREEXTPROC glFramebufferTexture;
	PFNGLDRAWBUFFERSPROC glDrawBuffers;

	PFNGLBLENDEQUATIONPROC glBlendEquation;
	PFNGLBINDIMAGETEXTUREPROC glBindImageTexture;
	PFNGLDISPATCHCOMPUTEPROC glDispatchCompute;
	PFNGLBINDBUFFERBASEPROC glBindBufferBase;
	PFNGLBINDBUFFERSBASEPROC glBindBuffersBase;

	PFNGLMAPBUFFERRANGEPROC glMapBufferRange;
	//PFNGLUNMAPBUFFERPROC glUnmapBuffer;
	PFNGLVERTEXPOINTERPROC glVertexPointer;
	PFNGLENABLESTATECLIENTPROC glEnableClientState;
	PFNGLDISABLESTATECLIENTPROC glDisableClientState;
	PFNGLMEMORYBARRIERPROC glMemoryBarrier;

public:
	PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
	PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
	PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;

};