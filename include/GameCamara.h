#ifndef GAMECAMARA_H
#define GAMECAMARA_H

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION // Apple
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


class GameCamara
{
    public:
        GameCamara();
        virtual ~GameCamara();
        void renderGameCamera();
        void toggleMouseWarp();

        // callback function
        void changeSize(int w, int h);
        void mousePosition(int x, int y);

        // Getter and Setter
        void goForwardStart();
        void goForwardStop();
        void goBackwardStart();
        void goBackwardStop();
        void goLeftStart();
        void goLeftStop();
        void goRigthStart();
        void goRigthStop();

        float mouseDirectionX;
        float mouseDirectionY;

    protected:

    private:
      GLfloat EYE_X, EYE_Y, EYE_Z;
      GLfloat CENTER_X, CENTER_Y, CENTER_Z;
      GLfloat UP_X, UP_Y, UP_Z;

      // Variable de pantalla
      int	ANCHO, ALTO;
    	int PREVIUSTIME;

    	//
    	float moveforward_backward;
    	float moveSiteward;

    	//Status Variablen
      bool FORWARD, BACKWARD, LEFT, RIGTH;

    	bool mouseWarp;

};

#endif // GAMECAMARA_H
