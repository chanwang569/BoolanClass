//业务操作

//Note: 多个变化方向的例子
class Stream{
   
public：
    virtual char Read(int number)=0;
    virtual void Seek(int position)=0;
    virtual void Write(char data)=0;
    virtual ~Stream(){}
};


//1+ m+n , 1+5+5= 11


//主体类
class FileStream: public Stream{
public:
    char Read(int number) override {
        //读文件流
    }
    void Seek(int position) override{
        //定位文件流
    }
     void Write(char data) override{
        //写文件流
    }

};

class NetworkStream :public Stream{
public:
     char Read(int number) override{
        //读网络流
    }
     void Seek(int position) override{
        //定位网络流
    }
     void Write(char data) override{
        //写网络流
    }
    
};

class MemoryStream :public Stream{
public:
     char Read(int number) override{
        //读内存流
    }
     void Seek(int position) override{
        //定位内存流
    }
     void Write(char data) override{
        //写内存流
    }
    
};


class DecoratorStream: public Stream{ //继承-接口规范
protected:
    //组合-复用实现
     unique_ptr<Stream> s;// =new FileSream, new Networkstream, ...
     DecoratorStream(unique_ptr<Stream> _s):s(std::move(_s))
     {

     }
};

//扩展操作
class CryptoStream: public DecoratorStream {

public:
  
     char Read(int number) override{
       
        //额外的加密操作...

        s->Read(number);//读文件流
        
        //额外的加密操作...
    }
     void Seek(int position) override{
        //额外的加密操作...
        s->Seek(position);//定位文件流
        //额外的加密操作...
    }
     void Write(byte data)override{
        //额外的加密操作...
        
        s->Write(data);//写文件流
        //额外的加密操作...
    }
};

class BufferedStream: public DecoratorStream {
  

     char Read(int number) override{
       
        //额外的操作...

        s->Read(number);//读文件流
        
        //额外的操作...

    }
     void Seek(int position) override{
        //额外的操作...
        s->Seek(position);//定位文件流
        //额外的操作...
    }
     void Write(byte data)override{
        //额外的操作...
        
        s->Write(data);//写文件流
        //额外的操作...
    }
};


void Process(){

    //编译时装配
    //CryptoFileStream *fs1 = new CryptoFileStream();

    //BufferedFileStream *fs2 = new BufferedFileStream();

    //CryptoBufferedFileStream *fs3 =new CryptoBufferedFileStream();

    unique_ptr<Stream> ps=make_unique<FileSteam>();
    unique_ptr<CryptoStream> cs=make_unique<CryptoStream>(ps);
    unique_ptr<BufferedStream> bcs=make_unique<CryptoStream>(cs);

}