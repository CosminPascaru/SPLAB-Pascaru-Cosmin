#include <iostream>
#include <vector>


class Element {
public:
    virtual void print() const = 0;

    virtual void add(Element*) = 0;
    virtual void remove(Element*) = 0;
    virtual Element* get(const size_t) const = 0;
};

class Table: public Element {
private:
    std::string title;

public:
    Table(const std::string& title) : title(title) {}

    void print() const {
        std::cout << "    Table: " << title << '\n';
    }

    void add(Element*) {}
    void remove(Element*) {}
    Element* get(const size_t) const {}

};

class Image: public Element {
private:
    std::string imageName;

public:
    Image(const std::string& imageName) : imageName(imageName) {}

    void print() const {
        std::cout << "    Image: " << imageName << '\n';
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

    void print() const {
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
    void print() const {
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

    void print() const {
            std::cout << title << '\n';
            
            for (const Element* element : children) {
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

    Element* get(const size_t) {}
};

int main() {

    Book karte = Book("Titlu karte");
    Author autor1 = Author("Cel mai", "autor");
    Author autor2 = Author("!Cel mai", "autor");

    karte.addAuthor(autor1);
    karte.addAuthor(autor2);

    karte.add(new Image("Imagine"));
    karte.add(new Paragraph("teeexxttt"));

    karte.add(new Section("Cea mai sectiune 1"));
    
    karte.get(3)->add(new Section("Cea mai sectiune 1.1"));
    
    karte.get(3)->get(1)->add(new Paragraph("paragraf 1.1"));

    //karte.get(3)->add(new Paragraph("paragraf 1"));

    //karte.get(3)->add(new Paragraph("paragraf 1"));

    

    karte.printBook();
    karte.print();
    return 0;
}
