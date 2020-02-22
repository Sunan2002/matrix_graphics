#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  screen s;
  clear_screen(s);
  struct matrix *edges;
  struct matrix *m1;
  struct matrix *m2;

  edges = new_matrix(4, 4);

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

  display(s);
  save_ppm(s, "matrix.ppm");
  save_extension(s, "matrix.png");

  free_matrix( edges );
} 