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
    Element* get(const size_t) {}

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
    Element* get(const size_t) {}

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
    Element* get(const size_t) {}

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
    Section(const std::string& title) :title(title) {}

    ~Section() {        
        for (Element* element : children)
            delete element;
    }

    void print() const {
            std::cout << "Section: " << title << '\n';
            
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

    Element* get(const size_t index) {
        return children[index];
    }
}

class Author {
private:
    std::string name;

public:
    Author () {}
    Author(const std::string& name) : name(name) {}

    void print() const {
        std::cout << "Author: " << name << '\n';
    }

};



class Book {
private:
    std::string title;
    Author author;
    TableofContent ToC;
    std::vector<Chapter> chapters;

public:
    Book(const std::string& title) : title(title) {}

    void createChapter(const std::string& chapterName) {
        Chapter chapter(chapterName);
        chapters.push_back(chapter);
    }

    Chapter& getChapter(const size_t index) { 
        return chapters[index];
    }

    void addAuthor(const Author& author) {
        this->author = author;
    }

    void addToC(const TableofContent& ToC) {
        this->ToC = ToC;
    }

    void print() const {
        std::cout << "Book title: " << title << '\n';
        author.print();
        for (const Chapter& chapter : chapters) {
            chapter.print();
        }
    }

};

int main() {



    return 0;
}
