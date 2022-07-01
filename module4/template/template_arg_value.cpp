#include <iostream>
#include <array>
using namespace std;

template <typename T=int, long Size=10> 
class Array {
private:
	T* ptr;

public:
    Array(){}
	Array(T arr[]);
	void print();
};

template <typename T, size_t Size> 
Array<T,Size>::Array(T arr[])
{
	ptr = new T[Size];
	for (int i = 0; i < Size; i++)
		ptr[i] = arr[i];
}

template <typename T, size_t Size> 
void Array<T,Size>::print()
{
	for (int i = 0; i < Size; i++)
		cout << " " << *(ptr + i);
	cout << endl;
}


int main()
{

	int arr[5] = { 1, 2, 3, 4, 5 };

	Array<> arrInt{arr};
	arrInt.print();


}
