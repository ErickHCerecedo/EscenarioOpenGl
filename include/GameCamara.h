#ifndef GAMECAMARA_H
#define GAMECAMARA_H

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include "math.h"


class GameCamara
{
    public:
        GameCamara();
        virtual ~GameCamara();

        // Inicio del escenario
        void init(int argc, char **argv);
        void initLight();
        void resize(int width, int height);
        // Camara
        void renderGameCamera();
        // Control de Mouse
        void toggleMouseWarp();
        void mousePosition(int x, int y);
        // Control de Teclado
        void key(unsigned char key, int x, int y);
        void keyup(unsigned char key, int x, int y);
        // Control de estados
        void goForwardStart();
      	void goForwardStop();
      	void goBackwardStart();
      	void goBackwardStop();
      	void goLeftStart();
      	void goLeftStop();
      	void goRightStart();
      	void goRightStop();
        // Variables de direccion del mouse
        float mouseDirectionX;
      	float mouseDirectionY;
        float ANGLE;
        
    protected:

    private:

      // Tamaño de la pantalla
      GLint ANCHO, ALTO;
      // Variables del observador
      float EYE_X;
      float EYE_Y;
      float EYE_Z;
      float CENTER_X;
      float CENTER_Y;
      float CENTER_Z;
      float UP_X;
      float UP_Y;
      float UP_Z;
      // Variables de perspectiva
      GLfloat FOVY;
      GLfloat ZNEAR;
      GLfloat ZFAR;
      // Variables de estado
      bool FORWARD;
      bool BACKWARD;
      bool LEFT;
      bool RIGHT;
      // Variable mouse
      bool mouseWarp;
      // Variable tiempo
      int PREVIOUSTIME;
      float moveforward_backward;
		  float moveSiteward;

};

#endif // GAMECAMARA_H
