

      /************************************************************
      *
      *   file d:\cips\cips.h
      *
      *       Functions: This file contains no functions. It
      *          contains declarations of the data structures used
      *          by the C Image Processing Systems CIPS.
      *
      *   Purpose:
      *      To declare data structures.
      *
      *   Modifications:
      *      June 1990 = created
      *
      **********************************************************/

#include <stdio.h>

/*#include <io.h>
*/
#include <fcntl.h>
/*#include <dos.h>
*/
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
/*#include <sys\types.h>
#include <sys\stat.h>
*/

#define MAX_NAME_LENGTH       80
#define ROWS                  85
#define COLS                 100
#define ROW                  100
#define COL                  100 
#define MAXR                 70
#define MINR                 50
#define MINC                 40
#define MAXC                 100
#define HEIGHT_THRESHOLD     0.3
#define CHARACTER_WIDTH1     20  /*  For English 20, Urdu 40*/
#define TEXT_SIZE1           300 /*  For English 300,Telugu 300,Urdu 900 ,Oriya 300, Kannada 500 */  
#define GRAY_LEVELS          255
#define BISECTION_THRESHOLD  40  /* Based on Character occurance probability */ 
#define PREWITT              1
#define PEAK_SPACE           50
#define PEAKS                 30
#define KIRSCH                 2
#define SOBEL                  3
#define STACK_SIZE          4000
#define STACK_FILE_LENGTH    500
#define FORGET_IT            -50
#define STACK_FILE     "f:stack"


      /*********************************************
      *
      *   N O T E
      *   P O R T A B I L I T Y   I S S U E
      *
      *   The next two statements help port the 
      *   system to non-Microsoft C compilers.
      *   
      *   If you use Microsoft C, then you should
      *   #define MSC 1     and
      *   #undef  OTHERC
      *   
      *   If you are using another C compiler or
      *   are porting this to another type of 
      *   machine, then you should 
      *   #undef  MSC
      *   #define OTHERC 1
      *   
      *   Now you need to make changes in mymsc.c
      *
      **********************************************/

#define MSC 1
#undef  OTHERC

      /*********************************************
      *
      *   N O T E
      *   P O R T A B I L I T Y   I S S U E
      *
      *   Define the Microsoft contants.  If you
      *   are using OTHERC, then just put numbers
      *   there to hold a place.
      *
      *********************************************/

#ifdef MSC
#define VRES16COLOR  _VRES16COLOR
#define ERESCOLOR    _ERESCOLOR
#define MAXCOLORMODE _MAXCOLORMODE
#define HRESBW       _HRESBW
#define MRES4COLOR   _MRES4COLOR
#define TEXTC80      _TEXTC80
#define GCLEARSCREEN _GCLEARSCREEN
#endif

#ifdef OTHERC
#define VRES16COLOR  1
#define ERESCOLOR    1
#define MAXCOLORMODE 1
#define HRESBW       1
#define MRES4COLOR   1
#define TEXTC80      1
#define GCLEARSCREEN 1
#endif

      /**************************************************
      *
      *   The following struct defines the information
      *   you need to read from the tiff file
      *   header.
      *
      ***************************************************/

typedef struct tiff_header_struct{
   short lsb;
   long  bits_per_pixel;
   long  image_length;
   long  image_width;
   long  strip_offset;
}Head;

                /*********************************************
                *
                *       The following four unions are used
                *       to put the bytes from the header
                *       into either an integer or a floating
                *       point number.
                *
                **********************************************/

union short_char_union{
        short s_num;
        char  s_alpha[2];
};

union int_char_union{
        int  i_num;
   char i_alpha[2];
};

union long_char_union{
        long  l_num;
        char  l_alpha[4];
};

union float_char_union{
        float f_num;
        char  f_alpha[4];
};

 typedef struct Store
    {
       int x;
       int y;
    }st;


