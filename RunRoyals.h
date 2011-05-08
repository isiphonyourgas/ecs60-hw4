// Author: davis

#ifndef RUN_ROYALS_H
  #define	RUN_ROYALS_H
#include <fstream>
using namespace std;

class Person
{
public:
  char ID[30];
  char name[100];
  int birthYear;
  int deathYear;
  char spouseNames[5][100];
  int spouseBirthYears[5];
  int spouseDeathYears[5];
  int marriageYears[5];
  int spouseCount;
  Person():birthYear(0), deathYear(0),spouseCount(0){}
  friend ofstream& operator<< (ofstream &outf, const Person &p);
};  // class Person()


#endif	/* RUN_ROYALS_H */

