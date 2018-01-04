// Scribble - gcc version compiles using the libXbgi library for Unix like systems
// @version v:3.0 - Dec 26, 2017
// @aouthor parth_shel

// Include the header files
#include"dos.h" //for mouse programming,delay
#include<graphics.h> //for graphics functions
#include<stdlib.h> //for exit function
//#include<alloc.h> //for getimage/putimage
#include"conio.h" //for kbhit
#include<ctype.h> //for text processing
#include<stdio.h> //for image saving
#include<string.h> //for strings
//#include<fstream.h> //for data file system

using namespace std;

// Declare  Methods
void mainmenu();
void scribblepad(unsigned int pensize, unsigned int pencolor, unsigned int drawselect);
void abtscr();
void helpscr();
void showmouseptr(void);
void getmousepos(int *button, int *x, int *y);
void mousehide();
void setposi(int &x,int &y);
void restrictmouseptr(int x1,int y1,int x2,int y2);
void spray(int a, int b, int s, int c);
void roundedRectangle( int x1, int y1, int x2, int y2, int cornerRadius);
void consoleLoading();
int getkey(void);
void flushKeyboard(void);

//union REGS in,out;
int button=0,x=0,y=0;

//class for buttons
class buttons
{
protected :
int left, top, right, bottom;
public :
buttons()//default construtor
{
	left=0;
	top=0;
	right=0;
	bottom=0;
}
buttons(int x1, int y1, int x2, int y2)//parametarized constructor
{
	left=x1;
	top=y1;
	right=x2;
	bottom=y2;
}
void show()
{
setcolor(WHITE);
roundedRectangle(left,top,right,bottom,5);
}
int pressEffect()
{
	if (x>left && x<right && y>top && y<bottom && button== WM_LBUTTONDOWN){ //btn press event
		int a=left;
		int b=top;
		unsigned int sz ;
		sz = imagesize(left,top,right,bottom);
		void * image = (void *)malloc(sz);
		//mousehide();
		getimage(left,top,right,bottom,image);
		setfillstyle(SOLID_FILL,WHITE);
		setcolor(WHITE);
		floodfill(left+5,top+1,WHITE);
		bar(left+3,top+3,right-3,bottom-3);
		delay(50);
		setfillstyle(SOLID_FILL,LIGHTGRAY);
		setcolor(LIGHTGRAY);
		floodfill(left+5,top+1,WHITE);
		bar(left+3,top+3,right-3,bottom-3);
		delay(70);
		setfillstyle(SOLID_FILL,DARKGRAY);
		setcolor(DARKGRAY);
		floodfill(left+5,top+1,WHITE);
		bar(left+3,top+3,right-3,bottom-3);
		delay(30);
		setfillstyle(SOLID_FILL,BLACK);
		setcolor(BLACK);
		floodfill(left+7,top+7,WHITE);
		bar(left,top,right,bottom);
		putimage(a,b,image,COPY_PUT);
		free(image);
		//delay(100);
		//showmouseptr();
		setcolor(WHITE);
		return(1);
	}
	else
		return(0);
}
int press()
{
	if (x>left && x<right && y>top && y<bottom && button== WM_LBUTTONDOWN){ //btn press event
		return(1);
	}
	else
		return(0);
}
int hover()
{
	if (x>left && x<right && y>top && y<bottom){ //btn hover
		return(1);
	}
	else
		return(0);
}
};

//class for radio buttons
class radioButtons : public buttons
{
public :
radioButtons(int x1, int y1, int x2, int y2)
{
	left=x1;
	top=y1;
	right=x2;
	bottom=y2;
}
int select()
{
	if (x>left && x<right && y>top && y<bottom && button== 1){ //btn press event
		setcolor(WHITE);
		roundedRectangle(left,top,right,bottom,5);
		return(1);
	}
	else
		return(0);
}
void unselect()
{
setcolor(BLACK);
roundedRectangle(left,top,right,bottom,5);
setcolor(WHITE);
}
};



//Main
int main()
{
int gd,gm,errorcode;
//initialize graphics mode
gd=DETECT;
//initgraph(&gd,&gm,"");
initwindow(640, 480);

errorcode = graphresult();
if (errorcode != grOk)  // an error occurred
{
   consoleLoading();
   printf("\n \t \t \t \t SCRIBBLE ver:2.0.1");
   printf("\n\n\n BGI Graphics error! \t E:01.G");
   printf("\n\n Please visit www.project-scribble.com for support.");
   printf("\n Scribble Team. ");
   printf("\n \n \n Press any key to exit.");
   getch();
   exit(1);             // return with error code
}

cleardevice();
//setposi(320,190);//set mouse position
mainmenu();
closegraph();
return 0;
}

// Method for Help
//@param: void
//@return: void
//@throws: none
//@author: Parth S.
void helpscr(){
cleardevice();
  roundedRectangle(1,1,639,477,7);//screen border
  settextstyle(3,0,3);
  outtextxy(275,50,"Help");
  settextstyle(3,0,2);
  outtextxy(20,100,"Scribble has powerful tools for your creative ideas.");
  outtextxy(20,125,"Every feature and user interface element has been designed");
  outtextxy(20,150,"to be immediately intuitive and easily learned without");
  outtextxy(20,175,"any assistance .");
  outtextxy(20,200,"You can draw on the Scribble Pad using your mouse as a ");
  outtextxy(20,225,"pointing tool; Mouse Left Click to draw using the drawing ");
  outtextxy(20,250,"tool and Mouse Right Click to erase.");
  outtextxy(20,275,"You can save and work on your drawings using the 'Save' & ");
  outtextxy(20,300,"'Open' features. ");
  outtextxy(20,325,"These powerful tools help create a wonderful drawing ");
  outtextxy(20,350,"experience .");
  buttons backBtn(550,440,630,470);//back btn
  backBtn.show();
  outtextxy(572,444,"Back");
while (1)
    {
		button = mouseclick();
		x = mousex();
		y = mousey();
		if(backBtn.pressEffect()) { //Back btn
			mainmenu();
		}
    }
}

// Method for About
//@param: void
//@return void
//@throws: void
//@author: Parth S.
void aboutscr(){
cleardevice();
  roundedRectangle(1,1,639,477,7);//screen border
  settextstyle(3,0,3);
  outtextxy(250,50,"About Scribble");
  settextstyle(3,0,2);
  outtextxy(20,100,"Scribble v:3.0 is a software developed in C++ designed");
  outtextxy(20,125,"to give you powerful tools for your creative ideas.");
  outtextxy(20,200,"   Credits :");
  outtextxy(20,225,"Design & Development - Parth Shelgaonkar");
  //outtextxy(20,275,"Graphics & Interface  - Ayush Parekh");
  //outtextxy(20,300,"Testing & Production  - Sahil Ramteke");
  //outtextxy(20,350,"For any assistance or feedback, please contact :");
  //outtextxy(20,375,"contactus@project-scribble.com .");
  //outtextxy(20,410," Web Page: www.project-scribble.com ");
  //line(18,400,336,400);
  //line(142,435,400,435);
  buttons backBtn(550,440,630,470);//back btn
  backBtn.show();
  outtextxy(572,444,"Back");
while (1)
  {
		button = mouseclick();
		x = mousex();
		y = mousey();
		if(backBtn.pressEffect()) { //Back btn
			mainmenu();
		}
    }
}

// Method for Main Menu
//@param: void
//@return void
//@throws: void
//@author: Parth S.
void mainmenu()
{
cleardevice();
  roundedRectangle(1,1,639,477,7);//screen border
  //pencil graphic
  line(70,420,80,390);
  line(70,420,100,410);
  line(74,410,80,416);
  line(80,390,90,390);
  line(90,390,90,400);
  line(90,400,100,400);
  line(100,400,100,410);
  line(80,390,270,200);
  line(90,390,275,205);
  line(100,400,285,215);
  line(100,410,290,220);
  line(270,200,290,220);
  line(273,197,293,217);
  line(270,200,284,186);
  line(290,186,304,200);
  line(290,220,304,206);
  arc(287,187,19,163,3);
  arc(303,203,0,75,3);
  arc(303,203,270,360,3);
  arc(303,203,287,270,3);
  line(35,425,140,425);
  line(90,435,170,435);
  line(135,445,195,445);
  setcolor(CYAN);
  setfillstyle(SOLID_FILL,CYAN);
  floodfill(102,400,WHITE);
  floodfill(90,388,WHITE);
  setcolor(GREEN);
  setfillstyle(SOLID_FILL,GREEN);
  floodfill(92,398,WHITE);
  setcolor(DARKGRAY);
  setfillstyle(SOLID_FILL,DARKGRAY);
  floodfill(272,200,WHITE);
  setcolor(BROWN);
  setfillstyle(SOLID_FILL,BROWN);
  floodfill(88,398,WHITE);
  setcolor(RED);
  setfillstyle(SOLID_FILL,RED);
  floodfill(287,187,WHITE);
  setcolor(WHITE);
  setfillstyle(SOLID_FILL,WHITE);

  settextstyle(3,0,5);
  outtextxy(270,75,"SCRIBBLE");
  settextstyle(3,0,2);
  outtextxy(414,205,"Scribble Pad");
  outtextxy(460,355,"Exit");
  outtextxy(457,255,"Help");
  outtextxy(448,305,"About");
  buttons scribblePadBtn(400,200,550,230);//Scribble Pad btn
  buttons helpBtn(400,250,550,280);//Help btn
  buttons aboutBtn(400,300,550,330);//About btn
  buttons exitBtn(400,350,550,380);//Exit btn
  scribblePadBtn.show();
  helpBtn.show();
  aboutBtn.show();
  exitBtn.show();
while (1)
{
	button = mouseclick();
	x = mousex();
	y = mousey();
	
	if(scribblePadBtn.pressEffect()) { //Scribble Pad btn
		scribblepad(3,WHITE,1);
	}
	else if(helpBtn.pressEffect()) { //Help btn
		helpscr();
	}
	else if(aboutBtn.pressEffect()) { //About btn
		aboutscr();
	}
	else if(exitBtn.pressEffect()) { //Exit btn
		cleardevice();
		exit(0);
	}
}
}

//Method for Drawing Screen
//@param: pensize, pencolor & drawselect
//@return void
//@throws: void
//@author: Parth S.
void scribblepad( unsigned int pensize, unsigned int pencolor, unsigned int drawselect)
{

 unsigned int x1=0,x2=0,y1=0,y2=0;
 unsigned int a=0,b=0,xrad=0,yrad=0;
 unsigned int lsize;
 int hotKey;
 mousehide();
 cleardevice();
	 roundedRectangle(1,15,639,450,7);//Scribble Area
	 buttons doneBtn(595,455,635,475);//Done btn
	 buttons clearBtn(505,455,590,475);//Clear btn

	 radioButtons penSize1(10,455,30,475);//pensize 1 btn
	 radioButtons penSize3(35,455,55,475);//pensize 3 btn
	 radioButtons penSize5(60,455,80,475);//pensize 5 btn

	 radioButtons penColorR(95,455,115,475);//pencolor R btn
	 radioButtons penColorY(120,455,140,475);//pensize Y btn
	 radioButtons penColorG(145,455,165,475);//pensize G btn
	 radioButtons penColorB(170,455,190,475);//pensize B btn
	 radioButtons penColorW(195,455,215,475);//pensize W btn

	 radioButtons drawingToolBtn(230,455,250,475);//drawing tool btn
	 radioButtons selectionToolBtn(255,455,275,475);//selection tool btn
	 radioButtons lineToolBtn(280,455,300,475);//line tool btn
	 radioButtons boxToolBtn(305,455,325,475);//box tool btn
	 radioButtons fillBoxToolBtn(330,455,350,475);//filled box tool btn
	 radioButtons circleToolBtn(355,455,375,475);//circle tool btn
	 radioButtons fillCircleToolBtn(380,455,400,475);//filled circle tool btn
	 radioButtons airBrushToolBtn(405,455,425,475);//air brush tool btn

	 buttons saveBtn(458,455,478,475);//save btn
	 buttons openBtn(433,455,453,475);//open btn

	 //system tray
	 setfillstyle(SOLID_FILL,WHITE);
	 fillellipse(20,465,1,1);//pensize 1
	 fillellipse(45,465,3,3);//pensize 3
	 fillellipse(70,465,5,5);//pensize 5
	 fillellipse(205,465,7,7);//pencolor white
	 setcolor(RED);
	 setfillstyle(1,RED);
	 fillellipse(105,465,7,7);//pencolor red
	 setcolor(GREEN);
	 setfillstyle(1,GREEN);
	 fillellipse(155,465,7,7);//pencolor green
	 setcolor(BLUE);
	 setfillstyle(1,BLUE);
	 fillellipse(180,465,7,7);//pencolor blue
	 setcolor(YELLOW);
	 setfillstyle(1,YELLOW);
	 fillellipse(130,465,7,7);//pencolor yellow
	 setcolor(WHITE);
	 setfillstyle(1,15);
	 setlinestyle(1,0,1);
	 rectangle(258,458,273,472);//selection tool
	 setlinestyle(0,0,1);
	 line(232,473,232,472);//drawing tool
	 line(232,473,233,473);
	 line(232,472,247,457);
	 line(233,473,248,458);
	 line(247,457,249,459);
	 line(249,459,244,464);
	 line(285,470,295,460);//line tool
	 rectangle(308,457,322,472);//box tool
	 bar(333,458,347,472);//filled box tool
	 circle(365,465,7);//circle tool
	 fillellipse(390,465,7,7);//filled circle tool
	 setcolor(BLACK);//air brush tool
	 setfillstyle(10,WHITE);
	 fillellipse(415,465,10,10);
	 setcolor(LIGHTCYAN);
	 setfillstyle(SOLID_FILL,LIGHTCYAN);
	 /*arc(433,572,180,270,1);//fill color tool
	 line(432,472,434,470);
	 line(433,473,435,471);
	 arc(435,470,270,315,1);
	 arc(435,470,135,180,1);
	 line(434,469,442,461);
	 line(436,471,444,463);
	 line(442,461,444,463);
	 floodfill(440,465,LIGHTCYAN);
	 floodfill(433,472,LIGHTCYAN);
	 floodfill(434,471,LIGHTCYAN);
	 setcolor(BROWN);
	 setfillstyle(SOLID_FILL,BROWN);
	 arc(446,459,0,90,2);
	 line(446,457,445,458);
	 line(448,459,447,460);
	 line(445,458,444,457);
	 line(447,460,448,461);
	 arc(444,458,90,180,1);
	 arc(447,461,270,360,1);
	 line(443,458,447,462);
	 floodfill(446,459,BROWN);
	 floodfill(444,458,BROWN);
	 floodfill(447,461,BROWN);*/
	 setcolor(WHITE);
	 arc(438,460,90,180,3);//open icon
	 arc(438,470,180,270,3);
	 arc(448,470,270,360,3);
	 line(438,457,444,457);
	 line(435,460,435,470);
	 line(438,473,448,473);
	 line(451,470,451,464);
	 setcolor(LIGHTMAGENTA);
	 line(448,457,451,457);
	 line(451,457,451,460);
	 line(451,457,445,463);
	 setcolor(WHITE);
	 setfillstyle(SOLID_FILL,WHITE);
	 line(460,457,472,457);//save icon
	 line(472,457,475,461);
	 line(475,461,475,473);
	 line(475,473,460,473);
	 line(460,473,460,457);
	 bar(463,466,473,473);
	 bar(463,457,471,462);
	 setcolor(BLACK);
	 setfillstyle(SOLID_FILL,BLACK);
	 bar(468,458,470,461);
	 line(464,467,472,467);
	 line(464,469,472,469);
	 line(464,471,472,471);
	 setcolor(MAGENTA);
	 setfillstyle(SOLID_FILL,MAGENTA);
	 floodfill(468,465,WHITE);
	 setcolor(WHITE);
	 setfillstyle(SOLID_FILL,WHITE);
	 settextstyle(0,0,3);
	 doneBtn.show();
	 clearBtn.show();
	 outtextxy(605,460,"Done");
	 outtextxy(515,460,"ScribblePad");

	 switch(pensize){
		case 1 : penSize1.show(); break;
		case 3 : penSize3.show(); break;
		case 5 : penSize5.show(); break;
	 }
	 switch(pencolor){
		case RED : penColorR.show(); break;
		case YELLOW : penColorY.show(); break;
		case GREEN : penColorG.show(); break;
		case BLUE : penColorB.show(); break;
		case WHITE : penColorW.show(); break;
	 }
	 switch(drawselect){
		case 1 : drawingToolBtn.show(); break;
		case 2 : airBrushToolBtn.show(); break;
		case 3 : lineToolBtn.show(); break;
		case 4 : boxToolBtn.show(); break;
		case 5 : fillBoxToolBtn.show(); break;
		case 6 : circleToolBtn.show(); break;
		case 7 : fillCircleToolBtn.show(); break;
		case 8 : selectionToolBtn.show(); break;
	 }

while(1)
{
	 button = mouseclick();
	 x = mousex();
	 y = mousey();

 if(x>1+pensize && x<639-pensize && y<450-pensize && y>15+pensize && button==1 && drawselect==1){ // Drawing Tool
	 setcolor(pencolor);
	 setfillstyle(1,pencolor);
	 fillellipse(x,y,pensize,pensize);
	 setcolor(WHITE);
	 setfillstyle(1,WHITE);
 }
 else if(x>6+pensize && x<634-pensize && y<445-pensize && y>20+pensize && button==3){ // Erasing Tool
	 setcolor(BLACK);
	 setfillstyle(1,BLACK);
	 bar(x-(pensize+5),y-(pensize+5),x+(pensize+5),y+(pensize+5));
	 setcolor(WHITE);
	 setfillstyle(1,WHITE);
 }
 else if(x>11+pensize && x<629-pensize && y<440-pensize && y>26+pensize && button==1 && drawselect==2){ //Airbrush Tool
	 spray(x,y,pensize,pencolor);
 }
 else if(x>1 && x<639 && y<450 && y>15 && button==1 && drawselect==6){//Circle Tool
		while(1){
			showmouseptr();
			getmousepos(&button,&x,&y);
			if(x>1 && x<639 && y>15 && y<450 && button==1){
				putpixel(x,y,pencolor);
				x1=x;y1=y;
				break;
				}
			}
		while(x>1 && x<639 && y>15 && y<450 && button==1){//drag mouse
			showmouseptr();
			getmousepos(&button,&x,&y);
			if(button==0){
				x2=x;y2=y;
				break;
				}
			}
			if (x1<x2){
			  a=x1+((x2-x1)/2);
			  xrad=(x2-x1)/2;
			}
			else if (x2<x1){
			  a=x2+((x1-x2)/2);
			  xrad=(x1-x2)/2;
			}
			if (y1>y2){
			  b=y2+((y1-y2)/2);
			  yrad=(y1-y2)/2;
			}
			else if(y2>y1){
			  b=y1+((y2-y1)/2);
			  yrad=(y2-y1)/2;
			}
			setcolor(pencolor);
			mousehide();
			ellipse(a,b,0,360,xrad,yrad);
			showmouseptr();
			setcolor(WHITE);
			x1=0;x2=0;y1=0;y2=0;
			a=0;b=0;xrad=0;yrad=0;

	}
else if(x>11+pensize && x<629-pensize && y<430-pensize && y>26+pensize && button==1 && drawselect==7){//Filled Circle Tool
	while(1){
		showmouseptr();
		getmousepos(&button,&x,&y);
		if(x>1 && x<639 && y>15 && y<450 && button==1){
		  putpixel(x,y,pencolor);
		  x1=x;y1=y;
		  break;
		  }
		}
	while(x>1 && x<639 && y>15 && y<450 && button==1){//drag mouse
		showmouseptr();
		getmousepos(&button,&x,&y);
		if(button==0){
			x2=x;y2=y;
			break;
			}
		}
			if (x1<x2){
			  a=x1+((x2-x1)/2);
			  xrad=(x2-x1)/2;
			}
			else if (x2<x1){
			  a=x2+((x1-x2)/2);
			  xrad=(x1-x2)/2;
			}
			if (y1>y2){
			  b=y2+((y1-y2)/2);
			  yrad=(y1-y2)/2;
			}
			else if(y2>y1){
			  b=y1+((y2-y1)/2);
			  yrad=(y2-y1)/2;
			}
			 mousehide();
			 setcolor(pencolor);
			 setfillstyle(1,pencolor);
			 fillellipse(a,b,xrad,yrad);
			 setcolor(WHITE);
			 setfillstyle(1,WHITE);
			 showmouseptr();
			 x1=0;x2=0;y1=0;y2=0;
			 a=0;b=0;xrad=0;yrad=0;
	}
 else if(x>1 && x<639 && y>15 && y<450 &&button==1 && drawselect==3){//Line Tool
	while(1){
		showmouseptr();
		getmousepos(&button,&x,&y);
		if(x>1 && x<639 && y>15 && y<450 && button==1){
		    putpixel(x,y,pencolor);
		    x1=x;y1=y;
		    break;
		    }
		}
	while(x>1 && x<639 && y>15 && y<450 && button==1){//drag mouse
		showmouseptr();
		getmousepos(&button,&x,&y);
		if(button==0){
			x2=x;y2=y;
			break;
			}
		}
	if(pensize==1)
	    lsize=1;
	else if(pensize==3)
	    lsize=2;
	else if(pensize==5)
	    lsize=3;
	setcolor(pencolor);
	setlinestyle(0,0,lsize);
	mousehide();
	line(x1,y1,x2,y2);
	showmouseptr();
	setcolor(WHITE);
	setlinestyle(0,0,1);
	x1=0;y1=0;x2=0;y2=0;
	}
 else if(x>1 && x<639 && y>15 && y<450 &&button==1 && drawselect==8){//Selection Tool
	while(1){
		showmouseptr();
		getmousepos(&button,&x,&y);
		if(x>1 && x<639 && y>15 && y<450 && button==1){
		    putpixel(x,y,pencolor);
		    x1=x;y1=y;
		    break;
		    }
		}
	while(x>1 && x<639 && y>15 && y<450 && button==1){//drag mouse
		showmouseptr();
		getmousepos(&button,&x,&y);
		if(button==0){
			x2=x;y2=y;
			break;
			}
		}
	 unsigned int sz ;
	 sz = imagesize(x1,y1,x2,y2);
	 void * image = (void *)malloc(sz);
	 mousehide();
	 getimage(x1,y1,x2,y2,image);
	 mousehide();
	 setlinestyle(1,0,1);
	 rectangle(x1,y1,x2,y2);
	 setlinestyle(0,0,1);
	 showmouseptr();
			if (x1<x2){
			  xrad=(x2-x1)/2;
			  a=x1;
			}
			else if (x2<x1){
			  xrad=(x1-x2)/2;
			  a=x2;
			}
			if (y1>y2){
			  yrad=(y1-y2)/2;
			  b=y2;
			}
			else if(y2>y1){
			  yrad=(y2-y1)/2;
			  b=y1;
			}
				while(1){
				showmouseptr();
				getmousepos(&button,&x,&y);
				restrictmouseptr(1+xrad,15+yrad,639-xrad,449-yrad);
				  // if(x>a && x<a+xrad+xrad && y>b && y<b+yrad+yrad && button==1){
				    //	while(button==1){
				//     		showmouseptr();
				  //		getmousepos(&button,&x,&y);
				    //		restrictmouseptr(1+xrad,10+yrad,639-xrad,449-yrad);
						if(button==1){
							mousehide();
							putimage(x-xrad,y-yrad,image,COPY_PUT);
							free(image);
							setcolor(BLACK);
							setfillstyle(1,BLACK);
							bar(x1,y1,x2,y2);
							setfillstyle(1,WHITE);
							setcolor(WHITE);
							showmouseptr();
							drawselect=1;
							drawingToolBtn.show();
							drawingToolBtn.select();
							selectionToolBtn.unselect();
							restrictmouseptr(2,15,638,479);
							break;
							}
				//		}
				  //	}
				}
	x1=0;y1=0;x2=0;y2=0;
	xrad=0;yrad=0;a=0;b=0;
	}
 else if(x>1 && x<639 && y>15 && y<450 &&button==1 && drawselect==4){//Box Tool
	while(1){
		showmouseptr();
		getmousepos(&button,&x,&y);
		if(x>1 && x<639 && y>15 && y<450 && button==1){
		    putpixel(x,y,pencolor);
		    x1=x;y1=y;
		    break;
		    }
		}
	while(x>1 && x<639 && y>15 && y<450 && button==1){//drag mouse
		showmouseptr();
		getmousepos(&button,&x,&y);
		if(button==0){
			x2=x;y2=y;
			break;
			}
		}
	setcolor(pencolor);
	mousehide();
	rectangle(x1,y1,x2,y2);
	showmouseptr();
	setcolor(WHITE);
	x1=0;y1=0;x2=0;y2=0;
	}
 else if(x>1 && x<639 && y>15 && y<450 &&button==1 && drawselect==5){//Filled Box Tool
	while(1){
		showmouseptr();
		//getmousepos(&button,&x,&y);
		button = mouseclick();
		x = mousex();
		y = mousey();
		if(x>1 && x<639 && y>15 && y<450 && button==1){
		    putpixel(x,y,pencolor);
		    x1=x;y1=y;
		    break;
		    }
		}
	while(x>1 && x<639 && y>15 && y<450 && button==1){//drag mouse
		showmouseptr();
		//getmousepos(&button,&x,&y);
		button = mouseclick();
		x = mousex();
		y = mousey();
		if(button==0){
			x2=x;y2=y;
			break;
			}
		}
	 setcolor(pencolor);
	 setfillstyle(1,pencolor);
	 mousehide();
	 bar(x1,y1,x2,y2);
	 showmouseptr();
	 setcolor(WHITE);
	 setfillstyle(1,WHITE);
	 x1=0;y1=0;x2=0;y2=0;
	}
 else if(doneBtn.pressEffect()) // Done btn
	 mainmenu();
 else if(clearBtn.pressEffect())// Clear btn
	scribblepad(pensize,pencolor,drawselect);
 else if(penSize1.press()){ //size 1 btn
	 pensize=1;
	 mousehide();
	 penSize3.unselect();
	 penSize5.unselect();
	 penSize1.select();
	 showmouseptr();
	 }
 else if(penSize3.press()){ //size 3 btn
	 pensize=3;
	 mousehide();
	 penSize1.unselect();
	 penSize5.unselect();
	 penSize3.select();
	 showmouseptr();
	 }
else if(penSize5.press()){ //size 5 btn
	 pensize=5;
	 mousehide();
	 penSize1.unselect();
	 penSize3.unselect();
	 penSize5.select();
	 showmouseptr();
	 }
else if(penColorW.press()){ //color white btn
	 pencolor=WHITE;
	 mousehide();
	 penColorR.unselect();
	 penColorY.unselect();
	 penColorG.unselect();
	 penColorB.unselect();
	 penColorW.select();
	 showmouseptr();
	 }
else if(penColorR.press()){ //color red btn
	 pencolor=RED;
	 mousehide();
	 penColorR.select();
	 penColorY.unselect();
	 penColorG.unselect();
	 penColorB.unselect();
	 penColorW.unselect();
	 showmouseptr();
	 }
else if(penColorG.press()){ //color green btn
	 pencolor=GREEN;
	 mousehide();
	 penColorR.unselect();
	 penColorY.unselect();
	 penColorG.select();
	 penColorB.unselect();
	 penColorW.unselect();
	 showmouseptr();
	 }
else if(penColorB.press()){ //color blue btn
	 pencolor=BLUE;
	 mousehide();
	 penColorR.unselect();
	 penColorY.unselect();
	 penColorG.unselect();
	 penColorB.select();
	 penColorW.unselect();
	 showmouseptr();
	 }
else if(penColorY.press()){ //color yellow btn
	 pencolor=YELLOW;
	 mousehide();
	 penColorR.unselect();
	 penColorY.select();
	 penColorG.unselect();
	 penColorB.unselect();
	 penColorW.unselect();
	 showmouseptr();
	 }
else if(drawingToolBtn.press()){//drawing tool btn
	drawselect=1;
	mousehide();
	drawingToolBtn.select();
	selectionToolBtn.unselect();
	lineToolBtn.unselect();
	boxToolBtn.unselect();
	fillBoxToolBtn.unselect();
	circleToolBtn.unselect();
	fillCircleToolBtn.unselect();
	airBrushToolBtn.unselect();
	showmouseptr();
	}
else if(airBrushToolBtn.press()){//airbrush tool btn
	drawselect=2;
	mousehide();
	drawingToolBtn.unselect();
	selectionToolBtn.unselect();
	lineToolBtn.unselect();
	boxToolBtn.unselect();
	fillBoxToolBtn.unselect();
	circleToolBtn.unselect();
	fillCircleToolBtn.unselect();
	airBrushToolBtn.select();
	showmouseptr();
	}
else if(selectionToolBtn.press()){//selection tool btn
	drawselect=8;
	mousehide();
	drawingToolBtn.unselect();
	selectionToolBtn.select();
	lineToolBtn.unselect();
	boxToolBtn.unselect();
	fillBoxToolBtn.unselect();
	circleToolBtn.unselect();
	fillCircleToolBtn.unselect();
	airBrushToolBtn.unselect();
	showmouseptr();
	}
else if(lineToolBtn.press()){//line tool btn
	drawselect=3;
	mousehide();
	drawingToolBtn.unselect();
	selectionToolBtn.unselect();
	lineToolBtn.select();
	boxToolBtn.unselect();
	fillBoxToolBtn.unselect();
	circleToolBtn.unselect();
	fillCircleToolBtn.unselect();
	airBrushToolBtn.unselect();
	showmouseptr();
	}
 else if(boxToolBtn.press()){//box tool btn
	drawselect=4;
	mousehide();
	drawingToolBtn.unselect();
	selectionToolBtn.unselect();
	lineToolBtn.unselect();
	boxToolBtn.select();
	fillBoxToolBtn.unselect();
	circleToolBtn.unselect();
	fillCircleToolBtn.unselect();
	airBrushToolBtn.unselect();
	showmouseptr();
	}
else if(fillBoxToolBtn.press()){//filled box tool btn
	drawselect=5;
	mousehide();
	drawingToolBtn.unselect();
	selectionToolBtn.unselect();
	lineToolBtn.unselect();
	boxToolBtn.unselect();
	fillBoxToolBtn.select();
	circleToolBtn.unselect();
	fillCircleToolBtn.unselect();
	airBrushToolBtn.unselect();
	showmouseptr();
	}
else if(circleToolBtn.press()){//circle tool btn
	drawselect=6;
	mousehide();
	drawingToolBtn.unselect();
	selectionToolBtn.unselect();
	lineToolBtn.unselect();
	boxToolBtn.unselect();
	fillBoxToolBtn.unselect();
	circleToolBtn.select();
	fillCircleToolBtn.unselect();
	airBrushToolBtn.unselect();
	showmouseptr();
	}
else if(fillCircleToolBtn.press()){//filled circle tool btn
	drawselect=7;
	mousehide();
	drawingToolBtn.unselect();
	selectionToolBtn.unselect();
	lineToolBtn.unselect();
	boxToolBtn.unselect();
	fillBoxToolBtn.unselect();
	circleToolBtn.unselect();
	fillCircleToolBtn.select();
	airBrushToolBtn.unselect();
	showmouseptr();
	}
 else if(saveBtn.press()){//saving image
 setcolor(BLACK);
 setfillstyle(1,BLACK);
 bar(0,0,639,14);
 setcolor(WHITE);
 setfillstyle(1,WHITE);
 struct savef
 {
 int col; int row; int color;
 }sf;
 int x,y;
 char fname[15],s[1];
 //ofstream fp;
 FILE * fp; 
 /*outtextxy(3,2,"Enter the name of the file: ");
 //scanf("%s",fname);
 gets(fname);
 strcat(fname,".pic");*/
 strcpy(fname,"SCRIBBLE.PIC");
 setcolor(BLACK);
 setfillstyle(1,BLACK);
 bar(0,0,639,9);
 setcolor(WHITE);
 setfillstyle(1,WHITE);
 outtextxy(3,2,"Working on it...");
 //fp.open(fname,ios::out);
 fp = fopen(fname, "w");
 mousehide();
 for(x=1;x<=640;x++)
 {
 for(y=15;y<=450;y++)
 {
	if(getpixel(x,y)>0)
	{
	sf.col=x; sf.row=y; sf.color=getpixel(x,y);
	//fp<<sf.col<<','<<sf.row<<','<<sf.color<<',';
	fprintf(fp, "%d,%d,%d,", sf.col, sf.row, sf.color);
	}
 }
 }
 showmouseptr();
 //fp.close();
 fclose(fp);
 setcolor(BLACK);
 setfillstyle(1,BLACK);
 bar(0,0,639,9);
 setcolor(WHITE);
 setfillstyle(1,WHITE);
 }
 else if(openBtn.press()){//opening image
 setcolor(BLACK);
 setfillstyle(1,BLACK);
 bar(0,0,639,14);
 setcolor(WHITE);
 setfillstyle(1,WHITE);
 struct savef
 {
 int col; int row; int color;
 }sf;
 char fname[15],ch;
 //ifstream fp;
 FILE * fp;
 /*outtextxy(3,2,"Enter the name of the file: ");
 //scanf("%s",fname);
 gets(fname);
 strcat(fname,".pic");*/
 strcpy(fname,"SCRIBBLE.PIC");
 setcolor(BLACK);
 setfillstyle(1,BLACK);
 bar(0,0,639,14);
 setcolor(WHITE);
 setfillstyle(1,WHITE);
 //fp.open(fname,ios::in);
 fp  = fopen(fname, "r");
	if(fp==NULL)
	{
		outtextxy(3,2,"File not found! ");
		delay(1000);
	}
	else
		/*while(!(fp.eof()))
		{
			fp>>sf.col;
			fp>>ch;
			fp>>sf.row;
			fp>>ch;
			fp>>sf.color;
			fp>>ch;
			putpixel(sf.col,sf.row,sf.color);
		}*/
		
		//TODO: file reading and tokenizing to disp pixels


 //fp.close();
 fclose(fp);
 setcolor(BLACK);
 setfillstyle(1,BLACK);
 bar(0,0,639,14);
 setcolor(WHITE);
 setfillstyle(1,WHITE);
 }

 else if(doneBtn.hover()){//Done btn hover
 settextstyle(0,0,1);
 outtextxy(3,2,"Back to Menu.");
 }
 else if(clearBtn.hover()){//Clear btn hover
 settextstyle(0,0,1);
 outtextxy(3,2,"New ScribblePad.");
 }
 else if(penSize1.hover()){//size 1 btn hover
 settextstyle(0,0,1);
 outtextxy(3,2,"Size : Small.");
 }
 else if(penSize3.hover()){//size 3 btn hover
 settextstyle(0,0,1);
 outtextxy(3,2,"Size : Medium.");
 }
 else if(penSize5.hover()){//size 5 btn hover
 settextstyle(0,0,1);
 outtextxy(3,2,"Size : Large.");
 }
 else if(penColorW.hover()){//color white btn hover
 settextstyle(0,0,1);
 outtextxy(3,2,"Color : White.");
 }
 else if(penColorB.hover()){//color blue btn hover
 settextstyle(0,0,1);
 outtextxy(3,2,"Color : Blue.");
 }
 else if(penColorG.hover()){//color green btn hover
 settextstyle(0,0,1);
 outtextxy(3,2,"Color : Green.");
 }
 else if(penColorR.hover()){//color red btn hover
 settextstyle(0,0,1);
 outtextxy(3,2,"Color : Red.");
 }
 else if(penColorY.hover()){//color yellow hover
 settextstyle(0,0,1);
 outtextxy(3,2,"Color : Yellow.");
 }
 else if(drawingToolBtn.hover()){//drawing tool hover
 settextstyle(0,0,1);
 outtextxy(3,2,"Drawing Tool.");
 }
 else if(selectionToolBtn.hover()){//selection tool hover
 settextstyle(0,0,1);
 outtextxy(3,2,"Selection Tool.");
 }
 else if(lineToolBtn.hover()){//line tool hover
 settextstyle(0,0,1);
 outtextxy(3,2,"Line Tool.");
 }
 else if(boxToolBtn.hover()){//box tool hover
 settextstyle(0,0,1);
 outtextxy(3,2,"Box Tool.");
 }
 else if(fillBoxToolBtn.hover()){//fill box tool hover
 settextstyle(0,0,1);
 outtextxy(3,2,"Fill Box Tool.");
 }
 else if(circleToolBtn.hover()){//circle tool hover
 settextstyle(0,0,1);
 outtextxy(3,2,"Circle Tool.");
 }
 else if(fillCircleToolBtn.hover()){//fill circle tool hover
 settextstyle(0,0,1);
 outtextxy(3,2,"Fill Circle Tool.");
 }
 else if(airBrushToolBtn.hover()){//airbrush tool hover
 settextstyle(0,0,1);
 outtextxy(3,2,"Air-Brush Tool.");
 }
 else if(x>91 && x<139 && y>455 && y<475){//system tray hover
 settextstyle(0,0,1);
 outtextxy(3,2,"System Tray.");
 }
 else if(x>216 && x<229 && y>455 && y<475){//system tray hover
 settextstyle(0,0,1);
 outtextxy(3,2,"System Tray.");
 }
 else if(x>1 && x<639 && y>15 && y<450){//drawing tool instruction
 settextstyle(0,0,1);
 outtextxy(3,2,"Scribble Pad. Hold Left mouse button to draw and Right mouse button to erase.");
 }
 else if(saveBtn.hover()){//save btn hover
 settextstyle(0,0,1);
 outtextxy(3,2,"Save your drawing.");
 }
 else if(openBtn.hover()){//open btn hover
 settextstyle(0,0,1);
 outtextxy(3,2,"Open a saved drawing.");
 }

/* else if(kbhit){// programming for hot keys
 hotKey=getkey();
	if(hotKey==0x18D && pensize==1){
		pensize=3;
		penSize1.unselect();
		penSize3.select();
	}
	else if(hotKey==0x18D && pensize==3){
		pensize=5;
		penSize3.unselect();
		penSize5.select();
	}
	else if(hotKey==0x191 && pensize==5){
		pensize=3;
		penSize5.unselect();
		penSize3.select();
	}
	else if(hotKey==0x191 && pensize==3){
		pensize=1;
		penSize3.unselect();
		penSize1.select();
	}
	flushKeyboard();
	showmouseptr();
	getmousepos(&button,&x,&y);
	restrictmouseptr(2,10,638,479);
 }*/
 else{
	 setcolor(BLACK);
	 setfillstyle(1,BLACK);
	 bar(0,0,639,14);
	 setcolor(WHITE);
	 setfillstyle(1,WHITE);
     }
 }
 }

//Method for AirBrush
//@param: coordinates of centre, radius & color
//@return void
//@throws: void
//@author: Parth S.
 void spray(int a, int b, int s, int c){
 mousehide();
	putpixel(a-s/2,b-s/3,c);
	putpixel(a+s/2,b-s/1,c);
	putpixel(a-s/3,b-s/1,c);
	putpixel(a-s/3,b-s/2,c);
	putpixel(a+s/3,b-s/1,c);
	putpixel(a-s/1,b-s/2,c);
	putpixel(a-s/2,b-s/3,c);
	putpixel(a+s/1,b-s/3,c);
	putpixel(a-s/2,b-s/1,c);
	putpixel(a+s/3,b+s/2,c);
	putpixel(a+s/3,b-s/3,c);
	putpixel(a+s/3,b+s/1,c);
	putpixel(a+s/2,b+s/3,c);
	putpixel(a+s/1,b+s/2,c);
	putpixel(a-s/2,b+s/3,c);
	putpixel(a+s/1,b+s/2,c);
	putpixel(a+s/1,b+s/2,c);
	putpixel(a+s/1,b+s/3,c);
	putpixel(a+s/2,b-s/1,c);
	putpixel(a-s/1,b+s/2,c);
	putpixel(a+s/3,b+s/3,c);
	putpixel(a+s/3,b+s/2,c);
	putpixel(a-s/2,b+s/1,c);
	putpixel(a+s/1,b-s/2,c);
	putpixel(a+s/2,b-s/3,c);
 showmouseptr();
 }

//Method to draw Rounded Rectangles
//@param: co-ordinates of top left & bottom right corner and radius of edge
//@return: void
//@throws: none
//@author: Parth S.
void roundedRectangle( int x1, int y1, int x2, int y2, int cornerRadius)
{
    /* p1-p2
       |  |
       p4-p3
    */
    int p1_x = x1;
    int p1_y = y1;
    int p2_x = x2;
    int p2_y = y1;
    int p3_x = x2;
    int p3_y = y2;
    int p4_x = x1;
    int p4_y = y2;

    // draw straight lines
    line(p1_x+cornerRadius, p1_y, (p2_x-cornerRadius), p2_y);
    line(p2_x, (p2_y+cornerRadius), p3_x, (p3_y-cornerRadius));
    line((p4_x+cornerRadius), p4_y, (p3_x-cornerRadius) ,p3_y);
    line(p1_x, (p1_y+cornerRadius), p4_x, (p4_y-cornerRadius));

    // draw arcs
    arc((p1_x+cornerRadius), (p1_y+cornerRadius), 90, 180, cornerRadius);
    arc((p2_x-cornerRadius), (p2_y+cornerRadius), 0, 90, cornerRadius);
    arc((p3_x-cornerRadius), (p3_y-cornerRadius), 270, 360, cornerRadius);
    arc((p4_x+cornerRadius), (p4_y-cornerRadius), 180, 270, cornerRadius);
}

//Method for loding screen in console mode
//@param: void
//@return: void
//@throws: none
//@author: Parth S.
void consoleLoading()
{
int time = 300;

for(int i = 0;i < 3;i++)
{
	printf("   Loading...   | ");
	delay(time);
	clrscr();
	printf("   Loading...   / ");
	delay(time);
	clrscr();
	printf("   Loading...   - ");
	delay(time);
	clrscr();
	printf("   Loading...   \\ ");
	delay(time);
	clrscr();
}
}

//Method for Hot Keys
//@param: void
//@return: hex value of keyboard entry
//@throws: none
//@author: Parth S.
/*int getkey(void)
{
   union REGS keyin, keyout;
   keyin.h.ah = 0x08;
   int86(0x21, &keyin, &keyout);
   if (keyout.h.al == 0)
   {
      return(getkey()+0x100);
   }
   else
   {
      return(keyout.h.al);
   }
}

// Method to flush keyboard buffer
//@param: void
//@return: void
//@throws: none
//@author: Parth S.
void flushKeyboard()
{
	while(kbhit())
		getch();
}*/

// Mouse Functions :

// Method to show cursor
void showmouseptr()
{
/*
in.x.ax=1;
int86(0x33, &in, &out);
*/
}

// Method to get status of mouse pointer:
//including position of pointer & buttons pressed
void getmousepos(int *button, int *x, int *y)
{
/*
in.x.ax=3;
int86(0x33, &in, &out);
*button=out.x.bx;// return integer value.
*/
// 0 if no button pressed
// 1 if left click
// 2 if right click
// 3 if middle btn press
/*
*x=out.x.cx;// X Position
*y=out.x.dx;// Y Position
*/
*button = mouseclick();
*x = mousex();
*y = mousey();
}

// Method to set mouse position
void setposi(int &x,int &y) {
 /*
 in.x.ax=4;
 in.x.cx=x;
 in.x.dx=y;
 int86(51,&in,&out);
 */
}

// Method to hide mouse
void mousehide() {
 /*
 in.x.ax=2;
 int86(51,&in,&out);
 */ 
}

// Method to restrict mouse
void restrictmouseptr(int x1,int y1,int x2,int y2)
 {
 /*
 in.x.ax=7;
 in.x.cx=x1;
 in.x.dx=x2;
 int86(51,&in,&out);
 in.x.ax=8;
 in.x.cx=y1;
 in.x.dx=y2;
 int86(51,&in,&out);
 */ 
}
