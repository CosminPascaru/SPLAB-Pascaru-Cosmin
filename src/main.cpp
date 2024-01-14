#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "../headers/elements.hpp"

int main() {
    BookRender* render = new BookRender();
    ToCupdate* ToC = new ToCupdate();
    BookStatistics* stats = new BookStatistics();

    Book book = Book("Da Book");
    Author author1 = Author("Author", "McAuthor");
    Author author2 = Author("Author", "McAutherino");

    book.addAuthor(author1);
    book.addAuthor(author2);

    Section* section1 = new Section("Cea mai sectiune 1");
    book.addElement(section1);

    section1->addElement(new Paragraph("texttext"));
    section1->addElement(new Paragraph("texttexttext"));
    section1->addElement(new Table("tabel"));

    Section* section2 = new Section("Sectiune 2");
    book.addElement(section2);

    section2->addElement(new ImageProxy("img"));

    book.accept(ToC);
    ToC->saveToC(book.getToC());

    book.accept(stats);
    stats->printStats();

    book.accept(render);
    
    return 0;
}
