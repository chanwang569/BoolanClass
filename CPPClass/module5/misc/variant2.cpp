#include <iostream>
#include <any>
#include <vector>

using namespace std;




struct WidgetA{
    double x{};
};

struct WidgetB{
    double x{};
    double y{};
};
struct WidgetC{
    double x{};
    double y{};
    double z{};
    double u{};
    double v{};
    double w{};
};

union WidgetABCU{
    WidgetA a;
    WidgetB b;
    WidgetC c;

    WidgetABCU(){}
    ~WidgetABCU(){}
    
};

struct TranslateVisitor {

  void operator()(WidgetA const& a) {
    cout << "Translate WidgetA!"<<endl;
  }
  void operator()(WidgetB const& b) {
    cout << "Translate WidgetB!"<<endl;
  }
  void operator()(WidgetC const& b) {
    cout << "Translate WidgetC!"<<endl;
  }
};

int main(){

    using Widget = std::variant<WidgetA, WidgetB,WidgetC>;
    
    vector<Widget> v;
    v.push_back(WidgetA{});
    v.push_back(WidgetB{});
    v.push_back(WidgetC{});
    
    for_each( v.begin(), v.end(), 
      [](Widget& w){ 
        TranslateVisitor visitor;
        std::visit(visitor, w);
      }
    );
  
    


}
