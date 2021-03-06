class Messager{
protected:
    unique_ptr<MessagerImp> pmb;//=new PCMessager(); MobileMessager();
public:

    Messager(unique_ptr<MessagerImp> _pmb):pmb(std::move(_pmb))
    {

    }

    virtual void Login(string username, string password)=0;
    virtual void SendMessage(string message)=0;
    virtual void SendPicture(Image image)=0;

    virtual ~Messager(){}
}

class MessagerImp {
public:
    virtual void PlaySound()=0;
    virtual void DrawShape()=0;
    virtual void WriteText()=0;
    virtual void Connect()=0;
    
    virtual ~MessagerImp(){}
};

// 1+1+m+n = 1+1+10+6= 18


//平台实现
class PCMessager : public MessagerImp{
public:
    
    void PlaySound() override{
        //**********
    }
    void DrawShape() override{
        //**********
    }
    void WriteText() override{
        //**********
    }
    void Connect() override{
        //**********
    }
};

class MobileMessager : public MessagerImp{
public:
    
    void PlaySound() override{
        //==========
    }
    void DrawShape() override{
        //==========
    }
    void WriteText() override{
        //==========
    }
    void Connect() override{
        //==========
    }
};



//业务抽象
class MessagerLite : public  Messager{

public:
    
    void Login(string username, string password) override{
        
        pmb->Connect();
        //........
    }
    void SendMessage(string message) override{
        
        pmb->WriteText();
        //........
    }
    void SendPicture(Image image) override{
        
        pmb->DrawShape();
        //........
    }
};



class MessagerPerfect :public  Messager {
 
public:
    
    void Login(string username, string password) override{
        
        pmb->PlaySound();
        //********
        pmb->Connect();
        //........
    }
    void SendMessage(string message) override{
        
        pmb->PlaySound();
        //********
        pmb->WriteText();
        //........
    }
    void SendPicture(Image image) override{
        
        pmb->PlaySound();
        //********
        pmb->DrawShape();
        //........
    }
};





void Process(){
        //运行时装配
        unique_ptr<MessagerImp> pMImp= std::make_unique<MobileMessager>();

        unique_ptr<Messager> pM= std::make_unique<MessagerPerfect>(pMImp);

       
}


