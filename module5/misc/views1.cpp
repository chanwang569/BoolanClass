
#include <iostream>
#include <vector>
#include <map>
#include <ranges>


class Point{
  int x;
  int y;
  Widget* w;

  friend bool operator==(const Point&, const Point&)=default;

}
int main()
{

  std::vector coll{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

  auto v = std::views::take(
    std::views::transform(
      std::views::filter(coll,[] (auto elem) { return elem % 3 == 0; }),
      [] (auto elem) { return elem * elem; }),
  3);




  auto v = coll
    | std::views::filter([] (auto elem) { return elem % 3 == 0; })
    | std::views::transform([] (auto elem) { return elem * elem; })
    | std::views::take(3);

}




