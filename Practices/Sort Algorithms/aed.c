#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

#include <assert.h>

/* ATENCAO AOS VARIOS #define ESPECIFIOS DE CADA ALGORITMO */

typedef int Item;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) { Item t = A; A = B; B = t; }
#define compexch(A, B) if (less(B, A)) exch(A, B)

#define N 200000
#define maxN 1000000
#define M 100000

void selection(Item a[], int l, int r)
{ 
  int i, j, min;
  for (i = l; i < r; i++) {
    min = i;
    for (j = i+1; j <= r; j++) 
      if (less(a[j], a[min])) 
        min = j; 
    exch(a[i], a[min]); 
  }
}

void insertion(Item a[], int l, int r)
{ 
  int i;

  /* Coloca menor elemento na primeira posicao */
  for (i = l+1; i <= r; i++)
    compexch(a[l], a[i]);

  for (i = l+2; i <= r; i++) {
    int j = i;

    /* Variavel auxiliar para guardar o valor a[i] */
    Item v = a[i];

    /* Enquanto v < a[j] puxar os valores para a direita */
    /* Como o primeiro elemento e' o menor podemos omitir a condicao j>=l */
    while (less(v, a[j-1])) {
      a[j] = a[j-1];
      j--;
    }

    /* Guardar o valor originalmente na posicao i na posicao libertada */
    a[j] = v;
  }
}

void bubble(Item a[], int l, int r)
{ 
  int i, j, done;
  for (i = l; i < r; i++){
    done=1;
    for (j = r; j > i; j--) 
      if (less(a[j], a[j-1])){  
        exch(a[j-1], a[j]);
        done=0;
      }
    if (done) break;
  }
}

void shellsort(Item a[], int l, int r)
{ 
  int i, j, h;
  Item v;

  /* 1, 4, 13, 40, 121, 364, 1093, 3280, ... */
  for (h = 1; h <= (r-l)/9; h = 3*h+1)
    ;

  /* Execucao para os valores de h, por ordem inversa. */
  for ( ; h > 0; h /= 3) {

    /* Insertion sort com saltos de tamanho h. */
    for (i = l+h; i <= r; i++) {
      j = i;
      v = a[i];

      while (j >= l+h && less(v, a[j-h])) {
        a[j] = a[j-h]; 
        j -= h;
      }
      a[j] = v;
    }
  }
}

int partition(Item a[], int l, int r) {
  int i = l-1;
  int j = r;

  /* a[r] 'e o pivot. */
  Item v = a[r];

  /* Enquanto o iterador da esquerda for menor que o iterador da direita. */
  while (i < j) {

    /* Enquanto a[i]<v avanca com o i para a direita. */
    while (less(a[++i], v));

    /* Enquanto v<a[j] avanca com o j para a esquerda. */
    while (less(v, a[--j]))
      if (j == l) /* O elemento onde se faz a particao pode ser o primeiro! */
        break;

    /* Trocar, se for o caso! */
    if (i < j)
      exch(a[i], a[j]);
  }

  /* Colocar o pivot na posicao i. */
  exch(a[i], a[r]);

  /* Retorna posicao onde ocorreu a particao. */
  return i;
}

void quicksort(Item a[], int l, int r) 
{
  int i;

  if (r <= l)
    return;

  i = partition(a, l, r);
  quicksort(a, l, i-1);
  quicksort(a, i+1, r);
}

#define QM 10

void quicksortM(Item a[], int l, int r) 
{
  int i;

  if(r-l <= QM) {
    insertion(a, l, r);
    return;
  }

  i = partition(a, l, r);
  quicksort(a, l, i-1);
  quicksort(a, i+1, r);
}

Item aux[maxN];

void merge(Item a[], int l, int m, int r)
{ 
  int i, j, k;
  for (i = m+1; i > l; i--) 
    aux[i-1] = a[i-1];
  for (j = m; j < r; j++)
    aux[r+m-j] = a[j+1];
  for (k = l; k <= r; k++)
    if (less(aux[j], aux[i]))
      a[k] = aux[j--];
    else
      a[k] = aux[i++];
}

void mergesort(Item a[], int l, int r) { 
  int m = (r+l)/2;

  if (r <= l)
    return;

  mergesort(a, l, m);
  mergesort(a, m+1, r);
  merge(a, l, m, r);
}

#define LEFT(x)   (((x) << 1) + 1)
#define RIGHT(x)  (((x) + 1) << 1)
#define PARENT(x) ((((x) + 1) >> 1) - 1)

void fixDown(Item a[], int l, int r, int k)
{
  int ileft, iright, largest=k;

  ileft=l+LEFT(k-l);
  iright=l+RIGHT(k-l);

  if (ileft<=r && less(a[largest],a[ileft])) 
    largest=ileft;
  if (iright<=r && less(a[largest],a[iright]))
    largest=iright;

  if (largest!=k){
    exch(a[k],a[largest]);
    fixDown(a, l, r, largest);
  }
}

void buildheap(Item a[], int l, int r){
  int k, heapsize = r-l+1;
  for (k = heapsize/2-1; k >= l; k--)
    fixDown(a, l, r, l+k);
}

void heapsort(Item a[], int l, int r) { 
  buildheap(a,l,r);
  while (r-l > 0) {
    exch(a[l], a[r]);
    fixDown(a, l, --r, l);
  }
}

/*
 * int a[]
 *  +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
 *  |  5 |  2 |  1 |  6 |  5 |  3 |  3 |  4 |  0 |  1 |  2 |  4 |  6 |  0 |  4 |  6 |  3 |  1 |
 *  +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
 *    l                                                                                     r
 *
 * N = r-l+1 = 18 e M = 7
 */
void distcount(int a[], int l, int r)
{
  int i, j, cnt[M+1];
  int b[maxN];

  /*
   * Inicializar cnt[M+1] a 0
   *  +----+----+----+----+----+----+----+----+
   *  |  0 |  0 |  0 |  0 |  0 |  0 |  0 |  0 |
   *  +----+----+----+----+----+----+----+----+
   */
  for (j = 0; j <= M; j++)
    cnt[j] = 0;

  /*
   * Contar elementos em a[], cnt[a[i]+1] fica com o numero de ocorrencias de a[i]
   *  +----+----+----+----+----+----+----+----+
   *  |  0 |  2 |  3 |  2 |  3 |  3 |  2 |  3 |
   *  +----+----+----+----+----+----+----+----+
   */
  for (i = l; i <= r; i++)
    cnt[a[i]+1]++;

  /*
   * Acumular valores em cnt[] por forma a que cnt[i] indique a posicao final de i
   *  +----+----+----+----+----+----+----+----+
   *  |  0 |  2 |  5 |  7 | 10 | 13 | 15 | 18 |
   *  +----+----+----+----+----+----+----+----+
   */
  for (j = 1; j < M; j++)
    cnt[j] += cnt[j-1];

  /*
   * Guardar em {{{b}}} os valores de {{{a}}} ordenados
   *
   * int cnt[]
   *  +----+----+----+----+----+----+----+----+
   *  |  2 |  5 |  7 | 10 | 13 | 15 | 18 | 18 |
   *  +----+----+----+----+----+----+----+----+
   *
   * int b[]
   *  +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
   *  |  0 |  0 |  1 |  1 |  1 |  2 |  2 |  3 |  3 |  3 |  4 |  4 |  4 |  5 |  5 |  6 |  6 |  6 |
   *  +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
   *
   * Notar que cnt[] e' actualizado 'a medida que são colocados os elementos em b[]
   */
  for (i = l; i <= r; i++)
    b[cnt[a[i]]++] = a[i];

  /*
   * Copiar {{{b}}} para {{{a}}}
   *
   * int a[]
   *  +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
   *  |  0 |  0 |  1 |  1 |  1 |  2 |  2 |  3 |  3 |  3 |  4 |  4 |  4 |  5 |  5 |  6 |  6 |  6 |
   *  +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
   */
  for (i = l; i <= r; i++)
    a[i] = b[i - l];
}

void distcount2(int a[], int l, int r)
{
  int i, j, cnt[M];
  int b[maxN];
  for (j = 0; j < M; j++)
    cnt[j] = 0;
  for (i = l; i <= r; i++)
    cnt[a[i]]++;
  for (j = 1; j < M; j++)
    cnt[j] += cnt[j-1];
  for (i = r; i >= l; i--)
    b[--cnt[a[i]]] = a[i];
  for (i = l; i <= r; i++)
    a[i] = b[i - l];
}

#define bitsword 32
#define bitsbyte 8
#define bytesword 4
#define digit(n,w) (0xff & ((n) >> ((bytesword - (w) - 1) << 3)))
#define nbit(n,w)  (0x01 & ((n) >> (bitsword - (w) - 1)))

/* Numero de valores possiveis para um digito */
#define R (1 << bitsbyte)

Item aux[maxN];

void radixLSD(Item a[], int l, int r)
{
  int i, j, w, count[R+1];
  for (w = bytesword-1; w >= 0; w--) {

    /* Counting sort para o digito w */
    for (j = 0; j < R; j++)
      count[j] = 0;
    for (i = l; i <= r; i++)
      count[digit(a[i], w) + 1]++;
    for (j = 1; j < R; j++)
      count[j] += count[j-1];
    for (i = l; i <= r; i++)
      aux[count[digit(a[i], w)]++] = a[i];
    for (i = l; i <= r; i++)
      a[i] = aux[i - l];
  }
}

void quicksortB(int a[], int l, int r, int w)
{
  int i = l, j = r;
  if (r <= l || w >= bitsword)
    return;

  /* Particiona o vector em duas áreas:
   *  - chaves com bit w a 0
   *  - chaves com bit w a 1
   */
  while (j != i) {
    while (nbit(a[i], w) == 0 && (i < j)) i++;
    while (nbit(a[j], w) == 1 && (j > i)) j--;
    exch(a[i], a[j]);
  }
  if (nbit(a[r], w) == 0)
    j++;

  /* Ordena recursivamente cada área */
  quicksortB(a, l, j-1, w+1);
  quicksortB(a, j, r, w+1);
}

#define bin(A) l+count[A]
void radixMSD(Item a[], int l, int r, int w)
{
  int i, j, count[R+1];

  if (w > bytesword)
    return;

  /* Optimizacao */
  if (r-l <= QM) {
    insertion(a, l, r);
    return;
  }

  /* Counting sort para o digito w */
  for (j = 0; j < R; j++)
    count[j] = 0;
  for (i = l; i <= r; i++)
    count[digit(a[i], w) + 1]++;
  for (j = 1; j < R; j++)
    count[j] += count[j-1];
  for (i = l; i <= r; i++)
    aux[count[digit(a[i], w)]++] = a[i];
  for (i = l; i <= r; i++)
    a[i] = aux[i - l];

  /* Os bins denotam as caixas discutidas acima */
  radixMSD(a, l, bin(0)-1, w+1);
  for (j = 0; j < R-1; j++)
    radixMSD(a, bin(j), bin(j+1)-1, w+1);
}

int
intcmp(const void * x, const void * y)
{
  return *((const int *) x) - *((const int *) y);
}

int diff(int a[], int an, int b[], int bn)
{
  int i;

  if (an != bn)
    return 1;

  for (i = 0; i < an; i++)
    if (a[i] != b[i])
      return 1;

  return 0;
}

void
timedlog(char *t)
{
  time_t current_time;
  char* c_time_string;

  current_time = time(NULL);
  c_time_string = ctime(&current_time);
  c_time_string[strlen(c_time_string) - 1] = '\0';

  printf("[%s] %s\n", c_time_string, t);
}

int
main(int argc, char *argv[])
{
  int i, a[N], r[N], s[N];

  if (argc > 1)
    srand(atoi(argv[1]));

  for (i = 0; i < N; i++) {
    a[i] = (M-1)*(1.0*rand()/RAND_MAX);
    assert(a[i] < M);
  }

  timedlog("running qsort");
  memcpy(r, a, sizeof(int)*N);
  assert(!diff(a, N, r, N));
  qsort(r, N, sizeof(int), intcmp);

  timedlog("testing selectionsort");
  memcpy(s, a, sizeof(int)*N);
  assert(!diff(a, N, s, N));
  selection(s, 0, N-1);
  assert(!diff(r, N, s, N));

  timedlog("testing insertionsort");
  memcpy(s, a, sizeof(int)*N);
  assert(!diff(a, N, s, N));
  insertion(s, 0, N-1);
  assert(!diff(r, N, s, N));

  timedlog("testing bubblesort");
  memcpy(s, a, sizeof(int)*N);
  assert(!diff(a, N, s, N));
  bubble(s, 0, N-1);
  assert(!diff(r, N, s, N));
  
  timedlog("testing shellsort");
  memcpy(s, a, sizeof(int)*N);
  assert(!diff(a, N, s, N));
  shellsort(s, 0, N-1);
  assert(!diff(r, N, s, N));
  
  timedlog("testing quicksort");
  memcpy(s, a, sizeof(int)*N);
  assert(!diff(a, N, s, N));
  quicksort(s, 0, N-1);
  assert(!diff(r, N, s, N));
  
  timedlog("testing quicksort+insertionsort");
  memcpy(s, a, sizeof(int)*N);
  assert(!diff(a, N, s, N));
  quicksortM(s, 0, N-1);
  assert(!diff(r, N, s, N));
  
  timedlog("testing mergesort");
  memcpy(s, a, sizeof(int)*N);
  assert(!diff(a, N, s, N));
  mergesort(s, 0, N-1);
  assert(!diff(r, N, s, N));
  
  timedlog("testing heapsort");
  memcpy(s, a, sizeof(int)*N);
  assert(!diff(a, N, s, N));
  heapsort(s, 0, N-1);
  assert(!diff(r, N, s, N));
  
  timedlog("testing countingsort");
  memcpy(s, a, sizeof(int)*N);
  assert(!diff(a, N, s, N));
  distcount(s, 0, N-1);
  assert(!diff(r, N, s, N));
  
  timedlog("testing countingsort (2)");
  memcpy(s, a, sizeof(int)*N);
  assert(!diff(a, N, s, N));
  distcount2(s, 0, N-1);
  assert(!diff(r, N, s, N));
  
  timedlog("testing radixLSD");
  memcpy(s, a, sizeof(int)*N);
  assert(!diff(a, N, s, N));
  radixLSD(s, 0, N-1);
  assert(!diff(r, N, s, N));
  
  timedlog("testing radixMSD");
  memcpy(s, a, sizeof(int)*N);
  assert(!diff(a, N, s, N));
  radixMSD(s, 0, N-1, 0);
  assert(!diff(r, N, s, N));
  
  timedlog("testing binary quicksort");
  memcpy(s, a, sizeof(int)*N);
  assert(!diff(a, N, s, N));
  quicksortB(s, 0, N-1, 0);
  assert(!diff(r, N, s, N));

  /* 
  for (i = 0; i < N; i++)
    printf("a[%3d] = %3d\n", i, a[i]);
  */

  return EXIT_SUCCESS;
}

