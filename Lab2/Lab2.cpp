#include <cstdlib>
#include <cmath>

#include "GL/glut.h"

#define dim 300

unsigned char prevKey;

void Display1() {
    double xmax, ymax, xmin, ymin;
    double a = 1, b = 2;
    double pi = 4 * atan(1.0);
    double ratia = 0.05;
    double t;

    xmax = a - b - 1;
    xmin = a + b + 1;
    ymax = ymin = 0;
    for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
        double x1, y1, x2, y2;
        x1 = a + b * cos(t);
        xmax = (xmax < x1) ? x1 : xmax;
        xmin = (xmin > x1) ? x1 : xmin;

        x2 = a - b * cos(t);
        xmax = (xmax < x2) ? x2 : xmax;
        xmin = (xmin > x2) ? x2 : xmin;

        y1 = a * tan(t) + b * sin(t);
        ymax = (ymax < y1) ? y1 : ymax;
        ymin = (ymin > y1) ? y1 : ymin;

        y2 = a * tan(t) - b * sin(t);
        ymax = (ymax < y2) ? y2 : ymax;
        ymin = (ymin > y2) ? y2 : ymin;
    }

    xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
    ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

    glColor3f(1, 0.1, 0.1);
    glBegin(GL_LINE_STRIP);
    for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
        double x1, y1;
        x1 = (a + b * cos(t)) / xmax;
        y1 = (a * tan(t) + b * sin(t)) / ymax;

        glVertex2f(x1, y1);
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
        double x2, y2;
        x2 = (a - b * cos(t)) / xmax;
        y2 = (a * tan(t) - b * sin(t)) / ymax;

        glVertex2f(x2, y2);
    }
    glEnd();
}

void Display2() {

    glColor3f(1, 0.1, 0.1);
    glPointSize(1.0);
    glBegin(GL_LINE_STRIP);
    double pi = 4 * atan(1.0);
    double xmax = 8 * pi;
    double ratia = 0.05;

    for (double x = 0; x <= 100; x += ratia) {
        double x1 = x / xmax;
        double y1;
        double d = abs(round(x) - x);
        y1 = (d / x);
        if (x == 0) {
            y1 = 1;
        }

        glVertex2f(x1, y1);
    }
    glEnd();
}

void Display3() {

    glColor3f(1, 0.1, 0.1);
    glBegin(GL_POINTS);
    double a = 0.2;
    double pi = 4 * atan(1.0);
    for (double t = -pi / 2; t <= pi / 2; t += 0.00001) {
        double cosSquared = pow(cos(t), 2);
        double denominator = 4 * cosSquared - 3;

        double x = a / denominator;
        double y = (a * tan(t)) / denominator;

        glVertex2f(x, y);
    }
    glEnd();
}

void Display4() {

    glColor3f(1, 0.1, 0.1);
    glBegin(GL_POINTS);
    double a = 0.1;
    double b = 0.2;
    for (double t = -10.0; t <= 10.0; t += 0.001) {
        double x = a * t - b * sin(t);
        double y = a - b * cos(t);

        glVertex2f(x, y);
    }
    glEnd();
}

void Display5() {

    glColor3f(1, 0.1, 0.1);
    glBegin(GL_POINTS);
    double pi = 4 * atan(1.0);
    double a = 0.4;
    for (double t = 2 * -pi; t <= 2 * pi; t += 0.001) {
        double r = abs(a * sqrt(2 * cos(2 * t)));
        double x = r * cos(t);
        double y = r * sin(t);

        glVertex2f(x, y);
    }
    glEnd();
}

void Display6() {

    glColor3f(1, 0.1, 0.1);
    glBegin(GL_POINTS);
    double a = 0.02;
    for (double t = 0; t <= 10; t += 0.001) {
        double r = a * exp(1 + t);
        double x = r * cos(t);
        double y = r * sin(t);

        glVertex2f(x, y);
    }
    glEnd();
}


void Init(void) {

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glLineWidth(1);

    glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
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
        default:
            break;
    }

    glFlush();
}

void Reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
    prevKey = key;
    if (key == 27) // escape
        exit(0);
    glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char **argv) {

    glutInit(&argc, argv);

    glutInitWindowSize(dim, dim);

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