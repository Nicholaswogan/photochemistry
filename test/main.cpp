#include "example.h"

int main(){
  try {
    Photochem::read_stuff();
  }
  catch(Photochem::PhotoException& e){
    std::cout << e.what() << std::endl;
  }
  
}