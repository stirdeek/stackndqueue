#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>
#include <string>

class ContainerException : public std::runtime_error {
public:
    explicit ContainerException(const std::string& message)
        : std::runtime_error(message) {}

    explicit ContainerException(const char* message)
        : std::runtime_error(message) {}
};

#endif // EXCEPTION_H
