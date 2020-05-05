#include <stdio.h>
#include <cs50.h>

void run(int num); //this function runs the program
void empty_space(int num); //this function produces white space
void hash_tag(int num); //this generate hashtags to the screen

int main(void)
{
    int num = -1;

    while (!(num >= 1 && num <= 8))
    {
        num = get_int("Height: ");
    }
    run(num);

}

void run(int num) //runs the program
{
    int symbol = -1;
    int space = -1;
    for (int i = 1; i <= num; i++)
    {
        symbol = i;
        space = num - i;
        empty_space(space);
        hash_tag(symbol);
        printf("  ");
        hash_tag(symbol);
        printf("\n");
    }
}

void empty_space(int num) //prints white space
{
    for (int j = 1; j <= num; j++)
    {
        printf(" ");
    }
}

void hash_tag(int num) //generates output to the user
{
    for (int i = 1; i <= num; i++)
    {
        printf("#");
    }
}