#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void displayPriceTable();
void displayAvailableDays();
void clrscr();

int main()
{
    clrscr();

    displayPriceTable();
    displayAvailableDays();

    return 0;
}

void displayPriceTable()
{
    FILE *ptr;
    char ch;

    ptr = fopen("./data.txt", "r");

    if (ptr == NULL)
    {
        printf("File not found");
        return;
    }

    do
    {
        ch = fgetc(ptr);
        printf("%c", ch);
    } while (ch != EOF);
}

void displayAvailableDays()
{
    // Get current time
    time_t t;
    struct tm *now;
    time(&t);
    now = localtime(&t);

    printf("\n\n\n\n\t\t\tAvailable dates in the next 2 weeks:");
    printf("\n----------------------------------------------------------------------------------------\n");

    // Print the dates for the next 2 weeks with the day of the week
    for (int i = 0; i < 14; i++)
    {
        // Calculate the date for the next day
        now->tm_mday += 1;
        mktime(now);

        // Format and print the date with the day of the week
        char date_str[20];
        strftime(date_str, sizeof(date_str), "%A %d/%m/%y", now);
        printf("%2d: %20s\t", i, date_str);

        (i + 1) % 3 == 0 && i != 0 && printf("\n\n");
    }
}

// Creating my own clrscr function because clrscr is deprecated...
void clrscr()
{
    // The system function is used to execute a command on the OS terminal.
    system("cls");
}