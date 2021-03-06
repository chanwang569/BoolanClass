class Messager{
public:
    //业务抽象
    virtual void Login(string username, string password)=0;
    virtual void SendMessage(string message)=0;
    virtual void SendPicture(Image image)=0;

    //平台实现
    virtual void PlaySound()=0;
    virtual void DrawShape()=0;
    virtual void WriteText()=0;
    virtual void Connect()=0;
    virtual ~Messager(){}

    
};






//平台实现
class PCMessagerBase : public Messager{
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

class MobileMessagerBase : public Messager{
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
class PCMessagerLite : public PCMessagerBase {
public:
    void Login(string username, string password) override{
        
        PCMessagerBase::Connect();
        //........
    }
    void SendMessage(string message) override{
        
        PCMessagerBase::WriteText();
        //........
    }
    void SendPicture(Image image) override{
        
        PCMessagerBase::DrawShape();
        //........
    }
};


class PCMessagerBusiness : public PCMessagerBase {
public:
    
    void Login(string username, string password) override{
        
        PCMessagerBase::PlaySound();
        //********
        PCMessagerBase::Connect();
        //........
    }
    void SendMessage(string message) override{
        
        PCMessagerBase::PlaySound();
        //********
        PCMessagerBase::WriteText();
        //........
    }
    void SendPicture(Image image) override{
        
        PCMessagerBase::PlaySound();
        //********
        PCMessagerBase::DrawShape();
        //........
    }
};


class MobileMessagerLite : public MobileMessagerBase {
public:
    
    void Login(string username, string password) override{
        
        MobileMessagerBase::Connect();
        //........
    }
    void SendMessage(string message) override{
        
        MobileMessagerBase::WriteText();
        //........
    }
    void SendPicture(Image image) override{
        
        MobileMessagerBase::DrawShape();
        //........
    }
};


class MobileMessagerBusiness : public MobileMessagerBase {
public:
    
    void Login(string username, string password) override{
        
        MobileMessagerBase::PlaySound();
        //********
        MobileMessagerBase::Connect();
        //........
    }
    void SendMessage(string message) override{
        
        MobileMessagerBase::PlaySound();
        //********
        MobileMessagerBase::WriteText();
        //........
    }
    void SendPicture(Image image) override{
        
        MobileMessagerBase::PlaySound();
        //********
        MobileMessagerBase::DrawShape();
        //........
    }
};

//PC, Mobile... 平台实现 m
//Business, Lite... 业务抽象 n
// 1+m+ m*n 

void Process(){
        //编译时装配
        Messager *m =
            new MobileMessagerBusiness();

        delete m;
}


