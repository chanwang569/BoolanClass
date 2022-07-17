#include <utility>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
using namespace std;




template <typename T> 
class Library
{
public:

	static  std::function<void(Library<T>*)> app_delete=[] (Library<T> * app)
	{
		cout<<"call customer deleteer."<<endl;
		app->run();
	};
    

	// struct Lambda{

	// 	void operator() (Library<T> * app) const
	// 	{
	// 		cout<<"call customer deleteer."<<endl;
	// 		app->destroy();
	// 		app->number++;
	// 	}
	// };

	//  static constexpr Lambda app_delete{};



	void run() 
	{
		cout << "Library.run"<<endl;
	}

    ~Library()
    {
        cout<<"Library dtor"<<endl;
    }
};




int main()
{

    Library<int> lib;
    //lib.app_delete(&lib);
    

}