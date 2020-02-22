#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  struct matrix *m1;
  struct matrix *m2;

  /*
  //Testing Code
  m2 = new_matrix(4, 2);
  printf("Testing add_edge. Adding (1, 2, 3), (4, 5, 6) m2 = ");
  add_point(m2, 1.0, 2.0, 3.0);
  add_point(m2, 4.0, 5.0, 6.0);
  print_matrix(m2);
  m1 = new_matrix(4,4);
  m1->lastcol = 4;
  ident(m1);
  printf("\nTesting ident. m1=\n");
  print_matrix(m1);
  printf("\nTesting matrix mult. m1 * m2=\n");
  matrix_mult(m1, m2);
  print_matrix(m2);
  m1->lastcol = 0;
  add_point(m1, 1.0, 2.0, 3.0);
  add_point(m1, 4.0, 5.0, 6.0);
  add_point(m1, 7.0, 8.0, 9.0);
  add_point(m1, 10.0, 11.0, 12.0);
  printf("\ntesting matrix mult. m1=\n");
  print_matrix(m1);
  printf("\ntesting matrix mult. m1 * m2 =\n");
  matrix_mult(m1,m2);
  print_matrix(m2);
  &*/

  //Generating an Image
  screen s;
  clear_screen(s);
  color c;

  struct matrix *draw;

  c.red = 0;
  c.green = 0;
  c.blue = 255;

  draw = new_matrix(4,1000);

  int x = XRES/2;
  int y = YRES/2;

  //plate

  add_edge(draw,x,y/2,0,x/2,y,0);
  //depth
  int i = 0;
  int tempx1 = x;
  int tempx2 = x/2;
  while(i < 30){
    add_edge(draw,tempx1,y/2,0,tempx2,y,0);
    tempx1--;
    tempx2--;
    i++;
  }


  add_edge(draw,x/2,y,0,x/2,y+100,0);
  //depth
  i = 0;
  tempx1 = x/2;
  int tempy1 = y+100;
  while(i<30){
    add_edge(draw,tempx1,y,0,tempx1,tempy1,0);
    tempx1--;
    tempy1++;
    i++;
  }

  add_edge(draw,x/2,y+100,0,3*x/2,y+100,0);
  //depth
  i = 0;
  tempx1 = x/2;
  tempx2 = 3*x/2;
  tempy1 = y + 100;
  while(i<30){
    add_edge(draw,tempx1,tempy1,0,tempx2,tempy1,0);
    tempx1--;
    tempx2--;
    tempy1++;
    i++;
  }
  add_edge(draw,3*x/2,y+100,0,3*x/2,y,0);
  add_edge(draw,3*x/2,y,0,x,y/2,0);

  draw_lines(draw, s, c);
  

  //Crest

  struct matrix *crest;
  crest = new_matrix(4,1000);

  c.red = 255;
  c.green = 0;
  c.blue = 0;

  int x1 = x/2 + 1;
  int x2 = 3*x/2 - 1;
  int y1 = y+99;
  int y2;

  while(y1 >= y+70){
    y2 = y1;
    add_edge(crest,x1,y1,0,x2,y2,0);
    y1--;
  }

  y2 = y;
  int bound = x2-30;
  while(x2 > bound){
    add_edge(crest,x1,y1,0,x2,y2,0);
    y1--;
    x2--;
    y2--;
  }
  int fr1 = y2; //fill-in region 1
  int fr2 = y1; //fill-in region 2

  y1 = y2;
  x1 = x1 + 30;
  bound = x1 + 45;
  while(x1 < bound){
    y1 = y2;
    add_edge(crest,x1,y1,0,x2,y2,0);
    x1++;
    x2--;
    y2--;
  }
  int fr3 = y1; //fill-in region 3
  int fx1 = x1; //fill-in xcor
  int fx2 = x2; //fill-in xcor

  draw_lines(crest, s, c);
  
  //fill-in

  struct matrix *fill;
  fill = new_matrix(4,1000);

  c.red = 255;
  c.green = 215;
  c.blue = 0;

  x1 = x/2;
  x2 = 3*x/2;
  y1 = y+69;
  y2 = y+69;
  while (y2 > y){
    add_edge(fill,x1,y1,0,x2,y2,0);
    y2--;
  }

  x1 = 3*x/2 - 30;
  x2 = x/2 + 30;
  y2 = fr1;
  y1 = y2;
  while(x2 > x/2){
    add_edge(fill,x1,y1,0,x2,y2,0);
    x2--;
    y2++;
  }
  while(y2 < fr2){
    add_edge(fill,x1,y1,0,x2,y2,0);
    y2++;
  }

  x1 = fx1;
  x2 = fx2;
  y1 = fr3;
  while(x1 != x2){
    y2 = y1;
    add_edge(fill,x1,y1,0,x2,y2,0);
    x1++;
    x2--;
    y1--;
  }


  draw_lines(fill,s,c);

  save_ppm(s, "matrix.ppm");
  save_extension(s, "matrix.png");
  display(s);

} 