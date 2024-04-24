#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cassert>

#include "GL/glut.h"

// the size of the window measured in pixels
#define dim 300

unsigned char prevKey;

class CartesianGrid {
public:
    CartesianGrid() {
        this->rows = this->columns = 14;
    }

    CartesianGrid(int rows, int columns) {
        this->rows = rows;
        this->columns = columns;
    }

    CartesianGrid(const CartesianGrid &c) {
        this->rows = c.rows;
        this->columns = c.columns;
    }

    CartesianGrid &operator=(CartesianGrid &c) {
        this->rows = c.rows;
        this->columns = c.columns;
        return *this;
    }

    int operator==(CartesianGrid &c) const {
        return ((this->rows == c.rows) && (this->columns == c.columns));
    }

    void draw() {
        float length = 1.8/rows;
        glColor3f(0.1, 0.1, 0.1);
        for (int iter = 0; iter <= rows; iter++) {
            glBegin(GL_LINE_STRIP);
            glVertex2d(-0.9, -0.9 + iter * length);
            glVertex2d(0.9, -0.9 + iter * length);
            glEnd();
        }
        for (int iter = 0; iter <= columns; iter++) {
            glBegin(GL_LINE_STRIP);
            glVertex2d(-0.9 + iter * length, -0.9 );
            glVertex2d(-0.9 + iter * length, 0.9);
            glEnd();
        }

        draw_pixels();
    }

    void draw_pixels(){
        glColor3f(0.1, 0.1, 0.1);
        float radius = 0.01;

        glEnd();
    }

protected:
    int rows, columns;
};


void Display1() {
    auto c = new CartesianGrid();
    c->draw();
}


void Display(void) {
    switch (prevKey) {
        case '0':
            glClear(GL_COLOR_BUFFER_BIT);
            break;
        case '1':
            glClear(GL_COLOR_BUFFER_BIT);
            Display1();
            break;
        default:
            break;
    }

    glFlush();
}

void Init(void) {

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glLineWidth(1);

    glPolygonMode(GL_FRONT, GL_LINE);
}

void Reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
    prevKey = key;
    if (key == 27)
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