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
  youngest = NULL;
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
  path[0] = 0;
  if(parent[0] != NULL)
  {
    parentID[0] = parent[0]->idCount;
  } else {
    parentID[0] = -1;
  }
  //These copy the information we need from the given array
  strcpy(name, p.name);
  birth = p.birthYear;
  spouseCount = p.spouseCount;
  id[0] = new char[30];
  strcpy(id[0], p.ID);
//idCount++;
//cout << this->id[0] << endl;;

  check = true;
  child = 0;
  royalSpouse = 0;

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
  cout << thisthing->id[thisthing->idCount] << " --> ";
  thisthing = thisthing->parent[thisthing->current];
}

cout << endl;
*/
  return this;
}

Thing* Thing::update(Person p, Thing *ptr, char flag, int level, const char *prev)
{
  idCount++;
  id[idCount] = new char[30];
  strcpy(id[idCount], p.ID);
  int i;
if(strcmp(p.name, "Archduke Johannes  of Austria") == 0)
  cout << "here\n";

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
        path[idCount] = 0;
      } else {
        parent[1] = ptr;
        current = 1;
        path[idCount] = 1;
        (parent[1]->child)++;
      }
    } else {
      if((strcmp(parent[0]->name, ptr->name) == 0) && ((parent[0])->birth == ptr->birth))
      {
        current = 0;
        path[idCount] = 0;
      } else {
        current = 1;
        path[idCount] = 1;
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
        path[idCount] = 0;
      } else {
        parent[1] = ptr;
        current = 1;
        path[idCount] = 1;
        (parent[1]->child)++;
      }
    } else {

      if((strcmp(parent[0]->name, ptr->name) == 0) && ((parent[0])->birth == ptr->birth))
      {
        current = 0;
        path[idCount] = 0;
      } else {
        current = 1;
        path[idCount] = 1;
      }
    }
      break;
    case '2'://child
    if(parent[1] == NULL)
    {
      if((strcmp(parent[0]->name, ptr->name) == 0) && ((parent[0])->birth == ptr->birth))
      {
        current = 0;
        path[idCount] = 0;
      } else {
        parent[1] = ptr;
        current = 1;
        path[idCount] = 1;
        (parent[1]->child)++;
      }
    } else {
      if((strcmp(parent[0]->name, ptr->name) == 0) && ((parent[0])->birth == ptr->birth))
      {
        current = 0;
        path[idCount] = 0;
      } else {
        current = 1;
        path[idCount] = 1;
      }
    }
    break;
  }
  parentID[idCount] = parent[current]->idCount;

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
{
  cout << thisthing->id[(thisthing->idCount)] << " --> ";
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
}

void Thing::unmark()
{
  flip = false;
  if((parent[0] != NULL) && (parent[0]->flip != false))
    parent[0]->unmark();
  if((parent[1] != NULL) && (parent[1]->flip != false))
    parent[1]->unmark(); 
}

Thing* Thing::search()
{
  Thing *temp1 = NULL;
  Thing *temp2 = NULL;
  if(this->flip == true)
    return this;

  if(parent[0] != NULL)
    temp1 = parent[0]->search();

  if(parent[1] != NULL)
    temp2 = parent[1]->search();

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
      return this;
    }
  }
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
  temp = data[i]->Load(people[0], temp, 'a', back, "NULL");
  check[i] = true;
  level++;

  for(j = 1; j < count; j++)	//Loads the rest of the people
  {
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
        if((0 == strcmp(data[i]->name,people[j].name)) && (data[i]->birth == people[j].birthYear))
        {
          temp = data[i]->update(people[j], temp, flag, back, people[j-1].ID);
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
    ss1.clear();	//Cleats the stream for next person
    ss2.clear();
  }//for
    
/*
for(i = 0; i < 76980; i++)
{
  if(check[i] != NULL)
  {
cout << data[i]->name << endl;
cout << data[i]->idCount << endl;
    for(j = 0; j <= data[i]->idCount; j++)
    {
      cout << data[i]->id[j] << endl;
    }
  }
}
*/



}  // Royals()


void Royals::getAncestor(const char *descendentName1, int descendentBirthYear1,
    const char *descendentName2, int descendentBirthYear2,
    const char **ancestorName, int *ancestorBirthYear)
{
  unsigned int i, j;

/*
for(i = 0; i < 76980; i++)
{
  if(check[i] != NULL)
  {
    cout << data[i]->id[0] << endl;
  }
}*/

  char id1[30], id2[30];
  i = Hash(descendentName1);//i stores decendent 1
  j = Hash(descendentName2);//j stores decendent 2
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
  Thing *item1, *item2, *current;
  current = NULL;
  item1 = data[i];
  item2 = data[j];
  item1->mark();
  current = item2->search();
  item1->unmark();
  

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


 /* int k, l, count, jump, a, pathway, b, len;
  int result1[15], result2[15];
  char *id, *cid, *totalID;
//  char id1[30], id2[30];
  k = 0;
  l = 0;
  b = 0;
  Thing *temp, *current, *item1, *item2, *back;
  item1 = data[i];
  item2 = data[j];
  stringstream ss1, ss2;
  current = NULL;
  for(k = 0; k < item2->idCount; k++)
  {
    cout << item2->id[k]<< endl;
  }
  cout << "\n\n\n";

  for(k = 0; k < item1->idCount; k++)
  {
    cout << item1->id[k]<< endl;
  }
cout << "\n\n\n";

  k = 0;

  while((k < item1->idCount) && (l < item2->idCount))
  {
    strcpy(id1, data[i]->id[k]);
    strcpy(id2, data[j]->id[l]);
//cout << id1 << "      " << id2 << endl;
//    len = strlen(id1);
    id = strtok(id1, ".");
    a = 0;
//cout << id1 << "     " << id2 << endl;
  //  for(a = 0; a < len; a++)
    while(id != NULL)
    {
      result1[a] = *id - 48;
      id = strtok(NULL, ".");
//cout << result1[a] << ".";
      a++;
    }
//cout << endl;
    a = 0;
    id = strtok(id2, ".");
    while(id != NULL)
    {
      result2[a] = *id - 48;
      id = strtok(NULL, ".");
//cout << result2[a] << ".";
      a++;
    }
//cout << endl;

  for(b = 0; b < 15; b++)
  {
    if(result1[b] != result2[b])
      break;
  }
  jump = a - b - 1;
//cout << jump << endl;
    while((ss1.good()==true))
    {
      id = ss1.get();
      if(id == '.')
        jump++;
      //strtok(NULL, ".");
    }

//cout << "BBBBBB = " << b << endl;

    if((result1[0] == result2[0]) && (jump > 0))
    {
      temp = data[j];
      back = temp;
      temp = temp->parent[temp->path[l]];
      pathway = back->parentID[l];
      for(a = 0; a < jump; a++)
      {
//cout << temp->id[pathway] << "      " << temp->name << endl;;
        back = temp;
        temp = temp->parent[temp->path[pathway]];
        pathway = back->parentID[pathway];

//        temp = temp->parent[temp->path[pathway]];
      }
if(pathway == -1)
{
cout << temp->id[0] << endl;
} else {
cout << temp->id[pathway] << endl;
}
      if(current == NULL)
      {
        current = temp;
      } else {
        if(current->birth < temp->birth)
          current = temp;
      }
    }
    ss1.clear();
    ss2.clear();
//cout << b + 1 << b << b -1 << endl;
    if(result1[b + 1] > result2[b + 1])
    {
      l++;
//cout << "LLLLLLLLLLLLLLL = " << l << endl;;
    } else {
      k++;
//cout << "KKKKKKKKKKKKKKKK = " << k << endl;;
    }
//cout<< item1->idCount << "      " << item2->idCount << endl;
  }*/
//  if(current != NULL)
    cout << current->name << "          " << current->birth << endl;
    cout << item1->id[0] << "     " << item2->id[0] << "     " <<current->id[0] << endl;

  *ancestorName = current->name;
  *ancestorBirthYear = current->birth;
  

/*
unsigned int p;
for(p = 0; p < 76980; p++)
{
  cout << p << endl;
//  if(check[p] == true)
//  {
//    if(data[p]->flip == true)
//      cout << data[p]->name << endl;
//  }
}
*/


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
