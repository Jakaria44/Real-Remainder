# include "iGraphics.h"
#include <math.h>
#include<string.h>
#include <windows.h>

double sx = 1280,
        sy = 720,
        scale_x =  sx / 1280.0,
        scale_y =  sy/720.0 ;

/** home page  **/

double  home_y = sy * 0.68,
        box_height = 70 * scale_y ;

typedef struct box{
    double bx, by, b_dx, b_dy;
} box;

box b1 = { .38* sx,
            home_y - box_height * 1 * 1.5 ,
            260 * scale_x,
            box_height },
    b2 = {  .38* sx,
            home_y - box_height * 2 * 1.5 ,
            260 * scale_x,
            box_height },
    b3 = {  .38* sx,
            home_y - box_height * 3 * 1.5 ,
            260 * scale_x,
            box_height
    }
    ;

int r = 15, t = 0, timer = 1;
int n_color = 0;
const int N = 5; // number of equations.
int len[N+1], parallel_y[N+1] , g_color[N+1];
int count_eqn = 1 ;
char str[100], str11[N][100], zx[10] ;

char  position[100];
double x = 840 *scale_x , y =360*scale_x , px , py  ;

//x, y moving circle.
int  tri = 4;

double point_array_size = (sx/0.05 > sy / 0.05)? (sx/0.05): (sy/0.05);
int p_size = point_array_size;

/*****   modes     *****/


int mode= 0;

int mode_point = 0,
    mode_axis = 1 ,
    mode_grid = 1,
    draw_mode = 0,
    tips_mode = 0,
    mode_color=0 ,
    mode_eqn = 0,
    diff_color_mode = 0,
    show_mode[N+1],
    show_anim_mode = 0;
    ;


/*****              general equation        *****/
/*****  ax^2 + by^2 + hxy + gx + fy + c = 0   *****/

double  a =   0,
        b =   0 ,
        c =   0,
        f =   0,
        g =   0 ,
        h =   0 ,
        D;          // discriminant: D = (h*i-f )*(h*i-f )- 4 * b * ( a * i*i + g * i + c);

char general[][10]= {"x^2","y^2", "xy","x", "y"};

/****   ZOOM    ****/

double z = 1;

typedef struct point{
    double x1;
    double x2;
    double y1;
    double y2;
} point;

point **p = NULL;

typedef struct color{
    double R;
    double G;
    double B;
}color;

color col[]={
            {255, 255,255},
            {237, 9, 210
            },
            {  0, 255, 25},
            {  0, 100, 255},
            { 226, 237, 9},
            {25, 211, 224}
            };

double col_x = .85 * sx, col_y = 0.75 * sy +50 *scale_y;


/***for ellastic collision  ***/

int n_collision = 0,
    animation_2 = -1,
    l_1 = 0,
    l_2 = 0,
    l_3 = 0,
    l_4 = 0,
    in_m1 = 0,
    in_m2 = 0,
    in_v1 = 0 ,
    in_v2 = 0 ;

char n_col[1000], text[10000], m1s[15], m2s[15], v1s[15], v2s[15] , v10s[15], v20s[15];

double x0 =200, x1 =300, x2 = 575,
        v1 = 0 ,v2= 2,
        y_col = 200,



        a1 = 75* scale_x* scale_y, a2= a1 ,
        k1, k2,
        time_anim_2 = .000001,
        time_anim_1= 1,
        m1 =1,
        m2=1;
void restart_collision();
void mode_change_collision(int ,int, int, int);
double dist(int, int, double, double);
void clear();
void refresh_string(char *, int);
void reset();       //for elastic collision
double myatoi(char* str);
int strfind(char a[], char s[]);
void refresh_neg(char *str);
void reset_co_eff();
void co_eff(char *str);
double discriminant(double i);
void draw_grid();
void draw_axes();
void pos_from_int();
void trace_point();
double f_tri(double aa, int a);
double f_trigon(double x, int a);
void draw_trigon(int a);
void  tri_function_text(int a);
double arith_pos(double x);
double arith_neg(double x);
double f11(double i);
double f12(double i);
void drawTextBox();
void inTextBox();
void f_project();
void make_point();
void set_color(int n);
void draw_curve();
void tips();
void draw_diff_color();
void ellastic_collision();
void graphing_calc();
void homepage();
void get_back();

int check(int, int, double, double, double, double);
int check_color(int, int, double, double, double, double);
void choose_color(int , int );
void anim_1();
void anim_2();

void iDraw();
void iMouseMove(int mx, int my);
void iMouse(int , int , int , int );
void iKeyboard(unsigned char key);
void iSpecialKeyboard(unsigned char key);


int main()
{
    //place your own initialization codes here.
    sprintf(v1s, "%.2lf", v1);
    sprintf(v2s, "%.2lf", v2);

    strcpy(v10s, v1s);
    strcpy(v20s, v20s);

    sprintf(m1s, "%.2lf", m1);
    sprintf(m2s, "%.2lf", m2);

    for(int j = 1; j <= N; j++){
        for(int i = 0; i< len[j]; i++){
            str11[j][i]='\0';
        }
    }

    for(int i = 0; i < 10; i++)  zx[i]='\0';

    for(int i = 1; i <= N ; i++){
        len[i]=0;
        show_mode[i]=0;
        parallel_y[i]=0;
        g_color[i]= 0;
    }

    l_1 =strlen(m1s) ;
    l_2 = strlen(m2s) ;
    l_3 = strlen(v1s),
    l_4 =strlen(v2s) ;

	str[0]= '\0';

	iSetTimer(time_anim_1,anim_1);
	iSetTimer(time_anim_2, anim_2);


    iInitialize(sx, sy, " Real Remainder ");
    return 0;
}

void restart_collision(){
    strcpy(v1s, v10s);
    strcpy(v2s, v20s);

    m1 = myatoi(m1s);
    m2 = myatoi(m2s);
    v1 = myatoi(v1s);
    v2 = myatoi(v2s);
    x1 =300* scale_x;
    x2 = 575* scale_x;
    n_collision = 0;
    animation_2= -1;
    iPauseTimer(1);
}
void refresh_string(char s[], int p){
    for(int i = p; i < 15;  i++){
        s[i]='\0';
    }
}
void reset(){
    z = 1;
    in_m1 = 0;
    in_m2 = 0;
    in_v1 = 0;
    in_v2 = 0;
    n_collision = 0;
    m1 = 1;
    m2 = 1;
    v1 = 0 ;
    v2= 2;
    animation_2 = -1;
    for(int i = 0; i< 15; i++){
        m1s[i]='\0';
        m2s[i]='\0';
        v1s[i]='\0';
        v2s[i]='\0';
        v10s[i]='\0';
        v20s[i]='\0';
    }
    sprintf(v1s, "%.2lf", v1);
    sprintf(v2s, "%.2lf", v2);

    sprintf(m1s, "%.2lf", m1);
    sprintf(m2s, "%.2lf", m2);

    sprintf(zx, "%.3lf", z);
    strcpy(v10s, v1s);
    strcpy(v20s, v20s);

    x1 =300* scale_x;
    x2 = 575* scale_x;

    l_1 =strlen(m1s) ;
    l_2 = strlen(m2s) ;
    l_3 = strlen(v1s) ,
    l_4 =strlen(v2s) ;
    a2 = a1;
}
double myatoi(char* str)
{
	int sign = 1, dec = 1, index = -1 ;
    double  res = 0;
	for (int i = 0; str[i] != '\0'; ++i)
    {

        if(str[i]==' ')         continue;
        else if(str[i]== '-')   sign = -1;
        else if(str[i]== '.')   dec = 0;
        else{
            if(dec)     res = res*10 + str[i]- '0';
            else        res = res + (str[i]- '0') * pow(10 , index--)   ;
        }
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
        default: c += myatoi(st);
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
    for(float i = 1; i < sx / 2; i+=20*z){
        iLine(0, sy/2 + i, sx, sy/2+i);
        iLine(0, sy/2 - i, sx, sy/2-i);
        iLine(sx/2+i , 0, sx/2+i, sy);
        iLine(sx/2-i , 0, sx/2-i, sy);
    }

}

void draw_axes()
{
    char s[15];
    iSetColor(250,250,250);
    iLine(0, sy/2 , sx, sy/2);
    iLine(sx/2, 0, sx/2, sy);
    for(float i = 0; i <= sx; i += sx / 10){
        sprintf(s, "%.1f", ( i - sx/2 )/z);
        iText(i, sy / 2 - 20 * scale_y, s,GLUT_BITMAP_HELVETICA_18);
        iPoint(i, sy/2, 3);
    }
    for(float i = 0; i <= sy; i += sy / 10){
        if(i == sy/2) continue;
        sprintf(s, "%.1f", ( i - sy/2 )/z);
        iText(sx / 2 + 5 * scale_x,i,  s,GLUT_BITMAP_HELVETICA_18);
        iPoint(sx/2,i,  3);
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

        //if(tri_y > sy || tri_y < 0) return NULL;
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

    for(int i = 1; i <= count_eqn; i++){
        //set_color[g_color[mode_eqn]];
        if(mode_eqn==i) iSetColor(255,255,255);
        else iSetColor(175, 175, 175);
        iRectangle(.75 * sx , 0.75 * sy - 30 * (i-1)* scale_y  , sx*0.25-20*scale_x, 30 *scale_y);
    }
    if(mode_eqn > 0) {
        iSetColor(255,255,255);
        iFilledRectangle(.75 * sx - scale_x, 0.75 * sy - 30 * scale_y* (mode_eqn-1) - scale_y , sx*0.25-18*scale_x , 32 *scale_y);
    }
}

void inTextBox(){
    for(int i = 1; i <= count_eqn; i++){
        if(strlen(str11[i]) ){
            iSetColor(255,255,255);

            if( i == mode_eqn)  iSetColor(0,0,0);

            iText(sx-65 * scale_x, .75 * sy + 10* scale_y - 30*(i-1) * scale_y," = 0",GLUT_BITMAP_HELVETICA_18);

            iText(.75 * sx + 10 *scale_x ,.75 * sy + 10 * scale_y - 30 * (i -1) * scale_y,str11[i],GLUT_BITMAP_HELVETICA_18);

            /**   selecting graphs to show    **/

            if(show_mode[i]==0)
                iSetColor(55,55,55);
            else iSetColor( 255,255,255);
            iFilledCircle(.75 * sx -15*scale_x  , 0.75 * sy+15 * scale_y - 30 * (i -1)   * scale_y, 10 * scale_x*scale_y);

            /***  button for choosing color    ***/
            set_color( g_color[i]);
            if(show_mode[i]) iFilledRectangle(sx -15 * scale_x , .75 *sy-30*(i-1) * scale_y , 12 * scale_x, 30*scale_y);

        }
        else{
            iSetColor(100,100,100);
            iText(.75 * sx + 10 *scale_x ,.75 * sy + 10 * scale_y - 30 * (i-1) * scale_y,"Enter equation here..",GLUT_BITMAP_HELVETICA_18);
        }

    }

    if(mode_eqn == 0 && count_eqn == 1 && strlen(str11[1])== 0)     // initial stage
    {
        iSetColor(100, 100, 100);
		iText(.75 * sx + 10 *scale_x ,.75 * sy + 10 * scale_y ,"Enter equation here..",GLUT_BITMAP_HELVETICA_18);
    }

    else if(mode_eqn > 0  && mode_eqn <=N)
    {
		iSetColor(80, 80, 80);
        if(strlen(str11[mode_eqn]) == 0)
            iText(.75 * sx + 10 *scale_x ,.75 * sy + 10 * scale_y - 30 * (mode_eqn -1 ) * scale_y,"Enter equation here..",GLUT_BITMAP_HELVETICA_18);

       }


}
/*

void f_project(){
	FILE *fp;

	fclose(fp);

}
*/


void make_point(){

    double j ;
    int i, count_x=0 ;
    strcpy(str, str11[mode_eqn]);  // to prevent changing of str11[mode_eqn]
    refresh_neg(str);
    co_eff(str);

    if(!b && !h && !f){
        // ax^2 + gx + c = 0;
        parallel_y[mode_eqn]= 1;
        double fy ;
        for( j = -sx/2; j < sx/2 ; j+=.0001){
            fy = a * j * j  +  g * j  +  c;
            if(abs( fy - 0) <.01){
                count_x++;
                for( i = 0; i < sy ; i++){
                    if(count_x == 1)    p[mode_eqn][i].x1 = j + sx/2;
                    else                p[mode_eqn][i].x2 = j + sx/2;
                    p[mode_eqn][i].y1 = i - sy/2;
                    p[mode_eqn][i].y2 = i + sy/2;

                }
                j+=.5;    //assuming the next point won't be this much closer.
            }
            if(count_x == 2) break;
        }
    }
    else {
       j =0;
        for(i = 0; i < p_size; i++){
            p[mode_eqn][i].y1 = f11(j) ;
            p[mode_eqn][i].y2 = f12(j) ;
            p[mode_eqn][i].x1 = j ;
            j+=0.05;
        }

    }
}


void set_color(int n){
    iSetColor(col[n].R, col[n].G, col[n].B);

}
void draw_curve_index(int j){
    set_color( g_color[j]);
    if( parallel_y[j]== 1){
        for(int i = 0; i <sy; i++){
            iPoint( sx/2 + (p[j][i].x1 - sx/2) * z, sy/2 + (p[j][i].y1 - sy/2) * z, 1 );
            iPoint( sx/2 + (p[j][i].x1 - sx/2) * z, sy/2 + (p[j][i].y2 - sy/2) * z, 1 );
            iPoint( sx/2 + (p[j][i].x2 - sx/2) * z, sy/2 + (p[j][i].y1 - sy/2) * z, 1 );
            iPoint( sx/2 + (p[j][i].x2 - sx/2) * z, sy/2 + (p[j][i].y2 - sy/2) * z, 1 );
       }
    }
    else {
        for(int i = 0; i < p_size; i++){
            if(p[j][i].y1 != NULL)    iPoint(   sx/2 + (p[j][i].x1 - sx/2) * z,  sy/2 + (p[j][i].y1 - sy/2) * z, 1 );
            if(p[j][i].y2 != NULL)    iPoint(   sx/2 + (p[j][i].x1 - sx/2) * z , sy/2 + (p[j][i].y2 - sy/2) * z , 1 );
        }
    }
}
void draw_curve(){

    set_color(n_color);

    for(int i = 1; i <= count_eqn; i++){
        if(show_mode[i]) draw_curve_index(i);
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

void draw_diff_color()
{


    iSetColor(0,0,0);
    iFilledRectangle(col_x-10*scale_x , col_y-10*scale_y , 170 * scale_x, 120 *scale_y);

    set_color(0);
    iFilledRectangle(col_x              , col_y                 , 50 *scale_x, 50 *scale_y);

    set_color(1);
    iFilledRectangle(col_x + 50* scale_x , col_y                , 50 * scale_x, 50*scale_y);

    set_color(2);
    iFilledRectangle(col_x + 100* scale_x, col_y                , 50 *scale_x, 50 *scale_y);

    set_color(3);
    iFilledRectangle(col_x               , col_y + 50 *scale_y  , 50 * scale_x, 50 *scale_y);

    set_color(4);
    iFilledRectangle(col_x + 50* scale_x  , col_y + 50 *scale_y , 50 * scale_x, 50 *scale_y);

    set_color(5);
    iFilledRectangle(col_x + 100* scale_x , col_y + 50 *scale_y , 50 * scale_x, 50 *scale_y);
}


void ellastic_collision()
{
    /***    resizing second box     ***/
    a2= a1 + 30 * log10(m2 /m1)* scale_x;

    iSetColor(255,255,255);
    iText(400 * scale_x, 100 * scale_y,"m1 : ",GLUT_BITMAP_HELVETICA_18);
    iText(400 * scale_x, 45 * scale_y,"v1 : ",GLUT_BITMAP_HELVETICA_18);

    iText(800 * scale_x, 100 * scale_y,"m2 : ",GLUT_BITMAP_HELVETICA_18);
    iText(800 * scale_x, 45 * scale_y,"v2 : ",GLUT_BITMAP_HELVETICA_18);

    /** highlight option  **/

    iSetColor(29, 245, 177);
    if(in_m1)   iFilledRectangle( 446 * scale_x,    86 * scale_y,   93 * scale_x,  38 * scale_y);
    if(in_m2)   iFilledRectangle( 846 * scale_x,    86 * scale_y,   93 * scale_x,  38 * scale_y);
    if(in_v1)   iFilledRectangle( 446 * scale_x,    36 * scale_y,   93 * scale_x,  38 * scale_y);
    if(in_v2)   iFilledRectangle( 846 * scale_x,    36 * scale_y,   93 * scale_x,  38 * scale_y);

    iSetColor(255,255,255);
    iFilledRectangle( 450 * scale_x,    90 * scale_y,   85 * scale_x,   30 * scale_y);        //m1
    iFilledRectangle( 450 * scale_x,    40 * scale_y,   85 * scale_x,   30 * scale_y);        //v1

    iFilledRectangle( 850 * scale_x,    90 * scale_y,   85 * scale_x,   30 * scale_y);        //m2
    iFilledRectangle( 850 * scale_x,    40 * scale_y,   85 * scale_x,   30 * scale_y);        //v2

    iFilledRectangle( 50 * scale_x,     300 * scale_y,  85 * scale_x,   30 * scale_y);        //resume
    iFilledRectangle( 50 * scale_x,     350 * scale_y,  85 * scale_x,   30 * scale_y);        //pause
    iFilledRectangle( 50 * scale_x,     400 * scale_y,  85 * scale_x,   30 * scale_y);        //reset
    iFilledRectangle( 50 * scale_x,     450 * scale_y,  85 * scale_x,   30 * scale_y);        // restart collision


    iSetColor(255,255,255);
    iText(545 * scale_x, 100* scale_y,   "kg", GLUT_BITMAP_HELVETICA_18);
    iText(545 * scale_x, 45* scale_y,    "m/s", GLUT_BITMAP_HELVETICA_18);
    iText(945 * scale_x, 100* scale_y,   "kg", GLUT_BITMAP_HELVETICA_18);
    iText(945 * scale_x, 45* scale_y,    "m/s", GLUT_BITMAP_HELVETICA_18);

    iSetColor(0,0,0);
    iText(465 * scale_x, 100* scale_y,   m1s, GLUT_BITMAP_HELVETICA_18);
    iText(455 * scale_x, 45* scale_y,    v1s, GLUT_BITMAP_HELVETICA_18);
    iText(865 * scale_x, 100* scale_y,   m2s, GLUT_BITMAP_HELVETICA_18);
    iText(855 * scale_x, 45* scale_y,    v2s, GLUT_BITMAP_HELVETICA_18);

    iText(60 * scale_x, 308* scale_y,"PAUSE",GLUT_BITMAP_HELVETICA_18);

    if(animation_2 == -1){
        iText(60* scale_x,   358* scale_y,     "START",GLUT_BITMAP_HELVETICA_18);
        iPauseTimer(1);

    }
    else iText(57 * scale_x, 358 * scale_y,"RESUME",GLUT_BITMAP_HELVETICA_18);
    iText(60 * scale_x, 408 * scale_y,"RESET",GLUT_BITMAP_HELVETICA_18);
    iText(53 * scale_x, 458 * scale_y,"RESTART",GLUT_BITMAP_HELVETICA_18);



    iSetColor(0,255,200);
    iLine(x0 * scale_x,     y_col * scale_y,        sx - 50 * scale_x,  y_col * scale_y);
    iLine(x0 * scale_x,     y_col * scale_y,        x0 * scale_x,       sy- 50 * scale_y);

    iSetColor(23, 227, 196);
    iFilledRectangle(x1 * scale_x , y_col * scale_y, a1 * scale_x,a1 * scale_y);
    iSetColor(0,200,255);
    iFilledRectangle(x2  * scale_x, y_col * scale_y, a2 * scale_x,a2 * scale_y);

    sprintf(n_col,"%d",n_collision );
    iSetColor(255,255,255);
    iText(sx / 2, sy* .75 ,n_col,GLUT_BITMAP_HELVETICA_18);

    iText(sx * .3, sy * .75, "No. of Collisions:",GLUT_BITMAP_HELVETICA_18);

    iSetColor(10,10,10);
    iText( x1 + .38*a1 *scale_x, y_col + .46 * a1 * scale_y, "m1", GLUT_BITMAP_HELVETICA_18);
    iText( x2 + .38*a2 *scale_x, y_col + .46 * a2 * scale_y, "m2", GLUT_BITMAP_HELVETICA_18);


}


void graphing_calc()
{
    if(mode_grid)  draw_grid();

    if(mode_axis) draw_axes();


    iSetColor(10,100,255);

    /** point tracing **/
    trace_point();

    /** text */
    tips();
    /** moving ball  **/
    if(draw_mode && show_mode[mode_eqn]){
        iSetColor(255,255,255);
        iText(sx-100*scale_x, 26*scale_y, "Moving Ball", GLUT_BITMAP_9_BY_15);
        if(!show_anim_mode) iSetColor(95,95,95);
        iFilledCircle(sx-115* scale_x, 30*scale_y, 8*scale_x* scale_y);
    }
    drawTextBox();
    inTextBox();


    iSetColor(255,255,255);
    iText(100*scale_x,15*scale_y,"ZOOM : ", GLUT_BITMAP_HELVETICA_18);
    iRectangle(185*scale_x,0,120*scale_x,40*scale_y);
    iFilledRectangle(185*scale_x,0,30*scale_x,40*scale_y);          //+
    iFilledRectangle(275*scale_x,0,30*scale_x,40*scale_y);          //-
    iFilledRectangle(315*scale_x,5*scale_y,70*scale_x,30*scale_y);      // reset

    iText(215*scale_x,15*scale_y,zx,GLUT_BITMAP_HELVETICA_18 );

    iSetColor(0,0,0);
    iText(195*scale_x,15*scale_y,"-",GLUT_BITMAP_HELVETICA_18 );
    iText(285*scale_x,15*scale_y,"+",GLUT_BITMAP_HELVETICA_18 );
    iText(322*scale_x,15*scale_y,"RESET", GLUT_BITMAP_HELVETICA_18);


    sprintf(zx, "%.3lf", z);
    strcat(zx, "x");
    iSetColor(25,225,200);
    if(draw_mode ==1) draw_curve();
    if(diff_color_mode) draw_diff_color();
    if(y != NULL && x <= sx && draw_mode && show_mode[mode_eqn] && show_anim_mode){
        iCircle(x,y,70);
        iSetColor( 28, 107, 235) ;
        iFilledCircle(x,y,7);
    }
}

void homepage(){
    iSetColor(103, 232, 235);
    if(sx== 1280) iShowBMP(0,0, "title.bmp");
    else {
	    if(sx>=800) iText(sx *.42, home_y, "Real Remainder", GLUT_BITMAP_TIMES_ROMAN_24 );
    	    else if(sx<600 ) iText(sx *.42, home_y, "Real Remainder", GLUT_BITMAP_9_BY_15 );
    }
    
    iSetColor(10, 10, 10);
    iFilledRectangle(b1.bx, b1.by, b1.b_dx, b1.b_dy);
    iFilledRectangle(b2.bx, b2.by, b2.b_dx, b2.b_dy);
    iFilledRectangle(b3.bx, b3.by, b3.b_dx, b3.b_dy);

    iSetColor(215, 247, 247);
    iText(b1.bx +20 * scale_x, b1.by +30 * scale_y, "GRAPHING CALCULATOR",GLUT_BITMAP_HELVETICA_18 );
    iText(b2.bx +40 * scale_x, b2.by +30 * scale_y, "ELASTIC COLLISION",GLUT_BITMAP_HELVETICA_18 );
    iText(b3.bx +110 * scale_x, b3.by +30 * scale_y, "EXIT",GLUT_BITMAP_HELVETICA_18 );

}

void get_back(){
    iSetColor(8, 60, 110);
    iFilledRectangle(0,0, 50*scale_x, 35*scale_y);
    iSetColor(211, 230, 227);
    iText(10*scale_x,15*scale_y,"Back", GLUT_BITMAP_9_BY_15);
}

void clear()
{
    free(p);
    for(int index = 0; index< N+1; index++)
        free(p[index]);
    for(int j = 1; j <= N; j++){
        for(int i = 0; i< len[j]; i++){
            //str[j][i]='\0';
            str11[j][i]='\0';
        }
    }
    for(int i = 0; i < 10; i++)  zx[i]='\0';
    for(int i =1; i <= N ; i++){
        len[i]=0;
        show_mode[i]=0;
        parallel_y[i]=0;
        g_color[i]=0;
    }
    // free(len);
    // free(show_mode);


    timer = 1;
    count_eqn = 1;
    mode_eqn = 0;
}

void iDraw()
{
    //place your drawing codes here
    iClear();

    //draw_trigon(tri);
    //tri_function_text(tri);

    if(mode == 0)
        homepage();

    else if(mode == 1){
        graphing_calc();
        get_back();
    }
    else if(mode == 2){
        ellastic_collision();
        get_back();
    }

}


/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/

int check(int mx, int my, double xL, double xH, double yL, double yH){

    if(mx >= xL && mx <= xH && my >= yL && my <= yH ) return 1;
    else return 0;
}

int check_color(int mx, int my,  double xL, double xH, double yL, double yH){
    if(mx >= col_x + xL && mx <=col_x +  xH && my >= col_y + yL && my <= col_y + yH ) return 1;
    else return 0;
}
void choose_color(int mx, int my){
     if( check_color(mx,  my , 0,  50 * scale_x , 0,  50 * scale_y)) {
            n_color = 0;
        }

    else if(check_color(mx , my,  50 * scale_x, 100 * scale_x, 0, 50 * scale_y))  {
        n_color = 1;
    }

    else if(check_color(mx , my,  100 * scale_x, 150 * scale_x, 0 , 50 * scale_y))   {
        n_color = 2;
    }

    else if(check_color(mx , my,  0, 50* scale_x, 50 * scale_y, 100 * scale_y))     {
        n_color = 3;
    }

    else if(check_color(mx , my,  50* scale_x, 100* scale_x, 50 * scale_y, 100 * scale_y))    {
        n_color = 4;
    }

    else if(check_color(mx , my,  100* scale_x, 150* scale_x, 50 * scale_y, 100 * scale_y))      {
        n_color = 5;
    }
}

void mode_change_collision(int ma, int mb , int mc, int md){
    in_m1 =ma;
    in_m2 = mb;
    in_v1 = mc;
    in_v2 = md;

}

void iMouse(int button, int state, int mx, int my)
{
    if(mode == 0)
    {
        if( check(mx, my, b1.bx, b1.bx + b1.b_dx, b1.by,  b1.by+b1.b_dy))
        {
            mode = 1;
            p= (point **)malloc(N * sizeof(point*));
            for(int index = 1; index<= N; index++)
                p[index] = (point *)malloc(sizeof(point) * p_size);
            if(!p)
            {
                perror("malloc");
                exit(EXIT_FAILURE);
            }

        }
        else if( check(mx, my, b2.bx, b2.bx+ b2.b_dx, b2.by, b2.by+ b2.b_dy))
        {
            mode = 2;
        }
        else if( check(mx, my, b3.bx, b3.bx+ b3.b_dx, b3.by, b3.by+ b3.b_dy))
        {
            exit(0);
        }
    }
    else if(mode == 1)
    {
        if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
        px=mx;
        py=my;

            if( check(mx, my,  .75 * sx ,  sx - 20 * scale_x ,   .75 * sy - 30 * scale_y* count_eqn , .75 * sy +30*scale_y) )
            {
                int i;
                for(i = 0; .75 * sy - 30 * i * scale_y> my; i++);
                mode_eqn= i +1;
                if(mode_eqn == count_eqn && mode_eqn < N) count_eqn++;
                mode_point = 0;
                diff_color_mode =0;
                tips_mode=0;
            }

            else if(check(mx, my, .75 * sx -25*scale_x , .75 * sx -5*scale_x  ,0.75 * sy+15 * scale_y - 30 * count_eqn , 0.75 * sy+25 * scale_y )){
                mode_point = 0;
                diff_color_mode =0;
                for(int ind = 1 ; ind <= count_eqn; ind++){
                    double  center_x=.75 * sx -15*scale_x,
                            center_y = 0.75 * sy+15 * scale_y - 30 * (ind -1);
                    if(strlen(str11[ind]) && dist(mx, my, center_x, center_y )<=10 * scale_x*scale_y)
                        show_mode[ind]= !show_mode[ind];
                }
            }
            /** show anim mode  **/

            else if( mode_eqn>0 && dist(mx,my, sx-115*scale_x, 30* scale_y ) <= 8){
                diff_color_mode = 0;
                mode_point = 0;
                tips_mode = 0;
                show_anim_mode = !(show_anim_mode);
            }
            /***    for tips    ***/

            else if( check(mx, my, 20*scale_x , 32*scale_x ,(sy-32*scale_y) ,(sy-20*scale_y))){
                mode_eqn = 0;
                mode_point = 0;
                tips_mode = (!tips_mode);
                diff_color_mode =0;
            }

            /***  for color mode  ***/

            else if( check(mx, my, sx -15 * scale_x ,sx -3 * scale_x , .75 *sy- 30 * count_eqn * scale_y , .75 *sy + 30 * scale_y)){
                int i, temp = mode_eqn;
                for(i = 0; .75 * sy - 30 * i * scale_y> my; i++);
                mode_eqn= i +1;
                mode_point = 0;
                if(temp == mode_eqn) diff_color_mode = (!diff_color_mode);  //checking same color box is selected or not
            }

            /****   choosing color   ***/

            else if( check(mx,my, col_x , col_x + 150 * scale_x, col_y, col_y + 100 * scale_y) && diff_color_mode)
            {
                choose_color(mx, my);
                g_color[mode_eqn]= n_color;
                //mode_eqn= 0;
                mode_point = 0;
            }

            /** getting back **/
            else if( check(mx, my, 0,50*scale_x,0, 35*scale_y)){

                clear();
                mode_point = 0;
                mode_eqn = 0;
                diff_color_mode = 0;
                mode = 0;
                draw_mode = 0;

            }

            /** zoom  **/

            else if( check(mx, my, 185*scale_x,305*scale_x,0,40*scale_y)){

                if(mx <= 215*scale_x && z> 0.4 ) z-=.125;
                else z+=.125;

                mode_point = 0;
                mode_eqn =0;
                diff_color_mode = 0;
            }

            /** reset zoom  **/
            else if( check(mx, my, 315*scale_x, 385*scale_x, 5*scale_y, 35*scale_y)){
                z = 1;
                mode_point = 0;
                mode_eqn =0;
                diff_color_mode = 0;
            }

            else {
                mode_eqn= 0;
                mode_point = 1;
                mode_color =0;
                diff_color_mode =0 ;
            }
        }
    }
    else if( mode == 2)
    {
        if( check(mx, my, 0,50*scale_x,0, 35*scale_y)){
            mode = 0;
            reset();
        }

        /** m1 input mode **/

        else if( check(mx, my, 450 * scale_x,535  * scale_x ,90 * scale_y,120 * scale_y)){
            mode_change_collision(1,0,0,0);
            iPauseTimer(1);
            if(animation_2== 1) animation_2 = 0;
        }

        /** v1 input mode **/

        else if(check(mx, my, 450 * scale_x,535 * scale_x, 40 * scale_y ,70 * scale_y )){
            mode_change_collision(0,0,1,0);
            iPauseTimer(1);
            if(animation_2== 1) animation_2 = 0;
        }

        /** m2 input mode **/

        else if( check(mx, my, 850 * scale_x,935 * scale_x,90 * scale_y ,120 * scale_y )){
            mode_change_collision(0,1,0,0);
            iPauseTimer(1);
            if(animation_2== 1) animation_2 = 0;
        }

        /** v2 input mode  **/
        else if( check(mx, my, 850 * scale_x,935 * scale_x,40 * scale_y ,70 * scale_y )){
            mode_change_collision(0,0,0,1);
            iPauseTimer(1);
            if(animation_2== 1) animation_2 = 0;
        }

        else if(check(mx, my,50 * scale_x, 135 * scale_x,300 * scale_y ,330 * scale_y  )){
            iPauseTimer(1);
            animation_2 = 0;
            mode_change_collision(0,0,0,0);
        }
        else if(check(mx, my,50 * scale_x, 135 * scale_x,350 * scale_y ,380 * scale_y  )){
            iResumeTimer(1);
            animation_2 = 1;
            mode_change_collision(0,0,0,0);
        }
        else if(check(mx, my,50 * scale_x, 135 * scale_x,400 * scale_y ,430  * scale_y )){
            mode_change_collision(0,0,0,0);
            reset();
        }
        else if(check(mx, my,50 * scale_x, 135 * scale_x,450 * scale_y ,480 * scale_y  )){
            mode_change_collision(0,0,0,0);
            restart_collision();
        }
    }

    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        //x -= 5;
        //y -= 5;
       if(mode == 1) {
            mode_point = 0;
       }

    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{

   if(mode == 1)
   {
        /***    taking input   ****/
        int i;
        if(mode_eqn >0)
        {
            if(key == '\r')     // \r =enter key
            {
                str11[mode_eqn][len[mode_eqn]] ='\0';
                draw_mode = 1;
                make_point();
                show_mode[mode_eqn]=1;
            }
            else if(key == '\b'){
                if(len[mode_eqn] != 0) str11[mode_eqn][--len[mode_eqn]]='\0';   //str[eqn_mode][--len] erokom hobe
            }
            else
            {
                str11[mode_eqn][len[mode_eqn]++] = key;
            }
        }
        if(mode_eqn == 0 && count_eqn >1){

                /** zoom in **/

            if(key =='+'){
                z+=.125;
            }
            if(key =='-'){
               if(z>.4) z-=.125;
            }
        }

        else if(key == 'q')
            exit(0);
        else if(key == 'p')
           iPauseTimer(0);
        else if(key == 'r')
            iResumeTimer(0);
        else if(key == 'g')
            mode_grid = !mode_grid;
        else if(key == 'a')
            mode_axis = !mode_axis;

    }

    if(mode == 2){
        if(in_m1)
        {
            if(key == '\r')     // \r =enter key
            {
                m1s[l_1] ='\0';
                //iResumeTimer(1);
                m1 = myatoi(m1s);
                if(animation_2 == 0) animation_2= 1;
                in_m1 = 0;
            }
            else if(key == '\b'){
                if(l_1 > 0) refresh_string(m1s,--l_1);
            }
            else
            {
                refresh_string(m1s, l_1);
                m1s[l_1++] = key;
            }
        }
        else if(in_m2)
        {
            if(key == '\r')     // \r =enter key
            {
                m2s[l_2] ='\0';
                //iResumeTimer(1);
                m2 = myatoi(m2s);
                if(animation_2 == 0) animation_2= 1;
                in_m2 = 0;
            }
            else if(key == '\b'){
                if(l_2 > 0) refresh_string(m2s,--l_2);
            }
            else
            {
                refresh_string(m2s, l_2);
                m2s[l_2++] = key;
            }

        }
        if(in_v1)
        {
           if(key == '\r')     // \r =enter key
            {
                v1s[l_3] ='\0';
                strcpy(v10s, v1s);
                v1 = myatoi(v1s);
                if(animation_2 == 0) animation_2= 1;
                in_v1 = 0;
            }
            else if(key == '\b'){
                if(l_3 > 0) refresh_string(v1s,--l_3);
            }
            else
            {
                refresh_string(v1s, l_3);
                v1s[l_3++] = key;
            }
        }
        else if(in_v2)
        {
            if(key == '\r')     // \r =enter key
            {
                v2s[l_4] ='\0';
                strcpy(v20s, v2s);
                v2 = myatoi(v2s);
                if(animation_2 == 0) animation_2= 1;
                in_v2 = 0;
            }
            else if(key == '\b'){
                if(l_4 > 0) refresh_string(v2s,--l_4);
            }
            else
            {
                refresh_string(v2s, l_4);
                v2s[l_4++] = key;
            }
        }
        else if( key == ' '){
            if(animation_2){
                animation_2 = 0;
                iPauseTimer(1);
            }
            else {
                animation_2 = 1;
                iResumeTimer(1);
            }
        }
        else if( key == 'p'){
            animation_2 = 0;
            iPauseTimer(1);
        }
        else if(key  == 'r'){
            animation_2 = 1;
            iResumeTimer(1);
        }
        else if(key == '+'){
            v1*=2;
            v2*=2;
        }
        else if(key == '-'){
            v1/=2;
            v2/=2;
        }
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
        exit(0);        // exits from all the program.
    }

    else if(key == GLUT_KEY_F2)
    {

    }
    else if(key == GLUT_KEY_DOWN)
    {
        mode_eqn++;
        if(mode_eqn == count_eqn && mode_eqn < N) count_eqn++;
    }
    else if(key == GLUT_KEY_UP)
    {
        mode_eqn--;
    }
    else if(key == GLUT_KEY_RIGHT && show_mode[mode_eqn] >0)
    {
        diff_color_mode = 1;
    }
    else if(key == GLUT_KEY_LEFT)
    {
        diff_color_mode = 0;
    }



    //place your codes for other keys here
}
void anim_1(){
    if(mode == 1){
        if(show_anim_mode && draw_mode && show_mode[mode_eqn]){
            x= p[mode_eqn][t].x1;
            if(timer == 2) {
                if(t <80 ) timer = 1;
                y = p[mode_eqn][t-=50].y2 ;
            }
            else y = p[mode_eqn][t+=50].y1;

            if(t>= p_size) timer = 2;
        }
    }

}

void anim_2()
{

    if(mode == 2){
        x2 -=v2;
		x1 -=v1;

		if((x1 - x0) <=.00000001){
			v1 = -v1;
			n_collision++;
			iSetColor(255,255,255);
		}
		if(abs(x2-x1) - a1 <0.001){
			k2 = ((m2 - m1) * v2 + 2 * m1 * v1) / (m1 + m2);
			k1 = ((m1 - m2) * v1 + 2 * m2 * v2) / (m1 + m2);
			v2 = k2;
			v1 = k1;
			n_collision++;
			iSetColor(255,255,255);
		}
    }
    sprintf(v1s, "%.2lf", v1);
    sprintf(v2s, "%.2lf", v2);
}

double dist(int mx, int my, double cen_x, double cen_y){

    double d = pow((mx-cen_x), 2)+  pow((my-cen_y), 2);
    return sqrt(d);
}
