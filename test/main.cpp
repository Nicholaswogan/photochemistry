#include "example.h"

int main(){
  try {
    read_stuff();
  }
  catch(PhotoException& e){
    std::cout << e.what() << std::endl;
  }
  
}