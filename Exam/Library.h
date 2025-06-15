#ifndef LIBRARY_H
#define LIBRARY_H

#include "Publication.h"
#include <string>
using namespace std;

void addPublication(Publication*& publications, int& count);
void removePublication(Publication*& publications, int& count);
void editPublication(Publication* publications, int count);
void searchPublication(Publication* publications, int count);
void sortPublications(Publication* publications, int count);
void displayPublications(Publication* publications, int count);
void savePublicationsToFile(Publication* publications, int count, const string& filename);
void loadPublicationsFromFile(Publication*& publications, int& count, const string& filename);
int getPublicationIndexById(Publication* publications, int count, int id);

#endif 
