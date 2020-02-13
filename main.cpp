#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include<string>
#include<bits/stdc++.h>

using namespace std;

float transFactor1 = 0.0f;    //translation factor for background hill (shortest1)
float transFactor2 = 0.0f;    //translation factor for background hill (longest)
float transFactor3 = 0.0f;    //translation factor for background hill (medium)
float transFactor4 = 0.0f;    //translation factor for background sun (round yellow image)
float transFactor5 = -0.01f;    //translation factor for obstacle (shortest2)
float transFactor6 = -0.01f;    //translation factor for obstacle (medium)
float transFactor7 = -0.01f;    //translation factor for obstacle (longest)
float transFactor8 = -0.01f;    //translation factor for obstacle (shortest)
float transFactor9 = 0.0f;    //translation factor for ball up
float transFactor10 = 0.0f;    //translation factor for ball up right
float transFactor11 = 0.0f;    //translation factor for life ball1
float transFactor12 = 0.0f;    //translation factor for life ball2

int a=450, b=225, r=50;       //variables for drawing a circle
int ab=-300, bb=-85, rb=15;   //variables for drawing a ball
int al=1600, bl=-85, rl=10;   //variables for drawing life ball1
int al2=3000, bl2=-30, rl2=10; //variables for drawing life ball2
int score=0;                  //variable for storing score
string str = "";              //convert score to string and store here
string go = "SCORE: ";
float speed=30.0f;

int life = 3;
int lifer = 3;
string strlife = "";              //convert life to string and store here
string go2 = "Life: ";

int upPressed = 0;
int pressed = 0;

bool down = false;
bool gameOver = false;


void printText(float x, float y, string st)                      //function for drawing text
{
    glColor3f(0.0,1.0,0.7);
    glRasterPos2f( x, y);
    for(int i=0;i< st.size();i+=1){
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, st[i]);
    }
}

float round(float var)
{
    float value = ((int)(100 * var));
    return (float)value / 100;
}

float getX(int val)                                             //function for getting position of x after being translated to certain point
{
    int width = glutGet(GLUT_WINDOW_WIDTH);
    float frac = (float)val/((float)width/2);
    return frac;
}

float getY(int val)                                             //function for getting position of y after being translated to certain point
{
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    float frac = (float)val/((float)height/2);
    return frac;
}

void draw(int x, int y){                                        //helper function for drawing circle (EX: here for drawing the sun)

    glBegin(GL_LINE_LOOP);

        glVertex2i(x+a,y+b);
        glVertex2i(x+a,-y+b);
        glVertex2i(-x+a,y+b);
        glVertex2i(-x+a,-y+b);
        glVertex2i(y+a,x+b);
        glVertex2i(y+a,-x+b);
        glVertex2i(-y+a,x+b);
        glVertex2i(-y+a,-x+b);

}

void drawBall(int x, int y){                                        //helper function for drawing circle (EX: here for drawing the ball)

    glBegin(GL_LINE_LOOP);

        glVertex2i(x+ab,y+bb);
        glVertex2i(x+ab,-y+bb);
        glVertex2i(-x+ab,y+bb);
        glVertex2i(-x+ab,-y+bb);
        glVertex2i(y+ab,x+bb);
        glVertex2i(y+ab,-x+bb);
        glVertex2i(-y+ab,x+bb);
        glVertex2i(-y+ab,-x+bb);

}

void drawLifeBall(int x, int y){                                        //helper function for drawing circle (EX: here for drawing the life ball1)

    glBegin(GL_LINE_LOOP);

        glVertex2i(x+al,y+bl);
        glVertex2i(x+al,-y+bl);
        glVertex2i(-x+al,y+bl);
        glVertex2i(-x+al,-y+bl);
        glVertex2i(y+al,x+bl);
        glVertex2i(y+al,-x+bl);
        glVertex2i(-y+al,x+bl);
        glVertex2i(-y+al,-x+bl);

}

void drawLifeBall2(int x, int y){                                        //helper function for drawing circle (EX: here for drawing the life ball2)

    glBegin(GL_LINE_LOOP);

        glVertex2i(x+al2,y+bl2);
        glVertex2i(x+al2,-y+bl2);
        glVertex2i(-x+al2,y+bl2);
        glVertex2i(-x+al2,-y+bl2);
        glVertex2i(y+al2,x+bl2);
        glVertex2i(y+al2,-x+bl2);
        glVertex2i(-y+al2,x+bl2);
        glVertex2i(-y+al2,-x+bl2);

}

void drawScene()                                        //function for drawing image on screen
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
        glColor3ub(128,64,0);
        gluOrtho2D(-500.0, 500.0, -300.0, 300.0);
        glBegin(GL_QUAD_STRIP);                         //for drawing the brown color dirt on the bottom of the screen
            glVertex2i(-500,-300);
            glVertex2i(500,-300);
            glVertex2i(-500,-100);
            glVertex2i(500,-100);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glColor3ub(0,128,0);
        gluOrtho2D(-500.0, 500.0, -300.0, 300.0);
        glBegin(GL_QUAD_STRIP);                        //for drawing the green grass street on the screen
            glVertex2i(-500,-150);
            glVertex2i(500,-150);
            glVertex2i(-500,-100);
            glVertex2i(500,-100);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glColor3ub(193,251,255);
        gluOrtho2D(-500.0, 500.0, -300.0, 300.0);
        glBegin(GL_QUAD_STRIP);                        //for drawing the blue sky on the top of the screen
            glVertex2i(-500,-100);
            glVertex2i(500,-100);
            glVertex2i(-500,300);
            glVertex2i(500,300);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glColor3ub(253,184,19);
        glTranslatef(transFactor4,0,0);               //for drawing circle (EX: here the yellow sun)
        gluOrtho2D(-500.0, 500.0, -300.0, 300.0);
        int x=0, y=r, d=1-r;
        while(x<=y){
            draw(x,y);
            if(d<0){
                d=d+2*x+3;
                x+=1;
            }else{
                d=d+2*(x-y)+5;
                x+=1;
                y-=1;
            }
        }
        glEnd();
    glPopMatrix();


    glPushMatrix();
        glColor3ub(255,255,255);
        glTranslatef(transFactor1,0,0);
        glBegin(GL_TRIANGLE_STRIP);                    //for drawing background hill (shortest)
            glVertex2f(getX(-500),getY(-100));
            glVertex2f(getX(-300),getY(-100));
            glVertex2f(getX(-400),getY(100));
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glColor3ub(255,255,255);
        glTranslatef(transFactor2,0,0);
        glBegin(GL_TRIANGLE_STRIP);                    //for drawing background hill (longest)
            glVertex2f(getX(-300),getY(-100));
            glVertex2f(getX(100),getY(-100));
            glVertex2f(getX(-100),getY(200));
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glColor3ub(255,255,255);
        glTranslatef(transFactor3,0,0);
        glBegin(GL_TRIANGLE_STRIP);                   //for drawing background hill (medium)
            glVertex2f(getX(200),getY(-100));
            glVertex2f(getX(400),getY(-100));
            glVertex2f(getX(300),getY(150));
        glEnd();
    glPopMatrix();


    glPushMatrix();
        glColor3ub(0,0,0);
        glTranslatef(transFactor5,0,0);
        glBegin(GL_POLYGON);                               //for drawing the obstacle (shortest1)
            glVertex2f(getX(600),getY(-100));
            glVertex2f(getX(585),getY(-50));
            glVertex2f(getX(600),getY(-50));
            glVertex2f(getX(585),getY(-100));
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glColor3ub(0,0,0);
        glTranslatef(transFactor6,0,0);
        glBegin(GL_POLYGON);                            //for drawing the obstacle (medium)
            glVertex2f(getX(1000),getY(-100));
            glVertex2f(getX(985),getY(-25));
            glVertex2f(getX(1000),getY(-25));
            glVertex2f(getX(985),getY(-100));
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glColor3ub(0,0,0);
        glTranslatef(transFactor7,0,0);
        glBegin(GL_POLYGON);                            //for drawing the obstacle (longest)
            glVertex2f(getX(1300),getY(-100));
            glVertex2f(getX(1285),getY(0));
            glVertex2f(getX(1300),getY(0));
            glVertex2f(getX(1285),getY(-100));
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glColor3ub(0,0,0);
        glTranslatef(transFactor8,0,0);
        glBegin(GL_POLYGON);                            //for drawing the obstacle (shortest2)
            glVertex2f(getX(1800),getY(-100));
            glVertex2f(getX(1785),getY(-50));
            glVertex2f(getX(1800),getY(-50));
            glVertex2f(getX(1785),getY(-100));
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glColor3ub(255,0,0);
        glTranslatef(transFactor10,transFactor9,0);               //for drawing ball
        gluOrtho2D(-500.0, 500.0, -300.0, 300.0);
        int xb=0, yb=rb, db=1-rb;
        while(xb<=yb){
            drawBall(xb,yb);
            if(db<0){
                db=db+2*xb+3;
                xb+=1;
            }else{
                db=db+2*(xb-yb)+5;
                xb+=1;
                yb-=1;
            }
        }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glColor3ub(0,0,255);
        glTranslatef(transFactor11,0,0);               //for drawing life ball1
        gluOrtho2D(-500.0, 500.0, -300.0, 300.0);
        int xl=0, yl=rl, dl=1-rl;
        while(xl<=yl){
            drawLifeBall(xl,yl);
            if(dl<0){
                dl=dl+2*xl+3;
                xl+=1;
            }else{
                dl=dl+2*(xl-yl)+5;
                xl+=1;
                yl-=1;
            }
        }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glColor3ub(0,0,255);
        glTranslatef(transFactor12,0,0);               //for drawing life ball2
        gluOrtho2D(-500.0, 500.0, -300.0, 300.0);
        int xl2=0, yl2=rl2, dl2=1-rl2;
        while(xl2<=yl2){
            drawLifeBall2(xl2,yl2);
            if(dl2<0){
                dl2=dl2+2*xl2+3;
                xl2+=1;
            }else{
                dl2=dl2+2*(xl2-yl2)+5;
                xl2+=1;
                yl2-=1;
            }
        }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glColor3ub(255,0,0);

        stringstream ss;
        if(life>0)
        {
            ss << score;

            str = ss.str();
            go = "Score: ";
            go += str;
        }

        //cout<<transFactor8;
        printText(-0.95,-0.92,go);                     //for printing score on the screen
    glPopMatrix();

    glPushMatrix();
        glColor3ub(0,255,0);

        stringstream ss2;
        ss2 << life;

        strlife = ss2.str();
        go2 = "Life: ";
        go2 += strlife;

        if(life<=0)
        {
            go2 = "Game over :(";
            gameOver = true;
            printf("\a");
            transFactor1=transFactor2=transFactor3=transFactor4=transFactor5=transFactor6=transFactor7=transFactor8=transFactor9=transFactor10=transFactor11=transFactor12=0.0f;
        }
        printText(-0.70,-0.92,go2);                     //for printing score on the screen
    glPopMatrix();

    glutSwapBuffers();
}

void update(int value)                                 //function mainly for updating translation factor value
{
    lifer=3;

    int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	if(width!=1000 || height!=600){
        glutReshapeWindow(1000,600);                   //constant screen size
	}
    ///////////////////////////////////////////
    transFactor1-=0.01f;
    if(transFactor1<getX(-300)){
        transFactor1 = 1 * getX(1000);
    }
    transFactor2-=0.01f;
    if(transFactor2<getX(-600)){
        transFactor2 = 1 * getX(1000);
    }
    transFactor3-=0.01f;
    if(transFactor3<getX(-900)){
        transFactor3 = 1 * getX(1000);
    }
    transFactor4-=0.001f;
    if(transFactor4<getX(-1000)){
        transFactor4 = 1 * getX(1000);
    }
    transFactor5-=0.01f;
    if(transFactor5<getX(-1100)){
        transFactor5 = 1 * getX(1000);
        score+=1;
    }
    transFactor6-=0.01f;
    if(transFactor6<getX(-1500)){
        transFactor6 = 1 * getX(1000);
        score+=1;                                    //one obstacle = 1 point
    }
    transFactor7-=0.01f;
    if(transFactor7<getX(-1800)){
        transFactor7 = 1 * getX(1000);
        score+=1;                                    //one obstacle = 1 point
    }
    transFactor8-=0.01f;
    if(transFactor8<getX(-2300)){
        transFactor8 = 1 * getX(1000);
        score+=1;                                    //one obstacle = 1 point
    }

    transFactor11-=0.01f;
    if(transFactor11<getX(-2500)){
        transFactor11 = 1 * getX(1000);
    }

    transFactor12-=0.01f;
    if(transFactor12<getX(-3500)){
        transFactor12 = 1 * getX(100);
    }



    float x1,x2,y1,y2,bx,by,by2;

    bx = round(getX(-300));
    by = round(getY(-85) + transFactor9);
    by2 = round(getY(-85-15) + transFactor9);

    ///Life ball1
    x1 = round(getX(1600) + transFactor11);
    y1 = round(getY(-85));
    x2 = round(getX(1610) + transFactor11);
    y2 = round(getY(-75));

    if(!gameOver)
    {
        if((x1 <= bx) && (x2 >= bx))
        {
            if((y1 <= by) && (y2 >= by))
            {
                //lifer=1;
                life++;
                printf("\a");
                transFactor11 = 1 * getX(1000);
                cout<<"\nLife ";
            }
            else
            {
                //lifer=2;
            }

        }
    }

    ///Life ball2
    x1 = round(getX(3000) + transFactor12);
    y1 = round(getY(-30));
    x2 = round(getX(3010) + transFactor12);
    y2 = round(getY(-20));

    if(!gameOver)
    {
        if((x1 <= bx) && (x2 >= bx))
        {
            cout<<"\nBall ";
            cout<<" Y1: "<<y1;
            cout<<" Y2: "<<y2;
            cout<<" By: "<<by;

            if((y1 <= by) && (y2 >= by))
            {
                //lifer=1;
                life++;
                printf("\a");
                transFactor12 = 1 * getX(100);
                cout<<"\nLife ";
            }
            else
            {
                //lifer=2;
            }

        }
    }



    ///shortest1 obstacle
    x1 = round(getX(600) + transFactor5);
    y1 = round(getY(-50));
    x2 = round(getX(585) + transFactor5);
    //y2 = round(getY(-50));

    if(x1 == bx)
    {
        if(by2 <= y1)
        {
            lifer=1;
            life--;
            printf("\a");
            cout<<"\nOver1 ";
        }
        else
        {
            lifer=2;
        }

    }
    else if(x2 == bx)
    {
        if(lifer==2)
        {
            if(by2 <= y1)
            {
                life--;
                printf("\a");
                cout<<"\nOver2 ";
            }
        }
    }

    ///shortest2 obstacle
    x1 = round(getX(1800) + transFactor8);
    y1 = round(getY(-50));
    x2 = round(getX(1785) + transFactor8);

    if(x1 == bx)
    {
        if(by2 <= y1)
        {
            lifer=1;
            life--;
            printf("\a");
            cout<<"\nOver1 ";
        }
        else
        {
            lifer=2;
        }

    }
    else if(x2 == bx)
    {
        if(lifer==2)
        {
            if(by2 <= y1)
            {
                life--;
                printf("\a");
                cout<<"\nOver2 ";
            }
        }
    }



    ///medium obstacle
    x1 = round(getX(1000) + transFactor6);
    y1 = round(getY(-25));
    x2 = round(getX(985) + transFactor6);

//    cout<<" \nX1: "<<x1<<" Y1: "<<y1;
//
//    cout<<" \nBX: "<<bx;
//    cout<<" BY: "<<by;

    if(x1 == bx)
    {
        cout<<" \nX1: "<<x1<<" Y1: "<<y1;

        cout<<" \nBX: "<<bx;
        cout<<" BY: "<<by;
        cout<<" BY2: "<<by2;
        if(by2 <= y1)
        {
            lifer=1;
            life--;
            printf("\a");
            cout<<"\nOver1 ";
        }
        else
        {
            lifer=2;
        }

    }
    else if(x2 == bx)
    {
        if(lifer==2)
        {
            if(by2 <= y1)
            {
                life--;
                printf("\a");
                cout<<"\nOver2 ";
            }
        }
    }



    ///longest obstacle
    x1 = round(getX(1300) + transFactor7);
    y1 = round(getY(0));
    x2 = round(getX(1285) + transFactor7);

    if(x1 == bx)
    {
        if(by2 <= y1)
        {
            lifer=1;
            life--;
            printf("\a");
            cout<<"\nOver1 ";
        }
        else
        {
            lifer=2;
        }

    }
    else if(x2 == bx)
    {
        if(lifer==2)
        {
            if(by2 <= y1)
            {
                life--;
                printf("\a");
                cout<<"\nOver2 ";
            }
        }
    }


    ///////////////////////////////////////////
    speed += 0.01f;
    glutPostRedisplay();
    glutTimerFunc(speed,update,0);
}

float up = 0;
float right =0;

void updateBall(int value)
{
    if ( upPressed==1 && transFactor9 <0.26)
    {
//        up+=.02;
//        transFactor9 = up;
//
//        glutPostRedisplay(); //Tell GLUT that the display has changed
//        glutTimerFunc(30, updateBall, 0);

        if(upPressed==1){
            up+=.02;
            transFactor9 = up;
            glutPostRedisplay();
            glutTimerFunc(30, updateBall, 0);
        }else{
            transFactor9 = down;
            glutPostRedisplay();
            glutTimerFunc(30, updateBall, 0);
        }
    }
    else if ( upPressed==2 && transFactor9 <0.50)
    {
        up+=.02;
        transFactor9 = up;

        glutPostRedisplay(); //Tell GLUT that the display has changed
        glutTimerFunc(30, updateBall, 0);

    }

}

void updateBallDown(int value)
{

    //upPressed = 1;
    //up = 0;

    down = true;

    if(upPressed == 1 && transFactor9>=0)
    {
        transFactor9 -= 0.02;
        up -= 0.02;

        if(transFactor9 <= 0)
        {
            pressed = 0;
            up = 0;
            upPressed = 0;
            transFactor9 = 0;
            glutPostRedisplay();

            down = false;
        }

        else
        {
            glutPostRedisplay(); //Tell GLUT that the display has changed
            glutTimerFunc(30, updateBallDown, 0);
        }

    }
    else if(upPressed == 2 && transFactor9>= 0.26)
    {
        transFactor9 -= 0.02;
        up -= 0.02;

        glutPostRedisplay(); //Tell GLUT that the display has changed
        glutTimerFunc(30, updateBallDown, 0);

        if(transFactor9 <= 0.26)
        {
            upPressed = 1;
        }
    }

}

//void updateBallRight(int value)
//{
//
//    transFactor10+=0.01f;
//
//    if(transFactor10>getX(775)){
//        transFactor10 = 1 * getX(775);
//    }
//
//    glutPostRedisplay(); //Tell GLUT that the display has changed
//
//}

//void updateBallLeft(int value)
//{
//    transFactor10-=0.01f;
//
//    if(transFactor10<getX(-182)){
//        transFactor10 = 1 * getX(-182);
//    }
//
//    glutPostRedisplay(); //Tell GLUT that the display has changed
//
//}

void specialKeys(int key, int x, int y) {
    switch (key) {
      case GLUT_KEY_UP:
          if(!down && !gameOver)
          {
              if(pressed==0)
              {
                  upPressed = 1;
                  pressed = 1;

                  updateBall(0);
                  glutTimerFunc(800, updateBallDown, 0);
              }
              else if(pressed==1)
              {
                pressed = 2;
                upPressed = 2;
                updateBall(0);
              }
          }
          break;
//      case GLUT_KEY_DOWN:
//          updateBallDown(0);
//          break;

//        case GLUT_KEY_RIGHT:
//          updateBallRight(0);
//          break;
//        case GLUT_KEY_LEFT:
//          updateBallLeft(0);
//          break;

    }
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 600);
	glutCreateWindow("Bounce Game");
	glutDisplayFunc(drawScene);
	glutSpecialFunc(specialKeys); //Special Key Handler
	glutTimerFunc(20,update,0);
	glutTimerFunc(20,updateBall,0);
	glutMainLoop();
	return 0;
}
