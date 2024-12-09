#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {False, True} bool;
typedef struct maillon {
  int v;
  struct maillon *suiv;
  } maillon, *Liste;


void global(void);