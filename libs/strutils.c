#include "strutils.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

str* strsplit(str s, char d, size_t* lr) {
  str tmp = strdup(s);
  if (!tmp) return NULL;
  str w = strtok(tmp, &d);
  str* v = malloc(sizeof(str));
  if (!v){
    free(v);
    free(w);
    free(tmp);
    return NULL;
  }
  size_t l = 0;
  while (w != NULL) {
    l++;
    v = realloc(v, l * sizeof(str));
    if (!v) {
      for (size_t i = 0; i < l; i++) free(v[i]);
      free(v);
      free(w);
      free(tmp);
      return NULL;
    }
    v[l - 1] = strdup(w);
    w = strtok(NULL, &d);
  }
  if (lr != NULL)
    *lr = l;
  free(tmp);
  return v;
}

str strreverse(str s) {
  size_t l = strlen(s);
  str tmp = malloc(l);
  if (!tmp) return NULL;
  for (int i = l - 1; i >= 0; i--) {
    tmp[l - (i + 1)] = s[i];
  }
  tmp[l] = 0x00;
  return tmp;
}

// God help me
str strjoin(str* sa, size_t sal, char d) {
  size_t toalloc = 0;
  for (size_t i = 0; i < sal; i++)
    toalloc += strlen(sa[i]);
  toalloc += sal - 1 + 1;
  str temp = malloc(toalloc);
  if (!temp) return NULL;
  size_t pos = 0;
  for (size_t i = 0; i < sal; i++) {
    size_t len = strlen(sa[i]);
    memcpy(&temp[pos], sa[i], len);
    pos += len;
    if (i < sal - 1)
      temp[pos++] = d;
  }
  temp[pos] = '\0';
  return temp;
}

int strhas(str s, char c) {
  for (size_t i = 0; s[i]; i++) {
    if (s[i] == c) return 1;
  }
  return 0;
}

str strtitlecase(str s) {
  str temp = strdup(s);
  if (!temp) return NULL;
  if (temp[0] >= 0x61 && temp[0] <= 0x7a)
    temp[0] -= 0x20;
  for (size_t i = 1; temp[i]; i++) {
    if (temp[i] >= 0x61 && temp[i] <= 0x7a) {
      //if (temp[i - 1] == ' ' || temp[i - 1] == '-' || temp[i - 1] == '/' || temp[i - 1] == '\\' || temp[i - 1] == '\n')
      if (strhas(" -/\\\n", temp[i-1]))
        temp[i] -= 0x20;
    }
  }
  return temp;
}

str struppercase(str s) {
  str temp = strdup(s);
  if (!temp) return NULL;
  for (size_t i = 0; temp[i]; i++) {
    if (temp[i] >= 0x61 && temp[i] <= 0x7a)
      temp[i] -= 0x20;
  }
  return temp;
}

str strlowercase(str s) {
  str temp = strdup(s);
  if (!temp) return NULL;
  for (size_t i = 0; temp[i]; i++) {
    if (temp[i] >= 0x41 && temp[i] <= 0x5a)
      temp[i] += 0x20;
  }
  return temp;
}

str strreversecase(str s) {
  str temp = malloc(strlen(s) + 1);
  if (!temp) return NULL;
  for (size_t i = 0; s[i]; i++) {
    if (s[i] >= 0x41 && s[i] <= 0x5a)
      temp[i] = s[i] + 0x20;
    else if (s[i] >= 0x61 && s[i] <= 0x7a)
      temp[i] = s[i] - 0x20;
    else
      temp[i] = s[i];
  }
  temp[strlen(s)] = 0x00;
  return temp;
}


void dptrfree(void** dp, size_t ln) {
  for (size_t i = 0; i < ln; i++) free(dp[i]);
  free(dp);
}

// 2/11/26 FIXED A 37 BYTE BIG MEMORY LEAK:
// All heap blocks were freed -- no leaks are possible
str strreplace(str s, char c, char r) {
  str t = strdup(s);
  for (size_t i = 0; t[i]; i++) {
    if (t[i] == c) t[i] = r;
  }
  return t;
}

size_t strcount(str s, char c) {
  size_t cc = 0; // char count
  size_t n; // current char
  for (n = 0; s[n]; n++)
    if (s[n] == c) cc++;
  return cc;
}

str strrem(str s, char c) {
  size_t cc = strcount(s, c);
  if (cc == 0) return s;
  size_t cc2 = strlen(s) - cc;
  cc2++; // increment by 1 to give it space for a null term
  str t = malloc(cc2);
  size_t n, n2;
  for (n = n2 = 0; s[n]; n++)
    if (s[n] != c) t[n2++] = s[n]; // n2 moves only when it does't find c, n moves every iteration
  t[cc2] = 0;
  return t;
}
