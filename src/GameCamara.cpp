#include "GameCamara.h"

GameCamara::GameCamara()
{
  // Define el tamaño de la pantalla
  ANCHO=1280;
  ALTO=720;
  // Inicio de variables del observador
  EYE_X=0.0;
  EYE_Y=0.0;
  EYE_Z=0.0;
  CENTER_X=10;
  CENTER_Y=10;
  CENTER_Z=10;
  UP_X=0;
  UP_Y=1;
  UP_Z=0;
  // Inicio de la variable de perspectiva
  FOVY = 90.0;
  ZNEAR = 0.01;
  ZFAR=2000.0;
  // Inicio del estado del observador
  FORWARD=false;
  BACKWARD=false;
  LEFT=false;
  RIGHT=false;
  // TIME
  PREVIOUSTIME=0;
  moveforward_backward = 50.0f;
	moveSiteward = 30.0f;
  ANGLE=0.0f;
  mouseWarp=true;
}

GameCamara::~GameCamara()
{
    //dtor
}

void GameCamara::init(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(10, 10);
  glutInitWindowSize(ANCHO, ALTO);
  glutCreateWindow("Planetario");

  glClearColor(0.604, 0.788, 0.996, 1);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);
  initLight();
}

void GameCamara::initLight()
{
  // Constantes de Luz
  const GLfloat light_ambient[]  = { 0.8f, 0.8f, 0.8f, 1.0f };
  const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
  const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  const GLfloat light_position[] = { 500.0f, 500.0f, 500.0f, 0.0f };

  const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
  const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
  const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
  const GLfloat high_shininess[] = { 128.0f };

  //glClearColor(0.349, 0.62, 0.929,1);
  //glEnable(GL_CULL_FACE);
  //glCullFace(GL_BACK);

  //glEnable(GL_DEPTH_TEST);
  //glDepthFunc(GL_LESS);

  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);

  glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glShadeModel(GL_FLAT);
}

void GameCamara::resize(int width, int height)
{
  ANCHO=width;
  ALTO=height;
  glViewport(0, 0, ANCHO, ALTO);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(FOVY, (GLfloat)ANCHO/(GLfloat)ALTO, ZNEAR, ZFAR);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(EYE_X,EYE_Y,EYE_Z,CENTER_X,CENTER_Y,CENTER_Z,UP_X,UP_Y,UP_Z);
}

void GameCamara::renderGameCamera()
{
  int CURRENTTIME = glutGet(GLUT_ELAPSED_TIME);
	int TIMEINTERVAL = CURRENTTIME - PREVIOUSTIME;

  //Berechne Blickrichtung
  GLdouble DIR_X, DIR_Y, DIR_Z;

  DIR_X = sin(mouseDirectionY*M_PI/180)*sin(mouseDirectionX*M_PI/180);
  DIR_Z = sin(mouseDirectionY*M_PI/180)*cos(mouseDirectionX*M_PI/180);
  DIR_Y = cos(mouseDirectionY*M_PI/180);

  //Bewegung Berechnen
  if(FORWARD)
  {
    EYE_X += TIMEINTERVAL * DIR_X / 10;
  	EYE_Y += TIMEINTERVAL * DIR_Y / 10;
  	EYE_Z += TIMEINTERVAL * DIR_Z / 10;
  }
  if(BACKWARD)
  {
  	EYE_Z -= TIMEINTERVAL * DIR_Z / 10;
  	EYE_Y -= TIMEINTERVAL * DIR_Y / 10;
  	EYE_X -= TIMEINTERVAL * DIR_X / 10;
  }
  if(LEFT)
  {
  	EYE_X += TIMEINTERVAL * sin((mouseDirectionX+90)*M_PI/180) / 10;
  	EYE_Z += TIMEINTERVAL * cos((mouseDirectionX+90)*M_PI/180) / 10;
  }
  if(RIGHT)
  {
  	EYE_X -= TIMEINTERVAL * sin((mouseDirectionX+90)*M_PI/180) / 10;
  	EYE_Z -= TIMEINTERVAL * cos((mouseDirectionX+90)*M_PI/180) / 10;
  }

  PREVIOUSTIME = CURRENTTIME;
  glLoadIdentity();
  CENTER_X = EYE_X + DIR_X;
  CENTER_Y = EYE_Y + DIR_Y;
  CENTER_Z = EYE_Z + DIR_Z;
  gluLookAt(EYE_X,EYE_Y,EYE_Z,CENTER_X,CENTER_Y,CENTER_Z,UP_X,UP_Y,UP_Z);

  if(mouseWarp)
			glutWarpPointer(this->ANCHO / 2, this->ALTO / 2);
}

void GameCamara::mousePosition(int x, int y)
{
  if(mouseWarp)
		{
			mouseDirectionX -= (x - this->ANCHO/2) * 0.1f;
			mouseDirectionY += (y - this->ALTO/2) * 0.1f;
			if(mouseDirectionY > 180) mouseDirectionY = 180;
			else if(mouseDirectionY < 0) mouseDirectionY = 0;
		}
}

void GameCamara::toggleMouseWarp()
{
  mouseWarp = !mouseWarp;
}

void GameCamara::key(unsigned char key, int x, int y)
{
  switch(key)
	{
    case 'W':
		case 'w':
			goForwardStart();
			break;

    case 'S':
		case 's':
			goBackwardStart();
			break;

    case 'A':
		case 'a':
			goLeftStart();
			break;

    case 'D':
		case 'd':
			goRightStart();
			break;

    case 'P':
		case 'p':
			toggleMouseWarp();
			break;

		case 27:
			exit(0);
			break;

	}
}

void GameCamara::keyup(unsigned char key, int x, int y)
{
  switch(key)
	{
    case 'W':
		case 'w':
			goForwardStop();
			break;

    case 'S':
		case 's':
			goBackwardStop();
			break;

    case 'A':
		case 'a':
			goLeftStop();
			break;

    case 'D':
		case 'd':
			goRightStop();
			break;

		case 27:
			exit(0);
			break;

	}
}

void GameCamara::goForwardStart()
{
  FORWARD=true;
}

void GameCamara::goForwardStop()
{
  FORWARD=false;
}

void GameCamara::goBackwardStart()
{
  BACKWARD=true;
}

void GameCamara::goBackwardStop()
{
  BACKWARD=false;
}

void GameCamara::goLeftStart()
{
  LEFT=true;
}

void GameCamara::goLeftStop()
{
  LEFT=false;
}

void GameCamara::goRightStart()
{
  RIGHT=true;
}

void GameCamara::goRightStop()
{
  RIGHT=false;
}







//
