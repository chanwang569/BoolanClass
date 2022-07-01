
#include <iostream>
#include <vector>
#include <ranges>
namespace vws = std::views;

int main()
{
  std::cout << std::boolalpha;

  std::vector<int> coll{ 8, 15, 7, 0, 9, 13, 6, 0, 8, 15, 6 };

  auto vColl = coll
                | vws::transform([] (int i) {
                                    std::cout << " t1: " << i << '\n';
                                    return i;
                                 })
                | vws::transform([] (int i) {
                                    std::cout << "  t2: " << i << '\n';
                                    return i;
                                 })
                | vws::filter([] (int i) {
                                    bool ret = i % 3 == 0;
                                    std::cout << "   f1: " << i
                                              << " => " << ret;
                                    std::cout << (ret ? "\n" : "\n\n");
                                    return ret;
                              })
                | vws::transform([] (int i) {
                                    std::cout << "    t3: " << i << '\n';
                                    return i;
                                 })
                | vws::filter([] (int i) {
                                    bool ret = i % 2 == 0;
                                    std::cout << "     f2: " << i
                                              << " => " << ret;
                                    std::cout << (ret ? "\n" : "\n\n");
                                    return ret;
                              });


  for (int i : vColl) {
    std::cout << "      => " << i << '\n' << '\n';
  }
}

