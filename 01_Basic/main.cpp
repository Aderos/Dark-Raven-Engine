#include <AntTweakBar.h>

#include "FramePerSecond.h"
#include "ShaderManager.h"
#include "Object3D.h"
#include "Pipeline.h"
#include "Texture.h"
#include "OpenGL.h"
#include "Logo.h"
#include "Grid.h"

using namespace std;

#define NUM_SHADER 3
enum { BASIC = 0, COLOR, DISSOLVE };

ShaderManager* m_Shader;
FramePerSecond* m_FPS;
Pipeline* m_Pipeline;
Object3D* m_Obj[1];
OpenGL* m_OpenGL;
Logo* m_Logo;
Grid* m_Grid;
TwBar* bar;

GLuint iTexture;

Math::Vector4f vColObj;
Math::Vector3f vCamPos;
Math::Vector3f vPosObj;
Math::Vector3f vRotObj;
Math::Vector3f vScaObj;

float fDissolve;
float fAngleX;
float fAngleY;

int iCurrentShader;

bool bGrid;

double fFPS;

void Initialize()
{
	m_OpenGL = new OpenGL;
	m_OpenGL->Initialize(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR, VSYNC_ENABLED);

	m_Pipeline = new Pipeline(m_OpenGL);
	m_Pipeline->Initialize(45.0f, 1.0f, 1000.0f);
	m_Pipeline->SetCameraPosition(Vector3f(0.0f, 0.0f, -8.0f));
	m_Pipeline->SetCameraAngleX(5.0f);
	m_Pipeline->SetCameraAngleY(0.0f); 

	fAngleX = m_Pipeline->GetCameraAngleX();
	fAngleY = m_Pipeline->GetCameraAngleY();
	vCamPos = m_Pipeline->GetCameraPosition();

	m_Shader = new ShaderManager(m_OpenGL);
	m_Shader->Initialize();
	iCurrentShader = DISSOLVE;

	m_FPS = new FramePerSecond();
	fFPS = m_FPS->GetFPS();

	m_Logo = new Logo(m_OpenGL, m_Shader);
	m_Logo->Initialize((int)m_OpenGL->GetScreenWidth() - 80, (int)m_OpenGL->GetScreenHeight() - 80, 60, 60, "../Assets/Raven.tga");

	m_Grid = new Grid(m_OpenGL, m_Shader);
	m_Grid->Initialize();
	m_Grid->SetScale(Vector3f(0.4f));
	bGrid = true;

	m_Obj[0] = new Object3D(m_OpenGL);
	m_Obj[0]->Initialize("../Assets/Plane.obj", "../Assets/Plane.bmp");
	m_Obj[0]->SetPosition(Vector3f(0.0f, 0.0f, 0.0f));
	m_Obj[0]->SetScale(Vector3f(1.0f, 1.0f, 1.0f));
	m_Obj[0]->SetRotate(Vector3f(90.0f, 0.0f, 0.0f));

	vPosObj = m_Obj[0]->GetPosition();
	vScaObj = m_Obj[0]->GetScale();
	vRotObj = m_Obj[0]->GetRotate();
	vColObj = Math::Vector4f(0.0f, 0.5f, 1.0f, 1.0f);

	iTexture = (new Texture(m_OpenGL))->GetTexture2D("../Assets/Dissolve.bmp");
}

void Display(void)
{
	m_OpenGL->BeginScene(0.1f, 0.1f, 0.1f, 1.0f);

	if (vCamPos != m_Pipeline->GetCameraPosition()) { m_Pipeline->SetCameraPosition(vCamPos); }
	if (fAngleX != m_Pipeline->GetCameraAngleX())	{ m_Pipeline->SetCameraAngleX(fAngleX); }
	if (fAngleY != m_Pipeline->GetCameraAngleY())	{ m_Pipeline->SetCameraAngleY(fAngleY); }

	if (vPosObj != m_Obj[0]->GetPosition()) { m_Obj[0]->SetPosition(vPosObj); }
	if (vRotObj != m_Obj[0]->GetRotate())   { m_Obj[0]->SetRotate(vRotObj); }
	if (vScaObj != m_Obj[0]->GetScale())    { m_Obj[0]->SetScale(vScaObj); }

	Matrix44f mMVP = m_Pipeline->GetViewProjectionMatrix() * m_Obj[0]->GetWorldMatrix();

	if(bGrid)
		m_Grid->Draw(m_Pipeline->GetViewProjectionMatrix());

	switch (iCurrentShader)
	{
		case BASIC: m_Shader->UseShader(GLT_BASIC_SHADER, mMVP); break;
		case COLOR: m_Shader->UseShader(GLT_COLOR_SHADER, mMVP, vColObj); break;
		case DISSOLVE: m_Shader->UseShader(GLT_DISSOLVE_SHADER, mMVP, vColObj, fDissolve, iTexture); break;
	}
	
	m_Obj[0]->Draw();

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

	TwEnumVal shaderEV[NUM_SHADER] =
	{
		{ BASIC, "Basic" },
		{ COLOR, "Color" },
		{ DISSOLVE, "Dissolve" }
	};
	TwType shaderType = TwDefineEnum("ShaderType", shaderEV, NUM_SHADER);

	bar = TwNewBar("MENU");
	TwDefine(" MENU size='220 520' color='0 0 0' ");

	TwAddVarRW(bar, "", shaderType, &iCurrentShader, "label='Shader' group='Dark Raven Engine'");
	TwAddVarRO(bar, "", TW_TYPE_DOUBLE, &fFPS, "label='FPS' precision=2 group='Dark Raven Engine'");
	TwAddVarRW(bar, "", TW_TYPE_BOOLCPP, &bGrid, "label='Show grid' group='Dark Raven Engine'");

	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vCamPos.x, "label='Cam Pos X' min=-180 max=180 step=0.5 group='Camera Position'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vCamPos.y, "label='Cam Pos Y' min=-180 max=180 step=0.5 group='Camera Position'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &vCamPos.z, "label='Cam Pos Z' min=-180 max=180 step=0.5 group='Camera Position'");

	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &fAngleX, "label='Cam Rot X' min=-360 max=360 step=0.5 group='Camera Rotation'");
	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &fAngleY, "label='Cam Rot Y' min=-360 max=360 step=0.5 group='Camera Rotation'");

	TwAddVarRW(bar, "", TW_TYPE_COLOR4F, &vColObj	, "label='Color' group='Material' opened=true");

	TwAddVarRW(bar, "", TW_TYPE_FLOAT, &fDissolve, "label='Dissolve' min=0 max=1 step=0.01 group='Object Dissolve' ");
	
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