#include "req.h"
#include "parse.h"

int main(int argc, char *argv[])
{
    FILE *fp = validate_input(argc, argv[1]);
    if (fp == NULL)
    {
        return 0;
    }

    if (!do_parsing(fp))
    {
        return 0;
    }
}