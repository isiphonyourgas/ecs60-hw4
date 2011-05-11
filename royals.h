// Author: Sean Davis

#ifndef ROYALS_H
#define	ROYALS_H
#include "RunRoyals.h"
#include "QuadraticProbing.h"

class Thing {
public:
  Thing();
  Thing* Load(const Person p, Thing *ptr, char flag, int level);
  Thing* update(Person p, Thing *ptr, char flag, int level, Person previous);
 // Thing* update(const Person p, Thing *ptr, char flag, int level);
  
  Thing **parent, *youngest;
  int parentC;
  char *name;
  char **spouseName;
  int *spouseYear;
  int birth;
  int spouseCount;
  int idCount;
  char *id[100];
  bool check;
  int child;
  int royalSpouse;
};
/*
class Data {
public:
  Data();
  void insert(Person people);
  
  Thing data[76980];
};*/


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
  void printChild();

  Thing *data[76980];
  bool check[76980];
  Thing top[16];
  
  
};

#endif	/* ROYALS_H */

