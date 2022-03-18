#include "iGraphics.h"
#include <math.h>
#include<string.h>

int x = 640, y = 360, r = 15,dx,dy;
double xa[]={100, 100, 300},sx= 1280,sy=720;
double ya[]={100, 0, 150};
char  str[]="Jakaria", position[100];
double px=0, py=0 ;
int  mode_point = 0;




/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
    //place your drawing codes here
    iClear();

    /**draw graphs*/

    iSetColor(25,25,75);
    //iSetColor(00,00,00);
    for(int i = 1; i < sx / 2; i+=20){
        iLine(0, sy/2 + i, sx, sy/2+i);
        iLine(0, sy/2 - i, sx, sy/2-i);
        iLine(sx/2+i , 0, sx/2+i, sy);
        iLine(sx/2-i , 0, sx/2-i, sy);
    }


    /***draw axes**/
    iSetColor(25,200,200);
    iLine(0, sy/2 , sx, sy/2);
    iLine(sx/2, 0, sx/2, sy);

    /**straight line**/

    double m=1, c= 0;  //user input.. can also be written  ax + by + c =0;
    iSetColor(20,255,250);
    for(float j = 0; j <= sx; j+=0.25){
        double gy = (sy/2) + m * (j - (sx / 2)) + c;
            iPoint(j, gy,1);
        gy = (sy/2) - m * (j - (sx / 2)) + c;
        iPoint(j, gy,1);
    }

    /**parabola**/


    double a=50;   // will be  modified
    for(float j = 0; j <= sx; j+=0.15){
        double gy = sy / 2 + sqrt(4 * a * ( j - sx / 2 + 640 ));
        if( gy >= 0 && gy <= sy)    iPoint(j , gy , 1.5);
        gy = sy / 2 - sqrt(4  * a * ( j- sx / 2 + 640));
        if( gy >= 0 && gy <= sy)    iPoint(j , gy , 1);

    }

    //polynomial   (3 degree)
    double
    qa = 0,
    qb = 0.025,
    qc = 0,
    qd = 0;

    iSetColor(20,175,250);
    for(float j = 0; j<sx; j+=0.15){
        double gy = sy / 2 + qa * pow(j-sx/2, 3) + qb *  pow((j-sx/2), 2) + qc * pow(j- sx / 2 , 1) + qd  ;
        if( gy >= 0 && gy <= sy)    iPoint(j , gy , 1);
    }


    iSetColor(25,225,200);
    iEllipse(sx/2, sy/2,400,250);
    iSetColor(25,225,200);
    iEllipse(sx/2, sy/2,250,400);
    iSetColor(125,255,200);
    iCircle(x,y,100);
    iSetColor(10,100,255);


    /** point tracing **/

    if(mode_point==1) {
        double kx=1;
        if(px > sx-175) kx=-1;
        double A[7]={
                    px,
                    px+25.0 * kx,
                    px+25.0 * kx,
                    px+175.0 * kx,
                    px+175.0 * kx,
                    px+25.0 * kx,
                    px+25.0 * kx
                    },
                B[7]={
                    py,
                    py-8,
                    py-25.0,
                    py-25.0,
                    py+25.0,
                    py+25.0,
                    py+8};
            iFilledCircle(px, py,5);
            iSetColor(100,210,100);
            iPolygon(A,B,7);
            pos_from_int();

            iSetColor(10,255,100);
            iText(px + 30 - (1-kx)*100, py-4, position,GLUT_BITMAP_HELVETICA_18);
    }
}


void pos_from_int()
{
    int intpos_x= px-sx/2.0, intpos_y = py - sy/2.0; // origin has been transferred

    char pos_temp[]="x = ";
    strcpy(position, pos_temp);
    sprintf(pos_temp,"%d", intpos_x);
    strcat(position, pos_temp);
    strcat(position,", y = ");
    sprintf(pos_temp,"%d", intpos_y);
    strcat(position, pos_temp);
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //printf("x = %d, y= %d\n",mx,my);
    //place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/


void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        //printf("x = %d, y= %d\n",mx,my);
        //x += 5;
        // y += 5;

       px=mx;
       py=my;
       mode_point = 1;


    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        //x -= 5;
        //y -= 5;
       mode_point = 0;

    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{

    if(key == 'q')
    {
        exit(0);
    }
    else if(key == 'p')
    {
        iPauseTimer(0);
    }
    else if(key == 'r')
    {
        iResumeTimer(0);
    }
    else if(key == '+')
    {
        dx++;
        dy++;
    }
    else if(key == '-')
    {
        dx--;
        dy--;
    }

    //place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenever user hits special keys like-
	function keys, home, end, pg up, pg down, arrows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE_DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

    if(key == GLUT_KEY_F1)
    {
        exit(0);// exits from all the program.
    }

    else if(key == GLUT_KEY_UP)
    {
        y+=10;
    }
    else if(key == GLUT_KEY_DOWN)
    {
        y-=10;
    }
    else if(key == GLUT_KEY_RIGHT)
    {
        x+=10;
    }
    else if(key == GLUT_KEY_LEFT)
    {
        x-=10;
    }

    //place your codes for other keys here
}

void my_anim(){

	x += dx;
	y += dy;

	if(x > 1280 || x < 0)dx = -dx;
	if(y > 720  || y < 0)dy = -dy;
}

int main()
{
    //place your own initialization codes here.
    /*iSetTimer(10 ,my_anim);
	dx = 10;
	dy = 10;*/

    iInitialize(sx, sy, " Project 1126 ");
    return 0;
}

