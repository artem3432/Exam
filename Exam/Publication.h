#ifndef PUBLICATION_H
#define PUBLICATION_H

#include <string>
#include <iostream>
using namespace std;

enum class PublicationType {
    BOOK,
    MAGAZINE,
    THESIS,
    NEWSPAPER,
    ADVERTISEMENT,   
    UNKNOWN
};

inline string publicationTypeToString(PublicationType type) {
    switch (type) {
    case PublicationType::BOOK: return "Book";
    case PublicationType::MAGAZINE: return "Magazine";
    case PublicationType::THESIS: return "Thesis";
    case PublicationType::NEWSPAPER: return "Newspaper";
    case PublicationType::ADVERTISEMENT: return "Advertisement";
    default: return "Unknown";
    }
}

struct Publication {
    int id;
    PublicationType type;
    std::string title;
    std::string author;
    std::string issueDate;
    std::string returnDate;

    Publication() : id(0), type(PublicationType::UNKNOWN),
        title(""), author(""), issueDate(""), returnDate("") {
    }

    Publication(int id, PublicationType type, const std::string& title, const std::string& author,
        const std::string& issueDate, const std::string& returnDate)
        : id(id), type(type), title(title), author(author), issueDate(issueDate), returnDate(returnDate) {
    }
};


inline ostream& operator<<(ostream& os, const Publication& pub) {
    os << "ID: " << pub.id << "\n";
    os << "Type: " << publicationTypeToString(pub.type) << "\n";
    os << "Title: " << pub.title << "\n";
    os << "Author: " << pub.author << "\n";
    os << "Issue Date: " << pub.issueDate << "\n";
    os << "Return Date: " << pub.returnDate << "\n";
    return os;
}

#endif 
