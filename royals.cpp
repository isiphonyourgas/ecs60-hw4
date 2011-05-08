// Author: Sean Davis

#include "royals.h"
#include "RunRoyals.h"
#include <iostream>
#include <cstring>

inline int Hash(char *p)
{
  unsigned int val, i, len;
  len = strlen(p);
//  len = len / 2;
  val = 51390356;
  for(i = 0; i < len; i++)
  {
    val = (val ^ p[i]);
    val = val * 16777643;
  }
  val = val % 76980;

  return val;
}

Thing::Thing() {}

void Thing::Load(const char *n, int birthY, int spouse, char *i)
{
  strcpy(name, n);
  birthY = birth;
  spouseCount = spouse;
  strcpy(id, i);
}

Data::Data() {}

void Data::insert(Person people)
{
  int i = 0;
  cout << Hash(people.name) << endl;
  
}

Royals::Royals(const Person *people, int count)
{
  int i;
  for(i = 0; i < count; i++)
    data.insert(people[i]);
  
    
}  // Royals()


void Royals::getAncestor(const char *descendentName1, int descendentBirthYear1,
    const char *descendentName2, int descendentBirthYear2,
    const char **ancestorName, int *ancestorBirthYear)
{
} // getAncestor()


int Royals::getChildren(const char *name, int birthYear)
{
  return 0;
} // getSiblings()


void Royals::getDescendent(const char *ancestorName, int ancestorBirthYear,
    const char **descendentName, int *descendentBirthYear)
{
} //getDescedent()


int Royals::getMarriages(const char *name, int birthYear)
{
  return 0;
} // getSiblings()


int Royals::getSiblings(const char *name, int birthYear)
{
  return 0;
} // getSiblings()
