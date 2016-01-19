#include <AntTweakBar.h>

#include "FramePerSecond.h"
#include "ShaderManager.h"
#include "Object3D.h"
#include "Pipeline.h"
#include "OpenGL.h"
#include "Logo.h"
#include "Grid.h"

using namespace std;
#define NUM_OBJECT 4
enum { LAMP = 0, BENCH, LIGHT, PLANE };

Object3D* m_Obj[NUM_OBJECT];
ShaderManager* m_Shader;
FramePerSecond* m_FPS;
Pipeline* m_Pipeline;
OpenGL* m_OpenGL;
Logo* m_Logo;
Grid* m_Grid;
TwBar* bar;

Math::Vector4f vColObj;
Math::Vector3f vCamPos;
Math::Vector3f vPosObj;
Math::Vector3f vRotObj;
Math::Vector3f vScaObj;

float fDissolve;
float fAngleX;
float fAngleY;
int iSpec;

float fRot;

int iCurrentObject;
int iOldObject;

bool bGrid;

double fFPS;

void Initialize()
{
	m_OpenGL = new OpenGL;
	m_OpenGL->Initialize(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR, VSYNC_ENABLED);

	m_Pipeline = new Pipeline(m_OpenGL);
	m_Pipeline->Initialize(45.0f, 1.0f, 1000.0f);
	m_Pipeline->SetCameraPosition(Vector3f(0.0f, -0.5f, -6.0f));
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

	m_Obj[LAMP] = new Object3D(m_OpenGL);
	m_Obj[LAMP]->Initialize("../Assets/lamp.obj", "../Assets/lamp.tga");
	m_Obj[LAMP]->SetPosition(Vector3f(-0.82f, -0.2f, 0.0f));
	m_Obj[LAMP]->SetScale(Vector3f(0.9f, 1.0f, 0.9f));
	m_Obj[LAMP]->SetRotate(Vector3f(0.0f, 0.0f, 0.0f));

	m_Obj[BENCH] = new Object3D(m_OpenGL);
	m_Obj[BENCH]->Initialize("../Assets/bench.obj", "../Assets/benchTexture.bmp");
	m_Obj[BENCH]->SetPosition(Vector3f(0.65f, 0.0f, 0.0f));
	m_Obj[BENCH]->SetScale(Vector3f(1.0f, 1.0f, 1.0f));
	m_Obj[BENCH]->SetRotate(Vector3f(0.0f, 0.0f, 0.0f));

	m_Obj[LIGHT] = new Object3D(m_OpenGL);
	m_Obj[LIGHT]->Initialize("../Assets/cube.obj", "../Assets/plane.bmp");
	m_Obj[LIGHT]->SetPosition(Vector3f(-0.85f, 2.45f, 0.0f));
	m_Obj[LIGHT]->SetScale(Vector3f(0.1f, 0.1f, 0.1f));
	m_Obj[LIGHT]->SetRotate(Vector3f(0.0f, 0.0f, 0.0f));

	m_Obj[PLANE] = new Object3D(m_OpenGL);
	m_Obj[PLANE]->Initialize("../Assets/plane.obj", "../Assets/way_texture.bmp");
	m_Obj[PLANE]->SetNormalTexture("../Assets/ground_normal.bmp");
	m_Obj[PLANE]->SetPosition(Vector3f(0.0f, 0.0f, 0.0f));
	m_Obj[PLANE]->SetScale(Vector3f(5.0f, 1.0f, 5.0f));
	m_Obj[PLANE]->SetRotate(Vector3f(0.0f, 0.0f, 0.0f));

	vPosObj = m_Obj[LAMP]->GetPosition();
	vScaObj = m_Obj[LAMP]->GetScale();
	vRotObj = m_Obj[LAMP]->GetRotate();
	
	iCurrentObject = LAMP;
	iSpec = 8;
	fRot = 0.05f;
}

void Display(void)
{
	m_OpenGL->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	if (vCamPos != m_Pipeline->GetCameraPosition()) { m_Pipeline->SetCameraPosition(vCamPos); }
	if (fAngleX != m_Pipeline->GetCameraAngleX())	{ m_Pipeline->SetCameraAngleX(fAngleX); }
	if (fAngleY != m_Pipeline->GetCameraAngleY())	{ m_Pipeline->SetCameraAngleY(fAngleY); }

	if (iCurrentObject != iOldObject)
	{
		vPosObj = m_Obj[iCurrentObject]->GetPosition();
		vRotObj = m_Obj[iCurrentObject]->GetRotate();
		vScaObj = m_Obj[iCurrentObject]->GetScale();
	}

	if (vPosObj != m_Obj[iCurrentObject]->GetPosition()) { m_Obj[iCurrentObject]->SetPosition(vPosObj); }
	if (vRotObj != m_Obj[iCurrentObject]->GetRotate())   { m_Obj[iCurrentObject]->SetRotate(vRotObj); }
	if (vScaObj != m_Obj[iCurrentObject]->GetScale())    { m_Obj[iCurrentObject]->SetScale(vScaObj); }

	if (bGrid)
		m_Grid->Draw(m_Pipeline->GetViewProjectionMatrix());

	if (fAngleY > 62.8f) fAngleY -= 62.8f;
	fAngleY += fRot;

	// PLANE
	m_Shader->UseShader(GLT_GROUND_PARK_SHADER, m_Pipeline->GetViewProjectionMatrix() * m_Obj[PLANE]->GetWorldMatrix(), m_Obj[PLANE]->GetWorldMatrix(),
		m_Obj[LIGHT]->GetPosition(), iSpec, m_Obj[PLANE]->GetColorTexture(), m_Obj[PLANE]->GetNormalTexture());
	m_Obj[PLANE]->Draw();

	// LAMP
	m_Shader->UseShader(GLT_LAMP_PARK_SHADER, m_Pipeline->GetViewProjectionMatrix() * m_Obj[LAMP]->GetWorldMatrix(), m_Obj[LAMP]->GetWorldMatrix(),
		m_Obj[LIGHT]->GetPosition(), m_Obj[LAMP]->GetColorTexture());
	m_Obj[LAMP]->Draw();

	// BENCH
	m_Shader->UseShader(GLT_PARK_SHADER, m_Pipeline->GetViewProjectionMatrix() * m_Obj[BENCH]->GetWorldMatrix(), m_Obj[BENCH]->GetWorldMatrix(),
		m_Obj[LIGHT]->GetPosition(), m_Obj[BENCH]->GetColorTexture());
	m_Obj[BENCH]->Draw();

	TwDraw();

	m_Logo->Draw();
	m_OpenGL->EndScene();

	fFPS = m_FPS->GetFPS();

	iOldObject = iCurrentObject;

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

	glutCreateWindow("Dark Raven Engine - Scene Park");

	Initialize();

	TwInit(TW_OPENGL_CORE, NULL);

	glutMouseFunc((GLUTmousebuttonfun)TwEventMouseButtonGLUT);
	glutMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
	glutPassiveMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
	glutKeyboardFunc((GLUTkeyboardfun)TwEventKeyboardGLUT);
	glutSpecialFunc((GLUTspecialfun)TwEventSpecialGLUT);

	TwEnumVal objectEV[NUM_OBJECT] =
	{
		{ LAMP, "Lamp" },
		{ BENCH, "Bench" },
		{ LIGHT, "Light" },
		{ PLANE, "Plane" }
	};
	TwType objectType = TwDefineEnum("ObjectType", objectEV, NUM_OBJECT);

	bar = TwNewBar("MENU");
	TwDefine(" MENU size='220 520' color='0 0 0' ");

	TwAddVarRW(bar, "", objectType, &iCurrentObject, "label='Object' group='Dark Raven Engine'");
	TwAddVarRO(bar, "", TW_TYPE_DOUBLE, &fFPS, "label='FPS' precision=2 group='Dark Raven Engine'");
	TwAddVarRW(bar, "", TW_TYPE_BOOLCPP, &bGrid, "label='Show grid' group='Dark Raven Engine'");

	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vCamPos.x, "label='Cam Pos X' min=-180 max=180 step=0.5 group='Camera Position'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vCamPos.y, "label='Cam Pos Y' min=-180 max=180 step=0.5 group='Camera Position'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vCamPos.z, "label='Cam Pos Z' min=-180 max=180 step=0.5 group='Camera Position'");

	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &fAngleX, "label='Cam Rot X' min=-360 max=360 step=0.5 group='Camera Rotation'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &fAngleY, "label='Cam Rot Y' min=-360 max=360 step=0.5 group='Camera Rotation'");

	TwAddVarRW(bar, "", TW_TYPE_INT32, &iSpec, "label='Spec' min=0.0 max=512 step=1 group='Spot Light'");

	TwAddVarRW(bar, "", TW_TYPE_COLOR4F, &vColObj, "label='Color' group='Material' opened=true");

	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vRotObj.x, "label='Rotate X' min=0 max=359 step=1 group='Object Rotate' ");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vRotObj.y, "label='Rotate Y' min=0 max=359 step=1 group='Object Rotate' ");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vRotObj.z, "label='Rotate Z' min=0 max=359 step=1 group='Object Rotate' ");

	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vPosObj.x, "label='Position X' min=-10 max=10 step=0.01 group='Object Position'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vPosObj.y, "label='Position Y' min=-10 max=10 step=0.01 group='Object Position'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vPosObj.z, "label='Position Z' min=-10 max=10 step=0.01 group='Object Position'");

	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vScaObj.x, "label='Scale X' min=0 max=10 step=0.01 group='Object Scale'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vScaObj.y, "label='Scale Y' min=0 max=10 step=0.01 group='Object Scale'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vScaObj.z, "label='Scale Z' min=0 max=10 step=0.01 group='Object Scale'");

	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);

	glutMainLoop();

	return 0;
}