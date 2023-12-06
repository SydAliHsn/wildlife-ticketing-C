#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define BOOKINGS_FOLDER ("./bookings")

typedef struct Booking
{
    char name[25];
    int id;
    int ticketId;
    int numTickets;
    int days;
    int visitDay;
    int attractions[3];
    float price;
};

int ticketPrices[5] = {20, 12, 16, 60, 15};
float attractionPrices[3] = {2.5, 2, 5};
int personsPerTicket[5] = {1, 1, 1, 5, 1};

int displayFile(char[10]);
void displayAvailableDays();
int createBooking();
void clrscr();
char getChoice();
float calculatePrice(struct Booking);
int generateBookingId();
char *getTicketName(int);
int createBookingFile(struct Booking);
void displayBooking(int);
char *getDateString(int);
void deleteBooking(int);

int main()
{
    char choice;
    int bookingId;

    do
    {
        clrscr();

        sleep(1);
        displayFile("data.txt");
        sleep(1);
        displayAvailableDays();
        sleep(1);
        choice = getChoice();

        switch (choice)
        {
        case 'q':
            printf("\n\tExiting...\n\n\t\tBye!");
            return 0;
            break;

        case 'b':
            bookingId = createBooking();
            printf("\n\n\n");
            displayBooking(bookingId);
            break;

        case 'r':
            clrscr();
            printf("\n////////////////////////////////// REVIEW A BOOKING ////////////////////////////////////");
            printf("\n\n\t\tPlease enter a booking ID: ");
            scanf("%d", &bookingId);
            displayBooking(bookingId);
            break;

        case 'd':
            clrscr();
            printf("\n////////////////////////////////// CANCEL A BOOKING ////////////////////////////////////");
            printf("\n\n\t\tPlease enter a booking ID: ");
            scanf("%d", &bookingId);
            deleteBooking(bookingId);
            break;
        }
    } while (choice != 'q');

    return 0;
}

void deleteBooking(int bookingId)
{
    char fileName[20];
    FILE *file;
    int res;
    char choice;

    sprintf(fileName, "%s/%d.txt", BOOKINGS_FOLDER, bookingId);

    printf("\n\n\tThis is the booking you are going to delete: \n");
    res = displayFile(fileName);

    if (res != 0)
    {
        printf("\n\n\tNo booking found with this ID!");
    }
    else
    {
        printf("\n\n\tDo you want to delete this booking? (y/n): ");
        choice = getche();

        if (choice == 'y')
        {
            remove(fileName);
            printf("\n\n\tBooking# %d deleted successfully.", bookingId);
        }
    }

    printf("\n\tPress any key to continue.");
    getche();
}

void displayBooking(int bookingId)
{
    char fileName[20];
    int res;

    sprintf(fileName, "%s/%d.txt", BOOKINGS_FOLDER, bookingId);

    res = displayFile(fileName);

    if (res != 0)
    {
        printf("\n\n\t\tNo booking found with this ID!");
    }

    printf("\n\n\nPress any key to continue.");
    getch();
}

int displayFile(char fileName[20])
{
    FILE *file;
    char ch;

    file = fopen(fileName, "r");

    if (file == NULL)
    {
        // printf("File not found");
        return 1;
    }

    do
    {
        ch = fgetc(file);
        printf("%c", ch);
    } while (ch != EOF);

    fclose(file);
    return 0;
}

char *getDateString(int daysFromToday)
{
    static char date_str[20];

    // Get current time
    time_t t;
    struct tm *now;
    time(&t);
    now = localtime(&t);

    // Calculate the date for the day in number of daysFromToday.
    now->tm_mday += daysFromToday;
    mktime(now);

    // Format and print the date with the day of the week
    strftime(date_str, sizeof(date_str), "%A %d/%m/%y", now);

    return date_str;
}

void displayAvailableDays()
{

    printf("\n\n\n\t\t\tAvailable dates in the next 2 weeks:");
    printf("\n----------------------------------------------------------------------------------------\n");

    // Print the dates for the next 2 weeks with the day of the week
    for (int i = 1; i <= 14; i++)
    {
        printf("%2d: %20s\t", i, getDateString(i));

        i != 0 && i % 3 == 0 && printf("\n\n");
    }
}

// Creating my own clrscr function because clrscr is deprecated...
void clrscr()
{
    // The system function is used to execute a command on the OS terminal.
    system("cls");
}

char getChoice()
{
    char choice;
    do
    {
        printf("\n\n\n\tDo you want to: \n\t\tQuit (q) \n\t\tCreate a booking (b) \n\t\tReview a booking (r) \n\t\tDelete a booking (d) \n\tEnter your choice: ");
        choice = getche();
    } while (choice != 'q' && choice != 'b' && choice != 'r' && choice != 'd');
    return choice;
}

int createBooking()
{
    struct Booking booking = {
        attractions : {0, 0, 0},
    };
    int numAttractions;
    char choice;
    int i;

    clrscr();

    printf("\n\n\n////////////////////////////////////////////////////////////////////////////////////////");
    printf("\n////////////////////////////////// CREATE A BOOKING ////////////////////////////////////");
    printf("\n////////////////////////////////////////////////////////////////////////////////////////");

    do
    {
        printf("\n\n\tPlease enter your name (min. 3 characters): ");
        fgets(booking.name, 21, stdin);

        if (strlen(booking.name) - 1 < 3)
            printf("\n\tYour name must be at least 3 characters long.");
    } while (strlen(booking.name) - 1 < 3);

    displayFile("data.txt");
    do
    {
        printf("\n\n\tPlease enter the ticket type Id (1-5): ");
        scanf("%d", &booking.ticketId);

        if (booking.ticketId > 5 || booking.ticketId < 1)
            printf("\n\tThis ticket is not available. Please choose another one.");

    } while (booking.ticketId > 5 || booking.ticketId < 1);

    do
    {
        printf("\n\n\tPlease enter the number of tickets: ");
        scanf("%d", &booking.numTickets);

        if (booking.numTickets < 1)
            printf("\n\tYou have to book at least 1 ticket!");
    } while (booking.numTickets < 1);

    do
    {
        printf("\n\n\tPlease enter the number of days (1/2): ");
        scanf("%d", &booking.days);

        if (booking.days != 2 && booking.days != 1)
            printf("\n\tYou can only book for 1 or 2 days.");
    } while (booking.days != 2 && booking.days != 1);

    displayAvailableDays();
    do
    {
        if (booking.days > 1)
            printf("\n\n\tPlease enter the first day of visit (1-14): ");
        else
            printf("\n\n\tPlease enter the day of visit (1-14): ");

        scanf("%d", &booking.visitDay);

        if (booking.visitDay > 14 || booking.visitDay < 1)
        {
            printf("\n\tThis day is not available. Please choose another one.");
        }

    } while (booking.visitDay > 14 || booking.visitDay < 1);

    printf("\n\n\tChoose extra attractions.\n");
    for (i = 0; i < booking.days + 1; i++)
    {
        switch (i)
        {
        case 0:
            printf("\n\tLion Feeding ($2.50 per person) (y/n): ");
            break;

        case 1:
            printf("\n\tPenguin Feeding ($2.00 per person) (y/n): ");
            break;

        case 2:
            printf("\n\tEvening Barbecue ($5.00 per person) (y/n): ");
            break;

        default:
            break;
        }
        choice = getche();
        booking.attractions[i] = choice == 'y' ? 1 : 0;
    }

    booking.price = calculatePrice(booking);

    booking.id = generateBookingId();

    createBookingFile(booking);

    clrscr();
    printf("Booking created successfully!");

    return booking.id;
}

float calculatePrice(struct Booking booking)
{
    int i;

    float ticketsPrice = ticketPrices[booking.ticketId - 1] * booking.numTickets;
    if (booking.days == 2)
        ticketsPrice += ticketsPrice / 2;

    float attractionsPrice = 0;

    for (i = 0; i < 3; i++)
    {
        if (booking.attractions[i] == 1)
            attractionsPrice += attractionPrices[i] * booking.numTickets * personsPerTicket[booking.ticketId - 1];
    }

    return ticketsPrice + attractionsPrice;
}

int generateBookingId()
{
    srand(time(NULL));
    return rand() % 10000;
}

char *getTicketName(int ticketId)
{
    switch (ticketId)
    {
    case 1:
        return "Adult";
        break;
    case 2:
        return "Child";
        break;
    case 3:
        return "Senior";
        break;
    case 4:
        return "Family";
        break;
    case 5:
        return "Group";
        break;
    default:
        return "Unknown";
        break;
    }
}

int createBookingFile(struct Booking booking)
{
    char bookingString[150];
    char fileName[20];
    char firstDate[20];
    char secondDate[20];

    // Check if the folder exists
    struct stat st;
    if (stat(BOOKINGS_FOLDER, &st) == -1)
    {
        // Folder doesn't exist, create it
        if (mkdir(BOOKINGS_FOLDER) == 0)
        {
            printf("Folder created successfully.\n");
        }
        else
        {
            perror("Error creating bookings folder!");
            return 1;
        }
    }

    strcpy(firstDate, getDateString(booking.visitDay));
    strcpy(secondDate, getDateString(booking.visitDay + 1));

    sprintf(fileName, "./bookings/%d.txt", booking.id);
    FILE *file = fopen(fileName, "w");

    if (file == NULL)
    {
        printf("\nUnable to create booking file!");
        return 1;
    };

    fprintf(file, "\n\t\tBooking ID: %d\n\t\tCustomer Name: %s\t\tTicket Type: %s\n\t\tNo. of Tickets: %d\n\t\tAttractions:\n\t\t\tLion Feeding: %s\n\t\t\tPenguin Feeding: %s\n\t\t\tEvening Barbecue: %s\n\t\tPrice: $%.2f\n\t\tVisiting Date(s): %s - %s",
            booking.id,
            booking.name,
            getTicketName(booking.ticketId),
            booking.numTickets,
            booking.attractions[0] == 1 ? "yes" : "no",
            booking.attractions[1] == 1 ? "yes" : "no",
            booking.attractions[2] == 1 ? "yes" : "no",
            booking.price,
            firstDate,
            booking.days == 2 ? secondDate : "");

    fclose(file);
}