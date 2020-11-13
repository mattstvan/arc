#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>
#include <string>

/*
Arc exception type
*/
class ArcException: virtual public std::exception {
protected:
    std::string message;
public:
    // Default constructor
    ArcException() {
        this->message = "Arc encountered an unknown exception";
    }

    /* Direct constructor
    @param msg The error message
    */
    ArcException(std::string msg) {
        this->message = msg;
    };

    virtual ~ArcException() throw() {};

    virtual const char* what() const throw () {
       return message.c_str();
    }
};

#endif