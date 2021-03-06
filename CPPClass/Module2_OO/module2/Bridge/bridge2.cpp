class Messager{
protected:
    MessagerImp* m_pmi;//动态多态

public:

    Messager(MessagerImp* pmi):m_pmi(pmi)
    {
    }
    virtual void Login(string username, string password)=0;
    virtual void SendMessage(string message)=0;
    virtual void SendPicture(Image image)=0;

    virtual ~Messager(){}
}

class MessagerImp {
    virtual void PlaySound()=0;
    virtual void DrawShape()=0;
    virtual void WriteText()=0;
    virtual void Connect()=0;
    
    virtual ~MessagerImp(){}
};


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
        
        m_pmi->Connect();
        //........
    }
    void SendMessage(string message) override{
        
        m_pmi->WriteText();
        //........
    }
    void SendPicture(Image image) override{
        
        m_pmi->DrawShape();
        //........
    }
};



class MessagerBusiness :public  Messager {
 
public:
    
    void Login(string username, string password) override{
        
        m_pmi->PlaySound();
        //********
        m_pmi->Connect();
        //........
    }
    void SendMessage(string message) override{
        
        m_pmi->PlaySound();
        //********
        m_pmi->WriteText();
        //........
    }
    void SendPicture(Image image) override{
        
        m_pmi->PlaySound();
        //********
        m_pmi->DrawShape();
        //........
    }
};


//PC, Mobile... 平台实现 m
//Business, Lite... 业务抽象 n
// 1+m+n=11 

void Process(){

        //运行时装配
        MessagerImp* pmi=new MobileMessager();
        MessagerBusiness mb(pmi);

        mb.SendMessage();

        delete pmi;
       
       
}


