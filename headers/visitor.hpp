#pragma once

#include "elements.hpp"
#include "image.hpp"

class Book;
class Author;
class Section;
class TableOfContent;
class Paragraph;
class ImageProxy;
class ImageReal;
class Table;

class Visitor {
public:
    virtual void visitBook(Book*) = 0;
    virtual void visitAuthor(const Author*) = 0;  
    virtual void visitSection(const Section*) = 0;
    virtual void visitTableOfContent(TableOfContent*) = 0;
    virtual void visitParagraph(const Paragraph*) = 0;
    virtual void visitImgProxy(ImageProxy*) = 0;
    virtual void visitImg(ImageReal*) = 0;
    virtual void visitTable(const Table*) = 0;
};

class BookStatistics: public Visitor {
private:
    std::string title;
    int imgs;
    int tables;
    int paragraphs;
public:
    BookStatistics();
    void printStats() const;
    void visitBook( Book*);
    void visitSection(const Section*);
    void visitTableOfContent(TableOfContent*);
    void visitParagraph(const Paragraph*);
    void visitImgProxy(ImageProxy*);
    void visitImg(ImageReal*);
    void visitTable(const Table*);
    void visitAuthor(const Author*);
};

class BookRender: public Visitor {
private:

public:
    BookRender();
    void visitBook(Book*);
    void visitSection(const Section*);
    void visitTableOfContent(TableOfContent*);
    void visitParagraph(const Paragraph*);
    void visitImgProxy(ImageProxy*);
    void visitImg(ImageReal*);
    void visitTable(const Table*);
    void visitAuthor(const Author*);
};

class ToCupdate: public Visitor {
private:
    size_t page;
    std::string tempToC;
    
public:
    ToCupdate();
    void saveToC(TableOfContent* toc);
    void visitBook(Book*);
    void visitSection(const Section*);
    void visitTableOfContent(TableOfContent*);
    void visitParagraph(const Paragraph*);
    void visitImgProxy(ImageProxy*);
    void visitImg(ImageReal*);
    void visitTable(const Table*);
    void visitAuthor(const Author*);
};
