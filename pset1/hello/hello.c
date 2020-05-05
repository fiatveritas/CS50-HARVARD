#include<stdio.h>
#include<cs50.h>

int main(void) //first program for the course
{
    string name = get_string("What is your name?\n");
    printf("hello, %s\n", name);
}

//testing out whether the environment runs for this