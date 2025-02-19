
#include <cstdlib>
#include <cstdio>
#include <cmath>

/**********************************

  C:\Program Files\Microsoft SDKs\Windows\v7.0A\Include\gl\glut.h
  C:\Program Files\Microsoft SDKs\Windows\v7.0A\Lib\glut32.lib
  C:\Windows\System32\glut32.dll
 **********************************/

#include "GL/glut.h"


unsigned char prevKey;

void Display1() {

    glColor3f(0.2, 0.15, 0.88); // blue

    glBegin(GL_LINES); // line drawing
    glVertex2i(1, 1); // vertice coordinates
    glVertex2i(-1, -1);
    glEnd();

    glColor3f(1, 0.1, 0.1); // red

    glBegin(GL_LINES);
    glVertex2i(-1, 1);
    glVertex2i(1, -1);
    glEnd();


    glBegin(GL_LINES);
    glVertex2d(-0.5, 0);
    glVertex2d(0.5, 0);
    glEnd();
}

void Display2() {
    glColor3f(1, 0.1, 0.1); // red

    glBegin(GL_LINES);
    glVertex2f(1.0, 1.0);
    glVertex2f(0.9, 0.9);
    glVertex2f(0.8, 0.8);
    glVertex2f(0.7, 0.7);
    glVertex2f(0.6, 0.6);
    glVertex2f(0.5, 0.5);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-1.0, -1.0);
    glEnd();
}

void Display3() {

    glColor3f(1, 0.1, 0.1); // red
    glBegin(GL_POINTS);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(-0.5, -0.5);
    glEnd();
}

void Display4() {

    glColor3f(1, 0.1, 0.1);
    glBegin(GL_LINE_STRIP);
    glVertex2f(1, 1);
    glVertex2f(1, 0.9);
    glVertex2f(0.6, 0.6);
    glVertex2f(0.6, 0.5);
    glEnd();
}

void Display5() {

    glColor3f(1, 0.1, 0.1); // red
    glBegin(GL_LINE_LOOP);
    glVertex2f(1, 1);
    glVertex2f(1, 0.9);
    glVertex2f(0.6, 0.6);
    glVertex2f(0.6, 0.5);
    glEnd();
}

void Display6() {

    glColor3f(1, 0.1, 0.1); // red
    glBegin(GL_TRIANGLES);
    glVertex2f(1.0, 1.0);
    glVertex2f(1.0, 0.8);
    glVertex2f(0.8, 0.8);

    glVertex2f(-1.0, -1.0);
    glVertex2f(-1.0, -0.8);
    glVertex2f(-0.8, -0.8);
    glEnd();
}

void Display7() {

    glColor3f(1, 0.1, 0.1); // red
    glBegin(GL_QUADS);
    glVertex2f(1.0, 1.0);
    glVertex2f(1.0, 0.55);
    glVertex2f(0.5, 0.55);
    glVertex2f(0.3, 0.75);
    glEnd();
}

void Display8() {

    glColor3f(0.1, 0.1, 1); // blue
    glBegin(GL_POLYGON);

    glVertex2f(-0.35, 0.6);
    glVertex2f(0.35, 0.6);
    glVertex2f(0.7,0);
    glVertex2f(0.35, -0.6);
    glVertex2f(-0.35, -0.6);
    glVertex2f(-0.7,0);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 0.1, 0.1);
    glVertex2f(-0.26, 0.44);
    glVertex2f(0.26, 0.44);
    glVertex2f(0.53,0);
    glVertex2f(0.26, -0.44);
    glVertex2f(-0.26, -0.44);
    glVertex2f(-0.53,0);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex2f(-0.25, 0.4);
    glVertex2f(0.25, 0.4);
    glVertex2f(0.5,0);
    glVertex2f(0.25, -0.4);
    glVertex2f(-0.25, -0.4);
    glVertex2f(-0.5,0);
    glEnd();
}

void Init() {

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glLineWidth(3);
    glPointSize(4);
    glPolygonMode(GL_FRONT, GL_LINE);
}

void Display() {
    printf("Call Display\n");
    glClear(GL_COLOR_BUFFER_BIT);
    switch (prevKey) {
        case '1':
            Display1();
            break;
        case '2':
            Display2();
            break;
        case '3':
            Display3();
            break;
        case '4':
            Display4();
            break;
        case '5':
            Display5();
            break;
        case '6':
            Display6();
            break;
        case '7':
            Display7();
            break;
        case '8':
            Display8();
            break;
        default:
            break;
    }

    glFlush();
}

void Reshape(int w, int h) {
    printf("Call Reshape : width = %d, height = %d\n", w, h);
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
    printf("You have pressed <%c>. The mouse has the position %d, %d.\n",
           key, x, y);
    prevKey = key;
    if (key == 27)
        exit(0);
    glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
    printf("Call MouseFunc : you have %s the %s button in the position %d %d\n",
           (state == GLUT_DOWN) ? "pressed" : "released",
           (button == GLUT_LEFT_BUTTON) ?
           "left" :
           ((button == GLUT_RIGHT_BUTTON) ? "right" : "middle"),
           x, y);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow(argv[0]);
    Init();
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(KeyboardFunc);
    glutMouseFunc(MouseFunc);
    glutDisplayFunc(Display);
    glutMainLoop();

    return 0;
}
