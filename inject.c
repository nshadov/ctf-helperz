/* 
   COMPILE ME LIKE:
   gcc -shared -m32 -fPIC inject.c -ldl -o inject.dlsym
*/

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>

#include <dlfcn.h>

int strncmp(const char* s1, const char* s2, size_t n){
  printf("STRNCMP:\n");
  printf("1) %s\n", s1);
  printf("2) %s\n", s2);

  int (*original)(const char*, const char*, size_t);
  original = dlsym(RTLD_NEXT, "strncmp");
  
  return (*original)(s1, s2, n);
}


int strcmp(const char* s1, const char* s2){
  printf("STRCMP:\n");
  printf("1) %s\n", s1);
  printf("2) %s\n", s2);

  int (*original)(const char*, const char*);
  original = dlsym(RTLD_NEXT, "strcmp");

  return (*original)(s1, s2);
}


int rand(void){
  printf("RAND:\n");

  int (*original)(void);
  original = dlsym(RTLD_NEXT, "rand");

  int tmp = (*original)();

  printf("1) %d\n", tmp);
  
  return tmp;
}


long ptrace(int request, pid_t pid, void *addr, void *data) {
  printf("--- PTRACE ---\n");

  long (*original)(int, pid_t, void *, void *);
  original = dlsym(RTLD_NEXT, "ptrace");

  return (*original)(request, pid, addr, data);
  
}
