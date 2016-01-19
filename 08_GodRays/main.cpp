#include <AntTweakBar.h>

#include "FramePerSecond.h"
#include "ShaderManager.h"
#include "Object3D.h"
#include "Pipeline.h"
#include "Godrays.h"
#include "OpenGL.h"
#include "Logo.h"
#include "Grid.h"
#include "FBO.h"

using namespace std;

ShaderManager* m_Shader;
FramePerSecond* m_FPS;
Pipeline* m_Pipeline;
Object2D* m_ViewFBO;
Object3D* m_Obj[1];
OpenGL* m_OpenGL;
Godrays* m_God;
FBO* m_FBO[2]; 
Logo* m_Logo;
Grid* m_Grid;
TwBar* bar;

Math::Vector4f vColor;
Math::Vector3f vCamPos;
Math::Vector3f vPosObj;
Math::Vector3f vRotObj;
Math::Vector3f vScaObj;
Math::Vector3f vPosSun;
Math::Vector3f vScaSun;
Math::Vector3f vColSun;

float fAngleX;
float fAngleY;
float fDissolve;

double dExposure;
double dDensity;
double dWeight;
double dDecay;
double dFPS;

bool bGrid;

void Initialize()
{
	m_OpenGL = new OpenGL;
	m_OpenGL->Initialize(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR, VSYNC_ENABLED);

	m_Pipeline = new Pipeline(m_OpenGL);
	m_Pipeline->Initialize(45.0f, 1.0f, 100.0f);
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

	m_Obj[0] = new Object3D(m_OpenGL);
	m_Obj[0]->Initialize("../Assets/Plane.obj", "../Assets/Plane.bmp");
	m_Obj[0]->SetHeightTexture("../Assets/Dissolve.bmp");
	m_Obj[0]->SetPosition(Vector3f(0.0f, 0.0f, 0.0f));
	m_Obj[0]->SetScale(Vector3f(1));
	m_Obj[0]->SetRotate(Vector3f(90.0f, 0.0f, 0.0f));

	vPosObj = m_Obj[0]->GetPosition();
	vScaObj = m_Obj[0]->GetScale();
	vRotObj = m_Obj[0]->GetRotate();
	
	m_FBO[0] = new FBO(m_OpenGL);
	m_FBO[0]->Initialize();
	m_FBO[0]->ColorBuffer();
	m_FBO[0]->CheckBuffer();

	m_FBO[1] = new FBO(m_OpenGL);
	m_FBO[1]->Initialize();
	m_FBO[1]->ColorBuffer();
	m_FBO[1]->CheckBuffer();

	m_ViewFBO = new Object2D(m_OpenGL, m_Shader);
	m_ViewFBO->Initialize(0, 0, (int)m_OpenGL->GetScreenWidth(), (int)m_OpenGL->GetScreenHeight());

	m_God = new Godrays(m_OpenGL, m_Shader);
	m_God->Initialize((int)m_OpenGL->GetScreenWidth(), (int)m_OpenGL->GetScreenHeight());
	m_God->SetPosition(Vector3f(0.0f, 0.0f, -6.0f));
	m_God->SetScale(Vector3f(3.0f));
	m_God->SetRotate(Vector3f(0.0f));
	m_God->SetColor(Vector3f(1.0f));

	vPosSun = m_God->GetPosition();
	vScaSun = m_God->GetScale();
	vColSun = m_God->GetColor();

	vColor = Math::Vector4f(0.0f, 0.5f, 1.0f, 1.0f);

	fDissolve = 0.2f;

	dExposure = 0.2;
	dDensity = 0.926;
	dWeight = 0.58767;
	dDecay = 0.96815;
}

void Display(void)
{
	if (vCamPos != m_Pipeline->GetCameraPosition()) { m_Pipeline->SetCameraPosition(vCamPos); }
	if (fAngleX != m_Pipeline->GetCameraAngleX())	{ m_Pipeline->SetCameraAngleX(fAngleX); }
	if (fAngleY != m_Pipeline->GetCameraAngleY())	{ m_Pipeline->SetCameraAngleY(fAngleY); }

	if (vPosObj != m_Obj[0]->GetPosition()) { m_Obj[0]->SetPosition(vPosObj); }
	if (vRotObj != m_Obj[0]->GetRotate())   { m_Obj[0]->SetRotate(vRotObj); }
	if (vScaObj != m_Obj[0]->GetScale())    { m_Obj[0]->SetScale(vScaObj); }

	if (vPosSun != m_God->GetPosition()) { m_God->SetPosition(vPosSun); }
	if (vScaSun != m_God->GetScale())	 { m_God->SetScale(vScaSun); }
	if (vColSun != m_God->GetColor())	 { m_God->SetColor(vColSun); }

	Matrix44f mMVP = m_Pipeline->GetViewProjectionMatrix() * m_Obj[0]->GetWorldMatrix();

	// Black
	m_FBO[0]->Begin();
	m_OpenGL->BeginScene(0.1f, 0.1f, 0.1f, 0.0f);
	m_God->DrawSun(m_Pipeline->GetViewProjectionMatrix());

	//m_Shader->UseShader(GLT_DISSOLVE_SHADER, mMVP, Vector4f(0.0f, 0.0f, 0.0f, 1.0f), fDissolve, m_Obj[0]->GetHeightTexture());
	//m_Obj[0]->Draw();

	m_FBO[0]->End();

	// Color
	//m_FBO[1]->Begin();
	//m_OpenGL->BeginScene(0.1f, 0.1f, 0.1f, 0.0f);

	//m_Shader->UseShader(GLT_DISSOLVE_SHADER, mMVP, vColor, fDissolve, m_Obj[0]->GetHeightTexture());
	//m_Obj[0]->Draw();

	//if (bGrid)
	//	m_Grid->Draw(m_Pipeline->GetViewProjectionMatrix());

	//m_FBO[1]->End();

	// Blend finish
	m_OpenGL->EnableBlend();
	m_OpenGL->BeginScene(0.1f, 0.1f, 0.1f, 1.0f);

	m_God->SetTexture(m_FBO[0]->GetColorTexture());
	m_God->SetWeight(dWeight);
	m_God->SetDensity(dDensity);
	m_God->SetExposure(dExposure);
	m_God->SetDecay(dDecay);
	m_God->DrawGod(m_Pipeline->GetViewProjectionMatrix(), m_Pipeline->GetCameraPosition());

	//m_ViewFBO->SetTexture(m_FBO[0]->GetColorTexture());
	//m_ViewFBO->Draw();
	
	m_OpenGL->DisableBlend();

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

	m_Pipeline->CameraKeyboard(key, x, y);

	vCamPos = m_Pipeline->GetCameraPosition();
	fAngleX = m_Pipeline->GetCameraAngleX();
	fAngleY = m_Pipeline->GetCameraAngleY();

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

	bar = TwNewBar("MENU");
	TwDefine(" MENU size='220 660' color='0 0 0' ");

	TwAddVarRO(bar, "", TW_TYPE_DOUBLE, &dFPS, "label='FPS' precision=2 group='Dark Raven Engine'");
	TwAddVarRW(bar, "", TW_TYPE_BOOLCPP, &bGrid, "label='Grid' group='Dark Raven Engine'");
	
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vCamPos.x, "label='Cam Pos X' min=-180 max=180 step=0.5 group='Camera Position'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vCamPos.y, "label='Cam Pos Y' min=-180 max=180 step=0.5 group='Camera Position'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vCamPos.z, "label='Cam Pos Z' min=-180 max=180 step=0.5 group='Camera Position'");

	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &fAngleX, "label='Cam Rot X' min=-360 max=360 step=0.5 group='Camera Rotation'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &fAngleY, "label='Cam Rot Y' min=-360 max=360 step=0.5 group='Camera Rotation'");

	TwAddVarRW(bar, "", TW_TYPE_COLOR4F, &vColor, "label='Color' group='Material' opened=true");

	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &fDissolve, "label='Dissolve' min=0 max=1 step=0.01 group='Object Dissolve' ");

	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vPosSun.x, "label='Sun Pos X' min=-180 max=180 step=0.5 group='Sun'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vPosSun.y, "label='Sun Pos Y' min=-180 max=180 step=0.5 group='Sun'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vPosSun.z, "label='Sun Pos Z' min=-180 max=180 step=0.5 group='Sun'");

	TwAddVarRW(bar, "", TW_TYPE_DOUBLE, &dExposure, "label='Exposure' min=0 max=5 step=0.01 group='Object Godrays' ");
	TwAddVarRW(bar, "", TW_TYPE_DOUBLE, &dDecay, "label='Decay' min=0 max=5 step=0.01 group='Object Godrays' ");
	TwAddVarRW(bar, "", TW_TYPE_DOUBLE, &dDensity, "label='Density' min=0 max=5 step=0.01 group='Object Godrays' ");
	TwAddVarRW(bar, "", TW_TYPE_DOUBLE, &dWeight, "label='Weight' min=0 max=5 step=0.01 group='Object Godrays' ");
	TwAddVarRW(bar, "", TW_TYPE_COLOR3F, &vColSun, "label='Color' group='Object Godrays' opened=true");

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