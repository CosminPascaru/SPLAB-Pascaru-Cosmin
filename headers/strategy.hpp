#pragma once

#include <string>

class AlignmentStrategy {
public:
    virtual void display(std::string&) = 0;
    virtual void align(std::string&) = 0;
};

class AlignLeft: public AlignmentStrategy {
public:
    void display(std::string&) override;
    void align(std::string&) override;
};

class AlignRight: public AlignmentStrategy {
public:
    void display(std::string&) override;
    void align(std::string&) override;
};