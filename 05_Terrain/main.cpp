#include <AntTweakBar.h>
#include <GL/glew.h>

#include "FramePerSecond.h"
#include "ShaderManager.h"
#include "GL/freeglut.h"
#include "Pipeline.h"
#include "Terrain.h"
#include "OpenGL.h"
#include "Logo.h"
#include "Grid.h"

using namespace std;

ShaderManager* m_Shader;
FramePerSecond* m_FPS;
Pipeline* m_Pipeline;
OpenGL* m_OpenGL;
Logo* m_Logo;
Terrain* m_Terrain;
Grid* m_Grid;
TwBar* bar;

Math::Vector3f vCamPos;
Math::Vector3f vPosTer;
Math::Vector3f vScaTer;
Math::Vector3f vRotTer;
Math::Vector3f vLight;

float fAngleX;
float fAngleY;

int iHeight;

double dFPS;

bool bGrid;

void Initialize()
{
	m_OpenGL = new OpenGL;
	m_OpenGL->Initialize(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR, VSYNC_ENABLED);

	m_Pipeline = new Pipeline(m_OpenGL);
	m_Pipeline->Initialize(45.0f, 1.0f, 1000.0f);
	m_Pipeline->SetCameraPosition(Vector3f(0.0f, 0.0f, -8.0f));
	m_Pipeline->SetCameraAngleX(5.0f);
	m_Pipeline->SetCameraAngleY(-7.5f);

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
	bGrid = true;

	m_Terrain = new Terrain(m_OpenGL, m_Shader);
	m_Terrain->Initialize("../Assets/forest.bmp", "../Assets/terrain.bmp", "../Assets/NormalMap.bmp", 20);
	m_Terrain->SetPosition(Vector3f(0.0f, 0.0f, 0.0f));
	m_Terrain->SetRotate(Vector3f(0.0f, 0.0f, 0.0f));
	m_Terrain->SetScale(Vector3f(0.05f, 0.05f, 0.05f));
	m_Terrain->SetPositionLight(Vector3f(1.0f, 8.0f, 1.0f));

	vPosTer = m_Terrain->GetPosition();
	vRotTer = m_Terrain->GetRotate();
	vScaTer = m_Terrain->GetScale();
	vLight = m_Terrain->GetPositionLight();

	iHeight = 10.0f;
}

void Display(void)
{
	m_OpenGL->BeginScene(0.1f, 0.1f, 0.1f, 1.0f);

	if (vCamPos != m_Pipeline->GetCameraPosition()) { m_Pipeline->SetCameraPosition(vCamPos); }
	if (fAngleX != m_Pipeline->GetCameraAngleX())	{ m_Pipeline->SetCameraAngleX(fAngleX); }
	if (fAngleY != m_Pipeline->GetCameraAngleY())	{ m_Pipeline->SetCameraAngleY(fAngleY); }

	if (vPosTer != m_Terrain->GetPosition())	  { m_Terrain->SetPosition(vPosTer); }
	if (vRotTer != m_Terrain->GetRotate())		  { m_Terrain->SetRotate(vRotTer); }
	if (vScaTer != m_Terrain->GetScale())	      { m_Terrain->SetScale(vScaTer); }
	if (vLight  != m_Terrain->GetPositionLight()) { m_Terrain->SetPositionLight(vLight); }

	Matrix44f mVP = m_Pipeline->GetProjectionMatrix() * m_Pipeline->GetCameraMatrix();
	
	if (bGrid)
		m_Grid->Draw(mVP);

	m_Terrain->Draw(mVP, iHeight);
	
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
	TwDefine(" MENU size='220 460' color='0 0 0' ");

	TwAddVarRO(bar, "", TW_TYPE_DOUBLE, &dFPS, "label='FPS' precision=2 group='Dark Raven Engine'");
	TwAddVarRW(bar, "", TW_TYPE_BOOLCPP, &bGrid, "label='Show grid' group='Dark Raven Engine'");

	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vCamPos.x, "label='Cam Pos X' min=-180 max=180 step=0.5 group='Camera Position'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vCamPos.y, "label='Cam Pos Y' min=-180 max=180 step=0.5 group='Camera Position'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vCamPos.z, "label='Cam Pos Z' min=-180 max=180 step=0.5 group='Camera Position'");

	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &fAngleX, "label='Cam Rot X' min=-360 max=360 step=0.5 group='Camera Rotation'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &fAngleY, "label='Cam Rot Y' min=-360 max=360 step=0.5 group='Camera Rotation'");

	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vLight.x, "label='Light X' min=-100 max=100 step=1 group='Object Light'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vLight.y, "label='Light Y' min=-100 max=100 step=1 group='Object Light'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vLight.z, "label='Light Z' min=-100 max=100 step=1 group='Object Light'");

	TwAddVarRW(bar, "", TW_TYPE_INT16, &iHeight, "label='Height' min=0 max=359 step=1 group='Terrain' ");

	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vRotTer.x, "label='Rotate X' min=0 max=359 step=1 group='Terrain Rotate' ");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vRotTer.y, "label='Rotate Y' min=0 max=359 step=1 group='Terrain Rotate' ");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vRotTer.z, "label='Rotate Z' min=0 max=359 step=1 group='Terrain Rotate' ");

	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vPosTer.x, "label='Position X' min=-100 max=100 step=1.0 group='Terrain Position'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vPosTer.y, "label='Position Y' min=-10 max=10 step=0.01 group='Terrain Position'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vPosTer.z, "label='Position Z' min=-10 max=10 step=0.01 group='Terrain Position'");

	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vScaTer.x, "label='Scale X' min=0 max=10 step=0.01 group='Terrain Scale'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vScaTer.y, "label='Scale Y' min=0 max=10 step=0.01 group='Terrain Scale'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vScaTer.z, "label='Scale Z' min=0 max=10 step=0.01 group='Terrain Scale'");

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);

	glutMainLoop();

	return 0;
}