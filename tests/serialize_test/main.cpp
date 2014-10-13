#include <iostream>
#include <fstream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "test.hpp"

int main(){
  std::ofstream ofs("fichierDeSerialisation");

  Test zer(3,9);
  {
    zer.setC(3);
    zer.setC(6);
    zer.setC(9);
    zer.setC(12);
    zer.setD("try some string");
    std::cout << zer.getC()  << std::endl;


    boost::archive::text_oarchive oa(ofs);
    oa << zer;
  }

  Test troll;
  {
    std::ifstream ifs("fichierDeSerialisation");
    boost::archive::text_iarchive ia(ifs);
    ia >> troll;
  }
  
  std::cout << troll.getA() << std::endl;

}
