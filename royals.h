// Author: Sean Davis

#ifndef ROYALS_H
#define	ROYALS_H
#include "RunRoyals.h"
#include "QuadraticProbing.h"

class Thing {
public:
  Thing();
  void Load(const char *n, int birthY, int spouse, char* i);
  
  Thing *parent, **youngest;
  char *name;
  int birth;
  int spouseCount;
  char* id;
};

class Data {
public:
  Data();
  void insert(Person people);
  
  Thing data[76980];
};


class Royals {
public:
  Royals(const Person *people, int count);
  void getAncestor(const char *descendentName1, int descendentBirthYear1,
    const char *descendentName2, int descendentBirthYear2,
    const char **ancestorName, int *ancestorBirthYear);
  int getChildren(const char*name, int birthYear);
  void getDescendent(const char *ancestorName, int ancestorBirthYear,
    const char **descendentName, int *descendentBirthYear);
  int getMarriages(const char*name, int birthYear);
  int getSiblings(const char*name, int birthYear);

  Data data;
  
  
};

#endif	/* ROYALS_H */

