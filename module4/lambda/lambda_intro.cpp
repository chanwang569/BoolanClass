
#include <iostream>

using namespace std;


void print(vector<int> v)
{
	for_each(v.begin(), v.end(), [](int i)
        {
            std::cout << i << " ";
        });
	cout << endl;
}

int main()
{
	vector<int> v {8,4,5,10,2,11,18};

	print(v);

	
	auto p = find_if(v.begin(), v.end(), 
                [](int i){return i > 10;});
	
	sort(v.begin(), v.end(), 
        [](const int& a, const int& b) -> bool { return a > b;});

	print(v);


	int number = count_if(v.begin(), v.end(), 
        [](int a){ return (a >= 7);});
	cout << number << endl;


}
