// Author: Sean Davis

#include <fstream>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include "RunRoyals.h"
#include "royals.h"
#include "CPUTimer.h"

using namespace std;

struct Question
{
  char type;
  char name[256];
  int birthYear;
  char name2[256];
  int birthYear2;
  char answerName[256];
  int answerBirthYear;
  int answer;
};

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

void readFiles(const char *filename, Person **people, Question **questions,
  int *questionCount, int *numPeople)
{
  char s[1000];
  ifstream inf(filename);
  inf >> *numPeople >> *questionCount;
  inf.ignore(1000, '\n');
  *questions = new Question[*questionCount];

  for(int i = 0; i < *questionCount; i++)
  {
    inf.getline(s, 1000);
    strtok(s, ",");
    (*questions)[i].type = s[0];
    switch(s[0])
    {
      case 'c':
      case 'm':
      case 's':
        (*questions)[i].birthYear = atoi(strtok(NULL, ","));
        strcpy((*questions)[i].name, strtok(NULL, ",") );
        (*questions)[i].answer = atoi(strtok(NULL, ","));
        break;
      case 'd':
        (*questions)[i].birthYear = atoi(strtok(NULL, ","));
        strcpy((*questions)[i].name, strtok(NULL, ",") );
        (*questions)[i].answerBirthYear = atoi(strtok(NULL, ","));
        strcpy((*questions)[i].answerName, strtok(NULL, ",") );
        break;
      case 'a':
        (*questions)[i].birthYear = atoi(strtok(NULL, ","));
        strcpy((*questions)[i].name, strtok(NULL, ",") );
        (*questions)[i].birthYear2 = atoi(strtok(NULL, ","));
        strcpy((*questions)[i].name2, strtok(NULL, ",") );
        (*questions)[i].answerBirthYear = atoi(strtok(NULL, ","));
        strcpy((*questions)[i].answerName, strtok(NULL, ",") );
        break;
    } // switch

  }
  
  *people = new Person[*numPeople];
  ifstream inf2("all.csv");
 
  for(int i = 0; i < *numPeople; i++)
    inf2 >> (*people)[i];
} // readFile

int main(int argc, char** argv)
{
  int numPeople, questionCount, birthYear, answer;
  const char *name;
  Person *people;
  Question *questions;
  CPUTimer ct;

  readFiles(argv[1], &people, &questions, &questionCount, &numPeople);
  ct.reset();
  Royals *royals =  new Royals(people, numPeople);
  delete[] people;


  for(int i = 0; i < questionCount; i++)
  {
    switch(questions[i].type)
    {
      case 'c':
        answer = royals->getChildren(questions[i].name, questions[i].birthYear);
        if(answer != questions[i].answer)
/*          cout << "Question #" << i << " your answer: " << answer 
              << " correct: " << questions[i].answer << endl;*/
        break;
      case 'm':
        answer = royals->getMarriages(questions[i].name, questions[i].birthYear);
        if(answer != questions[i].answer)
/*          cout << "Question #" << i << " your answer: " << answer 
              << " correct: " << questions[i].answer << endl;*/
        break;
      case 's':
        answer = royals->getSiblings(questions[i].name, questions[i].birthYear);
        if(answer != questions[i].answer)
/*          cout << "Question #" << i << " your answer: " << answer 
              << " correct: " << questions[i].answer << endl;*/
        break;
      case 'd':
        royals->getDescendent(questions[i].name, questions[i].birthYear,
              &name, &birthYear);
        if(birthYear != questions[i].answerBirthYear
          || strcmp(name, questions[i].answerName) != 0)
/*          cout << "Question #" << i << " your answer: " << name << ' '
            << birthYear  << " correct: " << questions[i].answerName
            << ' ' << questions[i].answerBirthYear << endl;*/
        break;
      case 'a':
        royals->getAncestor(questions[i].name, questions[i].birthYear,
          questions[i].name2, questions[i].birthYear2,  &name, &birthYear);

        if(birthYear != questions[i].answerBirthYear
          || strcmp(name, questions[i].answerName) != 0)
//          cout << "Question #" << i << " your answer: " << name << ' '
//            << birthYear  << " correct: " << questions[i].answerName
//            << ' ' << questions[i].answerBirthYear << endl;
        break;
    } // switch

  } // for each question

  cout << "CPU Time: " << ct.cur_CPUTime() << endl;
  return 0;
} // main()

