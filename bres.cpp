#include <stdio.h>
#include <GL/glut.h>

int xa, ya, xb, yb;
int lineType;
int Round(float a)
{
    return(int)(a + 0.5);
}

void bresenhamLine(int xa, int ya, int xb, int yb, int lineType)
{
    int dx = abs(xb - xa);
    int dy = abs(yb - ya);
    int sx = (xa < xb) ? 1 : -1;
    int sy = (ya < yb) ? 1 : -1;

    int err = dx - dy;

    while (true)
    {
        glBegin(GL_POINTS);
        glVertex2d(xa, ya);
        glEnd();

        if (xa == xb && ya == yb)
            break;

        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            xa += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            ya += sy;
        }
    }

    glFlush();
}

void mouse1(int button, int state, int x, int y) {
    y = 480 - y;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
       xa=x;
       ya=y;
    }
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        xb=x;
        yb=y;
        glColor3f(1.0,0.0,0.0);
        bresenhamLine(xa, ya, xb, yb, lineType);
    }
}

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);
    bresenhamLine(0,240,640,240,1);
    bresenhamLine(320,0,320,480,1);
}

int main(int argc, char **argv)
{
    printf("Enter what type of line to draw (1. Simple 2. Dotted 3. Dashed 4. Solid) ");
    scanf("%d",&lineType);
    printf("Drag a line across the screen");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Bresenham Line");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    gluOrtho2D(0, 640, 0, 480);

    glutDisplayFunc(Draw);
    glutMouseFunc(mouse1);
    glutMainLoop();

    return 0;
}

