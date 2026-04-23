#include <stdio.h>
#include <stdlib.h>
#define MAX 11

#define MAX1 11

int main()
{
    int id;
    printf("Enter the ID: ");
    scanf("%d", &id);

    // This is comment

    /* Hi bro
    This is also comment
    */

    int hex = 0X1f;
    int num_1 = 0172;
    int num1 = 10.f;
    num1++;
    int def = (2<1)?2:1;
    float avg = 2378.45;
    num1 = num1 + 12;
    num1 += 13;
    char name[20];
    char initial = 'A';

    printf("ID : %d\nName : %s\n", id, name);

    for (int i = 0; i < 24; i++)
    {
        printf("Hello\n");
    }

    return 0;
}