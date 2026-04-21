#include "src.hpp"
#include <iostream>
#include <vector>
#include <string>
int main(){
  int num = 200;
  if (expect(num).ge(114).lt(514).Not().toBe(321)) std::cout << "OK1\n"; else std::cout << "BAD1\n";
  int x = 1;
  if (expect(x).Not().toBe(1).toBe(2)) std::cout << "BAD2\n"; else std::cout << "OK2\n";
  std::vector<int> v{1,3,5};
  if (expect(3).toBeOneOf(v)) std::cout << "OK3\n"; else std::cout << "BAD3\n";
  std::string s = "abc";
  if (expect(s).le(std::string("abd")).lt(std::string("zzz"))) std::cout << "OK4\n"; else std::cout << "BAD4\n";
  return 0;
}
