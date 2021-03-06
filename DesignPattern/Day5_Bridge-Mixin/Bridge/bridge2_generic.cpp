#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>
using namespace std;

/*
template<typename T>
concept MessagerImp = requires(T obj) {
    obj.PlaySound();
    obj.DrawShape();
    obj.WriteText();
    obj.Connect();
};
*/

template<typename Imp>
class Messager: public Imp
{
public:
     virtual void Login(string username, string password)=0;
     virtual void SendMessage(string message)=0;
     virtual void SendPicture(String image)=0;

};

class PCMessager {
public:
    
    void PlaySound() {
        //**********
    }
    void DrawShape() {
        //**********
    }
    void WriteText() {
        //**********
    }
    void Connect() {
        //**********
    }
};

class MobileMessager {
public:
    
    void PlaySound() {
        //==========
    }
    void DrawShape() {
        //==========
    }
    void WriteText() {
        //==========
    }
    void Connect() {
        //==========
    }
};

//业务抽象
template<typename Imp>
class MessagerLite : public Messager<Imp>{
public:
    
    void Login(string username, string password) override{
        
        Imp::Connect();
        //........
    }
    void SendMessage(string message) override{
        
        Imp::WriteText();
        //........
    }
    void SendPicture(String image) override{
        
        Imp::DrawShape();
        //........
    }
};


template<typename Imp>
class MessagerPerfect : public Messager<Imp>{
 
public:

    void Login(string username, string password) override{
        Imp::PlaySound();
        //********
        Imp::Connect();
        //........
    }
    void SendMessage(string message) override{
        
        Imp::PlaySound();
        //********
        Imp::WriteText();
        //........
    }
    void SendPicture(String image) override{
        
        Imp::PlaySound();
        //********
        Imp::DrawShape();
        //........
    }
};



int main(){
        //编译时装配;

        MessagerPerfect<PCMessager> mp;

        mp.Login();
}


