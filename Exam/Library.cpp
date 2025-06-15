#include "Library.h"
#include "ArrayTemplate.h"
#include "DateUtils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
using namespace std;

int getPublicationIndexById(Publication* publications, int count, int id) {
    for (int i = 0; i < count; i++) {
        if (publications[i].id == id) {
            return i;
        }
    }
    return -1;
}

void addPublication(Publication*& publications, int& count) {
    Publication newPub;
    cout << "Enter publication ID: ";
    cin >> newPub.id;
    cin.ignore();

    int typeChoice;
    cout << "Choose publication type: \n1. Book\n2. Magazine\n3. Thesis\n4. Newspaper\n";
    cin >> typeChoice;
    cin.ignore();
    if (typeChoice >= 1 && typeChoice <= 4)
        newPub.type = static_cast<PublicationType>(typeChoice);
    else
        newPub.type = PublicationType::UNKNOWN;

    cout << "Enter title: ";
    getline(cin, newPub.title);
    cout << "Enter author: ";
    getline(cin, newPub.author);

    string tmp;
    cout << "Enter issue date (YYYY-MM-DD): ";
    getline(cin, tmp);
    std::tm buf{};
    if (parseDate(tmp, buf))  newPub.issueDate = tmp;

    cout << "Enter return date (YYYY-MM-DD) (or leave empty): ";
    getline(cin, tmp);
    if (!tmp.empty() && parseDate(tmp, buf))    newPub.returnDate = tmp;

    addItemBack(publications, count, newPub);
    cout << "Publication added.\n";
}

void removePublication(Publication*& publications, int& count) {
    cout << "Enter publication ID to remove: ";
    int id;
    cin >> id;
    cin.ignore();

    int index = getPublicationIndexById(publications, count, id);
    if (index == -1) {
        cout << "Publication with ID " << id << " not found.\n";
        return;
    }

    delItem(publications, count, index);
    cout << "Publication removed successfully.\n";
}

void editPublication(Publication* publications, int count) {
    cout << "Enter publication ID to edit: ";
    int id;
    cin >> id;
    cin.ignore();

    int index = getPublicationIndexById(publications, count, id);
    if (index == -1) {
        cout << "Publication with ID " << id << " not found.\n";
        return;
    }

    Publication& pub = publications[index];
    int choice;
    cout << "Edit:\n1. Title\n2. Author\n3. Issue Date\n4. Return Date\n5. Type\n";
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
    case 1:
        cout << "Enter new title: ";
        getline(cin, pub.title);
        break;
    case 2:
        cout << "Enter new author: ";
        getline(cin, pub.author);
        break;
    case 3:
        cout << "Enter new issue date (YYYY-MM-DD): ";
        getline(cin, pub.issueDate);
        break;
    case 4:
        cout << "Enter new return date (YYYY-MM-DD): ";
        getline(cin, pub.returnDate);
        break;
    case 5: {
        int newType;
        cout << "Choose new publication type: \n1. Book\n2. Magazine\n3. Thesis\n4. Newspaper\n";
        cout << "Enter choice: ";
        cin >> newType;
        cin.ignore();
        switch (newType) {
        case 1: pub.type = PublicationType::BOOK; break;
        case 2: pub.type = PublicationType::MAGAZINE; break;
        case 3: pub.type = PublicationType::THESIS; break;
        case 4: pub.type = PublicationType::NEWSPAPER; break;
        default: pub.type = PublicationType::UNKNOWN; break;
        }
        break;
    }
    default:
        cout << "Invalid option.\n";
        break;
    }
    cout << "Publication updated successfully.\n";
}

void searchPublication(Publication* publications, int count) {
    cout << "Search by:\n1. Title\n2. Author\n3. Type\n";
    cout << "Enter choice: ";
    int choice;
    cin >> choice;
    cin.ignore();

    string keyword;
    if (choice == 1) {
        cout << "Enter title keyword: ";
        getline(cin, keyword);
        for (int i = 0; i < count; i++) {
            if (publications[i].title.find(keyword) != string::npos) {
                cout << publications[i] << endl;
            }
        }
    }
    else if (choice == 2) {
        cout << "Enter author keyword: ";
        getline(cin, keyword);
        for (int i = 0; i < count; i++) {
            if (publications[i].author.find(keyword) != string::npos) {
                cout << publications[i] << endl;
            }
        }
    }
    else if (choice == 3) {
        cout << "Choose type:\n1. Book\n2. Magazine\n3. Thesis\n4. Newspaper\n";
        int typeChoice;
        cin >> typeChoice;
        cin.ignore();
        PublicationType type;
        switch (typeChoice) {
        case 1: type = PublicationType::BOOK; break;
        case 2: type = PublicationType::MAGAZINE; break;
        case 3: type = PublicationType::THESIS; break;
        case 4: type = PublicationType::NEWSPAPER; break;
        default: type = PublicationType::UNKNOWN; break;
        }
        for (int i = 0; i < count; i++) {
            if (publications[i].type == type) {
                cout << publications[i] << endl;
            }
        }
    }
    else {
        cout << "Invalid choice.\n";
    }
}

bool compareByID(Publication a, Publication b) {
    return a.id > b.id;
}

bool compareByTitle(Publication a, Publication b) {
    return a.title > b.title;
}

bool compareByIssueDate(Publication a, Publication b) {
    return a.issueDate > b.issueDate;
}

void sortPublications(Publication* publications, int count) {
    cout << "Sort by:\n1. ID\n2. Title\n3. Issue Date\n";
    cout << "Enter choice: ";
    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        mySort(publications, count, compareByID);
    }
    else if (choice == 2) {
        mySort(publications, count, compareByTitle);
    }
    else if (choice == 3) {
        mySort(publications, count, compareByIssueDate);
    }
    else {
        cout << "Invalid sorting option.\n";
        return;
    }
    cout << "Publications sorted successfully.\n";
}


void displayPublications(Publication* publications, int count) {
    if (count == 0) { cout << "No publications.\n"; return; }
    for (int i = 0;i < count;i++) {
        cout << publications[i] << '\n';
        if (!publications[i].returnDate.empty() &&
            dateInPast(publications[i].returnDate))
            cout << "   !!! OVERDUE !!!\n";
        cout << "-----------------------\n";
    }
    cout << "Press Enter to menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


void savePublicationsToFile(Publication* publications, int count, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error opening file for writing.\n";
        return;
    }
    outFile << count << "\n";
    for (int i = 0; i < count; i++) {
        outFile << publications[i].id << "\n";
        outFile << static_cast<int>(publications[i].type) << "\n";
        outFile << publications[i].title << "\n";
        outFile << publications[i].author << "\n";
        outFile << publications[i].issueDate << "\n";
        outFile << publications[i].returnDate << "\n";
    }
    outFile.close();
    cout << "Publications saved to file successfully.\n";
}

void loadPublicationsFromFile(Publication*& publications, int& count, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error opening file for reading.\n";
        return;
    }
    int newCount;
    inFile >> newCount;
    inFile.ignore();

    if (publications != nullptr) {
        delete[] publications;
    }

    publications = new Publication[newCount];
    count = newCount;
    for (int i = 0; i < count; i++) {
        inFile >> publications[i].id;
        int typeInt;
        inFile >> typeInt;
        publications[i].type = static_cast<PublicationType>(typeInt);
        inFile.ignore();
        getline(inFile, publications[i].title);
        getline(inFile, publications[i].author);
        getline(inFile, publications[i].issueDate);
        getline(inFile, publications[i].returnDate);
    }
    inFile.close();
    cout << "Publications loaded from file successfully.\n";
}