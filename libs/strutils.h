#ifndef STRUTILS_H
#define STRUTILS_H

typedef char* str;

// returns an array of strings containing
// `s` split into smaller chunks by `d`
//
// `str s`: string
//
// `char d`: delimiter
//
// `int* lr`: length return
str* strsplit(str s, char d, unsigned long* lr);

// invert a string
//
// `str s`: string
str strinvert(str s);

// free a double-pointer variable
//
// `void** dp`: double-pointer
//
// `size_t ln`: double-pointer length
void dptrfree(void** dp, unsigned long ln);

// the polar opposite of `strsplit`
//
// `str* sa`: string array
//
// `size_t sal`: string array length
//
// `char d`: delimiter
str strjoin(str* sa, unsigned long sal, char d);

// title-case a string
//
// `str s`: string
str strtitlecase(str s);

// uppercase a string
//
// `str s`: string
str struppercase(str s);

// lowercase a string
//
// `str s`: string
str strlowercase(str s);

// `strlowercase` and `struppercase`
// in one function
//
// `str s`: string
str strreversecase(str s);


// replace all characters in `s`
// with `c`
//
// `str s`: string
// `char c`: character to be replaced
// `char r`: character to replace `c`
// `str rs`: return string (pass `NULL`)
// to use `return`
str strreplace(str s, char c, char r, str* rs);

// find `c` in `s`
//
// `str s`: string
// `char c`: character to find
int strhas(str s, char c);

#endif // STRUTILS_H
