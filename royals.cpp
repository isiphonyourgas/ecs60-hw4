// Author: Sean Davis

#include "royals.h"
#include "RunRoyals.h"
#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
#include <cstdlib>

inline int Hash(const char *p)
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
}//Just a Hash function I found online

inline int Hash2(int year, unsigned int val)
{
  val = ((val + (year - 1597) ) + 1) % 76980;
  return val;
}//Secondary Hash Function

Thing::Thing()
{
  check = false;
  spouseCount = 0;
  birth = 0;
  parent = new Thing*[2];
  parent[0] = NULL;
  parent[1] = NULL;
  child = 0;
  idCount = 0;
  name = new char[85];
}//Constrcutor

Thing* Thing::Load(const Person p, Thing *ptr, char flag, int level)
{
if(0 == strcmp(p.name,"Alfonso Sanz y Martnez de Arrizala"))
  cout << "error\n";

  parentC = 0;
//cout << p.ID << endl;
  switch(flag)
  {
    case '0':			//Ancestor
      for(int i = 0; i < level; i++)
        ptr = ptr->parent[ptr->parentC];	//Used algorithm to determine pos
      parent[0] = ptr;
      if(parent[0] != NULL)//Not root Node
      {
        (parent[0]->child)++;	//If its not the root node, we need to add a child to parent
      }
//cout << "uncle\n";
      break;
    case '1':			//Sibling
      ptr = ptr->parent[ptr->parentC]; //Must go up 1 level to reach parent
      parent[0] = ptr;
      (parent[0]->child)++;
      break;
    case '2':		//Current pointer already points to parent of child
      parent[0] = ptr;
      (parent[0]->child)++;
//cout << "Child\n";
      break;//It is a child
    case 'a':
      break;
  }

  //These copy the information we need from the given array
  strcpy(name, p.name);
  birth = p.birthYear;
  spouseCount = p.spouseCount;
  id[idCount] = new char[30];
  strcpy(id[idCount], p.ID);
  idCount++;
  check = true;
  child = 0;
  royalSpouse = 0;

  youngest = this;
  Thing *temp;
  temp = parent[0];
/*  if(temp != NULL)
  {
    while(((temp->youngest)->birth < p.birthYear) && (temp->parent != NULL))
    {
      temp->youngest = this;
      temp = temp->parent[0];
    }
  }
*/

Thing *thisthing;
thisthing = this;

while(thisthing != NULL)
{
  cout << thisthing->id[idCount - 1] << " --> ";
  thisthing = thisthing->parent[thisthing->parentC];
}

cout << endl;

  return this;
}

Thing* Thing::update(Person p, Thing *ptr, char flag, int level, Person previous)
{
  id[idCount] = new char[30];
  strcpy(id[idCount], p.ID);
  idCount++;

  switch(flag)
  {
    case '0'://ancestor
cout << "ANCESTOR SHIT\n";
      break;
    case '1'://sibling
cout << "SIBLING SHIT\n";
      break;
    case '2'://child
    if(parentC == 0)
    {
      if((strcmp(parent[0]->name, ptr->name) == 0) && ((parent[0])->birth == ptr->birth))
      {
        
      } else {
        parent[1] = ptr;
        parentC++;
      }
    }
    break;
  }


  return this;
}


Royals::Royals(const Person *people, int count)
{
  int i, j, level = 0;
  int k, prevlvl, m;
  Thing *temp = NULL;
  char flag;
  char id1, id2;
  int back = 0;
  stringstream ss1, ss2;


  for(i = 0; i < count; i++) 	//Marks used tableslots
    check[i] = false;

  i = Hash(people[0].name);	//Hash function
  data[i] = new Thing;		//Initializes first thing
  temp = data[i]->Load(people[0], temp, 'a', back);
  check[i] = true;
  level++;

  for(j = 1; j < count; j++)	//Loads the rest of the people
  {
if((strcmp(people[j].name, "Juan") == 0) && (people[j].birthYear == 1913))
  cout <<" Here\n";

 
    flag = 'a';		//Flag to determine what to load as
    i = Hash(people[j].name);
    ss1.str(people[j].ID);
    ss2.str(people[j - 1].ID);
    prevlvl = level;
    k = 0;
    m = 0;
    while(ss1.good() == true)
    {
      id1 = ss1.get();
      id2 = ss2.get();
      if(id1 == '.')
      {
        k++;
      } else {
        if(id2 == id1)
        {
          m++;
          if(ss1.peek() != '.')
            ss1.ignore();
          if(ss2.peek() != '.')
            ss2.ignore();
        }
      }
    }
    level = k;
    
    id1 = ss1.get();
    id2 = ss2.get();

//cout << level << "     " << prevlvl << endl;

    if(level  == prevlvl)
    {
//      cout << "sibling\n"; //sibling
      flag = '1';
    }
    if(level < prevlvl)//Ancestor
    {
//      cout << "ancestor\n";
      back = prevlvl - level + 1;
      flag = '0';
    }
    if(level > prevlvl)
    {
//      cout << "child\n";
      flag = '2';
    }
    
    while(1)
    {
      if(check[i] == true)
      {
    /*    if((0 == strcmp(data[i]->name,people[j].name)) && (data[i]->birth == people[j].birthYear))
        {
          cout << "COLLISION\n";
          temp = data[i];
          temp = data[i]->update(people[j], temp, flag, back, people[j-1]);
          break;
        }*/
      }
      if(check[i] == false)
      {
          data[i] = new Thing;
          check[i] = true;
          temp = data[i]->Load(people[j], temp, flag, back);	//Returns the freshley loaded object for future use
          break;
      } else {
        i = Hash2(people[j].birthYear, i);
      }//else
    }//while
    ss1.clear();	//Cleats the stream for next person
    ss2.clear();
  }//for
    
}  // Royals()


void Royals::getAncestor(const char *descendentName1, int descendentBirthYear1,
    const char *descendentName2, int descendentBirthYear2,
    const char **ancestorName, int *ancestorBirthYear)
{
} // getAncestor()


int Royals::getChildren(const char *name, int birthYear)
{
  unsigned int i, children;
  i = Hash(name);
  children = 0;
//Multiple entries are handled by inserting again so we have to add up all the children
  while(check[i] != false)
  {
    if((strcmp(name, data[i]->name) == 0) && (data[i]->birth == birthYear))
    {
      children = children + data[i]->child;
      break;
    } else {
      i = Hash2(birthYear, i);
    }
  }
  return children; 
} // getSiblings()


void Royals::getDescendent(const char *ancestorName, int ancestorBirthYear,
     const char **descendentName, int *descendentBirthYear)
{
/*
  unsigned int i, j, k, birth;
  char *name;
  i = Hash(ancestorName);
//Multiple entries are handled by inserting again so we have to add up all the children
  while(check[i] != false)
  {
    if((strcmp(ancestorName, data[i]->name) == 0) && (data[i]->birth == ancestorBirthYear))
    {
      //descendentName = &((data[i]->youngest)->name);
     // descendentBirthYear = &((data[i]->youngest)->birth);
      birth  = (data[i]->youngest)->birth;
      strcpy(name, (data[i]->youngest)->name);
cout << name << "         " << birth << endl;
      break;
    } else {
      i = Hash2(ancestorBirthYear, i);
    }
  }
*/
} //getDescedent()


int Royals::getMarriages(const char *name, int birthYear)
{
  int i, spouse = 0;
  i = 0;
  i = Hash(name);

  while(check[i] != false)
  {
//cout << data[i]->birth << "     " << birthYear << endl;
    if((strcmp(data[i]->name, name) == 0) && (data[i]->birth == birthYear))
    {
      spouse = data[i]->spouseCount;
      break;
    } else {
      i = Hash2(birthYear, i);
    }
  }
//cout << data[i].name << "          " << data[i].birth << endl;
/*  if(check[i] != false)
  { return data[i]->spouseCount; }
  else { return -1; }*/
  return spouse;
} // getMariages


int Royals::getSiblings(const char *name, int birthYear)
{

  unsigned int i, children;
  Thing *parent;
  i = Hash(name);
  children = 0;
//Multiple entries are handled by inserting again so we have to add up all the children
  while(check[i] != false)
  {
    if((strcmp(name, data[i]->name) == 0) && (data[i]->birth == birthYear))
    {
      if(data[i]->parent[0] != NULL)
      {
        parent = data[i]->parent[0];
        children = parent->child;
      } else {
        children = 1;
      }
      break;
    } else {
      i = Hash2(birthYear, i);
    }
  }
  children = children -1;
  return children;
  
} // getSiblings()

void Royals::printChild()
{
  for(int i = 0; i < 76980; i++)
  {
    if(check[i] != false)
      cout << data[i]-> name << "   " << data[i]->child << endl;
  }
}
