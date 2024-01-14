#include <chrono>
#include <thread>
#include <iostream>

#include "../headers/elements.hpp"


Table::Table(const std::string& title): title(title) {}
void Table::setTitle(const std::string& title) {
    this->title = title; 
}
std::string Table::getTitle() const {
    return this->title;
}
void Table::accept(Visitor* visitor) {
    visitor->visitTable(this);
}
void Table::addElement(Element*) {}
void Table::removeElement(Element*) {}
Element* Table::getElement(const size_t) const {
    return nullptr;
}


ImageReal::ImageReal(const std::string& url): url(url) {
    loadImage();
}
void ImageReal::setUrl(const std::string& url) {
    this->url = url;
}
std::string ImageReal::getUrl() const {
    return this->url;
}
void ImageReal::loadImage() {
    //simulated load time
    std::this_thread::sleep_for(std::chrono::seconds(2));
}
void ImageReal::display() {
    std::cout << "ImageReal: " << url << '\n';
}
void ImageReal::accept(Visitor* visitor) {
    visitor->visitImg(this);
}
void ImageReal::addElement(Element*) {}
void ImageReal::removeElement(Element*) {}
Element* ImageReal::getElement(const size_t) const {
    return nullptr;
}


ImageProxy::ImageProxy(const std::string& url): url(url), realImage(nullptr) {}
void ImageProxy::setUrl(const std::string& url) {
    this->url = url;
}
std::string ImageProxy::getUrl() const {
    return this->url;
}
void ImageProxy::display() {
    if(realImage == nullptr) {
        realImage = new ImageReal(url);
    }
    realImage->display();
}
void ImageProxy::accept(Visitor* visitor) {
    visitor->visitImgProxy(this);
}
void ImageProxy::addElement(Element*) {}
void ImageProxy::removeElement(Element*) {}
Element* ImageProxy::getElement(const size_t) const {
    return nullptr;
}
   

Paragraph::Paragraph(const std::string& text) : text(text), alignmentStrategy(new AlignLeft()) {}
void Paragraph::setText(const std::string& text) {
    this->text = text;
}
std::string Paragraph::getText() const {
    return this->text;
}
void Paragraph::setAlignmentStrategy(AlignmentStrategy* strategy) {
    this->alignmentStrategy = strategy;
}
void Paragraph::accept(Visitor* visitor){
    visitor->visitParagraph(this);
}
void Paragraph::addElement(Element*) {}
void Paragraph::removeElement(Element*) {}
Element* Paragraph::getElement(const size_t) const {
    return nullptr;
}

TableOfContent::TableOfContent(){ }
void TableOfContent::accept(Visitor* visitor) {
    visitor->visitTableOfContent(this);
}
std::string TableOfContent::getText() {
    return this->text;
}
void TableOfContent::setText(const std::string& text1) {
    text = text1;
}

Section::Section() {}
Section::Section(const std::string& title) :title(title) {}
Section::~Section() {
    for (Element* element : children)
        delete element;
}
void Section::setTitle(const std::string& title) {
    this->title = title;
}
std::string Section::getTitle() const {
    return this->title;
}
void Section::addElement(Element* element) {
    if(element) {
        children.push_back(element);
    }
}
void Section::removeElement(Element* elem_delete) {
    size_t iter = 0;
    for(Element* element : children) {
        if(element == elem_delete) {
            children.erase(children.begin() + iter);
        }
        else {
            iter++;
        }
    }
}
Element* Section::getElement(const size_t index) const {
    return children[index];
}
void Section::accept(Visitor* visitor) {
    visitor->visitSection(this);
    for(Element* element : children) {
        if(element) {
            element->accept(visitor);
        }
    }
}


Book::Book(const std::string& title, const std::vector<Author> authors) : title(title), authors(authors) {
    this->ToC = new TableOfContent();
}
Book::~Book() {
    delete ToC;
}
Book::Book(const std::string& title) : title(title) {
    this->ToC = new TableOfContent();
}
void Book::setTitle(const std::string& title) {
    this->title = title;
}
std::string Book::getTitle() const {
    return title;
}
void Book::addAuthor(const Author& author) {
    authors.push_back(author);
}
std::vector<Author> Book::getAuthors() const{
    return this->authors;
}
void Book::clearAuthors() {
    this->authors.clear();
}
void Book::accept(Visitor* visitor) {
    visitor->visitBook(this);
    Section::accept(visitor);
}
TableOfContent* Book::getToC(){
    return ToC;
}


Author::Author() {}
Author::Author(const std::string& name, const std::string& surname) : name(name), surname(surname) {}
void Author::setFullName(const std::string& name, const std::string& surname) {
    this->name = name;
    this->surname = surname;
}
std::string Author::getName() const {
    return this->name;
}
std::string Author::getSurname() const {
    return this->surname;
}
void Author::accept(Visitor* visitor) const {
    visitor->visitAuthor(this);
}

