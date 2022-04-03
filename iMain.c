# include "iGraphics.h"
#include <math.h>
#include<string.h>
#include <windows.h>

double sx = 1280,
        sy = 720,
        scale_x = sx / 1280.0,
        scale_y = sy/720.0 ;
int r = 15, t = 0;
int len;
int mode;
char str[100], str2[100] , tok[100][100];


char  position[100];
double x = 840 *scale_x , y =360*scale_x , px , py  ;
//x, y moving circle.

double point_array_size = sx/0.05;
int p_size = point_array_size;

/*****   modes     *****/
int mode_point = 0,
    mode_axis = 1 ,
    mode_grid = 1,
    draw_mode = 0,
    tips_mode = 0,
    mode_color=0 ;


/*****              general equation          *****/
/*****  ax^2 + by^2 + hxy + gx + fy + c = 0   *****/

double  a =   0,
        b =   0 ,
        c =   0,
        f =   0,
        g =   0 ,
        h =   0 ,
        D;          // discriminant: D = (h*i-f )*(h*i-f )- 4 * b * ( a * i*i + g * i + c);

char general[][10]= {"x^2","y^2", "xy","x", "y"};


typedef struct point{
    double x;
    double y1;
    double y2;
} point;

typedef struct color{
    double R;
    double G;
    double B;
} color;

point *p1 = NULL;

int myatoi(char* str)
{
	int res = 0, sign = 1;
	for (int i = 0; str[i] != '\0'; ++i)
    {

        if(str[i]==' ') continue;
        if(str[i]== '-') sign = -1;
        else
		    res = res * 10 + str[i] - '0';
    }
	return res*sign;
}

int strfind(char a[], char s[])
{
    int la, ls, j = 0;

    la = strlen(a);
    ls = strlen(s);
    if(la < ls) return -1;

    for(int i = 0 ; i < la; i++){

        if(a[i] == s[j]) j++;

        else j = 0;
        if( j == ls) return i - ls + 1;
    }
    return -1;
}

void refresh_neg(char *str){
    int ls = strlen(str), m= 0, n ;
    while (m<ls){
        if(str[m]=='-'){
            for(n = ls; n >m ; --n )
                str[n] = str[n-1];
            str[m] = '+';
            str[++ls] = '\0';
            m++;
        }
        m++;
    }
}

void reset_co_eff(){
    a = 0;
    b = 0;
    c = 0;
    f = 0;
    g = 0;
    h = 0;

}

//extracts the values of a,b,c,g,f,h from str[]

void co_eff(char *str){
    reset_co_eff();
    int k = 0;
	char* token = strtok(str,"+"),tok[100][100];
	while (token != NULL) {
        strcpy(tok[k++], token);
		token = strtok(NULL, "+");
	}
    int  j = 0,i = 0,  pos;
    do {
        do  {

            pos = strfind(tok[i], general[j]);
            if( pos == -1) j++;
        } while(pos == -1 && j < 5);

        char st[50] ;
        if(pos == -1) strcpy(st, tok[i] );
        else {
            strncpy(st,tok[i], pos);
            st[pos]='\0';
        }
        if(pos != -1 && myatoi(st) == 0) strcat(st,"1");

        switch (j)
        {
        case 0: a = myatoi(st);
            break;
        case 1: b = myatoi(st);
            break;
        case 2: h = myatoi(st);
            break;
        case 3: g = myatoi(st);
            break;
        case 4: f = myatoi(st);
            break;
        default: c = myatoi(st);
            break;
        }
        j = 0;
        pos = strfind(tok[++i], general[j]);
    }   while( i < k );

}

double discriminant(double i)
{
    return (h*i-f )*(h*i-f )- 4 * b * ( a * i*i + g * i + c);
}

void draw_grid()
{

    iSetColor(25,75,25);
    for(int i = 1; i < sx / 2; i+=20){
        iLine(0, sy/2 + i, sx, sy/2+i);
        iLine(0, sy/2 - i, sx, sy/2-i);
        iLine(sx/2+i , 0, sx/2+i, sy);
        iLine(sx/2-i , 0, sx/2-i, sy);
    }

}

void draw_axes()
{
    iSetColor(250,250,250);
    iLine(0, sy/2 , sx, sy/2);
    iLine(sx/2, 0, sx/2, sy);
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

void trace_point()
{
    if(mode_point==1) {
        double kx=1;
        if(px > sx - 185 * scale_x) kx=-1;
        double A[7]={
                    px,
                    px+25.0 * kx * scale_x,
                    px+25.0 * kx * scale_x,
                    px+185.0 * kx * scale_x,
                    px+185.0 * kx  * scale_x,
                    px+25.0 * kx * scale_x,
                    px+25.0 * kx * scale_x
                    },
                B[7]={
                    py,
                    py-8 * scale_y ,
                    py-25.0 * scale_y ,
                    py-25.0 * scale_y ,
                    py+25.0 * scale_y ,
                    py+25.0 * scale_y ,
                    py+8 * scale_y
                    };
        iFilledCircle(px, py,5);
        iSetColor(100,210,100);
        iPolygon(A,B,7);
        pos_from_int();

        iSetColor(10,255,100);
        iText(px + 30 * scale_x - (1-kx)*105 * scale_x , py-4 * scale_y, position,GLUT_BITMAP_HELVETICA_18);
    }
}


double arith_pos(double x)
{
    double fy;
    D = discriminant(x);
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
    D = discriminant(x);
    double fy;
    if(b !=0){

        fy = ( -(h * x + f ) - sqrt(D)) / ( 2 * b);
        return fy;
    }
    if(b == 0){
        return -(a * x * x + g * x + c)/( h * x + f);
    }
}

double f11(double i){
    i-= sx/2;
    D = discriminant(i);
    if( D < 0) return NULL;
    return sy / 2 + arith_neg(i );
}

double f12(double i){
    i-= sx/2;
    D = discriminant(i);
    if( D < 0) return NULL;
    return sy / 2 + arith_pos(i );
}

void drawTextBox()
{
	iSetColor(50, 150, 150);
    if(mode ) iSetColor(250,250,250);
	iRectangle(.75 * sx , 0.75 * sy , sx*0.25-20*scale_x, 30 *scale_y);
	/*
    iRectangle(.75 * sx , .75 * sy -30 * scale_x ,sx*0.25-20*scale_y, 30);
    iText(.75 * sx + 10 ,.75 * sy -20 ,"add equation",GLUT_BITMAP_HELVETICA_18);
    */
}

void inTextBox(){
    if(!strlen(str))
	{
        iSetColor(155, 155, 155);
		iText(.75 * sx + 10 *scale_x ,.75 * sy + 10 * scale_y ,"Enter equation here..",GLUT_BITMAP_HELVETICA_18);
    }
	else {
		iSetColor(255, 255, 255);
		iText(.75 * sx + 10 ,.75 * sy + 10 , str,GLUT_BITMAP_HELVETICA_18);
        iText(sx-65, .75 * sy + 10," = 0",GLUT_BITMAP_HELVETICA_18);
	}
}
/*

void f_project(){
	FILE *fp;

	fclose(fp);

}
*/


void make_point(){

    double j = 0;
    int i ;
    refresh_neg(str2);
    co_eff(str2);

    for(i = 0; i < p_size; i++){
        p1[i].x = j;
        p1[i].y1 = f11(j);
        p1[i].y2= f12(j);
        j+=0.05;
    }
}
color col[]={
            {255, 255,255},
            {255,0,0},
            {0,255,0},
            {0,0,255},
            };
void set_color(){
    int n = 2;
    iSetColor(col[n].R, col[n].G, col[n].B);
    iFilledRectangle(sx -15 * scale_x , .75 *sy + 10*scale_y , 12, 12);

}

void draw_curve(){

    set_color();
    for(int i = 0; i < p_size; i++){
        if(p1[i].y1 != NULL)    iPoint(p1[i].x, p1[i].y1, 1 );
        if(p1[i].y2 != NULL)    iPoint(p1[i].x, p1[i].y2, 1 );
    }
}

void tips(){
    iSetColor(255,255,255);
    iRectangle(20*scale_x , sy-32*scale_y ,12*scale_x,12*scale_y);
    iSetColor(50,200,250);
    if(tips_mode == 1){

        iText(20*scale_x  ,sy-45 *scale_y ,">press 'g' to show or hide GRIDs",GLUT_BITMAP_HELVETICA_18);
        iText(20*scale_x,sy-65 *scale_y,">press 'a' to show or hide AXES",GLUT_BITMAP_HELVETICA_18);
        iText(20*scale_x,sy-85 *scale_y,">press right mouse click to hide point tracing",GLUT_BITMAP_HELVETICA_18);
        iText(20*scale_x,sy-105 *scale_y,">Click anywhere in the grid to show point tracing",GLUT_BITMAP_HELVETICA_18);
        iSetColor(255,255,255);
        iFilledRectangle(22*scale_x, sy-30*scale_y, 8*scale_x, 8*scale_y);
    }
    else {
        iSetColor(255,255,255);
        iText(40*scale_x ,sy-32 *scale_y,"Click here for tips",GLUT_BITMAP_HELVETICA_18);

    }
}

/*
	function iDraw() is called again and again by the system.
*/
void iDraw()
{
    //place your drawing codes here
    iClear();

    if(mode_grid)  draw_grid();

    if(mode_axis) draw_axes();
	
    if(y != NULL && x <= sx && draw_mode ){
        iCircle(x,y,70);
        iFilledCircle(x,y,7);
    }
	
    iSetColor(10,100,255);


    /** point tracing **/
    trace_point();

    /** text */
    tips();

    drawTextBox();
    inTextBox();


    iSetColor(25,225,200);
    if(draw_mode ==1) draw_curve();

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
        
       px=mx;
       py=my;
       if(!mode)    mode_point = 1;

       if(mx >= .75 * sx  && mx <= .75 * sx +200*scale_x && my >= .75 * sy && my <= .75 * sy +30*scale_y )
		{
			mode = 1;
			mode_point = 0;
		}


        /***    for tips    ***/

        else if(mx>=20*scale_x && mx<= 32*scale_x && my>=(sy-32*scale_y) && my<=(sy-20*scale_y)){
            mode = 0;
            mode_point = 0;
            tips_mode = (!tips_mode);
        }
        /***  for color mode  ***/
        /*
        else if( mx>=sx -15  && mx<=sx -3 && my >= .75 *sy + 10 && my <= .75 *sy + 22){
            mode = 0;
            mode_point = 0;
            mode_color =1;
        }
    */
        else {
            mode = 0;
            mode_point = 1;
            mode_color =0;
        }
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
       mode_point = 0;

    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    /***    taking input   ****/
    int i;
	if(mode == 1)
	{
		if(key == '\r')     // \r =enter key
		{
			draw_mode = 1;
			mode = 1;
			strcpy(str2, str);
			make_point();
		}
		else if(key == '\b'){
			if(len != 0) str[--len]='\0';
		}
		else
		{
			str[len] = key;
			len++;
		}
	}


    else if(key == 'q')
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
    if(draw_mode){
    x=t;
    while( (f11(t)) == NULL ) t+=20;
    y = f11(t);
    //y = f12(t);   //need to fix;
    t+=10;
    if(t>=sx) t=0;
    }

}

int main()
{
    //place your own initialization codes here.

    p1 = (point *)malloc(sizeof(point) * p_size);
    if(!p1)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    len = 0;
	mode = 0;
	str[0]= '\0';
	iSetTimer(1,my_anim);

    iInitialize(sx, sy, " Real Remainder ");
    return 0;
}

