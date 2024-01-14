#pragma once

#include <string>
#include <vector>

#include "image.hpp"
#include "strategy.hpp"
#include "visitor.hpp"

class Visitor;

class Element {
public:
    virtual void accept(Visitor*) = 0;
    virtual void addElement(Element*) = 0;
    virtual void removeElement(Element*) = 0;
    virtual Element* getElement(const size_t) const = 0;
};

class Table: public Element {
private:
    std::string title;

public:
    Table(const std::string&);
    void setTitle(const std::string&);
    std::string getTitle() const;
    void accept(Visitor*);

    void addElement(Element*);
    void removeElement(Element*);
    Element* getElement(const size_t) const;
};

class ImageReal: public Element, Image{
private:
    std::string url;
    ImageContent content;
    void loadImage();

public:
    ImageReal(const std::string&);
    void setUrl(const std::string&);
    std::string getUrl() const;
    void display() override;
    void accept(Visitor*);

    void addElement(Element*);
    void removeElement(Element*);
    Element* getElement(const size_t) const;
};

class ImageProxy: public Element, Image {
private:
    std::string url;
    ImageDimensions dimensions;
    ImageReal* realImage;

public:
    ImageProxy(const std::string&);
    void setUrl(const std::string&);
    std::string getUrl() const;
    void accept(Visitor*);
    void display() override;
    void addElement(Element*);
    void removeElement(Element*);
    Element* getElement(const size_t) const;
};

class Paragraph: public Element {
private:
    std::string text;
    AlignmentStrategy* alignmentStrategy;

public:
    Paragraph(const std::string&);
    void setText(const std::string&);
    std::string getText() const;
    void setAlignmentStrategy(AlignmentStrategy*);
    void accept(Visitor*);

    void addElement(Element*);
    void removeElement(Element*);
    Element* getElement(const size_t) const;
};

class TableOfContent {
private:
    std::string text;

public:
    TableOfContent();
    std::string getText();
    void setText(const std::string& text);
    void accept(Visitor*);
};

class Section: public Element {
private:
    std::string title;
    std::vector<Element*> children;
 
public:
    Section();
    Section(const std::string&);
    ~Section();
    void setTitle(const std::string&);
    std::string getTitle() const;
    void accept(Visitor*);
    void addElement(Element*);
    void removeElement(Element*);
    Element* getElement(const size_t) const;
};

class Author {
private:
    std::string name;
    std::string surname;

public:
    Author();
    Author(const std::string&, const std::string&);
    void setFullName(const std::string&, const std::string&);
    std::string getName() const;
    std::string getSurname() const;
    void accept(Visitor*) const;
};

class Book: public Section {
private:
    std::string title;
    std::vector<Author> authors;
    TableOfContent* ToC;

public:
    Book(const std::string&, const std::vector<Author>);
    Book(const std::string&);
    ~Book();
    void setTitle(const std::string&);
    std::string getTitle() const;
    void addAuthor(const Author&);
    std::vector<Author> getAuthors() const;
    void clearAuthors();
    TableOfContent* getToC();
    void accept(Visitor*) override;
};

