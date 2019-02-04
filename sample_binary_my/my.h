
#pragma once
#include "monster_generated.h"



class Monster
{
 public:
 Monster(std::string name, int age):m_name(name),m_age(age){};
  std::string getName(){return m_name;};
  int getAge(){return m_age;};
 private:
  std::string m_name;
  int m_age;
};

class Monster2
{
 public:
 Monster2(std::string name, int age):m_name(name),m_age(age){};
  std::string getName(){return m_name;};
  int getAge(){return m_age;};
 private:
  std::string m_name;
  int m_age;
};
// An abstract class 
class SerializationInterface
{
  
public: 
    // Pure Virtual Function 
    virtual Monster unpack(const void *buf) = 0;
    virtual void * pack(Monster) = 0;
    
   /* Other members */
}; 


class MonsterSerializer: public SerializationInterface
{
 public:
  MonsterSerializer(){}
  void * pack(Monster my_monster){
    flatbuffers::FlatBufferBuilder fbb;
    auto name_buff = fbb.CreateString(my_monster.getName());
    auto my_mb = CreateMonster_table(fbb, my_monster.getAge(), name_buff);
    fbb.Finish(my_mb);
    return fbb.GetBufferPointer();
  }
  Monster unpack(const void *buf){
    auto my_monster = GetMonster_table(buf);
    return Monster(my_monster->name()->str(), my_monster->age());
  }
};

