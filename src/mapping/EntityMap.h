/*

  EntityMap

  Legacy design uses this object to handle Entity positioning
  and to parse all Entity-TileMap interaction.

  The current purpose of this object is to track Entity positions,
  and to handle the movement of Entities only.

*/

#include "../serialization/Boost_Serialization.h"


class EntityMap {

private:

  // Our serialization ALWAYS goes first
  friend class boost::serialization::access;
  template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
  {
    ar & width;
    ar & height;
    ar & pX;
    ar & pY;
    ar & pZ;
  }

// Map width and position in the global database
  
  int width, height;
  int pX, pY, pZ;

 public:

  EntityMap(){};
EntityMap(int Width, int Height, int posX, int posY, int posZ) : width(Width), height(Height), pX(posX), pY(posY), pZ(posZ){};
  
  virtual ~EntityMap(){};

};








