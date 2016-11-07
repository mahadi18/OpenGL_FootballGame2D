/*
 * Move The Ball, Avoid The Obstacles
 *
 * Written by A. S. M. AL-ZIHADI November 2016
 *
 *
 * There is a ball on a football ground.
 * Move the ball using the up, down, left and right keys
 * and avoid obstacles on the ground.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <bits/stdc++.h>
#include <stdlib.h>
#include <windows.h>

using namespace std;

int n=6;
float lx[ ] = { 15, -15, 15, -15,  -7.5, 7.5};
float lu[ ] = { 10,  10,  25, 25,    25,  20};
float ld[ ] = { -25, -25, 18, 18,  -20,  -25};

static float ball_x = -28.0;
static float ball_y = 0.0;
int windowWidth = 800, windowHeight=800;
float cx=0;
int score = 0;

/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

/***************** My Functions *******************/

void line(float x1, float y1, float x2, float y2, float r, float g, float b)
{
    glLineWidth(4.0);
    glBegin(GL_LINES);
    glColor3f(r, g, b);

    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();

}
void filledRect(float r, float g, float b)
{
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);

    glVertex2f(-35.0, -25.0);
    glVertex2f(35.0, -25.0);
    glVertex2f(35.0, 25.0);
    glVertex2f(-35.0, 25.0);
    glEnd();
}
void boarderRect()
{
    float r=1.0, g=1.0, b=1.0;

    line(-35.0, 25.0, 35.0, 25.0, r, g, b);         // boarder line up

    glPushMatrix();
    glRotatef(-180, 0.0, 0.0, 1.0);
    line(-35.0, 25.0, 35.0, 25.0, r, g, b);         // boarder line down
    glPopMatrix();

    line(34.8, -25.0, 34.8, 25.0, r, g, b);         // boarder line right
    glPushMatrix();
    glRotatef(-180, 0.0, 0.0, 1.0);
    line(34.8, -25.0, 34.8, 25.0, r, g, b);         // boarder line down
    glPopMatrix();

    //line(-35.0, -25.0, 35.0, -25.0, r, g, b);         // boarder line down
    //line(34.8, -25.0, 34.8, 25.0, r, g, b);         // boarder line right
    //line(-34.8, -25.0, -34.8, 25.0, r, g, b);         // boarder line left
}

void circle(float h, float k, float r, float cx)
{

    float PI = acos(-1);
    glBegin(GL_POLYGON);
    for(float i=0; i<=2*PI; i=i+(PI/200))
    {
        float x = h + cos(i)*r;
        float y = k + sin(i)*r;

        if(x>cx) glVertex2f(x,y);
    }
    glEnd();
}
void dBox()
{
    float r=1.0, g=1.0, b=1.0;
    line(0.0,-25.0, 0.0, 25.0, r,g,b);         // mid line

    line(-34.5,8.0, -30.0,8.0, r,g,b);         // goal bar up
    line(-30.2, 8.0, -30.2, -8.0, r,g,b);      //  right
    line(-34.5,-8.0, -30.0,-8.0, r,g,b);       // down

    line(-34.5,15.0, -25.0,15.0, r,g,b);         // D box
    line(-25.2, 15.0, -25.2, -15.0, r,g,b);      // right
    line(-34.5,-15.0, -25.0,-15.0, r,g,b);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    circle(-25.2, 0.0, 4.0, -25.2);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}



void obstacles()
{

    float r=0.0, g=0.0, b=1.0;

    for(int i=0; i<n; i++)
    {
        line(lx[i], lu[i], lx[i], ld[i], r, g, b);
    }

}

void ground()
{
    filledRect(0.0, 0.6, 0.2);   // Grass
    obstacles();
    boarderRect();  // boarder
    dBox();
    glPushMatrix();
    glRotatef(-180.0f, 0.0f, 0.0f, 1.0f);
    dBox();
    glPopMatrix();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    circle(0.0, 0.0, 4.0, -100.0);   // center
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    circle(0.0, 0.0, 1.0, -100.0);   // center point

}




void ball()
{
    glColor3f(1.0, 1.0, 0.0);
    circle(ball_x, ball_y, 1.5, -1000.0);
}
/********** Display Models *********/
static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D(-50, 50, -50, 50);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glViewport(-50, 0 ,windowWidth ,windowHeight);
    glPushMatrix();



    ground();
    ball();



    glFlush();
    glutSwapBuffers();
}
bool termination()
{
    for(int i=0; i<n; i++)
    {
         if( ( ball_y-1.5<=lu[i] &&  ball_y+1.5 >=ld[i])  && ( abs(lx[i]-ball_x)<=1.5 ) )
        {
            cout<<"\n\n\n\n\n";
            cout<<"\t\t**************** GAME OVER **************"<< endl;
            cout<<"\t\t*\t\t\t\t\t*"<< endl;
            cout<<"\t\t*\t\t\t\t\t*"<< endl;
            cout<<"\t\t*\t\t\t\t\t*"<< endl;
            cout<<"\t\t*\t\t YOU LOSE   \t\t*"<< endl;
            cout<<"\t\t*\t\t\t\t\t*"<< endl;
            cout<<"\t\t*\t\t TRY AGAIN  \t\t*"<< endl;
            cout<<"\t\t*\t\t\t\t\t*"<< endl;
            cout<<"\t\t*\t\t\t\t\t*"<< endl;
            cout<<"\t\t*\t\t\t\t\t*"<< endl;
            cout<<"\t\t*****************************************"<< endl;
            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";


            return true;
        }
        else
        {
            //score+=10;
        }
    }

    return false;

}

bool goal()
{
    if(ball_x==32 && (ball_y<=6 && ball_y>=-6))
    {
        cout<<"\n\n\n\n\n";
            cout<<"\t\t**************** GAME OVER **************"<< endl;
            cout<<"\t\t*\t\t\t\t\t*"<< endl;
            cout<<"\t\t*\t\t\t\t\t*"<< endl;
            cout<<"\t\t*\t\t\t\t\t*"<< endl;
            cout<<"\t\t*\t\t GOOOOOAAAL   \t\t*"<< endl;
            cout<<"\t\t*\t\t\t\t\t*"<< endl;
            cout<<"\t\t*\t\t PLAY AGAIN  \t\t*"<< endl;
            cout<<"\t\t*\t\t\t\t\t*"<< endl;
            cout<<"\t\t*\t\t\t\t\t*"<< endl;
            cout<<"\t\t*\t\t\t\t\t*"<< endl;
            cout<<"\t\t*****************************************"<< endl;
            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        return true;
    }
    else return false;
}

void SpecialInput(int key, int x, int y)
{
    switch (key)
    {
    case 27 :
    case 'q':
        exit(0);
        break;

    case GLUT_KEY_UP:
        ball_y+=0.5;
        if(ball_y>23) ball_y--;

        if(termination()) exit(0);
        if(goal()) exit(0);
        break;

    case GLUT_KEY_DOWN:
        ball_y-=0.5;
        if(ball_y<-23) ball_y++;
        if(termination()) exit(0);
        if(goal()) exit(0);
        break;

    case GLUT_KEY_RIGHT:
        ball_x+=0.5;
        if(ball_x>33) ball_x--;
        if(termination()) exit(0);
        if(goal()) exit(0);
        break;
    case GLUT_KEY_LEFT:
        ball_x-=0.5;
        if(ball_x<-33) ball_x++;
        if(termination()) exit(0);
        if(goal()) exit(0);
        break;
    }

    glutPostRedisplay();

}
static void idle(void)
{
    glutPostRedisplay();
}



/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("<< Dribble The Ball, Avoid The Obstacles >> (mahadi_CSE_2k12)");

    glutReshapeFunc(resize);
    glutSpecialFunc(SpecialInput);
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}
