

template<typename T>
typename std::enable_if<(sizeof(T) > 4)>::type foo() {

}


template<typename T>
std::enable_if_t<(sizeof(T) > 4)>
foo() {
}

//使用别名
template<typename T>
using EnableIfSizeGreater4 = std::enable_if_t<(sizeof(T) > 4)>;

template<typename T, typename = EnableIfSizeGreater4<T>>
void foo() {
}

//如果评估为false，构造函数不生成
template<typename STR,
typename = std::enable_if_t<std::is_convertible_v<STR, std::string>>>
Person(STR&& n);