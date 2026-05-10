#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

int makearray(int[]);
void bubble(int[], int);
void printout(int[], int);
const int SIZE = 100;

int makearray(int number[])
{
    int last = rand() % 11 + 10;   // random size 10-20

    for (int i = 0; i < last; i++)
    {
        number[i] = rand() % 100;  // random value 0-99
    }

    return last;
}

void bubble(int number[], int last)
{
    for (int i = 0; i < last - 1; i++)
    {
        if (number[i] > number[i + 1])
        {
            int temp = number[i];
            number[i] = number[i + 1];
            number[i + 1] = temp;
        }
    }
}

void printout(int number[], int last)
{
    for (int i = 0; i < last; i++)
    {
        cout << number[i] << "\t";
    }
    cout << endl;
}