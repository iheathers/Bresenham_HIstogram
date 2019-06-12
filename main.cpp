#include <iostream>
#include <GL/glut.h>

using namespace std;

void drawLine();
void inputData();
void CoordinateAxes();
void plot(float x, float y);

void drawBar(float );
void drawHistogram();

float x, y, dx, dy, D1, D2, xInc, yInc;
int arraySize;
static int step;

int frequency[5];
int main(int argc, char** argv)
{
    inputData();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500,500);

    glutCreateWindow("DDA Algorithm");
    glutDisplayFunc(drawHistogram);

    glutMainLoop();
    return 0;
}

void drawLine(float x1, float y1, float x2, float y2)
{

    CoordinateAxes();
    glColor3ub(255 ,255,255);
    glBegin(GL_POINTS);

        dx = x2 - x1;
        dy = y2 - y1;



        if (dy >= dx)
        {
            arraySize = dy;
            D1 = dx;
            D2 = dy;
            xInc = 0;
            yInc = 1;
        }
        else
        {
            arraySize = dx;
            D1 = dy;
            D2 = dx;
            xInc = 1;
            yInc = 0;
        }
        float P[int(arraySize)];
        P[0] = 2*D1 - D2;


        x = x1;
        y = y1;
        //plot(x, y);
        //cout << "(" << x << "," << y << ") ";
        //cout << D2;

        for(int i = 0; i < D2 ; i++)
        {
            if (P[i] <= 0)
            {
                plot(x , y);
                P[i+1] = P[i] + 2*D1;
                x += xInc;
                y += yInc;
                //cout << "(" << x << "," << y << ")";
            }
            else
            {
                plot(x , y );
                P[i+1] = P[i] + 2*D1 - 2*D2;
                x += 1;
                y += 1;
                //cout << "(" << x << "," << y << ")";
            }
        }
    glEnd();
    glFlush();
}

void inputData()
{
    cout << "Enter frequencies of 5 data: ";

    for (int i = 0; i < 5; i++)
    {
        cin >> frequency[i];
    }
}

void CoordinateAxes()
{
    glColor3ub(0,0,255);
    glBegin(GL_LINES);
        glVertex2f(0,1);
        glVertex2f(0,-1);
        glVertex2f(-1,0);
        glVertex2f(1,0);
    glEnd();
}

void plot(float x, float y)
{
    glVertex2f(x/500, y/500);
    cout << "(" << x << "," << y << ")";
}

void drawBar(int step, float freq)
{
    drawLine(step, 0, step, freq );
    drawLine(step, freq, step+25, freq);
    drawLine(step+25, 0, step + 25, freq);
}

void drawHistogram()
{
    for (int i = 0; i <= 5; i++)
    {
        drawBar(step, frequency[i]);
        step += 25;
    }

}
