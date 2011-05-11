/* 
 * File:   CreateFile.cpp
 * Author: davis
 *
 * Created on April 28, 2011, 8:32 PM
 */

#include <cstdlib>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cctype>
#include "people.h"
#include "royals.h"

using namespace std;



ifstream& operator>> (ifstream &inf, Person &p)
{
  char line[1000];

  inf.getline(line, 1000);
  if(strlen(line) < 10)
    return inf;
  strcpy(p.ID, strtok(line, ","));
  strcpy(p.name, strtok(NULL, ","));
  p.birthYear = atoi(strtok(NULL, ","));
  p.deathYear = atoi(strtok(NULL, ","));
  p.spouseCount = atoi(strtok(NULL, ","));

  for(int i = 0; i < p.spouseCount; i++)
  {
    strcpy(p.spouseNames[i], strtok(NULL, ","));
    p.spouseBirthYears[i] = atoi(strtok(NULL, ","));
    p.spouseDeathYears[i] = atoi(strtok(NULL, ","));
    p.marriageYears[i] = atoi(strtok(NULL, ","));
  } // for i

  return inf;
} // operator<<

int readFile(Person *people, int numPeople)
{
  ifstream inf("all.csv");
  int i = 0;
  while(inf >> people[i] && i < numPeople)
    i++;
  
  return i;
} // readFile

int main(int argc, char** argv)
{
  int count, numPeople, questions, seed, num, num2, answer, birthYear;
  char filename[80];
  const char *name;
  Person person;
  Person *people = new Person[7700];
  cout << "Number of people (10 - 7681): ";
  cin >> numPeople;
  cout << "Number of questions (1 - 100000): ";
  cin >> questions;
  cout << "Seed: ";
  cin >> seed;
  srand(seed);
  count = readFile(people, numPeople);
  Royals *royals =  new Royals(people, count);
  sprintf(filename, "trees-%d-%d-%d.txt", count, questions, seed);
  ofstream outf(filename);
  outf << count << ' ' << questions << endl;

  for(int i = 0; i < questions; i++)
  {
    switch(rand() % 10)
    {
      case 0:
        num = rand() % count;
        answer = royals->getChildren(people[num].name, people[num].birthYear);
        outf << 'c' << ',' << people[num].birthYear << ',' << people[num].name
          << ',' << answer << endl;
        break;
      case 1:
        num = rand() % count;
        answer = royals->getMarriages(people[num].name, people[num].birthYear);
        outf << 'm' << ',' << people[num].birthYear << ',' << people[num].name
           << ',' << answer << endl;
        break;
      case 2:
        num = rand() % count;
        answer = royals->getSiblings(people[num].name, people[num].birthYear);
        outf << 's' << ',' << people[num].birthYear << ',' << people[num].name
          << ',' << answer << endl;
        break;
      case 3:
      case 4:
      case 5:
        do
        {
          num = rand() % count;
          royals->getDescendent(people[num].name, people[num].birthYear,
              &name, &birthYear);
        } while(name == NULL);

        outf << 'd' << ',' <<  people[num].birthYear << ',' << people[num].name
           << ',' << birthYear << ',' << name << endl;
        break;
      default:

        do
        {
          num = rand() % count;
          num2 = rand() % count;
          royals->getAncestor(people[num].name, people[num].birthYear,
            people[num2].name, people[num2].birthYear,  &name, &birthYear);
        } while(name == NULL);
        
        outf << 'a' << ','<< people[num].birthYear << ',' << people[num].name
          << ',' << people[num2].birthYear << ',' << people[num2].name
          << ',' << birthYear << ',' << name << endl;
        break;
    } // switch

  } // for each question

  outf.close();

  return 0;
} // main()

