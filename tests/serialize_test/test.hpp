#include <string>

#include <vector>
#include <boost/serialization/vector.hpp>

class Test{
public:
  int	getA(void){return this->a;}
  int	getB(void){return this->b;}
  int	getC(void){return this->c[0];}
  void	setA(int _a){this->a = _a;}
  void	setB(int _b){this->b = _b;}
  void	setC(int _c){this->c.push_back(_c);}
  void	setD(std::string _d){this->d = _d;}
  
  
  
  Test() {};
  Test(int _a, int _b){
    this->a = _a;
    this->b = _b;
  }
  
private:
  
  friend class boost::serialization::access;

  template<class Archive>
  void serialize(Archive & ar, const unsigned int version) {
    ar & this->a;
    ar & this->b;
    ar & this->c;
    ar & this->d;
  }
  
  int a;
  int b;
  std::vector <int> c;
  std::string d;
};
