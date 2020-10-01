#ifndef UTCTIME_H
#define UTCTIME_H

#ifndef string
#include <string>
#endif

// UTC Date and Time
class UTCTime {
    public:
        double seconds_since_j2000;

    // Default constructor (J2000)
    UTCTime();

    // Constructor using double
    UTCTime(double seconds);

    // Constructor using long
    UTCTime(long seconds);

    // Print to std::cout
    void print();

    // Format date using strftime parameters
    std::string to_iso();
};

#endif