
#include <cstdlib>
#include <iostream>
#include <stack>

using namespace std;



template <typename F>
class ScopeGuard
{
public:
    explicit ScopeGuard(F&& f) : m_func(std::move(f)), m_dismiss(false)
    {

    }

    explicit ScopeGuard(const F& f) : m_func(f), m_dismiss(false){}

    ~ScopeGuard()
    {
        if (!m_dismiss)
            m_func();
    }

    ScopeGuard(ScopeGuard && rhs) : 
        m_func(std::move(rhs.m_func)), m_dismiss(rhs.m_dismiss){
            rhs.dismiss();
    }

    ScopeGuard()=delete;
    ScopeGuard(const ScopeGuard&)=delete;
    ScopeGuard& operator=(const ScopeGuard&)=delete;


    void dismiss()
    {
        m_dismiss = true;
    }

private:
    F m_func;
    bool m_dismiss;

};





void FileProcess()
{

    FILE* fp = fopen("filename", "wb");
    ScopeGuard scopeGuard(  [&]() { fclose(fp); }   );


    // 文件处理....


    //关闭文件
    //fclose(fp);
}




void invoke(int data)
{
        if(data<0)
        {
            invalid_argument exp("data");
            throw exp;
        }
}

void process()
{
    {
        stack<string> cityStack;

        cityStack.push("Shanghai"s);
        ScopeGuard scopeGuard{ [&]{ 
            string s=cityStack.top();
            cityStack.pop(); 
            cout<<"roll back: "<<s<<endl;
            }
        };
  
        cout<<"invoke..."<<endl;
        invoke(100);

        scopeGuard.dismiss();
    }
    
}



int main(){

    try {

        process();

         
   } catch(invalid_argument& e) {
       cerr<<"invalid arg: " << e.what()<<endl;
   }
  
}

