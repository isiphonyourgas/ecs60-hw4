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
}

inline int Hash2(int year, int val)
{
  val = (val + (year - 1800)) % 76980;
  return val;
}

Thing::Thing()
{
  check = false;
  spouseCount = 0;
  birth = 0;
  parent = NULL;
//  parent2 = NULL;
  child == 0;
}

Thing* Thing::Load(const Person p, Thing *ptr, char flag, int level)
{
  int i;
//cout << p.ID << endl;
  switch(flag)
  {
    case '0':
      for(int i = 0; i < level; i++)
        ptr = ptr->parent;
      parent = ptr;
      if(parent != NULL)//Not root Node
      {
        (parent->child)++;
if(strcmp(parent->name, "Walther Daublebsky") == 0)
  cout << "HERE\n";
      }
//cout << "uncle\n";
      break;
    case '1':
      ptr = ptr->parent; //Sibling
      parent = ptr;
      (parent->child)++;
if(strcmp(parent->name, "Walther Daublebsky") == 0)
  cout << "HERE\n";
//cout << parent->name << " has " << parent->child << "       " << parent->id << endl;
//cout << "sibling\n";
      break;
    case '2':
      parent = ptr;
      (parent->child)++;
if(strcmp(parent->name, "Walther Daublebsky") == 0)
  cout << "HERE\n";
//cout << "Child\n";
      break;//It is a child
  }

  
  strcpy(name, p.name);
  birth = p.birthYear;
  spouseCount = p.spouseCount;
  strcpy(id, p.ID);
  check = true;
  child = 0;
  royalSpouse = 0;
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
if(parent != NULL)
{ 
    cout << "Parent: " << parent->id << "     This: " << id << endl;
    cout << parent->name << "               " << name << endl << endl;
} else {
    cout << "I'm all alone: " << id << "       ";
    cout << name << endl << endl;
}*/
  return this;
}

/*Thing* Thing::update(const Person p, Thing *ptr, char flag, int level)
{

  switch(flag)
  {
    case '0':
      for(int i = 0; i < level; i++)
        ptr = ptr->parent;
      parent = ptr;
      if(parent != NULL)//Not root Node
      {
        (parent->child)++;
      }
//cout << "uncle\n";
      break;
    case '1':
      ptr = ptr->parent; //Sibling
      parent = ptr;
      (parent->child)++;
//cout << parent->name << " has " << parent->child << "       " << parent->id << endl;
//cout << "sibling\n";
      break;
    case '2':
      parent = ptr;
      (parent->child)++;
//cout << "Child\n";
      break;//It is a child
  }
  return this;
}*/

Royals::Royals(const Person *people, int count)
{
  int i, j, level = 0;
  int k, l;
  Thing *temp = NULL;
  char flag;
  char id[5], cid[5], clear[99];
  int id1[15], id2[15];
  int back = 0;
  stringstream ss1, ss2;
  for(i = 0; i < count; i++)
    check[i] = false;

  i = Hash(people[0].name);
  data[i] = new Thing;
  temp = data[i]->Load(people[0], temp, 'a', back);
  check[i] = true;
 // level++;

  for(j = 1; j < count; j++)
  {
if((strcmp(people[j].name, "Count Leopold von Drechsel auf Deufstetten") == 0) && (people[j].birthYear == 1962))
  cout <<" Here\n";

 
    flag = 'a';
    i = Hash(people[j].name);
    ss1.str(people[j].ID);
    ss2.str(people[j - 1].ID);

  //  ss1 << people[j].ID;
 //   ss2 << people[j-1].ID;
    for(k = 0; k < level; k++)
    {
      ss1.get(cid, 4, '.');
      ss2.get(id, 4, '.');
      ss1.ignore();
      ss2.ignore();
      id2[k] = atoi(cid);
      id1[k] = atoi(id);
//cout << id1[k] << "                                  " << id2[k] <<"                 "  << people[j-1].ID << endl;
      if(id1[k] != id2[k])
      {
        flag = '0';
        back = level - k + 1;
        level = k;
        break;
      }
    }
    k++;
    ss1.get(cid, 4, '.');
    ss2.get(id, 4, '.');
    ss1.ignore();
    ss2.ignore();
    id2[k] = atoi(cid);
    id1[k] = atoi(id);
//cout << id1[k] << "                                  " << id2[k] << endl;
    if(flag == 'a')
    {
      if((id1[k] == id2[k]))
      {
        flag = '2';//Child
        level++;
      } else {
        flag = '1';//sibling
      }
    }
    while(1)
    {
      if(check[i] == false)
      {
        data[i] = new Thing;
        check[i] = true;
        temp = data[i]->Load(people[j], temp, flag, back);
// cout << i << endl;
        break;
      } else {
        i = Hash2(people[j].birthYear, i);
      }//else
    }//while
//    ss1.str("");
//    ss2.str("");
    ss1.clear();
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
//if((strcmp(name, "Princess Olga of Greece") == 0) && (birthYear == 1971))
//  cout << "HERE\n";
//cout << name << endl;
  while(check[i] != false)
  {
    if((strcmp(name, data[i]->name) == 0) && (data[i]->birth == birthYear))
    {
      break;
    } else {
      i = Hash2(birthYear, i);
    }
  }
  //count = data[i]->spouseCount;
  if(check[i] == true)
  {
    children = data[i]->child;
    i = Hash2(birthYear, i);
  } else {
    children = -1;
  }

  while(check[i] != false)
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
  int i;
  i = 0;
  i = Hash(name);

  while(check[i] != false)
  {
//cout << data[i]->birth << "     " << birthYear << endl;
    if((strcmp(data[i]->name, name) == 0) && (data[i]->birth == birthYear))
    {
      break;
    } else {
      i = Hash2(birthYear, i);
    }
  }
//cout << data[i].name << "          " << data[i].birth << endl;
  if(check[i] != false)
  { return data[i]->spouseCount; }
  else { return -1; }
  return -1;
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
