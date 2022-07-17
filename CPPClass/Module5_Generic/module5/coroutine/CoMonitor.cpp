#include <concepts>
#include <exception>
#include <iostream>

#include <experimental/coroutine>

using namespace std;
using namespace experimental;


class CoTask {
 public:
 
  struct promise_type;
  using CoHandle = coroutine_handle<promise_type>;
  CoHandle hdl;          


  struct promise_type {
    promise_type() {
      cout << "       promise: constructor\n";
    }
    auto get_return_object() {       
      cout << "       promise: get_return_object()\n";
      return CoTask{CoHandle::from_promise(*this)};
    }
    auto initial_suspend() {     
      cout << "       promise: initial_suspend()\n";
      return suspend_always{}; 
    }
    void unhandled_exception() {     
      cout << "       promise: unhandled_exception()\n";
      terminate();         
    }
    void return_void() {      
      cout << "       promise: return_void()\n";
    }
    auto final_suspend() noexcept {  
      cout << "       promise: final_suspend()\n";
      return suspend_always{};  
    }
  };

  CoTask(auto h)
   : hdl{h} {          
      cout << "         CoTask: construct\n";
  }
  ~CoTask() {
    cout << "         CoTask: destruct\n";
    if (hdl) {
      hdl.destroy();   
    }
  }

  CoTask(const CoTask&) = delete;
  CoTask& operator=(const CoTask&) = delete;

  CoTask(CoTask&& c) noexcept
    : hdl{move(c.hdl)} {
    c.hdl = nullptr;
  }

  CoTask& operator=(CoTask&& c) noexcept {
    if (this == &c)
    {
      return *this;
    }

    if (hdl) {
      hdl.destroy(); 
    }
    hdl = move(c.hdl); 
    c.hdl = nullptr; 
    
    return *this;
  }
 
  bool resume()  {
    cout << "         CoTask: resume()\n";
    if (!hdl || hdl.done()) {
      return false;                     
    }
    hdl.resume();                       
    return !hdl.done();
  }
};

class Awaiter {
  inline static int maxId = 0;
  int id;
 public:
  Awaiter() : id{++maxId} {
    cout << "        Awaiter" << id << ": ==> constructor\n";
  }
  ~Awaiter() {
    cout << "        Awaiter" << id << ": <== destructor\n";
  }

  Awaiter(const Awaiter&) = delete;
  Awaiter& operator=(const Awaiter&) = delete;


  bool await_ready() const noexcept {
    cout << "        Awaiter" << id << ": await_ready()\n";
    return false; 
  }

 
  void await_suspend(auto) const noexcept {
    cout << "        Awaiter" << id << ": await_suspend()\n";
  }

  void await_resume() const noexcept {
    cout << "        Awaiter" << id << ": await_resume()\n";
  }
};

CoTask process(int max)
{
  cout << "  START process(" << max << ")\n";
  for (int i = 1; i <= max; ++i) {
    cout << "   process: " << i << '/' << max << '\n';

    co_await Awaiter{};               
    cout << "   process(" << max << ")\n";
  }
  cout << "  END process(" << max << ")\n";
}

int main()
{
  
  cout << "**** start process()\n";
  auto CoTask = process(3);            
  cout << "**** process() started\n";


  cout << "\n**** resume process() in loop\n";
  while (CoTask.resume()) {           // RESUME
    cout << "**** process() suspended\n";
    //...
    cout << "\n**** resume process() in loop\n";
  }

  cout << "\n**** process() loop done\n";
}

