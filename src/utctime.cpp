#include <iostream>
#include <ctime>
#include <utctime.h>

/*
UTC Date and Time methods
*/

// Default constructor (J2000)
UTCTime::UTCTime() {
    this->seconds_since_j2000 = 0.0;
}

// Constructor using double
UTCTime::UTCTime(double seconds) {
    this->seconds_since_j2000 = seconds;
}

// Constructor using long
UTCTime::UTCTime(long seconds) {
    this->seconds_since_j2000 = (double)seconds;
}

// Print to std::cout
void UTCTime::print() {
    std::cout << "[UTCTime]\n Seconds since J2000: " << seconds_since_j2000 << std::endl;
    std::cout << " ISO: " << to_iso() << std::endl;
}

// Format date as ISO string
std::string UTCTime::to_iso() {
    time_t t = (long)(seconds_since_j2000 + 946727935.816);
    auto nt = gmtime(&t);
    char buffer[256];
    strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S", nt);
    return std::string {buffer};
}