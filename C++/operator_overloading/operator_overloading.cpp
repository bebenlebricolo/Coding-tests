#include <iostream>
#include <chrono>
#include <ctime>


class date
{
public:
    date();
    date(unsigned int s,
         unsigned int mi,
         unsigned int h,
         unsigned int d,
         unsigned int mo,
         unsigned int y );
    void set_date(unsigned int s,
                  unsigned int mi,
                  unsigned int h,
                  unsigned int d,
                  unsigned int mo,
                  unsigned int y
                  );
    bool operator==(const date& other);
private:
    unsigned int seconds;
    unsigned int minutes;
    unsigned int hours;
    unsigned int day;
    unsigned int month;
    unsigned int year;
};

date::date() : seconds(0),
               minutes(0),
               hours(0),
               day(0),
               month(0),
               year(0)
{}

date::date(unsigned int s,
           unsigned int mi,
           unsigned int h,
           unsigned int d,
           unsigned int mo,
           unsigned int y ) : seconds(s),
                              minutes(mi),
                              hours(h),
                              day(d),
                              month(mo),
                              year(y) {}

void date::set_date(unsigned int s,
                    unsigned int mi,
                    unsigned int h,
                    unsigned int d,
                    unsigned int mo,
                    unsigned int y )
{
    seconds = s;
    minutes = mi;
    hours = h;
    day = d;
    month = mo;
    year = y;
};

bool date::operator==(const date& other)

{
    return ((seconds == other.seconds)  &&
            (minutes == other.minutes)  &&
            (hours   == other.hours)    &&
            (day     == other.day)      &&
            (month   == other.month)    &&
            (year    == other.year));
}

int main(const int argc, const char * const * const argv)
{
    date d1(0U,1U,2U,3U,4U,5U);
    date d2(0U,1U,2U,3U,4U,5U);

    if (d1 == d2)
    {
        std::cout << "both dates are identical!\n";
    }
    else
    {
        std::cout << "dates are different\n";
    }


    return 0;
}