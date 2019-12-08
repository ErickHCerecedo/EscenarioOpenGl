//
//  main.cpp
//  SistemaSolarErick
//
//  Created by Erick de Jesus Hernandez Cerecedo on 11/12/19.
//  Copyright � 2019 Erick de Jesus Hernandez Cerecedo. All rights reserved.
//


#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/freeglut.h>
#endif

#include <GL/glext.h>
#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "FreeImage.h"

#include "GameCamara.h"

GameCamara *gameCamara;

//se define la cantidad de texturas que se manejaran
#define NTextures 2
GLuint	texture[NTextures];
//variables para manejo de texturas
char *texturefiles[] = {
  "C:/Users/erick/Documents/CodeBlocks_Projects/ProyectoFinal/imagen3.bmp",
	"C:/Users/erick/Documents/CodeBlocks_Projects/ProyectoFinal/imagen1.bmp",
	"C:/Users/erick/Documents/CodeBlocks_Projects/ProyectoFinal/imagen2.bmp",
};

float points[5][3]={{0,0,10},{10,0,10},{10,0,0},{0,0,0},{5.0,10.0,5.0}};


bool readImage()
{
  	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0), *dib_copy(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);
	int i=0;
	while(i < NTextures){
        //check the file signature and deduce its format
        fif = FreeImage_GetFileType(texturefiles[i], 0);
        //if still unknown, try to guess the file format from the file extension
        if(fif == FIF_UNKNOWN)
            fif = FreeImage_GetFIFFromFilename(texturefiles[i]);
        //if still unkown, return failure
        if(fif == FIF_UNKNOWN){
                printf("exit 0\n");
            return false;
        }
        //check that the plugin has reading capabilities and load the file
        if(FreeImage_FIFSupportsReading(fif)){
                printf("reading image...\n");
            dib = FreeImage_Load(fif, texturefiles[i], BMP_DEFAULT);
        }
        //if the image failed to load, return failure
        if(!dib){
                printf("exit 1\n");
            return false;
        }
        //conversion to 24 bit deep color
        dib_copy = FreeImage_ConvertTo32Bits(dib);
        FreeImage_Unload(dib);
        dib = dib_copy;

        //TEXTURE GENERATION

        //retrieve the image data
        bits = FreeImage_GetBits(dib);
        //get the image width and height
        width = FreeImage_GetWidth(dib);
        height = FreeImage_GetHeight(dib);
        //if this somehow one of these failed (they shouldn't), return failure
        if((bits == 0) || (width == 0) || (height == 0))
            return false;

        //generate an OpenGL texture ID for this texture
        glGenTextures(1, &texture[i]);
        //bind to the new texture ID
        glBindTexture(GL_TEXTURE_2D, texture[i]);
        //store the texture data for OpenGL use
        // ** AGREGADO ** (filtros para la textura y condicional de mipmap) //
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0,
                     GL_BGRA, GL_UNSIGNED_BYTE, bits);

        //Free FreeImage's copy of the data
        FreeImage_Unload(dib);
        i++;
	}

	//return success
	return true;
}

void ImprimePiramide(int escala)
{
    glPushMatrix();
    glScalef(escala,escala,escala);
    int i;

    //activa la textura
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glColor3ub(255, 255, 255);

       //se dibuja la punta
       for(i=0;i<3;i++){
          glBegin(GL_TRIANGLES);
             glTexCoord2f(0.0f,0.5f);
             glVertex3f(points[4][0],points[4][1],points[4][2]);
             glTexCoord2f(0.0f,1.0f);
             glVertex3f(points[i][0],points[i][1],points[i][2]);
             glTexCoord2f(1.0f,1.0f);
             glVertex3f(points[i+1][0],points[i+1][1],points[i+1][2]);
          glEnd();
          }

           glBegin(GL_TRIANGLES);
                 glTexCoord2f(0.0f,0.5f);
                 glVertex3f(points[4][0],points[4][1],points[4][2]);
                 glTexCoord2f(0.0f,1.0f);
                 glVertex3f(points[3][0],points[3][1],points[3][2]);
                 glTexCoord2f(1.0f,1.0f);
                 glVertex3f(points[0][0],points[0][1],points[0][2]);
           glEnd();


    glBegin(GL_QUADS);
        glTexCoord2f(0.0f,1.0f);
        glVertex3f(points[0][0],points[0][1],points[0][2]);
        glTexCoord2f(1.0f,1.0f);
        glVertex3f(points[1][0],points[1][1],points[1][2]);
        glTexCoord2f(1.0f,0.0f);
        glVertex3f(points[2][0],points[2][1],points[2][2]);
        glTexCoord2f(0.0f,0.0f);
        glVertex3f(points[3][0],points[3][1],points[3][2]);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
 }

/* GLUT callback Handlers */

void resize(int width, int height)
{
  gameCamara->resize(width, height);
}

void Sol()
{
  glPushMatrix();
    glColor3f(0.953, 0.624, 0.094);
    glutWireSphere(15.0f,20,20);
  glPopMatrix();
}

void drawAxis()
{
    //X axis in red
    glColor3ub(30, 136, 229); // X Green
    glBegin(GL_LINES);
    glVertex3f(-50.0,0.0,0.0);
    glVertex3f(50.0,0.0,0.0);
    glEnd();
    glRasterPos3f(60.0f,0.0f,0.0f);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'X');

    //Y axis in green
    glColor3ub(183, 28, 28); // Y Red
    glBegin(GL_LINES);
    glVertex3f(0.0,-50.0,0.0);
    glVertex3f(0.0,50.0,0.0);
    glEnd();
    glRasterPos3f(-1.0f,60.0f,-0.0f);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'Y');

    //Z axis in blue
    glColor3ub( 0, 77, 64 ); // Z Blue
    glBegin(GL_LINES);
    glVertex3f(0.0,0.0,-50.0);
    glVertex3f(0.0,0.0,50.0);
    glEnd();
    glRasterPos3f(0.0f,0.0f,60.0f);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'Z');
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  gameCamara->renderGameCamera();

  glColor3f(1.0f, 0.0f, 0.0f);
  Sol();
  drawAxis();
  ImprimePiramide(2);
  glutSwapBuffers();
}


void idle()
{
  display();
}

void key(unsigned char key, int x, int y)
{
  gameCamara->key(key,x,y);
}

void keyup(unsigned char key, int x, int y)
{
  gameCamara->keyup(key,x,y);
}

void mousePosition(int x, int y)
{
	gameCamara->mousePosition(x,y);
}

void processTimedEvent(int x) {
  // perform light movement and trigger redisplay
    glutPostRedisplay();
    gameCamara->ANGLE += 0.3f;
  // start event again
  glutTimerFunc(10 , processTimedEvent, 0);
}

/* Program entry point */
int main(int argc, char *argv[])
{

  gameCamara = new GameCamara();
  FreeImage_Initialise();

  gameCamara->init(argc,argv);

  if(!readImage()) return 0;

  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutIdleFunc(idle);

  glutIgnoreKeyRepeat(1);

  glutKeyboardFunc(key);
  glutKeyboardUpFunc(keyup);
  glutPassiveMotionFunc(mousePosition);
  glutTimerFunc(20, processTimedEvent, 0);
  glutMainLoop();
  return 0;
}































//
