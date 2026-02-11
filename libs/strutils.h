#ifndef STRUTILS_H
#define STRUTILS_H

#ifdef __cplusplus
extern "C" {
#endif

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

// reverse a string
//
// `str s`: string
str strreverse(str s);

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
str strreplace(str s, char c, char r);

// find `c` in `s`
//
// `str s`: string
// `char c`: character to find
int strhas(str s, char c);

// count every instance of
// `c` in `s`
//
// `str s`: string
// `char c`: character to count
unsigned long strcount(str s, char c);

// remove every instance of
// `c` from `s`
//
// `str s`: string
// `char c`: character to remove
str strrem(str s, char c);

#ifdef __cplusplus
}
#endif

#endif // STRUTILS_H
