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
#include "Objetos.h"
//#include "Textura.h"

GameCamara *gameCamara;
Textura textura;
Objetos objeto1(&textura, 1);
Objetos objeto2(&textura, 2);
Objetos objeto3(&textura, 3);
Objetos objeto4(&textura, 4);
Objetos objeto5(&textura, 5);

/* GLUT callback Handlers */
void resize(int width, int height)
{
  gameCamara->resize(width, height);
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

  drawAxis();


  objeto1.dibujarObjeto(30.0);

  objeto2.dibujarObjeto(10.0);

  objeto3.dibujarObjeto(5.0);

  objeto4.dibujarObjeto(5.0);

  objeto5.dibujarObjeto(500.0);

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
  gameCamara = new GameCamara();      // Inicio de escenario
  FreeImage_Initialise();             // Inicio de la libreria de imagenes
  gameCamara->init(argc,argv);

  if(!textura.readImage()) return 0;

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
