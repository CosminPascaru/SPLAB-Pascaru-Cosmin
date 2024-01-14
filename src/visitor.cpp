#include <iostream>
#include <vector>
#include <string>

#include "../headers/visitor.hpp"
#include "../headers/elements.hpp"

BookStatistics::BookStatistics(): title("?"), imgs(0), tables(0), paragraphs(0){}
void BookStatistics::printStats() const {
    std::cout << "  Book stats:\n" << "Title: " << title << "\n>Images: " << imgs << "\n>Tables: " << tables << "\n>Paragraphs: " << paragraphs << "\n\n";
}
void BookStatistics::visitBook(Book* book){
    title = book->getTitle();
}
void BookStatistics::visitParagraph(const Paragraph* paragraph) {
    paragraphs++;
}
void BookStatistics::visitImgProxy(ImageProxy* img) {
    imgs++;
}
void BookStatistics::visitTable(const Table* table) {
    tables++;
}
void BookStatistics::visitAuthor(const Author* author) {}
void BookStatistics::visitImg(ImageReal* img) {}
void BookStatistics::visitSection(const Section* section) {}
void BookStatistics::visitTableOfContent(TableOfContent* toc) {}


BookRender::BookRender() {}
void BookRender::visitBook(Book* book) {
    std::cout <<  book->getTitle() << '\n';
    for(const Author author: book->getAuthors()) {
        visitAuthor(&author);
    }
    visitTableOfContent(book->getToC());
}
void BookRender::visitSection(const Section* section) {
    std::cout << section->getTitle() << '\n';
}
void BookRender::visitTableOfContent(TableOfContent* toc) {
    if(toc != nullptr) {
        std::cout << toc->getText() << '\n';
    }
}
void BookRender::visitParagraph(const Paragraph* paragraph) {
    std::cout << paragraph->getText() << '\n';
}
void BookRender::visitImgProxy(ImageProxy* img) {
    img->display();
}
void BookRender::visitImg(ImageReal* img) {
    img->display();
}
void BookRender::visitTable(const Table* table) {
    std::cout << table->getTitle() << '\n';
}
void BookRender::visitAuthor(const Author* author) {
    std::cout << author->getName() << ' ' << author->getSurname() << '\n';
}


ToCupdate::ToCupdate() :  page(1), tempToC("\nTable Of Content\n") {}
void ToCupdate::saveToC(TableOfContent* toc) {
    if(toc != nullptr) {
        toc->setText(this->tempToC);
    }
}
void ToCupdate::visitBook(Book* book) {
}
void ToCupdate::visitSection(const Section* section) {

    std::string tempTitle = section->getTitle();
    if(tempTitle != ""){
        this->tempToC += tempTitle + " ";
        size_t dots = 0;
        if(this->page < 10) {
            dots = 25 - tempTitle.length();
        }
        else {
            dots = 24 - tempTitle.length();
        }
        for(size_t i=0; i<=dots; i++){
            this->tempToC += '.';
        }
        this->tempToC += " " +  std::to_string(this->page) + '\n';
    }
}
void ToCupdate::visitTableOfContent(TableOfContent* toc) {
    
}
void ToCupdate::visitParagraph(const Paragraph* paragraph) {
    this->page++;
}
void ToCupdate::visitImgProxy(ImageProxy* img) {
    this->page++;   
}
void ToCupdate::visitImg(ImageReal* img) { }
void ToCupdate::visitTable(const Table* table) {
    this->page++;
}
void ToCupdate::visitAuthor(const Author* author) {
    
}
