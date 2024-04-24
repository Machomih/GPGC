#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cassert>

#include "GL/glut.h"

// the size of the window measured in pixels
#define dim 300

unsigned char prevKey;
int nivel = 0;


class C2coord {
public:
    C2coord() {
        m.x = m.y = 0;
    }

    C2coord(double x, double y) {
        m.x = x;
        m.y = y;
    }

    C2coord(const C2coord &p) {
        m.x = p.m.x;
        m.y = p.m.y;
    }

    C2coord &operator=(C2coord &p) {
        m.x = p.m.x;
        m.y = p.m.y;
        return *this;
    }

    int operator==(C2coord &p) {
        return ((m.x == p.m.x) && (m.y == p.m.y));
    }

protected:
    struct SDate {
        double x, y;
    } m;
};

class CPunct : public C2coord {
public:
    CPunct() : C2coord(0.0, 0.0) {}

    CPunct(double x, double y) : C2coord(x, y) {}

    CPunct &operator=(const CPunct &p) {
        m.x = p.m.x;
        m.y = p.m.y;
        return *this;
    }

    void getxy(double &x, double &y) {
        x = m.x;
        y = m.y;
    }

    int operator==(CPunct &p) {
        return ((m.x == p.m.x) && (m.y == p.m.y));
    }

    void marcheaza() {
        glBegin(GL_POINTS);
        glVertex2d(m.x, m.y);
        glEnd();
    }

    void print(FILE *fis) {
        fprintf(fis, "(%+f,%+f)", m.x, m.y);
    }

};

class CVector : public C2coord {
public:
    CVector() : C2coord(0.0, 0.0) {
        normalizare();
    }

    CVector(double x, double y) : C2coord(x, y) {
        normalizare();
    }

    CVector &operator=(CVector &p) {
        m.x = p.m.x;
        m.y = p.m.y;
        return *this;
    }

    int operator==(CVector &p) {
        return ((m.x == p.m.x) && (m.y == p.m.y));
    }

    CPunct getDest(CPunct &orig, double lungime) {
        double x, y;
        orig.getxy(x, y);
        CPunct p(x + m.x * lungime, y + m.y * lungime);
        return p;
    }

    void rotatie(double grade) {
        double x = m.x;
        double y = m.y;
        double t = 2 * (4.0 * atan(1.0)) * grade / 360.0;
        m.x = x * cos(t) - y * sin(t);
        m.y = x * sin(t) + y * cos(t);
        normalizare();
    }

    void deseneaza(CPunct p, double lungime) {
        double x, y;
        p.getxy(x, y);
        glColor3f(1.0, 0.1, 0.1);
        glBegin(GL_LINE_STRIP);
        glVertex2d(x, y);
        glVertex2d(x + m.x * lungime, y + m.y * lungime);
        glEnd();
    }

    void print(FILE *fis) {
        fprintf(fis, "%+fi %+fj", C2coord::m.x, C2coord::m.y);
    }

private:
    // it is used for normalizing a vector
    void normalizare() {
        double d = sqrt(C2coord::m.x * C2coord::m.x + C2coord::m.y * C2coord::m.y);
        if (d != 0.0) {
            C2coord::m.x = C2coord::m.x * 1.0 / d;
            C2coord::m.y = C2coord::m.y * 1.0 / d;
        }
    }
};

class CCurbaKoch {
public:
    void segmentKoch(double lungime, int nivel, CPunct &p, CVector v) {
        CPunct p1;
        if (nivel == 0) {
            v.deseneaza(p, lungime);
        } else {
            segmentKoch(lungime / 3.0, nivel - 1, p, v);
            p1 = v.getDest(p, lungime / 3.0);
            v.rotatie(60);
            segmentKoch(lungime / 3.0, nivel - 1, p1, v);
            p1 = v.getDest(p1, lungime / 3.0);
            v.rotatie(-120);
            segmentKoch(lungime / 3.0, nivel - 1, p1, v);
            p1 = v.getDest(p1, lungime / 3.0);
            v.rotatie(60);
            segmentKoch(lungime / 3.0, nivel - 1, p1, v);
        }
    }

    void afisare(double lungime, int nivel) {
        CVector v1(sqrt(3.0) / 2.0, 0.5);
        CPunct p1(-1.0, 0.0);

        CVector v2(0.0, -1.0);
        CPunct p2(0.5, sqrt(3.0) / 2.0);

        CVector v3(-sqrt(3.0) / 2.0, 0.5);
        CPunct p3(0.5, -sqrt(3.0) / 2.0);

        segmentKoch(lungime, nivel, p1, v1);
        segmentKoch(lungime, nivel, p2, v2);
        segmentKoch(lungime, nivel, p3, v3);
    }
};

class CArboreBinar {
public:
    void arboreBinar(double lungime, int nivel, CPunct &p, CVector v) {
        CPunct p1;
        if (nivel == 0) {
            v.deseneaza(p, lungime);
        } else {
            arboreBinar(lungime, nivel - 1, p, v);
            p1 = v.getDest(p, lungime);

            v.rotatie(-45);
            arboreBinar(lungime / 2.0, nivel - 1, p1, v);

            v.rotatie(90);
            arboreBinar(lungime / 2.0, nivel - 1, p1, v);
        }
    }

    void afisare(double lungime, int nivel) {
        CVector v(0.0, -1.0);
        CPunct p(0.0, 1.0);

        arboreBinar(lungime, nivel, p, v);
    }
};

class CArborePerron {
public:
    void arborePerron(double lungime, int nivel, double factordiviziune, CPunct p, CVector v) {
        assert(factordiviziune != 0);
        CPunct p1, p2;
        if (nivel == 0) {
        } else {
            v.rotatie(30);
            v.deseneaza(p, lungime);
            p1 = v.getDest(p, lungime);
            arborePerron(lungime * factordiviziune, nivel - 1, factordiviziune, p1, v);

            v.rotatie(-90);
            v.deseneaza(p, lungime);
            p1 = v.getDest(p, lungime);
            p2 = p1;

            v.rotatie(-30);
            v.deseneaza(p1, lungime);
            p1 = v.getDest(p1, lungime);
            arborePerron(lungime * factordiviziune, nivel - 1, factordiviziune, p1, v);

            p1 = p2;
            v.rotatie(90);
            v.deseneaza(p1, lungime);
            p1 = v.getDest(p1, lungime);
            p2 = p1;

            v.rotatie(30);
            v.deseneaza(p1, lungime);
            p1 = v.getDest(p1, lungime);
            arborePerron(lungime * factordiviziune, nivel - 1, factordiviziune, p1, v);

            p1 = p2;
            v.rotatie(-90);
            v.deseneaza(p1, lungime);
            p1 = v.getDest(p1, lungime);
            arborePerron(lungime * factordiviziune, nivel - 1, factordiviziune, p1, v);
        }
    }

    void afisare(double lungime, int nivel) {
        CVector v(0.0, 1.0);
        CPunct p(0.0, -1.0);

        v.deseneaza(p, 0.25);
        p = v.getDest(p, 0.25);
        arborePerron(lungime, nivel, 0.4, p, v);
    }
};


class CCurbaHilbert {
public:
    void curbaHilbert(double lungime, int nivel, CPunct &p, CVector &v, int d) {
        if (nivel == 0) {
        } else {
            v.rotatie(d * 90);
            curbaHilbert(lungime, nivel - 1, p, v, -d);

            v.deseneaza(p, lungime);
            p = v.getDest(p, lungime);

            v.rotatie(-d * 90);
            curbaHilbert(lungime, nivel - 1, p, v, d);

            v.deseneaza(p, lungime);
            p = v.getDest(p, lungime);

            curbaHilbert(lungime, nivel - 1, p, v, d);

            v.rotatie(-d * 90);
            v.deseneaza(p, lungime);
            p = v.getDest(p, lungime);

            curbaHilbert(lungime, nivel - 1, p, v, -d);

            v.rotatie(d * 90);
        }
    }

    void afisare(double lungime, int nivel) {
        CVector v(0.0, 1.0);
        CPunct p(0.0, 0.0);

        curbaHilbert(lungime, nivel, p, v, 1);
    }
};

class CSquare {
public:
    void square(double lungime, int nivel, CPunct &p) {
        int ratia = 3;
        if (nivel == 0) {
            double x, y;
            p.getxy(x, y);

            CVector v(0.0, -1.0);
            CPunct pp(x + lungime / 6, y + lungime / 6);

            v.deseneaza(pp, lungime / ratia);
            pp = v.getDest(pp, lungime / ratia);

            for (int i = 1; i <= 3; i++) {
                v.rotatie(-90);
                v.deseneaza(pp, lungime / ratia);
                pp = v.getDest(pp, lungime / ratia);
            }
        } else {
            double x, y;
            p.getxy(x, y);
            CPunct punct1(x - lungime / ratia, y - lungime / ratia);
            CPunct punct2(x - lungime / ratia, y);
            CPunct punct3(x, y + lungime / ratia);

            CPunct punct4(x, y - lungime / ratia);
            CPunct punct5(x - lungime / ratia, y + lungime / ratia);

            CPunct punct6(x + lungime / ratia, y - lungime / ratia);
            CPunct punct7(x + lungime / ratia, y);
            CPunct punct8(x + lungime / ratia, y + lungime / ratia);

            CPunct punct9(x, y);

            square(lungime / ratia, nivel - 1, punct1);
            square(lungime / ratia, nivel - 1, punct2);
            square(lungime / ratia, nivel - 1, punct3);
            square(lungime / ratia, nivel - 1, punct4);
            square(lungime / ratia, nivel - 1, punct5);
            square(lungime / ratia, nivel - 1, punct6);
            square(lungime / ratia, nivel - 1, punct7);
            square(lungime / ratia, nivel - 1, punct8);
            square(lungime, nivel - 1, punct9);
        }
    }

    void afisare(double lungime, int nivel) {
        CPunct p0(0.0, 0.0);
        CPunct p(0.8, 0.8);
        CVector v(0.0, -1.0);


        v.deseneaza(p, lungime);
        p = v.getDest(p, lungime);

        for (int i = 1; i <= 3; i++) {
            v.rotatie(-90);
            v.deseneaza(p, lungime);
            p = v.getDest(p, lungime);
        }

        square(lungime, nivel, p0);
    }
};

class CArborePerronSecond {
public:
    void arborePerron(double lungime, int nivel, double factordiv, CPunct p, CVector v) {
        assert(factordiv != 0);
        CPunct p1, p2;
        if (nivel == 0) {
        } else {
            v.rotatie(-45);
            v.deseneaza(p, lungime);
            p1 = v.getDest(p, lungime);
            arborePerron(lungime * factordiv, nivel - 1, factordiv, p1, v);

            v.rotatie(90);
            v.deseneaza(p, lungime);
            p1 = v.getDest(p, lungime);
            p2 = p1;


            v.rotatie(15);
            v.deseneaza(p1, lungime);
            p1 = v.getDest(p1, lungime);
            arborePerron(lungime * factordiv, nivel - 1, factordiv, p1, v);

            p1 = p2;
            v.rotatie(-60);
            v.deseneaza(p1, lungime);
            p1 = v.getDest(p1, lungime);
            p2 = p1;

            float lungime_latura_mica = lungime / 2;
            v.rotatie(-90);
            v.deseneaza(p1, lungime_latura_mica);
            p1 = v.getDest(p1, lungime_latura_mica);
            arborePerron(lungime * factordiv, nivel - 1, factordiv, p1, v);

            p1 = p2;
            v.rotatie(120);
            v.deseneaza(p1, lungime_latura_mica);
            p1 = v.getDest(p1, lungime_latura_mica);
            arborePerron(lungime * factordiv, nivel - 1, factordiv, p1, v);
        }
    }

    void afisare(double lungime, int nivel) {
        CVector v(0.0, -1.0);
        CPunct p(0.0, 1.0);

        v.deseneaza(p, 0.25);
        p = v.getDest(p, 0.25);
        arborePerron(lungime, nivel, 0.4, p, v);
    }
};

class CTriunghi {
public:
    void triunghi(double lungime, int nivel, CPunct &p, CVector v, int inverted) {
        CPunct p1;
        if (nivel == 0) {
            v.deseneaza(p, lungime);
        } else {
            if (inverted == 0) {
                v.rotatie(-60);
                triunghi(lungime / 2.0, nivel - 1, p, v, 1);
                p1 = v.getDest(p, lungime / 2.0);

                v.rotatie(60);
                triunghi(lungime / 2.0, nivel - 1, p1, v, 0);
                p1 = v.getDest(p1, lungime / 2.0);

                v.rotatie(60);
                triunghi(lungime / 2.0, nivel - 1, p1, v, 1);
                p1 = v.getDest(p1, lungime / 2.0);
            } else {
                v.rotatie(60);
                triunghi(lungime / 2.0, nivel - 1, p, v, 0);
                p1 = v.getDest(p, lungime / 2.0);

                v.rotatie(-60);
                triunghi(lungime / 2.0, nivel - 1, p1, v, 1);
                p1 = v.getDest(p1, lungime / 2.0);

                v.rotatie(-60);
                triunghi(lungime / 2.0, nivel - 1, p1, v, 0);
                p1 = v.getDest(p1, lungime / 2.0);
            }
        }
    }

    void afisare(double lungime, int nivel) {
        CPunct p1(-0.8, 0.8);
        CVector v1(0.0, -1.0);
        triunghi(lungime, nivel, p1, v1, 1);
    }

};


// displays the Koch snowflake
void Display1() {
    CCurbaKoch cck;
    cck.afisare(sqrt(3.0), nivel);

    char c[3];
    sprintf(c, "%2d", nivel);
    glRasterPos2d(-0.98, -0.98);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'v');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '=');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[0]);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[1]);

    glRasterPos2d(-1.0, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'c');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'u');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'b');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ' ');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'u');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ' ');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'K');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'o');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'c');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'h');

    nivel++;
}

// displays a binary tree
void Display2() {
    CArboreBinar cab;
    cab.afisare(1, nivel);

    char c[3];
    sprintf(c, "%2d", nivel);
    glRasterPos2d(-0.98, -0.98);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'v');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '=');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[0]);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[1]);

    glRasterPos2d(-1.0, 0.9);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'b');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'o');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ' ');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'b');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'n');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');

    nivel++;
}

// displays a fractal tree
void Display3() {
    CArborePerron cap;

    char c[3];
    sprintf(c, "%2d", nivel);
    glRasterPos2d(-0.98, -0.98);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'v');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '=');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[0]);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[1]);

    glRasterPos2d(-1.0, -0.9);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'b');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'o');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ' ');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'P');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'o');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'n');

    glPushMatrix();
    glLoadIdentity();
    glScaled(0.4, 0.4, 1);
    glTranslated(-0.5, -0.5, 0.0);
    cap.afisare(1, nivel);
    glPopMatrix();
    nivel++;
}

// displays the Hilbert curve
void Display4() {
    CCurbaHilbert cch;
    cch.afisare(0.05, nivel);

    char c[3];
    sprintf(c, "%2d", nivel);
    glRasterPos2d(-0.98, -0.98);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'v');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '=');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[0]);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[1]);

    glRasterPos2d(-1.0, -0.9);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'c');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'u');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'b');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ' ');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'H');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'b');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 't');

    nivel++;
}

void Display5() {
    CSquare csquare;
    CVector v(0.0, -1.0);
    csquare.afisare(1.6, nivel);

    char c[3];
    sprintf(c, "%2d", nivel);
    glRasterPos2d(-0.98, -0.98);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'v');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '=');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[0]);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[1]);

    glRasterPos2d(-1.0, -0.9);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'p');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 't');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 't');

    nivel++;
}

void Display6() {
    CArborePerronSecond capSecond;
    char c[3];
    sprintf(c, "%2d", nivel);
    glRasterPos2d(-0.98, -0.98);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'v');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '=');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[0]);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[1]);

    glRasterPos2d(-1.0, -0.9);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'a');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'b');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'o');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ' ');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'P');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'o');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'n');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '2');

    glPushMatrix();
    glLoadIdentity();
    glScaled(0.4, 0.4, 1);
    glTranslated(-0.5, -0.5, 0.0);
    capSecond.afisare(1, nivel);
    glPopMatrix();
    nivel++;
}

void Display7() {

    CTriunghi triunghi;
    triunghi.afisare(1, nivel);
    char c[3];
    sprintf(c, "%2d", nivel);
    glRasterPos2d(-0.98, -0.98);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'N');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'v');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'l');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '=');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[0]);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c[1]);

    glRasterPos2d(-1.0, -0.9);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 't');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'u');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'n');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'g');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'h');
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'i');


    nivel++;
}

void Init(void) {

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glLineWidth(1);

    glPointSize(3);

    glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
    switch (prevKey) {
        case '0':
            glClear(GL_COLOR_BUFFER_BIT);
            nivel = 0;
            fprintf(stderr, "nivel = %d\n", nivel);
            break;
        case '1':
            glClear(GL_COLOR_BUFFER_BIT);
            Display1();
            break;
        case '2':
            glClear(GL_COLOR_BUFFER_BIT);
            Display2();
            break;
        case '3':
            glClear(GL_COLOR_BUFFER_BIT);
            Display3();
            break;
        case '4':
            glClear(GL_COLOR_BUFFER_BIT);
            Display4();
            break;
        case '5':
            glClear(GL_COLOR_BUFFER_BIT);
            Display5();
            break;
        case '6':
            glClear(GL_COLOR_BUFFER_BIT);
            Display6();
            break;
        case '7':
            glClear(GL_COLOR_BUFFER_BIT);
            Display7();
            break;
        case 'r':
            glClear(GL_COLOR_BUFFER_BIT);
            nivel = 0;
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

