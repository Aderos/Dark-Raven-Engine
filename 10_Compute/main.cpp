#include <AntTweakBar.h>

#include "FramePerSecond.h"
#include "ShaderManager.h"
#include "Object3D.h"
#include "Pipeline.h"
#include "Texture.h"
#include "OpenGL.h"
#include <random>
#include <cmath>
#include "Logo.h"
#include "Grid.h"

using namespace std;

#define NUM_PARTICLES 512 * 512
#define WORK_GROUP_SIZE 128

GLuint posSSbo;
GLuint velSSbo;
GLuint colSSbo;

ShaderManager* m_Shader;
FramePerSecond* m_FPS;
Pipeline* m_Pipeline;
OpenGL* m_OpenGL;
Logo* m_Logo;
Grid* m_Grid;
TwBar* bar;

Math::Vector3f vCamPos;

float fAngleX;
float fAngleY;

bool bGrid;
bool bWireframe;

double fFPS;

std::vector<Vector4f> positionData;
std::vector<Vector4f> velocityData;

GLuint vao;

void Initialize()
{
	m_OpenGL = new OpenGL;
	m_OpenGL->Initialize(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR, VSYNC_ENABLED);

	m_Pipeline = new Pipeline(m_OpenGL);
	m_Pipeline->Initialize(45.0f, 0.1f, 1000.0f);
	m_Pipeline->SetCameraPosition(Vector3f(0.0f, 0.0f, -3.0f));
	m_Pipeline->SetCameraAngleX(5.0f);
	m_Pipeline->SetCameraAngleY(0.0f);

	fAngleX = m_Pipeline->GetCameraAngleX();
	fAngleY = m_Pipeline->GetCameraAngleY();
	vCamPos = m_Pipeline->GetCameraPosition();

	m_Shader = new ShaderManager(m_OpenGL);
	m_Shader->Initialize();

	m_FPS = new FramePerSecond();
	fFPS = m_FPS->GetFPS();

	m_Logo = new Logo(m_OpenGL, m_Shader);
	m_Logo->Initialize((int)m_OpenGL->GetScreenWidth() - 80, (int)m_OpenGL->GetScreenHeight() - 80, 60, 60, "../Assets/Raven.tga");

	m_Grid = new Grid(m_OpenGL, m_Shader);
	m_Grid->Initialize();
	m_Grid->SetScale(Vector3f(0.4f));
	bGrid = false;
	bWireframe = false;

	m_OpenGL->glGenBuffers(1, &posSSbo);
	m_OpenGL->glBindBuffer(GL_SHADER_STORAGE_BUFFER, posSSbo);
	m_OpenGL->glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_PARTICLES * sizeof(Vector4f), NULL, GL_STATIC_DRAW);

	GLint bufMask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT;

	std::default_random_engine generator;
	std::uniform_real_distribution<float> dX(-1, 1);
	std::uniform_real_distribution<float> dY(-1, 1);
	std::uniform_real_distribution<float> dZ(-1, 1);

	Vector4f *points = (Vector4f*)m_OpenGL->glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, NUM_PARTICLES * sizeof(Vector4f), bufMask);
	for (int i = 0; i < NUM_PARTICLES; i++)
	{
		Vector4f a = Vector4f(dX(generator), dY(generator), dZ(generator), 1.0f);
		points[i].x = a.x;
		points[i].y = a.y;
		points[i].z = a.z;
		points[i].w = 1;
	}

	m_OpenGL->GenVertexArrays(&vao);
	m_OpenGL->BindVertexArray(&vao);
	m_OpenGL->BindBufferData(posSSbo, NUM_PARTICLES, sizeof(Vector4f), &points[0], 0, 4);

	//m_OpenGL->glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
	
	m_OpenGL->glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, posSSbo);
	m_Shader->UseShader(GLT_ACCELERATION_SHADER, NUM_PARTICLES / WORK_GROUP_SIZE);
}

void Display(void)
{
	m_OpenGL->BeginScene(0.1f, 0.1f, 0.1f, 1.0f);

	if (vCamPos != m_Pipeline->GetCameraPosition()) { m_Pipeline->SetCameraPosition(vCamPos); }
	if (fAngleX != m_Pipeline->GetCameraAngleX()) { m_Pipeline->SetCameraAngleX(fAngleX); }
	if (fAngleY != m_Pipeline->GetCameraAngleY()) { m_Pipeline->SetCameraAngleY(fAngleY); }

	if (bGrid)
		m_Grid->Draw(m_Pipeline->GetViewProjectionMatrix());

	m_OpenGL->glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, posSSbo);
	m_Shader->UseShader(GLT_ACCELERATION_SHADER, NUM_PARTICLES / WORK_GROUP_SIZE);

	m_OpenGL->BindVertexArray(&vao);
	m_Shader->UseShader(GLT_PARTICLE_SHADER, m_Pipeline->GetViewProjectionMatrix());
	m_OpenGL->glEnableClientState(GL_VERTEX_ARRAY);
	m_OpenGL->DrawPoints(0, NUM_PARTICLES);
	m_OpenGL->glDisableClientState(GL_VERTEX_ARRAY);
	m_OpenGL->glBindBuffer(GL_ARRAY_BUFFER, 0);

	TwDraw();

	m_Logo->Draw();
	m_OpenGL->EndScene();

	fFPS = m_FPS->GetFPS();

	TwRefreshBar(bar);
}

void Reshape(int w, int h)
{
	TwWindowSize(w, h);
	m_Pipeline->UpdateProjection();
}


void Keyboard(unsigned char key, int x, int y)
{
	m_OpenGL->ExitGame(key);

	TwRefreshBar(bar);
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	FreeConsole();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(((glutGet(GLUT_SCREEN_WIDTH) - SCREEN_WIDTH) / 2), ((glutGet(GLUT_SCREEN_HEIGHT) - SCREEN_HEIGHT) / 2) - 10);

	glutCreateWindow("Dark Raven Engine");

	Initialize();

	TwInit(TW_OPENGL_CORE, NULL);

	glutMouseFunc((GLUTmousebuttonfun)TwEventMouseButtonGLUT);
	glutMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
	glutPassiveMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
	glutKeyboardFunc((GLUTkeyboardfun)TwEventKeyboardGLUT);
	glutSpecialFunc((GLUTspecialfun)TwEventSpecialGLUT);

	bar = TwNewBar("MENU");
	TwDefine(" MENU size='220 210' color='0 0 0' ");

	TwAddVarRO(bar, "", TW_TYPE_DOUBLE, &fFPS, "label='FPS' precision=2 group='Dark Raven Engine'");
	TwAddVarRW(bar, "", TW_TYPE_BOOLCPP, &bGrid, "label='Grid' group='Dark Raven Engine'");
	TwAddVarRW(bar, "", TW_TYPE_BOOLCPP, &bWireframe, "label='Wireframe' group='Dark Raven Engine'");

	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vCamPos.x, "label='Cam Pos X' min=-180 max=180 step=0.5 group='Camera Position'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vCamPos.y, "label='Cam Pos Y' min=-180 max=180 step=0.5 group='Camera Position'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vCamPos.z, "label='Cam Pos Z' min=-180 max=180 step=0.5 group='Camera Position'");

	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &fAngleX, "label='Cam Rot X' min=-360 max=360 step=0.5 group='Camera Rotation'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &fAngleY, "label='Cam Rot Y' min=-360 max=360 step=0.5 group='Camera Rotation'");

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);

	glutMainLoop();

	return 0;
}