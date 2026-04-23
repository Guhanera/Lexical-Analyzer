#include "req.h"

int do_parsing(FILE *fp)
{
    char ch;
    char buf[50];
    int idx = 0;
    int float_flag = 0;

    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            if (top_bracket != -1)
            {
                printf("\033[1;31mError: expected ')' or ']' before ';' token\033[0m\n");
                return 0;
            }
        }



        if (isalpha(ch) || ch == '_')
        {
            buf[idx++] = ch;
            while ((ch = fgetc(fp)) != EOF)
            {
                if (isalnum(ch) || ch == '_')
                {
                    buf[idx++] = ch;
                }
                else
                {
                    break;
                }
            }
            fseek(fp, -1, SEEK_CUR);
        }
        else if (isdigit(ch))
        {
            buf[idx++] = ch;
            if (ch == '0')
            {
                char next = fgetc(fp);
                buf[idx++] = next;

                // Binary number validation
                if (next != EOF && next == 'b')
                {
                    if (!validate_binary(buf, &idx, fp))
                    {
                        return 0;
                    }
                }

                // Hexadecimal number validation
                else if (next != EOF && (next == 'x' || next == 'X'))
                {
                    if (!validate_hex(buf, &idx, fp))
                    {
                        return 0;
                    }
                }

                // Octal number validation
                else if (next != EOF && isdigit(next))
                {
                    if (!validate_octal(buf, &idx, fp))
                    {
                        return 0;
                    }
                }

                else
                {
                    buf[idx - 1] = '\0'; // CASE : return 0;
                    printf("\033[31mNUMERIC CONSTANT : %s\033[0m\n", buf);
                    idx = 0;
                }

                fseek(fp, -1, SEEK_CUR);
                continue;
            }
            else
            {
                while ((ch = fgetc(fp)) != EOF)
                {
                    if (ch == '.')
                    {
                        float_flag = 1;
                        buf[idx++] = ch;
                        continue;
                    }
                    if (!isalnum(ch)) // if \n or ':' is present break and print the number
                    {
                        break;
                    }
                    if (idx == 1 && isalpha(ch))
                    {
                        printf("\033[1;31mError: invalid suffix on integer constant\033[0m\n");
                        return 0;
                    }
                    if (isdigit(ch))
                    {
                        buf[idx++] = ch;
                    }
                }

                fseek(fp, -1, SEEK_CUR);
            }
        }
        else
        {
            buf[idx] = '\0';
            idx = 0;
            if (float_flag)
            {
                printf("\033[34mFLOAT CONSTANT : %f\033[0m\n", atof(buf));
                float_flag = 0;
            }
            else if (atoi(buf) != 0)
            {
                printf("\033[31mNUMERIC CONSTANT : %d\033[0m\n", atoi(buf));
            }
            else
            {
                if (strlen(buf) != 0)
                {
                    if (check_keyword(buf))
                    {
                        printf("\033[33mKEYWORD : %s\033[0m\n", buf);
                    }
                    else
                    {
                        printf("\033[36mIDENTIFIER : %s\033[0m\n", buf);
                    }
                }
            }

            // Validate parantheses
            if(ch == '(' || ch == ')' || ch =='[' || ch == ']' || ch == '{' || ch == '}'){
                if(!validate_parantheses(ch)){
                    printf("\033[1;31mError: expected ')' or ']' before ';' token\033[0m\n");
                    return 0;
                }
            }

            if (ch == '"')    // Validate string literal
            {
                if (!validate_literal(buf, &idx, fp))
                {
                    return 0;
                }
            }
            else if (ch == '\'')  // Validate character
            {
                if (!validate_char(buf, &idx, fp))
                {
                    return 0;
                }
            }
            else if (ch == '#')  // Skip Preprocessor derivates
            {
                char next;
                while (((next = fgetc(fp)) != '\n') && (next != EOF));
            }
            else
            {
                if (ch != ' ')
                {
                    buf[idx++] = ch;
                }
                char next = fgetc(fp);
                if (next != EOF)
                {
                    if ((next == ch || next == '=') || (ch == '/' || next == '*'))
                    {
                        buf[idx++] = next; // consume next
                    }
                    else
                    {
                        fseek(fp, -1, SEEK_CUR); // rewind only if unused
                    }
                }

                buf[idx] = '\0';

                // Skip single line and multi line comments
                if (strcmp(buf, "//") == 0)
                {
                    char ch;
                    while (((ch = fgetc(fp)) != '\n') && ch != EOF)
                        ;
                }
                else if (strcmp(buf, "/*") == 0)
                {
                    char ch;
                    next = fgetc(fp);
                    while (ch != '*' && next != '/')
                    {
                        ch = next;
                        next = fgetc(fp);
                    }
                }

                if (check_symbol(buf))
                {
                    printf("SYMBOL :   %s\n", buf);
                }
                else if (check_operator(buf))
                {
                    printf("\033[35mOPERATOR : %s\033[0m\n", buf);
                }
                idx = 0;
            }
        }
    }

    if (top_curly_brace != -1)
    {
        printf("\033[1;31mError: expected '}' before ';' token\033[0m\n");
        return 0;
    }

    return 1;
}