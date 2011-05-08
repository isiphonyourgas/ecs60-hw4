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
}

Thing* Thing::Load(const Person p, Thing *ptr, char flag, int level)
{


//cout << p.ID << endl;
  switch(flag)
  {
    case '0':
      for(int i = 0; i < level; i++)
        ptr = ptr->parent;
      parent = ptr;
      break;
    case '1':
      ptr = ptr->parent; //Sibling
      parent = ptr;
      break;
    case '2':
      parent = ptr;
      break;//It is a child
  }

  
  strcpy(name, p.name);
  birth = p.birthYear;
  spouseCount = p.spouseCount;
  strcpy(id, p.ID);
  check = true;
  child = 0;
if(parent != NULL)
{ 
    cout << "Parent: " << parent->id << "     This: " << id << endl;
}
  return this;
}


/*Data::Data() {}

void Data::insert(Person people)
{
  int i;
  i = Hash(people.name);
  while(1)
  {
    if(data[i].check == false)
    {
      data[i].Load(people);
      break;
    } else {
      i = Hash2(people.birthYear, i);
    }
  }
}*/

Royals::Royals(const Person *people, int count)
{
  int i, j, level = 0;
  int k;
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
 // level++;

  for(j = 1; j < count; j++)
  {  
if(strcmp(people[j].ID, "1.1.1.1.3.2.")==0)
  cout << "Here\n";
 
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
        ss1.getline(clear, 99);
        ss2.getline(clear,99);   //Clears both streams
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
//cout << " 1 \n";
        data[i] = new Thing;
        check[i] = true;
        temp = data[i]->Load(people[j], temp, flag, back);
//        level++;
//cout << "2\n";
        break;
      } else {//if
        i = Hash2(people[j].birthYear, i);
      }//else
    }//while
//    ss1.str("");
//    ss2.str("");
  }//for
    
}  // Royals()


void Royals::getAncestor(const char *descendentName1, int descendentBirthYear1,
    const char *descendentName2, int descendentBirthYear2,
    const char **ancestorName, int *ancestorBirthYear)
{
} // getAncestor()


int Royals::getChildren(const char *name, int birthYear)
{
/*  int i;
  i = Hash(name);
  while(1)
  {
    if((data[i]->name == name) && (data[i]->birth == birthYear))
    {
      break;
    } else {
      i = Hash2(birthYear, i);
    }
  }*/
  return 0;
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
  while(1)
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
  return data[i]->spouseCount;
} // getSiblings()


int Royals::getSiblings(const char *name, int birthYear)
{
  return 0;
} // getSiblings()
