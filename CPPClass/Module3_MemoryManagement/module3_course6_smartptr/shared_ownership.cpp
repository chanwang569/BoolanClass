// 推荐，常用：成为共享所有权之一
void share(shared_ptr<widget>); 

// 推荐，常用：可能保留引用计数 
void may_share(const shared_ptr<widget>&); 

// 可行，不常用：打算重新指向别的对象
void reseat(shared_ptr<widget>&);
