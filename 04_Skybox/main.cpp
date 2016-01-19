#include <AntTweakBar.h>
#include <GL/glew.h>

#include "GL/freeglut.h"
#include "FramePerSecond.h"
#include "ShaderManager.h"
#include "Pipeline.h"
#include "OpenGL.h"
#include "Skybox.h"
#include "Logo.h"
#include "Grid.h"

using namespace std;

ShaderManager* m_Shader;
FramePerSecond* m_FPS;
Pipeline* m_Pipeline;
Skybox* m_Skybox[2];
OpenGL* m_OpenGL;
Grid* m_Grid;
Logo* m_Logo;
TwBar* bar;

Math::Vector3f vCamPos;
Math::Vector3f vRotSky;

float fAngleX;
float fAngleY;

bool bGrid;

double dOpacity;
double dFPS;

void Initialize()
{
	m_OpenGL = new OpenGL;
	m_OpenGL->Initialize(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR, VSYNC_ENABLED);

	m_Pipeline = new Pipeline(m_OpenGL);
	m_Pipeline->Initialize(45.0f, 1.0f, 1000.0f);
	m_Pipeline->SetCameraPosition(Vector3f(0.0f, 0.0f, -4.0f));
	m_Pipeline->SetCameraAngleX(0.0f);
	m_Pipeline->SetCameraAngleY(0.0f);

	fAngleX = m_Pipeline->GetCameraAngleX();
	fAngleY = m_Pipeline->GetCameraAngleY();
	vCamPos = m_Pipeline->GetCameraPosition();

	m_Shader = new ShaderManager(m_OpenGL);
	m_Shader->Initialize();

	m_FPS = new FramePerSecond();
	dFPS = m_FPS->GetFPS();

	m_Logo = new Logo(m_OpenGL, m_Shader);
	m_Logo->Initialize((int)m_OpenGL->GetScreenWidth() - 80, (int)m_OpenGL->GetScreenHeight() - 80, 60, 60, "../Assets/Raven.tga");

	m_Grid = new Grid(m_OpenGL, m_Shader);
	m_Grid->Initialize();
	m_Grid->SetScale(Vector3f(0.4f));
	bGrid = false;

	m_Skybox[0] = new Skybox(m_OpenGL, m_Shader);
	m_Skybox[0]->Initialize("../Assets/Skybox/l_right.bmp", 
							"../Assets/Skybox/l_left.bmp", 
							"../Assets/Skybox/Down.bmp", 
							"../Assets/Skybox/l_top.bmp", 
							"../Assets/Skybox/l_front.bmp", 
							"../Assets/Skybox/l_back.bmp");
	m_Skybox[0]->SetRotate(Vector3f(0.0f, 0.0f, 180.0f));

	m_Skybox[1] = new Skybox(m_OpenGL, m_Shader);
	m_Skybox[1]->Initialize("../Assets/Skybox/lostatseanight_right.bmp", 
							"../Assets/Skybox/lostatseanight_left.bmp", 
							"../Assets/Skybox/Down.bmp", 
							"../Assets/Skybox/lostatseanight_top.bmp", 
							"../Assets/Skybox/lostatseanight_front.bmp", 
							"../Assets/Skybox/lostatseanight_back.bmp");
	m_Skybox[1]->SetRotate(Vector3f(0.0f, 0.0f, 180.0f));
	
	vRotSky = m_Skybox[0]->GetRotate();
	
	dOpacity = 0;
}

void Display(void)
{
	m_OpenGL->BeginScene(0.1f, 0.1f, 0.1f, 1.0f);

	if (vCamPos != m_Pipeline->GetCameraPosition()) { m_Pipeline->SetCameraPosition(vCamPos); }
	if (fAngleX != m_Pipeline->GetCameraAngleX())	{ m_Pipeline->SetCameraAngleX(fAngleX); }
	if (fAngleY != m_Pipeline->GetCameraAngleY())	{ m_Pipeline->SetCameraAngleY(fAngleY); }

	if (vRotSky != m_Skybox[0]->GetRotate())
	{
		m_Skybox[0]->SetRotate(vRotSky);
		m_Skybox[1]->SetRotate(vRotSky);
	}
	if (bGrid)
		m_Grid->Draw(m_Pipeline->GetViewProjectionMatrix());
	
	if (vRotSky != m_Skybox[0]->GetRotate())
	{
		m_Skybox[0]->SetRotate(vRotSky);
		m_Skybox[1]->SetRotate(vRotSky);
	}

	m_Skybox[0]->Draw(m_Pipeline->GetViewProjectionMatrix(), 1.0f - dOpacity);
	m_Skybox[1]->Draw(m_Pipeline->GetViewProjectionMatrix(), dOpacity);

	vRotSky.y += 0.05f;
	if (vRotSky.y >= 360.0f) { vRotSky.y -= 360.0f; }

	TwDraw();

	m_Logo->Draw();
	m_OpenGL->EndScene();

	dFPS = m_FPS->GetFPS();

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
	TwDefine(" MENU size='220 270' color='0 0 0' ");

	TwAddVarRO(bar, "", TW_TYPE_DOUBLE, &dFPS, "label='FPS' precision=2 group='Dark Raven Engine'");
	TwAddVarRW(bar, "", TW_TYPE_BOOLCPP, &bGrid, "label='Show grid' group='Dark Raven Engine'");

	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vCamPos.x, "label='Cam Pos X' min=-180 max=180 step=0.5 group='Camera Position'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vCamPos.y, "label='Cam Pos Y' min=-180 max=180 step=0.5 group='Camera Position'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vCamPos.z, "label='Cam Pos Z' min=-180 max=180 step=0.5 group='Camera Position'");

	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &fAngleX, "label='Cam Rot X' min=-360 max=360 step=0.5 group='Camera Rotation'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &fAngleY, "label='Cam Rot Y' min=-360 max=360 step=0.5 group='Camera Rotation'");

	TwAddVarRW(bar, "", TW_TYPE_DOUBLE, &dOpacity, "label='Opacity' min=0 max=1 step=0.01 group='Skybox' ");

	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vRotSky.x, "label='Rotate X' min=0 max=359 step=1 group='Skybox' ");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vRotSky.y, "label='Rotate Y' min=0 max=359 step=1 group='Skybox' ");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vRotSky.z, "label='Rotate Z' min=0 max=359 step=1 group='Skybox' ");

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);

	glutMainLoop();

	return 0;
}