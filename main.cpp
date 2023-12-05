#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

std::chrono::seconds timeout(5);

struct ImageDimensions {
    unsigned int width;
    unsigned int height;
};

struct ImageContent {
    std::string nothing;
};

class Element {
public:
    virtual void print() = 0;

    virtual void add(Element*) = 0;
    virtual void remove(Element*) = 0;
    virtual Element* get(const size_t) const = 0;
};

class Table: public Element {
private:
    std::string title;

public:
    Table(const std::string& title) : title(title) {}

    void print() {
        std::cout << "    Table: " << title << '\n';
    }

    void add(Element*) {}
    void remove(Element*) {}
    Element* get(const size_t) const {}
};

class Image {
public:
    virtual void display() = 0;
};

class ImageReal: public Element, Image{
private:
    std::string url;
    ImageContent content;

    void loadImage() {
        //simulated load time
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    void display() override {
        std::cout << "    ImageReal: " << url << '\n';
    }

public:
    ImageReal(const std::string& url) : url(url) {
        loadImage();
    }

    void print() {
        display();
    }

    void add(Element*) {}
    void remove(Element*) {}
    Element* get(const size_t) const {}
};

class ImageProxy: public Element, Image {
private:
    std::string url;
    ImageDimensions dimensions;
    ImageReal* realImage;

    void display() override {
        if (realImage == nullptr) {
            realImage = new ImageReal(url);
        }
        realImage->print();
    }

public:
    ImageProxy(const std::string& url) : url(url), realImage(nullptr){}

    void print() {
        display();
    }

    void add(Element*) {}
    void remove(Element*) {}
    Element* get(const size_t) const {}
    
};

class Paragraph: public Element {
private:
    std::string text;

public:
    Paragraph(const std::string& text) : text(text) {}

    void print() {
        std::cout << "    Paragraph: " << text << '\n';
    }

    void add(Element*) {}
    void remove(Element*) {}
    Element* get(const size_t) const {}

};

class TableofContent: public Element {
private:
    std::string something;

public:
    void print() {
        std::cout << "Table of Content: " << something << '\n';
    }

    void add(Element*) {}
    void remove(Element*) {}
    Element* get(const size_t) {}

};

class Section: public Element {
private:
    std::string title;
    std::vector<Element*> children;

public:
    Section() {}
    Section(const std::string& title) :title(title) {}

    ~Section() {        
        for (Element* element : children)
            delete element;
    }

    void print() {
            std::cout << title << '\n';
            
            for (Element* element : children) {
                if(element){
                    element->print();
                }
            }
        }

    void add(Element* element){
        if(element){
            children.push_back(element);
        }
    }

    void remove(Element* elem_delete){
        size_t iter = 0; 
        for (Element* element : children) {
            if(element == elem_delete){
                    children.erase(children.begin() + iter);
            }
            else{
                iter++;
            }
        }
    }

    Element* get(const size_t index) const {
        return children[index];
    }
};

class Author {
private:
    std::string name;
    std::string surname;

public:
    Author () {}
    Author(const std::string& name, const std::string& surname) : name(name), surname(surname) {}

    void print() const {
        std::cout << "Author: " << name << ' ' << surname << '\n';
    }

};

class Book: public Section {
private:
    std::string title;
    std::vector<Author> authors;

public:
    Book(const std::string& title, const std::vector<Author> authors) : title(title), authors(authors) {} 
    Book(const std::string& title) : title(title) {}

    void printBook() const {
        std::cout << "Book title: " << title << '\n';
        for (const Author& author : authors) {
            author.print();
        }
    }

    void addAuthor(const Author& author) {
        authors.push_back(author);
    }
};

int main() {

    Book karte = Book("Titlu karte");
    Author autor1 = Author("Cel mai", "autor");

    karte.addAuthor(autor1);
    
    karte.add(new Section("Cea mai sectiune 1"));
    karte.add(new Section("Cea mai sectiune 2"));

    karte.get(0)->add(new ImageProxy("Imagine1 sec1"));

    karte.get(1)->add(new ImageProxy("Imagine1 sec2"));
    karte.get(1)->add(new ImageProxy("Imagine2 sec2"));

    karte.get(0)->print();
    return 0;
}
