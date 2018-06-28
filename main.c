#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include "Vector3.h"

#include <vector>

#define R 0
#define G 1
#define B 2

using namespace std;

vector<Vector3i> faceVector,
                 irisVector,
                 hairVector;
                 

GLuint leftArm,
       leftForearm,
       leftHand,
       shirt,
       jacket,
       rightArm,
       rightForearm,
       rightHand;

GLuint face,
       eyeBefore,
       iris,
       eyeAfter,
       hair;

int faceIndex, irisIndex, hairIndex, shirtIndex, jacketIndex; 

GLuint loadTexture(char* path) {
    GLuint ans = SOIL_load_OGL_texture(
        path,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    if (ans == 0) {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }

}

void inicializa() {
    glClearColor(1, 1, 1, 1);

    // habilita mesclagem de cores, para termos suporte a texturas (semi-)transparentes
    glEnable(GL_BLEND );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    leftArm      = loadTexture("leftarm.png");
    leftForearm  = loadTexture("leftforearm.png");
    leftHand     = loadTexture("lefthand.png");
    shirt        = loadTexture("shirt.png");
    jacket       = loadTexture("jacket.png");
    rightArm     = loadTexture("rightarm.png");
    rightForearm = loadTexture("rightforearm.png");
    rightHand    = loadTexture("righthand.png");

    face      = loadTexture("face.png");
    eyeBefore = loadTexture("eye-before.png");
    iris      = loadTexture("iris.png");
    eyeAfter  = loadTexture("eye-after.png");
    hair      = loadTexture("hair.png");

    faceVector.push_back(Vector3i(248, 213, 194));
    faceVector.push_back(Vector3i(239, 188, 166));
    faceVector.push_back(Vector3i(230, 170, 134));
    faceVector.push_back(Vector3i(210, 148, 107));
    faceVector.push_back(Vector3i(199, 142,  98));
    faceVector.push_back(Vector3i(174, 112,  66));
    faceVector.push_back(Vector3i(131,  87,  54));
    faceVector.push_back(Vector3i(136,  86,  59));
    faceVector.push_back(Vector3i(113,  80,  49));

    irisVector.push_back(Vector3i(164,  81,   0));
    irisVector.push_back(Vector3i( 99,  99,  99));
    irisVector.push_back(Vector3i(197,  63,   0));
    irisVector.push_back(Vector3i(233, 170,  12));
    irisVector.push_back(Vector3i(208,   1,  57));
    irisVector.push_back(Vector3i(204, 154,   1));
    irisVector.push_back(Vector3i( 37, 121, 201));

    hairVector.push_back(Vector3i(164,  81,   0));
    hairVector.push_back(Vector3i( 99,  99,  99));
    hairVector.push_back(Vector3i(197,  63,   0));
    hairVector.push_back(Vector3i(233, 170,  12));
    hairVector.push_back(Vector3i(208,   1,  57));
    hairVector.push_back(Vector3i(204, 154,   1));
    hairVector.push_back(Vector3i( 37, 121, 201));

}


void drawStep(GLuint texture, Vector3i color) {
    glColor3ub(color[R], color[G], color[B]);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_TRIANGLE_FAN);
        // Associamos um canto da textura para cada vértice
        glTexCoord2f(0, 0); glVertex3f(-1, -1,  0);
        glTexCoord2f(1, 0); glVertex3f( 1, -1,  0);
        glTexCoord2f(1, 1); glVertex3f( 1,  1,  0);
        glTexCoord2f(0, 1); glVertex3f(-1,  1,  0);
    glEnd();
}

void desenha(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f (1, 1, 1);

    // Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	    glTranslatef(0, -1.4, 0);
            glScalef(0.629032258, 0.514925373, 1.0);	
            drawStep(leftArm,      hairVector[jacketIndex]);
            drawStep(leftForearm,  hairVector[jacketIndex]);
            drawStep(leftHand,     faceVector[faceIndex]);
            drawStep(shirt,        hairVector[shirtIndex]);
            drawStep(jacket,       hairVector[jacketIndex]);
            drawStep(rightArm,     hairVector[jacketIndex]);
            drawStep(rightForearm, hairVector[jacketIndex]);
            drawStep(rightHand,    faceVector[faceIndex]);
        glPopMatrix();

        /** Face **/
        drawStep(face, faceVector[faceIndex]);
	drawStep(eyeBefore, Vector3i(255, 255, 255));
	drawStep(iris, irisVector[irisIndex]);
	drawStep(eyeAfter, Vector3i(255, 255, 255));
        drawStep(hair, hairVector[hairIndex]);
    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();
}

void redimensiona(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4, 4, -4, 4, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void teclado(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
	case 'h':
		if(++hairIndex >= hairVector.size()) hairIndex = 0;
		break;
	case 'f':
		if(++faceIndex >= faceVector.size()) faceIndex = 0;
		break;
	case 'i':
		if(++irisIndex >= irisVector.size()) irisIndex = 0;
		break;
	case 'j':
		if(++jacketIndex >= hairVector.size()) jacketIndex = 0;
		break;
	case 's':
		if(++shirtIndex >= hairVector.size()) shirtIndex = 0;
		break;
    }
}

void atualiza() {
    glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(800, 800);
   glutInitWindowPosition(100, 100);

   glutCreateWindow("Carregando textura com SOIL");

   glutReshapeFunc(redimensiona);
   glutKeyboardFunc(teclado);
   glutDisplayFunc(desenha);
   glutIdleFunc(atualiza);

   inicializa();

   glutMainLoop();

   return 0;
}
