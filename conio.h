// implement the conio.h library to work with gcc
// @author: parth_shel
// @version: v:1.0 - Dec. 26, 2017

//include headers
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>

//gotoxy() function definition
void gotoxy(int x,int y) {
    printf("%c[%d;%df",0x1B,y,x);
}

//clrscr() function definition
void clrscr(void) {
    system("clear");
}

static struct termios Old, New;
 
/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &Old); //grab old terminal i/o settings
  New = Old; //make new settings same as old settings
  New.c_lflag &= ~ICANON; //disable buffered i/o
  New.c_lflag &= echo ? ECHO : ~ECHO; //set echo mode
  tcsetattr(0, TCSANOW, &New); //apply terminal io settings
}
 
/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &Old);
}
 
/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}
 
/* 
Read 1 character without echo 
getch() function definition.
*/
/*char getch(void) 
{
  return getch_(0);
}*/
 
/* 
Read 1 character with echo 
getche() function definition.
*/
char getche(void) 
{
  return getch_(1);
}

/* gets as a wrapper around fgets() */
void gets(char * s) {
	fgets(s, 256, stdin);
}
