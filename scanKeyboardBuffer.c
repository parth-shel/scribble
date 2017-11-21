//scanning the keyboard buffer
#include<stdio.h>//for printf
#include <conio.h>//for kbhit
#include <dos.h>//for regs

int getkey(void);

void main(void)                                                                                                            /* 8 */
{
   int hotKey;
      if (kbhit)
      {
	 hotKey=getkey();
	 printf("%x\n",hotKey);
      }
   getch();
}

int getkey(void)
{
   union REGS in, out;
   in.h.ah = 0x08;
   int86(0x21, &in, &out);
   if (out.h.al == 0)
   {
      return(getkey()+0x100);
   }
   else
   {
      return(out.h.al);
   }
}
