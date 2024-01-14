#include <iostream>

#include "../headers/strategy.hpp"

void AlignLeft::display(std::string& text) {
    //align(text); 
    std::cout << "    Aligned to the left: " << text << '\n';
}
void AlignLeft::align(std::string& text) {
    //some method to align the text :)
}

void AlignRight::display(std::string& text) {
    //align(text);   
    std::cout << "    Aligned to the right: " << text << '\n';
}
void AlignRight::align(std::string& text) {
    //some method to align the text :)
}
