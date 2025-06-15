#include <iostream>  
#include "Library.h"  
#include "Publication.h"  
#include "ArrayTemplate.h"  
#include <limits>  
using namespace std;  

int main() {  
   Publication* publications = nullptr;  
   int count = 0;  
   const string filename = "publications.txt";  
   int choice = 0;   

   {  
       Publication sampleData[10] = {  
           Publication{101, PublicationType::BOOK, "1984", "George Orwell", "2025-04-01", ""},  
           Publication{102, PublicationType::BOOK, "To Kill a Mockingbird", "Harper Lee", "2025-04-02", ""},  
           Publication{103, PublicationType::NEWSPAPER, "The New York Times", "Various", "2025-04-03", "2025-04-04"},  
           Publication{104, PublicationType::NEWSPAPER, "The Guardian", "Various", "2025-04-04", "2025-04-05"},  
           Publication{105, PublicationType::ADVERTISEMENT, "Super Sale", "MegaStore", "2025-04-05", ""},  
           Publication{106, PublicationType::BOOK, "Brave New World", "Aldous Huxley", "2025-04-06", ""},  
           Publication{107, PublicationType::NEWSPAPER, "Daily News", "Various", "2025-04-07", "2025-04-08"},  
           Publication{108, PublicationType::ADVERTISEMENT, "Limited Offer", "ShopNow", "2025-04-08", ""},  
           Publication{109, PublicationType::BOOK, "The Catcher in the Rye", "J.D. Salinger", "2025-04-09", ""},  
           Publication{110, PublicationType::NEWSPAPER, "Financial Times", "Various", "2025-04-10", "2025-04-11"}  
       };  

       publications = new Publication[10];  
       for (int i = 0; i < 10; i++) {  
           publications[i] = sampleData[i];  
       }  
       count = 10;  
   }  

   do {  
       cout << "======== Library Menu ========\n";  
       cout << "1. Display Publications\n";  
       cout << "2. Add Publication\n";  
       cout << "3. Remove Publication\n";  
       cout << "4. Edit Publication\n";  
       cout << "5. Search Publication\n";  
       cout << "6. Sort Publications\n";  
       cout << "7. Save Publications to File\n";  
       cout << "8. Load Publications from File\n";  
       cout << "9. Exit\n";  
       cout << "Enter your choice: ";  
       if (!(cin >> choice)) {  
           cin.clear();  
           cin.ignore(numeric_limits<streamsize>::max(), '\n');  
           choice = -1;   
       }  
       else {  
           cin.ignore(numeric_limits<streamsize>::max(), '\n');  
       }  

       switch (choice) {  
       case 1:  
           displayPublications(publications, count);  
           break;  
       case 2:  
           addPublication(publications, count);  
           break;  
       case 3:  
           removePublication(publications, count);  
           break;  
       case 4:  
           editPublication(publications, count);  
           break;  
       case 5:  
           searchPublication(publications, count);  
           break;  
       case 6:  
           sortPublications(publications, count);  
           break;  
       case 7:  
           savePublicationsToFile(publications, count, filename);  
           break;  
       case 8:  
           loadPublicationsFromFile(publications, count, filename);  
           break;  
       case 9:  
           cout << "Exiting program...\n";  
           break;  
       default:  
           cout << "Invalid option. Please try again.\n";  
       }  
       cout << "\n";  
   } while (choice != 9);  

   delete[] publications;  
   return 0;  
}
