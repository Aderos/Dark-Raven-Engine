#include <AntTweakBar.h>
#include <cstdio>
#include <vector>

#include "GL/freeglut.h"
#include "OpenGL.h"
#include "Logo.h"
#include "ShaderManager.h"
#include "FramePerSecond.h"
#include "ShadowView.h"
#include "Grid.h"
#include "Pipeline.h"
#include "Object3D.h"
#include "Object2D.h"
#include "FBO.h"

#define NUM_OBJ 3

enum { PLANE, MONKEY, WALL };

using namespace std;

int CModel = PLANE;

ShaderManager* m_Shader;
ShadowView* m_View;
Pipeline* m_Pipeline;
Object3D* m_Obj[3];
OpenGL* m_OpenGL;
Logo* m_Logo;
//Object2D* m_ViewFBO;
TwBar* bar;
FBO* m_FBO;

FramePerSecond* m_FPS;
Grid* m_Grid;

Vector4f vColor;
Vector3f vCameraPosition;
Vector3f vCameraRotation;
Vector3f vLight;

int OldModel;

Math::Vector3f vCamPos;
Math::Vector3f vPosObj;
Math::Vector3f vRotObj;
Math::Vector3f vScaObj;

float fAngleX;
float fAngleY;

double dFPS;

bool bGrid;

void Initialize()
{
	m_OpenGL = new OpenGL;
	m_OpenGL->Initialize(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR, VSYNC_ENABLED);

	m_Pipeline = new Pipeline(m_OpenGL);
	m_Pipeline->Initialize(45.0f, 1.0f, 100.0f);
	m_Pipeline->SetCameraPosition(Vector3f(0.0f, 0.0f, -18.0f));
	m_Pipeline->SetCameraAngleX(5.0f);
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

	m_View = new ShadowView(m_OpenGL, m_Shader);
	m_View->Initialize((int)m_OpenGL->GetScreenWidth() - 220, 4, 200, 150);
	m_View->SetTexture("plane.bmp");

	m_Grid = new Grid(m_OpenGL, m_Shader);
	m_Grid->Initialize();
	m_Grid->SetScale(Vector3f(0.4f));
	bGrid = true;

	m_Obj[0] = new Object3D(m_OpenGL);
	m_Obj[0]->Initialize("../Assets/Plane.obj", "../Assets/Plane.bmp");
	m_Obj[0]->SetPosition(Vector3f(0.0f, -0.1f, 0.0f));
	m_Obj[0]->SetRotate(Vector3f(0.0f, 0.0f, 0.0f));
	m_Obj[0]->SetScale(Vector3f(6.5f, 4.5f, 4.5f));

	m_Obj[1] = new Object3D(m_OpenGL);
	m_Obj[1]->Initialize("../Assets/Cube.obj", "../Assets/Cube.bmp");
	m_Obj[1]->SetPosition(Vector3f(0.0f, 1.2f, 0.0f));
	m_Obj[1]->SetRotate(Vector3f(0.0f, 0.0f, 0.0f));
	m_Obj[1]->SetScale(Vector3f(1.0f, 1.0f, 1.0f));

	m_Obj[2] = new Object3D(m_OpenGL);
	m_Obj[2]->Initialize("../Assets/Plane.obj", "../Assets/Plane.bmp");
	m_Obj[2]->SetPosition(Vector3f(0.0f, 2.9f, -4.5f));
	m_Obj[2]->SetRotate(Vector3f(90.0f, 0.0f, 0.0f));
	m_Obj[2]->SetScale(Vector3f(6.5f, 4.5f, 3.0f));

	OldModel = CModel;
	vPosObj = m_Obj[CModel]->GetPosition();
	vRotObj = m_Obj[CModel]->GetRotate();
	vScaObj = m_Obj[CModel]->GetScale();
	vLight = Vector3f(-20.0, 20.0, 5.0f);
	vColor = Vector4f(0.0f, 0.5f, 1.0f, 1.0f);

	m_FBO = new FBO(m_OpenGL);
	m_FBO->Initialize();
	m_FBO->DepthBuffer();
	m_FBO->CheckBuffer();

	//m_ViewFBO = new Object2D(m_OpenGL, m_Shader);
	//m_ViewFBO->Initialize((int)m_OpenGL->GetScreenWidth() - 220, 4, 200, 150);
	//m_ViewFBO->SetTexture("plane.bmp");
}

void Display(void)
{
	if (OldModel != CModel)
	{
		vPosObj = m_Obj[CModel]->GetPosition();
		vScaObj = m_Obj[CModel]->GetScale();
		vRotObj = m_Obj[CModel]->GetRotate();
	}

	if (vPosObj != m_Obj[CModel]->GetPosition()) { m_Obj[CModel]->SetPosition(vPosObj); }
	if (vScaObj != m_Obj[CModel]->GetScale())    { m_Obj[CModel]->SetScale(vScaObj); }
	if (vRotObj != m_Obj[CModel]->GetRotate())   { m_Obj[CModel]->SetRotate(vRotObj); }

	// Depth Scene
	m_FBO->Begin();
	m_OpenGL->BeginScene(0.1f, 0.1f, 0.1f, 1.0f);

	//m_Pipeline->SetCameraLookAt(-vLight, Vector3f(1.0f, -1.0f, 0.0f), Vector3f(0.0f, 1.0f, 0.0f));
	m_Pipeline->SetCameraAngleX(0.0f);
	m_Pipeline->SetCameraAngleY(0.0f);
	m_Pipeline->SetCameraPosition(Vector3f(0.0f, -1.0f, vCamPos.z));
	vLight = Vector3f(0.0f, -1.0f, vCamPos.z);

	m_Shader->UseShader(GLT_BASIC_SHADER, m_Pipeline->GetViewProjectionMatrix() * m_Obj[0]->GetWorldMatrix());
	m_Obj[0]->Draw();

	m_Shader->UseShader(GLT_BASIC_SHADER, m_Pipeline->GetViewProjectionMatrix() * m_Obj[1]->GetWorldMatrix());
	m_Obj[1]->Draw();

	m_Shader->UseShader(GLT_BASIC_SHADER, m_Pipeline->GetViewProjectionMatrix() * m_Obj[2]->GetWorldMatrix());
	m_Obj[2]->Draw();

	m_FBO->End();

	// Normal Scene
	
	if (vCamPos != m_Pipeline->GetCameraPosition()) { m_Pipeline->SetCameraPosition(vCamPos); }
	if (fAngleX != m_Pipeline->GetCameraAngleX()) { m_Pipeline->SetCameraAngleX(fAngleX); }
	if (fAngleY != m_Pipeline->GetCameraAngleY()) { m_Pipeline->SetCameraAngleY(fAngleY); }

	m_OpenGL->BeginScene(0.1f, 0.1f, 0.1f, 1.0f);
	
	//if (bGrid)
	//	m_Grid->Draw(m_Pipeline->GetViewProjectionMatrix());

	m_Shader->UseShader(GLT_SHADOW_MAPPING_SHADER, m_Pipeline->GetViewProjectionMatrix() * m_Obj[0]->GetWorldMatrix(), m_Obj[0]->GetWorldMatrix(), vLight, m_FBO->GetDepthTexture());
	m_Obj[0]->Draw();

	m_Shader->UseShader(GLT_SHADOW_MAPPING_SHADER, m_Pipeline->GetViewProjectionMatrix() * m_Obj[1]->GetWorldMatrix(), m_Obj[0]->GetWorldMatrix(), vLight, m_FBO->GetDepthTexture());
	m_Obj[1]->Draw();

	m_Shader->UseShader(GLT_SHADOW_MAPPING_SHADER, m_Pipeline->GetViewProjectionMatrix() * m_Obj[2]->GetWorldMatrix(), m_Obj[0]->GetWorldMatrix(), vLight, m_FBO->GetDepthTexture());
	m_Obj[2]->Draw();
	
	// Rest
	m_View->SetTexture(m_FBO->GetDepthTexture());
	m_View->Draw();

	TwDraw();

	m_Logo->Draw();
	m_OpenGL->EndScene();

	dFPS = m_FPS->GetFPS();

	TwRefreshBar(bar);

	OldModel = CModel;
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

	TwEnumVal objEV[NUM_OBJ] =
	{
		{ PLANE, "Plane" },
		{ MONKEY, "Monkey" },
		{ WALL, "Wall" }
	};
	TwType objType = TwDefineEnum("ObjectType", objEV, NUM_OBJ);

	bar = TwNewBar("MENU");
	TwDefine(" MENU size='220 540' color='0 0 0' ");

	TwAddVarRW(bar, "Object", objType, &CModel, "");
	
	TwAddVarRO(bar, "", TW_TYPE_DOUBLE, &dFPS, "label='FPS' precision=2 group='Dark Raven Engine'");
	TwAddVarRW(bar, "", TW_TYPE_BOOLCPP, &bGrid, "label='Show grid' group='Dark Raven Engine'");

	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vCamPos.x, "label='Cam Pos X' min=-180 max=180 step=0.5 group='Camera Position'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vCamPos.y, "label='Cam Pos Y' min=-180 max=180 step=0.5 group='Camera Position'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vCamPos.z, "label='Cam Pos Z' min=-180 max=180 step=0.5 group='Camera Position'");

	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &fAngleX, "label='Cam Rot X' min=-360 max=360 step=0.5 group='Camera Rotation'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &fAngleY, "label='Cam Rot Y' min=-360 max=360 step=0.5 group='Camera Rotation'");

	TwAddVarRW(bar, "", TW_TYPE_DIR3F, &vLight, "label='Direction' opened=true group='Light'");

	TwAddVarRW(bar, "", TW_TYPE_COLOR4F, &vColor, "label='Ambient' group='Material'");
	
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