#include "req.h"

char bracket[100];
char curly_brace[100];
int top_bracket = -1;
int top_curly_brace = -1;

FILE *validate_input(int arg_count, char *file_name)
{
    FILE *fp;
    if (arg_count > 2)
    {
        fprintf(stderr, "\033[1;31mError: Invalid argument\033[0m\n");
        return NULL;
    }

    fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "\033[1;31mError: File not found\033[0m\n");
        return NULL;
    }
    return fp;
}

int validate_hex(char *buf, int *idx, FILE *fp)
{
    char ch;
    while ((ch = fgetc(fp)) != ';')
    {
        if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f'))
        {
            buf[(*idx)++] = ch;
        }
        else
        {
            printf("\033[1;31mError: invalid suffix '%c' on integer constant\033[0m\n", ch);
            return 0;
        }
    }
    buf[(*idx)++] = '\0';
    printf("\033[31mNUMERIC CONSTANT : %s\033[0m\n", buf);
    *idx = 0;
}

int validate_octal(char *buf, int *idx, FILE *fp)
{
    fseek(fp, -1, SEEK_CUR);
    char ch;
    while ((ch = fgetc(fp)) != ';')
    {
        if (ch > '7')
        {
            printf("\033[1;31mError: invalid digit '%c' in octal constant\033[0m\n", ch);
            return 0;
        }
        else
        {
            buf[(*idx)++] = ch;
        }
    }
    buf[(*idx)] = '\0';
    printf("\033[31mNUMERIC CONSTANT : %s\033[0m\n", buf);
    *idx = 0;
}

int validate_binary(char *buf, int *idx, FILE *fp)
{
    char ch;
    while ((ch = fgetc(fp)) != ';')
    {
        if (ch != '0' && ch != '1')
        {
            printf("\033[1;31mError: invalid digit \"2\" in binary constant\033[0m\n");
            return 0;
        }
        else
        {
            buf[(*idx)++] = ch;
        }
    }
    buf[*idx] = '\0';
    printf("\033[31mNUMERIC CONSTANT : %s\033[0m\n", buf);
    *idx = 0;
}

int validate_literal(char *buf, int *idx, FILE *fp)
{
    char ch;
    while ((ch = fgetc(fp)) != '"')
    {
        if (ch == '\n')
        {
            printf("\033[1;31mError : String literal not completed\033[0m\n");
            return 0;
        }
        buf[(*idx)++] = ch;
    }
    buf[*idx] = '\0';
    *idx = 0;
    printf("\033[32mLITERAL : \"%s\"\033[0m\n", buf);
}

int validate_char(char *buf, int *idx, FILE *fp)
{
    char ch;
    while ((ch = fgetc(fp)) != '\'')
    {
        if (ch == '\n')
        {
            printf("\033[1;31mError: missing terminating ' character\033[0m\n");
            return 0;
        }
        if (*idx >= 1)
        { // Case : char ch = 'AA';
            printf("\033[1;31mError: Overflow in char const\033[0m\n");
            return 0;
        }
        buf[(*idx)++] = ch;
    }
    buf[*idx] = '\0';
    *idx = 0;
    printf("\033[32mCHARACTER CONST : '%s'\033[0m\n", buf);
}

int validate_parantheses(char ch)
{
    if (ch == '(' || ch == '[')
    {
        bracket[++top_bracket] = ch;
    }
    if (ch == ')' || ch == ']')
    {
        char temp = bracket[top_bracket--];
        if((ch == ')' && temp != '(') || (ch == ']' && temp != '[')){
            return 0;
        }
    }

    if (ch == '{')
    {
        curly_brace[++top_curly_brace] = ch;
    }
    if (ch == '}')
    {
        char temp = curly_brace[top_curly_brace--];
        if(ch == '}' && temp != '{'){
            return 0;
        }
    }
    return 1;
}

int check_keyword(char *s)
{
    const char *keywords[] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "goto", "if",
        "inline", "int", "long", "register", "restrict", "return", "short",
        "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while", "_Alignas", "_Alignof", "_Atomic", "_Bool", "_Complex",
        "_Generic", "_Imaginary", "_Noreturn", "_Static_assert", "_Thread_local"};

    for (int i = 0; i < 32; i++)
    {
        if (strcmp(s, keywords[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int check_symbol(char *ch)
{
    const char *symbols[] = {",", ";", ".", "->", "...", "(", ")", "{", "}", "[", "]", "\\", "\"", "'"};

    int len = sizeof(symbols) / sizeof(symbols[0]);
    for (int i = 0; i < len; i++)
    {
        if (strcmp(ch, symbols[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int check_operator(char *s)
{
    const char *operator[] = {
        /* Arithmetic operators */
        "+",
        "-",
        "*",
        "/",
        "%",
        "++",
        "--",

        /* Relational operators */
        "==",
        "!=",
        ">",
        "<",
        ">=",
        "<=",

        /* Logical operators */
        "&&",
        "||",
        "!",

        /* Bitwise operators */
        "&",
        "|",
        "^",
        "~",
        "<<",
        ">>",

        /* Assignment operators */
        "=",
        "+=",
        "-=",
        "*=",
        "/=",
        "%=",
        "&=",
        "|=",
        "^=",
        "<<=",
        ">>=",

        /* Ternary opeartor */
        "?",":"
    };

    int len = sizeof(operator) / sizeof(operator[0]);
    for (int i = 0; i < len; i++)
    {
        if (strcmp(s, operator[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}