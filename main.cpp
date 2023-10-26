#include <iostream>
#include <vector>


class Element {
public:
    virtual void print() const = 0;
};

class Table: public Element {
private:
    std::string title;

public:
    Table(const std::string& title) : title(title) {}

    void print() const {
        std::cout << "    Table: " << title << '\n';
    }

};

class Paragraph: public Element {
private:
    std::string text;

public:
    Paragraph(const std::string& text) : text(text) {}

    void print() const {
        std::cout << "    Paragraph: " << text << '\n';
    }

};

class Image: public Element {
private:
    std::string imageName;

public:
    Image(const std::string& imageName) : imageName(imageName) {}

    void print() const {
        std::cout << "    Image: " << imageName << '\n';
    }

};

class SubChapter {
private:
    std::string name;
    std::vector<Element*> elements;

public:
    SubChapter(const std::string& name) : name(name) {}

    ~SubChapter() {
        for (Element* element : elements)
            delete element;
    }

    void createImage(const std::string& imageName) {
        Image* image = new Image(imageName);
        elements.push_back(image);
    }

    void createParagraph(const std::string& text) {
        Paragraph* paragraph = new Paragraph(text);
        elements.push_back(paragraph);
    }

    void createTable(const std::string& title) {
        Table* table = new Table(title);
        elements.push_back(table);
    }

    void print() const {
        std::cout << "  Subchapter: " << name << '\n';
        for (const Element* element : elements)
            if (element)
                element->print();
    }

};

class Chapter {
private:
    std::string name;
    std::vector<SubChapter> subchapters;

public:
    Chapter(const std::string& name) : name(name) {}

    void createSubchapter(const std::string& subchapter_name) {
        SubChapter subchapter(subchapter_name);
        subchapters.push_back(subchapter);
    }

    SubChapter& getSubChapter(const size_t index) {
        return subchapters[index];
    }

    void print() const {
        std::cout << "Chapter: " << name << '\n';
        for (const SubChapter& subchapter : subchapters)
            subchapter.print();
    }

};

class Author {
private:
    std::string name;

public:
    Author(const std::string& name) : name(name) {}

    void print() const {
        std::cout << "Author: " << name << '\n';
    }

};

class TableofContent {
private:
    std::string something;

public:
    void print() {
        std::cout << "Table of Content: " << something << '\n';
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
    Book book("This is the McBook");
    Author author("Author McAuthor");

    book.addAuthor(author);

    book.createChapter("McChapter I");
    book.createChapter("McChapter II");
    book.createChapter("McChapter III");
    book.createChapter("McChapter IV");
    book.createChapter("McChapter V");
    book.createChapter("McChapter VI");
    book.createChapter("McChapter VII");
    book.createChapter("McChapter VIII");

    book.getChapter(0).createSubchapter("SubMcChapter I");
    book.getChapter(0).createSubchapter("SubMcChapter II");
    book.getChapter(0).createSubchapter("SubMcChapter III");

    book.getChapter(0).getSubChapter(0).createImage("McImage I");
    book.getChapter(0).getSubChapter(0).createImage("McImage II");
    book.getChapter(0).getSubChapter(0).createTable("McTable I");
    book.getChapter(0).getSubChapter(0).createTable("McTable II");
    book.getChapter(0).getSubChapter(0).createImage("McImage III");
    book.getChapter(0).getSubChapter(0).createParagraph("McParagraph I");
    book.getChapter(0).getSubChapter(0).createParagraph("McParagraph II");
    book.getChapter(0).getSubChapter(0).createTable("McTable III");

    book.getChapter(1).createSubchapter("SubMcChapter I");
    book.getChapter(1).createSubchapter("SubMcChapter II");
    book.getChapter(1).createSubchapter("SubMcChapter III");


    book.getChapter(2).createSubchapter("SubMcChapter I");
    book.getChapter(2).createSubchapter("SubMcChapter II");
    book.getChapter(2).createSubchapter("SubMcChapter III");


    book.getChapter(4).createSubchapter("SubMcChapter I");
    book.getChapter(4).createSubchapter("SubMcChapter II");
    book.getChapter(4).createSubchapter("SubMcChapter III");

    book.print();

    return 0;
}
