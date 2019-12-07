//
//  main.cpp
//  SistemaSolarErick
//
//  Created by Erick de Jesus Hernandez Cerecedo on 11/12/19.
//  Copyright � 2019 Erick de Jesus Hernandez Cerecedo. All rights reserved.
//

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION // Apple
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Librerias
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "math.h"

// Variables dimensiones de la pantalla
GLint ANCHO=1280;
GLint ALTO=720;

// Variables para establecer los valores de glutPerspective
GLfloat FOVY=60.0;
GLfloat ZNEAR=0.01;
GLfloat ZFAR=200;

// Variable que definen la posicion del observador
float EYE_X=0.0;
float EYE_Y=0.0;
float EYE_Z=0.0;
float CENTER_X=1;
float CENTER_Y=1;
float CENTER_Z=1;
float UP_X=0;
float UP_Y=1;
float UP_Z=0;

//Variables para matrices de rotacion y traslaci�n
float Theta=0;
//float Radio=1.0;
float PI = 3.14159265359;
float Direction[3] = {1.0,0.0,0.0};

GLfloat anguloSol = 0.0f;
/* GLUT callback Handlers */


float RadToDeg(float r)
{
      return ((180.0*r)/PI);
}

float DegToRad(float g)
{
      return ((g*PI)/180.0);
}

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;
    ANCHO = width;
    ALTO = height;

    glViewport(0, 0, ANCHO, ALTO);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOVY, (GLfloat)ANCHO/ALTO, ZNEAR, ZFAR);
    //glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(EYE_X,EYE_Y,EYE_Z,CENTER_X,CENTER_Y,CENTER_Z,UP_X,UP_Y,UP_Z);

}

void LookAt()
{
    Direction[0] = cos(DegToRad(Theta));
    Direction[2] = sin(DegToRad(Theta));
    CENTER_X = EYE_X + Direction[0];
    CENTER_Z = EYE_Z + Direction[2];
}

void drawAxis()
{
    //glShadeModel(GL_SMOOTH);
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

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);
    //glColor3d(1,0,0);

    drawAxis();

    glPushMatrix();
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    glRotatef(anguloSol, 0.0f, 0.0f, 1.0f);
    glColor3f(0.953, 0.624, 0.094);
    glutWireSphere(5.0f,20,20);
      glColor3f(0.682, 0.714, 0.69);
    glPopMatrix();

    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
      case 'W': // Adelante
      case 'w':
        EYE_X += Direction[0];
        EYE_Y += Direction[1];
        EYE_Z += Direction[2];
        CENTER_X = EYE_X + Direction[0];
        CENTER_Y = EYE_Y + Direction[1];
        CENTER_Z = EYE_Z + Direction[2];

        break;
      case 'S': // Atras
      case 's':
        EYE_X -= Direction[0];
        EYE_Y -= Direction[1];
        EYE_Z -= Direction[2];
        CENTER_X = EYE_X + Direction[0];
        CENTER_Y = EYE_Y + Direction[1];
        CENTER_Z = EYE_Z + Direction[2];
        break;
      case 'A': // Izquierda
      case 'a':
        Theta -= 1.0f;
        Theta = (Theta < 0.0) ? 359.0 : Theta;
        LookAt();
        break;
      case 'D': // Derecha
      case 'd':
        Theta += 1.0f;
        Theta = (Theta > 359.0) ? 0.0 : Theta;
        LookAt();
        break;
      case 27 :
        exit(0);
        break;
    }

    glLoadIdentity();
    gluLookAt(EYE_X,EYE_Y,EYE_Z,CENTER_X,CENTER_Y,CENTER_Z,UP_X,UP_Y,UP_Z);
    glutPostRedisplay();
}

// Constantes de Luz
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

void init()
{

  ANCHO = 1280;
  ALTO = 720;

  glClearColor(0.196, 0.196, 0.196,1);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

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
}

static void idle(void)
{
    glutPostRedisplay();
}

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(ANCHO,ALTO);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_SINGLE);
    glutCreateWindow("Proyecto Final");
    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}
