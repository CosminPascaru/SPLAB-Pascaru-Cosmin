#pragma once

struct ImageDimensions {
    unsigned int width;
    unsigned int height;
};

struct ImageContent {
    std::string nothing;
};

class Image {
public:
    virtual void display() = 0;
};