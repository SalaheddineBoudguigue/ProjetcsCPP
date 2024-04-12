#include <iostream>
#include "Liste.h"
#include "copier.h"

int main() {
  Liste<int> l;

  l.push_back(1);
  l.push_back(2);
  l.push_back(6);
  l.push_back(4);
  l.push_back(-2);

  std::cout << *first_largest_or_equal(l.begin(), l.end(), 3) << std::endl;

  // for (auto it = l.begin(); it != l.end(); ++it){
  //   *it *= 2;
  //   std::cout << *it << std::endl;
  // }

  // std::cout<<"/*===============================*/"<<std::endl;

  // std::cout << *find(l.begin(), l.end(), 2) << std::endl;

  std::cout<<"/*===============================*/"<<std::endl;

  Liste<int> * copy = sortedCopy(l); // need to be freed
  

  // auto it = l.begin();
  // ++it;

  // // l.insert(it, 100);
  // it = l.insert(it, 200);
  // it = l.erase(it);
  // // *it = 7777;
  // it = l.insert(it, 300);


  for (auto it2 = copy->begin(); it2 != copy->end(); ++it2){
    std::cout << *it2 << std::endl;
  }

  // l.iterator_insert(l.begin(), 10000);
  //unsigned int size = l.size();
  // for (unsigned int i=0; i < size; i++){
  //   std::cout << l.front() << std::endl;
  //   l.pop_front();
  // }

  //     for (Liste<int>::iterator it = l.begin(); it != l.end(); ++it){
  //     std::cout << *it << std::endl;
  // }

  delete copy;
  return 0;

}
