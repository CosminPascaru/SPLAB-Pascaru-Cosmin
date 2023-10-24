#include <iostream>
#include <vector>

class SubChapter {
private:
    std::string name;
public:
    SubChapter(const std::string& name) : name(name) {}

    std::string print() const {
        return name;
    }
};

class Chapter {
private:
    std::string name;
    std::vector<SubChapter> sub_chapters;

public:
    Chapter(const std::string& name) : name(name) {}

    std::string print() const {
        return name;
    }
};

class Book {
private:
    std::string title;
    std::vector<Chapter> chapters;

public:
    Book(const std::string& title) : title(title) {}

    void addChapter(const std::string& chapterName) {
        Chapter chapter(chapterName);
        chapters.push_back(chapter);
    }

    void printChapters() const {
        std::cout << "Chapters in the book '" << title << "':" << std::endl;
        for (const Chapter& chapter : chapters) {
            std::cout << " - " << chapter.print() << std::endl;
        }
    }
};

int main() {
    Book myBook("Sample Book");
    myBook.addChapter("Chapter 1");
    myBook.addChapter("Chapter 2");
    myBook.addChapter("Chapter 3");

    myBook.printChapters();

    return 0;
}
