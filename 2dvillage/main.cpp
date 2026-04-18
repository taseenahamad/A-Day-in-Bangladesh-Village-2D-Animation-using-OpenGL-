#include <GL/glut.h>
#include <math.h>

/* ---------- animation variables ---------- */

float sunX = 50;
float boatX = 0;
float farmerX = 0;
float birdX = 0;

int dayState = 0; // 0=morning,1=evening,2=night

/* ---------- circle function ---------- */

void drawCircle(float x,float y,float r)
{
    glBegin(GL_POLYGON);
    for(int i=0;i<360;i++)
    {
        float rad = i * 3.1416 / 180;
        glVertex2f(x + cos(rad)*r, y + sin(rad)*r);
    }
    glEnd();
}

/* ---------- background ---------- */

void drawSky()
{
    if(dayState==0)
        glColor3f(0.6,0.9,1); // morning
    else if(dayState==1)
        glColor3f(1,0.6,0.3); // sunset
    else
        glColor3f(0.05,0.05,0.2); // night

    glBegin(GL_QUADS);
    glVertex2f(0,200);
    glVertex2f(400,200);
    glVertex2f(400,400);
    glVertex2f(0,400);
    glEnd();
}

/* ---------- ground ---------- */

void drawGround()
{
    glColor3f(0.2,0.8,0.2);

    glBegin(GL_QUADS);
    glVertex2f(0,0);
    glVertex2f(400,0);
    glVertex2f(400,200);
    glVertex2f(0,200);
    glEnd();
}

/* ---------- river ---------- */

void drawRiver()
{
    glColor3f(0.2,0.5,1);

    glBegin(GL_QUADS);
    glVertex2f(0,70);
    glVertex2f(400,70);
    glVertex2f(400,120);
    glVertex2f(0,120);
    glEnd();
}

/* ---------- sun ---------- */

void drawSun()
{
    if(dayState!=2)
    {
        glColor3f(1,1,0);
        drawCircle(sunX,330,20);
    }
}

/* ---------- moon ---------- */

void drawMoon()
{
    if(dayState==2)
    {
        glColor3f(1,1,1);
        drawCircle(320,320,18);
    }
}

/* ---------- stars ---------- */

void drawStars()
{
    if(dayState==2)
    {
        glColor3f(1,1,1);
        drawCircle(50,360,2);
        drawCircle(100,340,2);
        drawCircle(150,370,2);
        drawCircle(200,350,2);
        drawCircle(250,360,2);
    }
}

/* ---------- trees ---------- */

void drawTree(float x)
{
    glColor3f(0.4,0.2,0.1);

    glBegin(GL_QUADS);
    glVertex2f(x,200);
    glVertex2f(x+10,200);
    glVertex2f(x+10,240);
    glVertex2f(x,240);
    glEnd();

    glColor3f(0,0.7,0);
    drawCircle(x+5,260,25);
}

/* ---------- hut ---------- */

void drawHut()
{
    glColor3f(0.7,0.4,0.2);

    glBegin(GL_QUADS);
    glVertex2f(220,200);
    glVertex2f(300,200);
    glVertex2f(300,250);
    glVertex2f(220,250);
    glEnd();

    glColor3f(0.5,0.1,0.1);

    glBegin(GL_TRIANGLES);
    glVertex2f(210,250);
    glVertex2f(310,250);
    glVertex2f(260,290);
    glEnd();
}

/* ---------- boat ---------- */

void drawBoat()
{
    glColor3f(0.5,0.3,0.1);

    glBegin(GL_POLYGON);
    glVertex2f(boatX+50,100);
    glVertex2f(boatX+120,100);
    glVertex2f(boatX+100,85);
    glVertex2f(boatX+70,85);
    glEnd();
}

/* ---------- farmer ---------- */

void drawFarmer()
{
    glColor3f(0,0,0);

    drawCircle(farmerX+100,200,6);

    glBegin(GL_LINES);
    glVertex2f(farmerX+100,195);
    glVertex2f(farmerX+100,180);
    glEnd();
}

/* ---------- birds ---------- */

void drawBirds()
{
    glColor3f(0,0,0);

    glBegin(GL_LINES);
    glVertex2f(birdX+20,350);
    glVertex2f(birdX+30,360);

    glVertex2f(birdX+30,360);
    glVertex2f(birdX+40,350);
    glEnd();
}

/* ---------- display ---------- */

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawSky();
    drawGround();
    drawRiver();

    drawSun();
    drawMoon();
    drawStars();

    drawTree(60);
    drawTree(120);

    drawHut();

    drawBoat();
    drawFarmer();
    drawBirds();

    glFlush();
}

/* ---------- animation ---------- */

void update(int v)
{
    sunX += 0.3;
    boatX += 0.6;
    farmerX += 0.4;
    birdX += 1;

    if(boatX > 350) boatX = -120;
    if(farmerX > 250) farmerX = -100;
    if(birdX > 380) birdX = -50;

    if(sunX > 350)
    {
        sunX = 50;
        dayState++;

        if(dayState > 2)
            dayState = 0;
    }

    glutPostRedisplay();
    glutTimerFunc(30, update, 0);
}

/* ---------- init ---------- */

void init()
{
    glClearColor(0.6,0.9,1,0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0,400,0,400,-1,1);
}

/* ---------- main ---------- */

int main(int argc,char** argv)
{
    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400,400);
    glutCreateWindow("A Day in Bangladesh Village");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(30, update, 0);

    glutMainLoop();
    return 0;
}
