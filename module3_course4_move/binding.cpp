TVec createTVec(); 
TVec vt1;

vt1 = createTVec(); // 右值源 : 移动OK

TVec vt2(createTVec()); // 右值源 : 移动OK, 但返回值优化会优化掉）


vt1 = vt2; // 左值源: 需要拷贝
TVec vt3(vt2); // 左值源: 需要拷贝

std::size_t f(std::string str); 

std::string s("C++11");
f(s); // 左值源: 需要拷贝


void f1(const TVec&); 	// const 左值引用
const TVec vt;

f1(vt); 				// OK 
f1(createTVec()); 		// OK

void f2(const TVec&); 	// #1: const 左值引用
void f2(TVec&&); 		// #2: non-const 右值引用

f2(vt); 				// 左值 ⇒ #1
f2(createTVec()); 		// 都可以, 优先 ⇒ #2

void f3(const TVec&&); 	// #1: const 右值引用
void f3(TVec&&); 		// #2: non-const 右值引用

f3(vt); 				// 错误， 左值
f3(createTVec()); 		// 都可以, 优先 ⇒ #2
