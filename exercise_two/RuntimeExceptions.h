#ifndef RUNTIMEEXCEPTIONS_H
#define RUNTIMEEXCEPTIONS_H
// Modified for CSCI 220 Fall 13
// Updated Fall 21

//Modified by: Jesus Rodriguez-Luna 10/27/2023

#include <exception>

using namespace std;

class RuntimeException : public std::exception {
private:
    string errorMessage;

public:
    RuntimeException(const char* err) : errorMessage(err) {}

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }
};

class NonexistentElement : public RuntimeException
{
public:
	NonexistentElement(const char *err) : RuntimeException(err) {}
};

class BoundaryViolation : public RuntimeException 
{
public:
	BoundaryViolation(const char *err) : RuntimeException(err) {}
};
#endif