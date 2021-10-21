#include<iostream>
#include<graphics.h>
#include<time.h>
#include<cmath>
#include<math.h>
#include<stdio.h>
#include<string>
#include<sstream>
#include<string.h>
#define PI 3.14159265

using namespace std;
class Gun;
//class Building;


class Window
{
public:
    bool live;
    int health;
    float winx,winy;
Window(int x,int y){
       winx = x;
       health = 3;
       winy = y;
       live = true;
       }

    void draw()
    {

                rectangle(winx,winy,winx+40,winy+40);
                if(live){
                int points[] = {winx,winy+40,winx+40,winy+40,winx+43,winy+13,winx+30,winy+33,winx+10,winy+10,winx-2,winy+34,winx,winy+40};
                setcolor(YELLOW);
                setfillstyle(1,YELLOW);
                fillpoly(7, points);
                setcolor(WHITE);
        }
    }

    void fireOut()
    {
        if(live==true){
        for(int i=0;i<30;i++){
            setcolor(LIGHTCYAN);
            circle(winx+20,winy+20,i);
            setcolor(WHITE);
            delay(10);

        }
        live=false;}
    }
    bool isInside(int x,int y){
       if(winx+4<x && x<winx+35 && y<winy+40 && y>winy+2){fireOut();return true;}
       return false;
    }


}w1(540,50),w2(540,120),w3(540,200),w4(540,280);

class Building{
public:
int height,bx,by;

Building()
{
bx = 500; by = 40; height=350;
}
void draw()
{
    setcolor(LIGHTGRAY);
    line(bx,by,bx+600,by);
    line(bx,by+height,bx+600,by+height);
    line(bx,by,bx,by+height);
    w1.draw(); w2.draw();
    w3.draw(); w4.draw();



}

}building;


bool checkWindows(int x,int y)
{
if(w1.isInside(x,y) ||
w2.isInside(x,y) ||
w3.isInside(x,y) ||
w4.isInside(x,y)){return true;}
return false;

}

class Gun{
public:
float gun_initial_x,gun_length,gun_initial_y,gun_end_y,gun_end_x,gun_width,degree,speed;

Gun(){
gun_initial_x = 2;
speed = 4;
gun_length=150;
gun_initial_y = 240;
gun_end_y = 240;
gun_width = 30;
gun_end_x = sqrt(pow(gun_length,2) - pow((gun_end_y-gun_initial_y),2));
degree = 0;
}

void draw()
{

 setcolor(LIGHTRED);
 char speedText[6];
 stringstream ss;
 ss<<speed;
 ss>>speedText;
 char fina[100] = "Speed : ";
for(int i=8,j=0;speedText[j]!='\0';i++,j++)fina[i] = speedText[j];
 setcolor(LIGHTGRAY);
 outtextxy(30,20,fina);
 outtextxy(30,40,"w to move up");
 outtextxy(30,60,"w to move down");
 outtextxy(30,80,"a to decrease speed");
 outtextxy(30,100,"d to increase speed");
 outtextxy(30,120,"p to shoot");
 setcolor(LIGHTRED);
 gun_end_x = gun_initial_x + gun_length*cos(degree*PI/180);
 gun_end_y = gun_initial_y - gun_length*sin(degree*PI/180);
 //rectangle(gun_initial_x,gun_initial_y-20,gun_end_x,gun_end_y);
line(gun_initial_x,gun_initial_y,gun_end_x,gun_end_y);
line(gun_initial_x,gun_initial_y-gun_width,gun_end_x,gun_end_y-gun_width);
}

void shoot()
{
    float x=gun_end_x,y=(gun_end_y+gun_end_y-gun_width)/2;
    float m = (y-((gun_initial_y+gun_initial_y-gun_width)/2))/(gun_end_x-gun_initial_x);
    float xn=x,yn=y;

    while(true){

        xn+=speed;
        yn = m * (xn - x) + y;
        draw();
        building.draw();
        //setcolor(LIGHTBLUE);
        setfillstyle(1,LIGHTBLUE);
        fillellipse(xn,yn,15,15);
        y = yn;
        x = xn;
        if(checkWindows(x,y))break;
        if(x>getmaxx() || y>getmaxy() || y<0)break;
        delay(5);
        cleardevice();
    }

}

void moveGun(){
char ch;
if(kbhit()){
 ch = getch();
 if(ch=='w'){if(degree<15)degree++;}
 else if(ch=='s'){if(degree>-15)degree--;}
 else if(ch=='a'){speed--;}
 else if(ch=='d'){speed++;}
 else if(ch=='p')shoot();
 if(speed >20 || speed <2)speed = 4;
}
}
}gun;
//Building building;




void start()
{




    while(true){
    setbkcolor(BLACK);
    building.draw();
    gun.draw();
    gun.moveGun();

    //building.draw();
    delay(15);
    cleardevice();
    }


}

int main()
{
    int gd=0,gm;
    initgraph(&gd,&gm,"");
    initwindow(600,400,"Water Balloon Game",300,30);
    cleardevice();
    start();
    getch();
    closegraph();
    return 0;
}
