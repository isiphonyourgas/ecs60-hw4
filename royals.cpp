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
  //check = false;
  parent[0] = NULL;
  parent[1] = NULL;
  flip = false;
}//Constrcutor

Thing* Thing::Load(const Person p, Thing *ptr, char flag, int level, const char *prev)
{
  current = 0;
  switch(flag)
  {
    case '0':			//Ancestor
      
      for(int i = 0; i < level; i++)
      {
        ptr = ptr->parent[ptr->current];	//Used algorithm to determine pos
      }
      parent[0] = ptr;
      if(parent[0] != NULL)//Not root Node
      {
        (parent[0]->child)++;	//If its not the root node, we need to add a child to parent
      }
      break;
    case '1':			//Sibling
      ptr = ptr->parent[current]; //Must go up 1 level to reach parent
      parent[0] = ptr;
      (parent[0]->child)++;
      break;
    case '2':		//Current pointer already points to parent of child
      parent[0] = ptr;
      (parent[0]->child)++;
      break;//It is a child
    case 'a':
      break;
  }
  strcpy(name, p.name);
  birth = p.birthYear;
  spouseCount = p.spouseCount;
//  check = true;
  child = 0;

  youngest = this;
  Thing *temp;
  temp = parent[0];
  while(temp != NULL)
  {
    if((temp->youngest)->birth < p.birthYear)
    {
      temp->youngest = this;
      temp = temp->parent[temp->current];
    } else {
      break;
    }
  }

/*
Thing *thisthing;
thisthing = this;

while(thisthing != NULL)
{
  cout << thisthing->name << " --> ";
  thisthing = thisthing->parent[thisthing->current];
}

cout << endl;
*/
  return this;
}

Thing* Thing::update(Person p, Thing *ptr, char flag, int level, const char *prev)
{
  int i;
//  strcpy(id, p.ID);

  switch(flag)
  {
    case '0'://ancestor
      for(i = 0; i < level; i++)
      {
        ptr = ptr->parent[ptr->current];
      }
      
    if(parent[1] == NULL)
    {
      if((strcmp(parent[0]->name, ptr->name) == 0) && ((parent[0])->birth == ptr->birth))
      {
        current = 0;
      } else {
        parent[1] = ptr;
        current = 1;
        (parent[1]->child)++;
      }
    } else {
      if((strcmp(parent[0]->name, ptr->name) == 0) && ((parent[0])->birth == ptr->birth))
      {
        current = 0;
      } else {
        current = 1;
      }
    }
      break;
    case '1'://sibling
    ptr = ptr->parent[ptr->current];

    if(parent[1] == NULL)
    {
      if((strcmp(parent[0]->name, ptr->name) == 0) && ((parent[0])->birth == ptr->birth))
      {
        current = 0;
      } else {
        parent[1] = ptr;
        current = 1;
        (parent[1]->child)++;
      }
    } else {

      if((strcmp(parent[0]->name, ptr->name) == 0) && ((parent[0])->birth == ptr->birth))
      {
        current = 0;
      } else {
        current = 1;
      }
    }
      break;
    case '2'://child
    if(parent[1] == NULL)
    {
      if((strcmp(parent[0]->name, ptr->name) == 0) && ((parent[0])->birth == ptr->birth))
      {
        current = 0;
      } else {
        parent[1] = ptr;
        current = 1;
        (parent[1]->child)++;
      }
    } else {
      if((strcmp(parent[0]->name, ptr->name) == 0) && ((parent[0])->birth == ptr->birth))
      {
        current = 0;
      } else {
        current = 1;
      }
    }
    break;
  }
//  parentID[idCount] = parent[current]->idCount;

  Thing *temp;

  temp = parent[current];
  while(temp != NULL)
  {
    if((temp->youngest)->birth < (this->youngest)->birth)
    {
      temp->youngest = this->youngest;
      temp = temp->parent[temp->current];
    } else {
      break;
    }
  }

/*

Thing *thisthing;
thisthing = this;

while(thisthing != NULL)
{:246,2
  cout << thisthing->name << " --> ";
  thisthing = thisthing->parent[thisthing->current];
}

cout << endl;
*/
  return this;
}

void Thing::mark()
{

  flip = true;

   if((parent[0] != NULL) && (parent[0]->flip != true))
    parent[0]->mark();
   if((parent[1] != NULL) && (parent[1]->flip != true))
    parent[1]->mark();
}//Marks all nodes

void Thing::unmark()
{
  flip = false;
  if((parent[0] != NULL) && (parent[0]->flip != false))
    parent[0]->unmark();
  if((parent[1] != NULL) && (parent[1]->flip != false))
    parent[1]->unmark(); 
}//Unmarks all node

Thing* Thing::search()
{
  Thing *temp1 = NULL;
  Thing *temp2 = NULL;

  if((flip == true) && (birth != 0))// Value hit, returning
  {
    return this;
  }

  if(parent[0] != NULL)
    temp1 = parent[0]->search();

  if(parent[1] != NULL)
    temp2 = parent[1]->search();

//If statements to determine which to return
  if(temp1 != NULL)
  {
    if(temp2 != NULL)
    {
      if(temp1->birth > temp2->birth)
      {
        return temp1;
      } else {
        return temp2;
      }
    } else {
      return temp1;
    }
  } else {
    if(temp2 != NULL)
    {
      return temp2;
    } else {
      return NULL;
    }
  }
}

Royals::Royals(const Person *people, int count)
{
  int i, j, level = 0;
//  int k, prevlvl, m;
  int prevlvl;
  Thing *temp = NULL;
  char flag;
//  char id1, id2;
  char id1[30];
  char *blah;
  int back = 0;
  stringstream ss1, ss2;

  for(i = 0; i < count; i++) 	//Marks used tableslots
    check[i] = false;

  i = Hash(people[0].name);	//Hash function
  data[i] = new Thing;		//Initializes first thing
  temp = data[i]->Load(people[0], temp, 'a', back, "NULL");
  check[i] = true;
  level++;

  for(j = 1; j < count; j++)	//Loads the rest of the people
  {
    flag = 'a';		//Flag to determine what to load as
    i = Hash(people[j].name);
//    ss1.str(people[j].ID);
//    ss2.str(people[j - 1].ID);
    strcpy(id1, people[j].ID);
//    strcpy(id2, people[j-1].ID);
    prevlvl = level;
//    k = 0;
//    m = 0;


//Finds level
/*    while(ss1.good() == true)
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
    id2 = ss2.get();*/
  blah = strpbrk(id1, ".");
  level = 0;
  while(blah != NULL)
  {
    blah = strpbrk(blah + 1, ".");
    level++;
  }

//************************************************************
//Flag Set
    if(level  == prevlvl)
    {
      flag = '1';
    }
    if(level < prevlvl)//Ancestor
    {
      back = prevlvl - level + 1;
      flag = '0';
    }
    if(level > prevlvl)
    {
      flag = '2';
    }
//*************************************************************
    while(1)
    {
      if(check[i] == true)
      {
        if((0 == strcmp(data[i]->name,people[j].name)) && (data[i]->birth == people[j].birthYear))
        {
          temp = data[i]->update(people[j], temp, flag, back, people[j-1].ID); //Updates any relevent info
          break;
        } else {
          i = Hash2(people[j].birthYear, i);
        }
      } else {
          data[i] = new Thing;
          check[i] = true;
          temp = data[i]->Load(people[j], temp, flag, back, people[j-1].ID);	//Returns the freshley loaded object for future use
          break;
      }//else
    }//while
    ss1.clear();	//resets stream flag for next person
    ss2.clear();
  }//for
   

}  // Royals()


void Royals::getAncestor(const char *descendentName1, int descendentBirthYear1,
    const char *descendentName2, int descendentBirthYear2,
    const char **ancestorName, int *ancestorBirthYear)
{
  unsigned int i, j;

//Hash function
  i = Hash(descendentName1);//i stores decendent 1
  j = Hash(descendentName2);//j stores decendent 2

//Hash table find
  while(check[i] != false)
  {
    if((strcmp(descendentName1, data[i]->name) == 0) && (data[i]->birth == descendentBirthYear1))
    {  break; } else {
      i = Hash2(descendentBirthYear1, i);
    }
  }
  while(check[j] != false)
  {
    if((strcmp(descendentName2, data[j]->name) == 0) && (data[j]->birth == descendentBirthYear2))
    {  break; } else {
      j = Hash2(descendentBirthYear2, j);
    }
  }

//Marks the anscestor nodes and searches from other item until reaches marked node

  Thing *item1, *item2, *current;
  current = NULL;
  item1 = data[i];
  item2 = data[j];
  item1->mark();
  current = item2->search();
  item1->unmark();
//**********************************************************************
//Checking for overlap
  if(current == item1)
  {
    if(item1->parent[0] != NULL)
    {
      if(item1->parent[1] != NULL)
      {
        if((item1->parent[0])->birth > (item1->parent[1])->birth)
        {
          current = item1->parent[0];
        } else {
          current = item1->parent[1];
        }
      } else {
        current = item1->parent[0];
      }
    }
  }
//************************************************************************
  if(current == item2)
  {
    if(item2->parent[0] != NULL)
    {
      if(item2->parent[1] != NULL)
      {
        if((item2->parent[0])->birth > (item2->parent[1])->birth)
        {
          current = item2->parent[0];
        } else {
          current = item2->parent[1];
        }
      } else {
        current = item2->parent[0];
      }
    }
  }
//***********************************************************************
//Checking for birthyear = 0
  while(current->birth == 0)
  {
    if(current->parent[0] != NULL)
    {
      if(current->parent[1] != NULL)
      {
        if((current->parent[0]->birth > current->parent[1]->birth))
        {
          current = current->parent[0];
        } else {
          current = current->parent[1];
        }
      } else {
        current = current->parent[0];
      }
    }
  }
//    cout << current->name << "          " << current->birth << endl;
//    cout << item1->id[0] << "     " << item2->id[0] << "     " <<current->id[0] << endl;

  *ancestorName = current->name;
  *ancestorBirthYear = current->birth;
  

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

  unsigned int i;
  i = Hash(ancestorName);
//Multiple entries are handled by inserting again so we have to add up all the children
  while(check[i] != false)
  {
    if((strcmp(ancestorName, data[i]->name) == 0) && (data[i]->birth == ancestorBirthYear))
    {
      *descendentBirthYear = (data[i]->youngest)->birth;
      *descendentName = (data[i]->youngest)->name;
      break;
    } else {
      i = Hash2(ancestorBirthYear, i);
    }
  }

} //getDescedent()


int Royals::getMarriages(const char *name, int birthYear)
{
  int i, spouse = 0;
  i = 0;
  i = Hash(name);

  while(check[i] != false)
  {
    if((strcmp(data[i]->name, name) == 0) && (data[i]->birth == birthYear))
    {
      spouse = data[i]->spouseCount;
      break;
    } else {
      i = Hash2(birthYear, i);
    }
  }
  return spouse;
} // getMariages


int Royals::getSiblings(const char *name, int birthYear)
{

  unsigned int i, children;
  Thing *parent;
  i = Hash(name);
  children = 0;
//Hash the values
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
