#ifndef REQ_H
#define REQ_H

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


extern char bracket[100];
extern char curly_brace[100];
extern int top_bracket;
extern int top_curly_brace;

FILE* validate_input(int arg_count,char *file_name);

int validate_hex(char *buf,int *idx,FILE *fp);
int validate_octal(char *buf,int *idx,FILE *fp);
int validate_binary(char *buf,int *idx,FILE *fp);

int validate_literal(char *buf,int *idx,FILE *fp);
int validate_char(char *buf,int *idx,FILE *fp);

int validate_parantheses(char ch);

int check_keyword(char *s);
int check_symbol(char* ch);
int check_operator(char *s);

#endif