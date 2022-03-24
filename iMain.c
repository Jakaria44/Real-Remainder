# include "iGraphics.h"
#include <math.h>
#include<string.h>

int r = 15,dx,dy;
double xa[]={100, 100, 300};
double ya[]={100, 0, 150};
char  str[]="Jakaria", position[100];
double x = 840, y =360 , px=0, py=0 ,t=0;
int  tri = 1,mode_point = 0, mode_axis = 1 , mode_grid = 1;

double sx = 1280, sy = 720;

/*****              general equation        *****/
/*****  ax2 + by2 + hxy + gx + fy + c = 0   *****/

double a=01,
       b=-01,
       c=0,
       f=0,
       g=0,
       h=0,
       D;          // discriminant: D = (h*i-f )*(h*i-f )- 4 * b * ( a * i*i + g * i + c);



void draw_grid()
{

    iSetColor(25,25,75);
    for(int i = 1; i < sx / 2; i+=20){
        iLine(0, sy/2 + i, sx, sy/2+i);
        iLine(0, sy/2 - i, sx, sy/2-i);
        iLine(sx/2+i , 0, sx/2+i, sy);
        iLine(sx/2-i , 0, sx/2-i, sy);
    }

}

void draw_axes()
{
    iSetColor(25,200,200);
    iLine(0, sy/2 , sx, sy/2);
    iLine(sx/2, 0, sx/2, sy);
}

void draw_st_line()
{

    double m=1, c= 0;  //user input.. can also be written  ax + by + c =0;
    iSetColor(20,255,250);
    for(float j = 0; j <= sx; j+=0.25){
        double gy = (sy/2) + m * (j - (sx / 2)) + c;
            iPoint(j, gy,1);
            gy = (sy/2) - m * (j - (sx / 2)) + c;
            iPoint(j, gy,1);
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

void draw_polynomial()
{
    double
    qa = 0,
    qb = 0.025,
    qc = 0,
    qd = 0;

    iSetColor(20,175,250);
    for(float j = 0; j<sx; j+=1){
        //double gy = sy / 2 + qa * pow(j-sx/2, 3) + qb *  pow((j-sx/2), 2) + qc * pow(j- sx / 2 , 1) + qd  ;
        double gy = sy / 2 +10*sin((j-sx/2)*180/3.14159);
        if( gy >= 0 && gy <= sy)    iPoint(j , gy , 1);
    }
}

void draw_parabola()
{
    double a=50;   // will be  modified
    for(float j = 0; j <= sx; j+=0.15){
        double gy = sy / 2 + sqrt(4 * a * ( j - sx / 2 + 640 ));
        //double gy = sy / 2 + pow((j-sx/2),2)*cos(1/(j-sx/2));
        if( gy >= 0 && gy <= sy)    iPoint(j , gy , 1.5);
        gy = sy / 2 - sqrt(4  * a * ( j- sx / 2 + 640));
        if( gy >= 0 && gy <= sy)    iPoint(j , gy , 1);

    }

}

void trace_point()
{

    if(mode_point==1) {
        double kx=1;
        if(px > sx-185) kx=-1;
        double A[7]={
                    px,
                    px+25.0 * kx,
                    px+25.0 * kx,
                    px+185.0 * kx,
                    px+185.0 * kx,
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
        iText(px + 30 - (1-kx)*105, py-4, position,GLUT_BITMAP_HELVETICA_18);
    }
}


double f_tri(double aa, int a)
{
    switch (a)
    {
    case 1:    return sin(aa);

    case 11:   return asin(aa);                                                    // arc sin x

    case 2:    return cos(aa);

    case 22:   return acos(aa);

    case 3:    return tan(aa);

    case 33:   return atan(aa);

    case 4:    return 1 / tan(aa);                                                     //cot(aa)

    case 44:   return atan(1/aa);

    case 5:    return 1/cos(aa);                                                           //sec(aa)

    case 55:   return acos(1/aa);

    case 6:    return 1/sin(aa);                                                           //cosec(aa)

    case 66:   return asin(1/aa);

    }
}

double f_trigon(double x, int a){           // a: checking function (sin or cos or ...)
        double tri_x , tri_y ;

        tri_x = (x-sx/2)*3.1415926535/180;
        tri_y = sy / 2 + 100 * f_tri(tri_x, a);

        if(tri_y > sy || tri_y < 0) return NULL;
        return tri_y;

}
void draw_trigon(int a)
{

    iSetColor(20,175,250);
    for(double i = 0 ;i < sx; i+=.5)
    {
        double tri_y = f_trigon(i,a);
        if(tri_y != NULL)
        iPoint(i, tri_y, 1);
    }

}

void  tri_function_text(int a)
{

    switch (a)
    {
    case 1: iText(50, 540, "y = sin (x)",GLUT_BITMAP_HELVETICA_18);
            return ;

    case 11:    iText(50,540, "y = arc sin (x)",GLUT_BITMAP_HELVETICA_18);
            return ;

    case 2:     iText(50, 540 , "y = cos (x)",GLUT_BITMAP_HELVETICA_18);
            return ;

    case 22:     iText(50, 540 , "y = arc cos (x)",GLUT_BITMAP_HELVETICA_18);
            return ;

    case 3:     iText(50, 540, "y = tan (x)",GLUT_BITMAP_HELVETICA_18);
            return ;

    case 33:     iText(50, 540 , "y = arc tan (x)",GLUT_BITMAP_HELVETICA_18);
            return ;

    case 4:     iText(50, 540 , "y = cot (x)",GLUT_BITMAP_HELVETICA_18);
            return ;

    case 44:     iText(50, 540 , "y = arc cot (x)",GLUT_BITMAP_HELVETICA_18);
            return ;

    case 5:     iText(50, 540 , "y = sec (x)",GLUT_BITMAP_HELVETICA_18);
            return ;

    case 55:     iText(50, 540 , "y = arc sec (x)",GLUT_BITMAP_HELVETICA_18);
            return ;

    case 6:     iText(50, 540 , "y = cosec (x)",GLUT_BITMAP_HELVETICA_18);
            return ;

    case 66:     iText(50, 540 , "y = arc cosec (x)",GLUT_BITMAP_HELVETICA_18);
            return ;

    }

}

double arith_pos(double x)
{
    double fy;
    if(b !=0){

        fy = ( -(h * x + f ) + sqrt(D)) / ( 2 * b);
        return fy;
    }
    if(b == 0){
        return -(a * x * x + g * x + c)/( h * x + f);
    }
}
double arith_neg(double x)
{
    double fy;
    if(b !=0){

        fy = ( -(h * x + f ) - sqrt(D)) / ( 2 * b);
        return fy;
    }
    if(b == 0){
        return -(a * x * x + g * x + c)/( h * x + f);
    }
}

void draw_conic()
{

    for(double i =- sx / 2; i < sx / 2; i+=.1){
        D= (h*i-f )*(h*i-f )- 4 * b * ( a * i*i + g * i + c);

        if( D < 0) continue;
        double conic_y;
        conic_y = sy / 2 + arith_neg(i );
        if(conic_y < sy || conic_y > 0) iPoint( i +sx / 2 , conic_y, 1);
        conic_y = sy/2 + arith_pos(i );
        if(conic_y < sy || conic_y > 0) iPoint( i +sx / 2, conic_y, 1);
    }

}

/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
    //place your drawing codes here
    iClear();

    /*
    iCircle(300,320,20);/*
    iSetColor(25,255,200);
    iFilledRectangle(x+20,y+20,100,100);
    iLine(300,300,545,515);
    iSetColor(25,205,255);
    iText(10,10,"click to go",GLUT_BITMAP_HELVETICA_18);
    iFilledPolygon(xa, ya, 3);

    iShowBMP2(500,564,"wheel.bmp", 0xffffff);
    iLine(300,300,500,300);
    //iRectangle(375,320,70,20);
    double xa[]={375,400,450,390};
    double ya[]={320,175,175,320};
    iPolygon(xa, ya, 4);
    iLine(340,500,300,325);*/

    /**draw grids*/

    if(mode_grid)  draw_grid();

    if(mode_axis)draw_axes();

    //draw_st_line();

    //draw_parabola();

    //draw_polynomial(); //   (3 degree)

    draw_trigon(tri);
    tri_function_text(tri);
    // porer egulo modify korte hobe..


    iSetColor(25,225,200);
    iEllipse(sx/2, sy/2,400,250);
    iSetColor(25,225,200);
    iEllipse(sx/2, sy/2,250,400);
    iSetColor(125,255,200);
    iCircle(x,y,75);
    iSetColor(10,100,255);


    /** point tracing **/
    trace_point();

    /** text */
    iSetColor(50,200,250);
    iText(20,10,"press 'g' to show or hide GRIDs",GLUT_BITMAP_HELVETICA_18);
    iText(20,50,"press 'a' to show or hide AXES",GLUT_BITMAP_HELVETICA_18);
    iText(20,85,"press right mouse click to hide point tracing",GLUT_BITMAP_HELVETICA_18);
    iText(20,120,"Pess click anywhere in the grid to show point tracing",GLUT_BITMAP_HELVETICA_18);

    /**********
        y = sin(5x)
        5x


    **********/
    iFilledCircle(x,y,10);

    iSetColor(25,155,200);
    draw_conic();

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
    else if(key == 'g')
        {
            mode_grid = !mode_grid;
        }
    else if(key == 'a')
        {
            mode_axis = !mode_axis;
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

    x=t;
    y = f_trigon(t,tri) ;
    t+=2;
    if(t>=sx) t=0;

    /*
	x += dx;
	y += dy;

	if(x > 1280 || x < 0)dx = -dx;
	if(y > 720  || y < 0)dy = -dy;
        */
}

int main()
{
    //place your own initialization codes here.
    /*iSetTimer(10 ,my_anim);
	dx = 10;
	dy = 10;*/

	iSetTimer(1,my_anim);

    iInitialize(sx, sy, " Project 1126 ");
    return 0;
}

