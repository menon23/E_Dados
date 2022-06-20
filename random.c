#include <stdio.h>
#include "mtwister.h"

int main() {
  MTRand r = seedRand(1234567);

  int i;/*
  for(i=0; i<10; i++) {
    printf("%f\n", genRand(&r));
  }*/
  int nonce = genRand(&r)*1000000;
  printf("%d\n", nonce);
  nonce = genRand(&r)*1000000;
  printf("%d\n", nonce);

  return 0;
}
