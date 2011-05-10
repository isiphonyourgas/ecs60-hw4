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
  parent = NULL;
//  parent2 = NULL;
  child == 0;
}//Constrcutor

Thing* Thing::Load(const Person p, Thing *ptr, char flag, int level)
{
  int i;
if(0 == strcmp(p.name,"Alfonso Sanz y Martnez de Arrizala"))
  cout << "error\n";


//cout << p.ID << endl;
  switch(flag)
  {
    case '0':			//Ancestor
      for(int i = 0; i < level; i++)
        ptr = ptr->parent;	//Used algorithm to determine pos
      parent = ptr;
      if(parent != NULL)//Not root Node
      {
        (parent->child)++;	//If its not the root node, we need to add a child to parent
      }
//cout << "uncle\n";
      break;
    case '1':			//Sibling
      ptr = ptr->parent; //Must go up 1 level to reach parent
      parent = ptr;
      (parent->child)++;
      break;
    case '2':		//Current pointer already points to parent of child
      parent = ptr;
      (parent->child)++;
//cout << "Child\n";
      break;//It is a child
    case 'a':
      break;
  }

  //These copy the information we need from the given array
  strcpy(name, p.name);
  birth = p.birthYear;
  spouseCount = p.spouseCount;
  strcpy(id, p.ID);
  check = true;
  child = 0;
  royalSpouse = 0;

  //Checks and loads the spouses
  if(spouseCount != 0)
  {
    spouseName = new char*[spouseCount];
    spouseYear = new int[spouseCount];
    for(i = 0; i < spouseCount; i++)
    {
      if(strcmp(p.spouseNames[i], "") == 0)
      {  break; } else {
        spouseName[i] = new char[85];
        strcpy(spouseName[i], p.spouseNames[i]);
        spouseYear[i] = p.spouseBirthYears[i];
        royalSpouse++;
      }
    }
  }
/*
Thing *thisthing;
thisthing = this;

while(thisthing != NULL)
{
  cout << thisthing->id << " --> ";
  thisthing = thisthing->parent;
}

cout << endl;*/

  return this;
}


Royals::Royals(const Person *people, int count)
{
  int i, j, level = 0;
  int k, l, prevlvl, m;
  Thing *temp = NULL;
  char flag;
  char id[40], cid[40], clear[99];
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
    /*  if(check[i] == true)
      {
        if((0 == strcmp(data[i]->name,people[j].name)) && (data[i]->birth == people[j].birthYear))
          break;
      }*/
      if(check[i] == false)
      {
          data[i] = new Thing;
          check[i] = true;
//  cout << people[j].ID <<"     " <<  level << "      "<< back << endl;

          temp = data[i]->Load(people[j], temp, flag, back);	//Returns the freshley loaded object for future use
     //temp->parent
// cout << i << endl;
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
  int i, j, k, count, children, SpousebirthYear;
  char Spousename[85];
  i = Hash(name);
  children = 0;
//  cout << name << "    " << birthYear << endl;
//if((strcmp(name, "Annica Martin") == 0) && (birthYear == 1853))
//  cout << "HERE\n";
//cout << name << endl;
//Multiple entries are handled by inserting again so we have to add up all the children
  while(check[i] != false)
  {
    if((strcmp(name, data[i]->name) == 0) && (data[i]->birth == birthYear))
    {
      children = children + data[i]->child;
      break;
    //  i = Hash2(birthYear, i);
    } else {
      i = Hash2(birthYear, i);
    }
  }
  //count = data[i]->spouseCount;

/*  while(check[i] != false)
  {
    if((strcmp(name, data[i]->name) == 0) && (data[i]->birth == birthYear))
    {
      break;
    } else {
      i = Hash2(birthYear, i);
    }
  }
  if(check[i] == true)
    children = children + data[i]->child;
*/
/*  for(j = 0; j < count; j++)
  {
    strcpy(Spousename, data[i]->spouseName[j]);
    SpousebirthYear = data[i]->spouseYear[j];
    k = Hash(Spousename);
    while(check[k] != false)
    {
      if((strcmp(Spousename, data[k]->name) == 0) && (data[k]->birth == SpousebirthYear))
      {
        break;
      } else {
        k = Hash2(SpousebirthYear, k);
      }
    }
    if(check[k] == true)
    {
      children = children + data[k]->child;
    }
  }
*/
//cout << "Returning: " << data[i]->name << endl;
  return children; 
} // getSiblings()


void Royals::getDescendent(const char *ancestorName, int ancestorBirthYear,
    const char **descendentName, int *descendentBirthYear)
{
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
  return 0;
} // getSiblings()

void Royals::printChild()
{
  for(int i = 0; i < 76980; i++)
  {
    if(check[i] != false)
      cout << data[i]-> name << "   " << data[i]->child << endl;
  }
}
