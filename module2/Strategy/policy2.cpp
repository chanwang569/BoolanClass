#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
#include <list>
using namespace std;

//Policy-based Design 

class MarkdownListStrategy 
{
public:
  void start(ostringstream& oss) {};
  void end(ostringstream& oss) {};
  void add_list_item(ostringstream& oss, const string& item) 
  {
    oss << " * " << item << endl;
  }
};

class HtmlListStrategy
{
public:
  void start(ostringstream& oss) 
  {
    oss << "<ul>" << endl;
  }

  void end(ostringstream& oss) 
  {
    oss << "</ul>" << endl;
  }

  void add_list_item(ostringstream& oss, const string& item) 
  {
    oss << "<li>" << item << "</li>" << endl;
  }
};


template <typename ListPolicy>
class TextProcessor : private ListPolicy 
{
public:
  void clear()
  {
    oss.str("");
    oss.clear();
  }
  void append_list(const vector<string> items)
  {
    ListPolicy::start(oss);
    for (auto& item : items)
      ListPolicy::add_list_item(oss, item);
    ListPolicy::end(oss);
  }

  string str() const { return oss.str(); }
private:
  ostringstream oss;
};



int main()
{
  // markdown
  TextProcessor<MarkdownListStrategy> tp1;
  cout<<sizeof(tp1)<<endl;
  tp1.append_list({"Policy", "Design", "Pattern"});
  cout << tp1.str() << endl;

   // html
  TextProcessor<HtmlListStrategy> tp2;
  tp2.append_list({"Policy", "Design", "Pattern"});
  cout << tp2.str() << endl;

  getchar();
  return 0;
}