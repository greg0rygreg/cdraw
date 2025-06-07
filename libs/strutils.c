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
  *lr = l;
  free(tmp);
  return v;
}

str strinvert(str s) {
  size_t l = strlen(s);
  str tmp = malloc(l);
  if (!tmp) return NULL;
  for (int i = l - 1; i >= 0; i--) {
    tmp[l - (i + 1)] = s[i];
  }
  tmp[l] = 0x00;
  return tmp;
}

str strjoin(str* sa, size_t sal, char d) {
  size_t toalloc = 0;
  for (size_t i = 0; i < sal; i++)
    toalloc += strlen(sa[i]);
  toalloc += sal - 1;
  toalloc += 1;
  str temp = malloc(toalloc);
  if (!temp) return NULL;
  temp[0] = 0x00;
  for (size_t i = 0; i < sal; i++) {
    strcat(temp, sa[i]);
    if (i < sal - 1) {
      temp[strlen(temp)] = d;
      temp[strlen(temp) + 1] = 0x00;
    }
  }
  return temp;
}

str strtitlecase(str s) {
  str temp = strdup(s);
  if (!temp) return NULL;
  if (temp[0] >= 0x61 && temp[0] <= 0x7a)
    temp[0] -= 0x20;
  for (size_t i = 1; i < strlen(temp); i++) {
      if (temp[i - 1] == ' ' || temp[i - 1] == '-' || temp[i - 1] == '/' || temp[i - 1] == '\\' || temp[i - 1] == '\n') {
        if (temp[i] >= 0x61 && temp[i] <= 0x7a)
          temp[i] -= 0x20;
      }
  }
  return temp;
}

str struppercase(str s) {
  str temp = strdup(s);
  if (!temp) return NULL;
  for (size_t i = 0; i < strlen(temp); i++) {
    if (temp[i] >= 0x61 && temp[i] <= 0x7a)
      temp[i] -= 0x20;
  }
  return temp;
}

str strlowercase(str s) {
  str temp = strdup(s);
  if (!temp) return NULL;
  for (size_t i = 0; i < strlen(temp); i++) {
    if (temp[i] >= 0x41 && temp[i] <= 0x5a)
      temp[i] += 0x20;
  }
  return temp;
}

str strreversecase(str s) {
  str temp = malloc(strlen(s) + 1);
  if (!temp) return NULL;
  for (size_t i = 0; i < strlen(s); i++) {
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
  for (size_t i = 0; i < ln; i++)
    free(dp[i]);
  free(dp);
}

str strreplace(str s, char c, char r, str* rs) {
  str t = strdup(s);
  for (int i = 0; i < strlen(t); i++) {
    if (t[i] == c) {
      t[i] = r;
    }
  }
  if (rs == NULL)
    return t;
  else {
    *rs = strdup(t);
    free(t);
    return NULL;
  }
}

int strhas(str s, char c) {
  for (int i = 0; i < strlen(s); i++) {
    if (s[i] == c)
      return 1;
  }
  return 0;
}