//Note V3: 继续增加OracleDBFactory的实现，用来封装一组 Connection， Command，DataReader的组合
//数据库访问有关的基类
class IDBConnection{   
};
class IDBCommand{   
};
class IDataReader{  
};



class IDBFactory{   //系列工厂
public:
    virtual shared_ptr<IDBConnetion> CreateDBConnection()=0;
    virtual shared_ptr<IDBCommand> CreacteDBCommand()=0;
    virtual shared_ptr<IDataReader> CreateDataReader()=0;
    

};


//支持My SQL
class SqlConnection: public IDBConnection{
    
};
class SqlCommand: public IDBCommand{
    
};
class SqlDataReader: public IDataReader{
    
};


class SqlDBFactory:public IDBFactory{
public:
    shared_ptr<IDBConnection> CreateDBConnection() override
    {

    }

    shared_ptr<IDBCommand> CreateDBCommand() override
    {

    }

    shared_ptr<IDataReader> CreateDataReader() override
    {

    }   
 
};

//支持Oracle
class OracleConnection: public IDBConnection{
    
};

class OracleCommand: public IDBCommand{
    
};

class OracleDataReader: public IDataReader{
    
};

class OracleDBFactory:public IDBFactory{
public:
    shared_ptr<IDBConnection> CreateDBConnection() override
    {

    }

    shared_ptr<IDBCommand> CreateDBCommand() override
    {

    }

    shared_ptr<IDataReader> CreateDataReader() override
    {

    }   
 
};



class EmployeeDAO{
    unique_ptr<IDBFactory> dbFactory;// SqlDBFactory, OracleDBFactory...
    
public:

    EmployeeDAO(unique_ptr<IDBFactory> dbFactory):dbFactory(std:move(dbFactory))
    {
        
    }


    vector<EmployeeDO> GetEmployees(){
        shared_ptr<IDBConnection> connection =
            dbFactory->CreateDBConnection();
        connection->ConnectionString("...");

        shared_ptr<IDBCommand> command =
            dbFactory->CreateDBCommand();
        command->CommandText("...");
        command->SetConnection(connection); //关联性

        shared_ptr<IDBDataReader> reader =
         command->ExecuteReader(); //关联性
        while (reader->Read()){

        }

    }
};
