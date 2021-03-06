#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

int tokenIdx = 0;
char *tokens;

int E();
int F();
int T();

void error(char *msg) {
  printf("%s", msg);
  assert(0);
}

char ch() {
  char c = tokens[tokenIdx];
  return c;
}

char next() {
  char c = ch();
  tokenIdx++;
  return c;
}

int isNext(char *set) {
  char c = ch();
  return (c!='\0' && strchr(set, c)!=NULL);
}

int nextTemp() {
  static int tempIdx = 0;
  return tempIdx++;
}

// E = T ([+-] T)*
int E() {
  int i1 = T();
  while (isNext("+-")) { 
    char op=next();
    int i2 = T();
    int i = nextTemp();
    printf("t%d=t%d%ct%d\n", i, i1, op, i2);
    i1 = i;
  }
  return i1;
}

// T = F ([*/] F)*
int T() {
  int t1 = F();
  while (isNext("*/")) {
    char op=next();
    int t2 = F();
    int t =nextTemp();
    printf("t%d=t%d%ct%d\n", t, t1, op, t2);
    t1=t;
  }
  return t1;
}

// F =  Number | Id | '(' E ')'
int F() {
  int f;
  char c = ch();
  if (isdigit(c)||isalpha(c)) {
    next(); // skip c
    f = nextTemp();
    printf("t%d=%c\n", f, c);
  } 
  else if (c=='(') { // '(' E ')'
    next();
    f = E();
    assert(ch()==')');
    next();
  } 
  else {
    error("F = (E) | Number fail!");
  }
  return f; 
}

void parse(char *str) {
  tokens = str;
  E();
}

int main(int argc, char * argv[]) {
  printf("=== EBNF Grammar =====\n");
  printf("E=T ([+-] T)*\n");
  printf("T=F ([*/] F)*\n");
  printf("F=Number | '(' E ')'\n");
  printf("==== parse:%s ========\n", argv[1]);
  parse(argv[1]);
}
