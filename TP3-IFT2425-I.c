//------------------------------------------------------
// module  : Tp-IFT2425-I.c
// author  : François Poitras et Guillaume Noel Martel
// date    : \today
// version : 1.0
// language: C++
// note    :
//------------------------------------------------------
//

//------------------------------------------------
// FICHIERS INCLUS -------------------------------
//------------------------------------------------
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <new>
#include <time.h>

//-------------------------
//--- Windows -------------
//-------------------------
#include <X11/Xutil.h>

Display   *display;
int   screen_num;
int     depth;
Window    root;
Visual*   visual;
GC    gc;

//---------------------------------------------------------
//  Alloue de la memoire pour une matrice 1d de float
//----------------------------------------------------------
float* fmatrix_allocate_1d(int hsize)
{
  float* matrix;
  matrix = new float[hsize];
  return matrix;
}

//----------------------------------------------------------
//  Alloue de la memoire pour une matrice 2d de float
//----------------------------------------------------------
float** fmatrix_allocate_2d(int vsize, int hsize)
{
  float** matrix;
  float *imptr;

  matrix = new float*[vsize];
  imptr = new  float[(hsize) * (vsize)];

  for (int i = 0; i < vsize; i++, imptr += hsize)
    matrix[i] = imptr;
  return matrix;
}

//----------------------------------------------------------
// Libere la memoire de la matrice 1d de float
//----------------------------------------------------------
void free_fmatrix_1d(float* pmat)
{ delete[] pmat; }

//----------------------------------------------------------
// Libere la memoire de la matrice 2d de float
//----------------------------------------------------------
void free_fmatrix_2d(float** pmat)
{ delete[] (pmat[0]);
  delete[] pmat;
}

//-------------------------//
//---- Fonction Pour TP ---//
//-------------------------//
float sum(float* numbers, int start, int end)
{
  if (start + 1 == end) return numbers[start];
  int half = (start + end) / 2;
  return sum(numbers, start, half) + sum(numbers, half, end);
}

//----------------------------------------------------------
//----------------------------------------------------------
// PROGRAMME PRINCIPAL -------------------------------------
//----------------------------------------------------------
//----------------------------------------------------------
int main(int argc, char** argv)
{
  int   i, j, k, l;
//--------------------------------------------------------------------------------
// PROGRAMME ---------------------------------------------------------------------
//--------------------------------------------------------------------------------

//>Var
  float result;
  float result_;

//>Cst
  const float PI = 3.14159265358979323846264338;
  int NBINTERV = 5000000;
  int NbInt = NBINTERV;
  if (argc > 1)  { NbInt = atoi(argv[1]); }
  float* VctPts = fmatrix_allocate_1d(NbInt + 1);

//Programmer ici

  result = 0;
  float intervalLen = 1 / (float)NbInt;
  for (int i = 0; i <= NbInt; i++)
  {
    float x = i / (float)NbInt;
    VctPts[i] = 4 * sqrt(1 - x*x);
    if (i > 0) {
      result += (VctPts[i] + VctPts[i-1]) * intervalLen / 2;
    }
  }

  printf("[1>Given_Order:] Pi=%.10lf Er=%.10lf LogEr=%.10lf\n",
    result, PI - result, log(PI - result));

  result = sum(VctPts, 0, NbInt + 1)/(NbInt+1);
  printf("[2>PairwiseSum:] Pi=%.10lf Er=%.10lf LogEr=%.10lf\n",
    result, PI - result, log(PI - result));

  float temp = 0;
  float s = 0;
  float e = 0;
  float y = 0;
  for (int i = 0; i <= NbInt; i++)
  {
    temp = s;
    y = VctPts[i] + e;
    s = temp + y;
    e = (temp - s) + y;
  }
  s /= NbInt + 1;
  printf("[3>KahanSummat:] Pi=%.10lf Er=%.10lf LogEr=%.10lf\n",
    s, PI - s, log(PI - s));

//retour sans probleme
  printf("\n Fini... \n\n\n");
  return 0;
}



