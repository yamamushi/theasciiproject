/*

  Tile.h
  2-24-2013

  -Jon Rumion (Yamamushi@gmail.com)


  This is going to be the source of a lot of headaches.

 */

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include <string>

class Tile {

private:

  friend class boost::serialization::access;
  template<class Archive>
      void serialize(Archive & ar, const unsigned int version)
  {
    ar & posX;
    ar & posY;
    ar & symbol;
  }

  int posX, posY;
  std::wstring symbol;

  
public:

  Tile(){};
  Tile(int PosX, int PosY, std::wstring Symbol) : posX(PosX), posY(PosY), symbol(Symbol){};
  virtual ~Tile(){};

};
