#include <stdio.h>
#include <assert.h>
#include <stdbool.h>


// Data models/ structs used in this program
typedef enum month{jan, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec} month;
typedef struct date
{
    month m;
    int d;
} date;

// This function is used on calculation of next date to check if we are at the last day of a month, then we need to increment month as well.
int numberOfDays(month m)
{
    switch (m)
    {
    // January, March, May, July, August, October, and December have 31.
    case feb:
        return 28;
    case jan:
    case mar:
    case may:
    case jul:
    case aug:
    case oct:
    case dec:
        return 31;
    default:
        return 30;
    }
}

// The function below does the calcluation, based on the number of days a month has and
// either increments it, or changes the month as well. It returns a new "date"
//since a new struct is returned it is passed by value
date nextDay(date d){
    int current_m = d.m;
    int current_d = d.d;
    month new_month;
    int new_day;
    assert(current_d > 0 && current_d <= numberOfDays(current_m));
    if (d.d < numberOfDays(current_m))
    {
        new_day = d.d + 1;
        new_month = current_m;
    }
    else
    {
        new_day = 1;
        new_month = (current_m + 1) % 12;
    }
    date new_date = {new_month, new_day};
    return new_date;
}

// This function is used for ease of printing rather than printing number
char *monthToString(month m)
{
    switch (m)
    {
    case jan:
        return "January";
    case feb:
        return "February";
    case mar:
        return "March";
    case apr:
        return "April";
    case may:
        return "May";
    case jun:
        return "June";
    case jul:
        return "July";
    case aug:
        return "August";
    case sep:
        return "September";
    case oct:
        return "October";
    case nov:
        return "November";
    case dec:
        return "December";
    default:
        assert(false); // otherwise return unrecognized month
        return "unrecognized month";
    }
}

///// Main fybction calls

int main(){
    // First part
    date d = {jan, 1};
    date nextD = nextDay(d);
    printf("Part A: next day of %s, %d is %s, %d \n\n", monthToString(d.m), d.d, monthToString(nextD.m), nextD.d);
    // Rest of the dates
    printf("Part B: \n");
    //feb 28, mar 14, oct 31, dec 31
    date dates[4] = {{feb, 28}, {mar, 14}, {oct, 31}, {dec, 31}};
    for (int i = 0; i < 4; ++i){
        date nextDate = nextDay(dates[i]);
        printf("next day of %s, %d is %s, %d \n", monthToString(dates[i].m), dates[i].d, monthToString(nextDate.m), nextDate.d);
    }
    printf("\n\n");
    return 0;
}