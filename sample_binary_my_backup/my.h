
#pragma once
#include "monster_generated.h"

using namespace MyGame::Sample;

// An abstract class 
class SerializationInterface
{
  
public: 
    // Pure Virtual Function 
    virtual MyGame::Sample::Monster *unpack(const void *buf) = 0;
    virtual void * pack(MyGame::Sample::Monster) = 0;
    
   /* Other members */
}; 


class MonsterBuilderClass: public SerializationInterface
{
 public:
  MonsterBuilderClass(){
    auto weapon_one_name = builder.CreateString("Sword");
    short weapon_one_damage = 3;
    auto weapon_two_name = builder.CreateString("Axe");
    short weapon_two_damage = 5;

    // Use the `CreateWeapon` shortcut to create Weapons with all fields set.
  auto sword = CreateWeapon(builder, weapon_one_name, weapon_one_damage);
  auto axe = CreateWeapon(builder, weapon_two_name, weapon_two_damage);

  // Create a FlatBuffer's `vector` from the `std::vector`.
  std::vector<flatbuffers::Offset<Weapon>> weapons_vector;
  weapons_vector.push_back(sword);
  weapons_vector.push_back(axe);
  auto weapons = builder.CreateVector(weapons_vector);

  // Second, serialize the rest of the objects needed by the Monster.
  auto position = Vec3(1.0f, 2.0f, 3.0f);

  auto name = builder.CreateString("MyMonster");

  unsigned char inv_data[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  auto inventory = builder.CreateVector(inv_data, 10);

  // Shortcut for creating monster with all fields set:
  auto orc = CreateMonster(builder, &position, 150, 80, name, inventory,
                           Color_Red, weapons, Equipment_Weapon, axe.Union());


  builder.Finish(orc);  // Serialize the root of the object.
  }
  const MyGame::Sample::Monster* GetMonster(){ return MyGame::Sample::GetMonster(builder.GetBufferPointer());};
     

  MyGame::Sample::Monster *unpack(const void *buf){
    return NULL;
  }
  void * pack(MyGame::Sample::Monster){
    return NULL;
  }
 private:
    flatbuffers::FlatBufferBuilder builder;
};
