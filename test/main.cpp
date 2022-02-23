#include "photochem.hpp"

int main(){
  try {
    Photochem::Settings s = Photochem::read_settings("../settings_ModernEarth.yaml");
  }
  catch(Photochem::PhotoException& e){
    std::cout << e.what() << std::endl;
  }
  
}