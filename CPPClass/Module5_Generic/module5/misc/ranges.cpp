
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void print(const auto& coll) {
  for (const auto& elem : coll) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';
}

int main()
{
  std::vector<std::string> coll{"Rio", "Tokyo", "New York", "Berlin"};
  
  sort(coll.begin(), coll.end());
  std::ranges::sort(coll);     
 
  print(coll);

  int arr[] = {42, 0, 8, 15, 7};
  std::ranges::sort(arr);      
  print(arr);                 
}

