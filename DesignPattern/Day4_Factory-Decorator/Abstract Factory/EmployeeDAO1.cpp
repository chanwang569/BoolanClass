
//Note: v1. 不好的版本，GetEmployees， UpdateEmployee， DeleteEmployee 
//都要分别关心 connection, command, reader 的使用
class SqlConnection{};

class SqlCommand{};

class SqlDataReader{};


class EmployeeDAO{
public:
    vector<EmployeeDO> GetEmployees(){
        
        shared_ptr<SqlConnection> connection=  make_shared<SqlConnection>();

        connection->ConnectionString ("...");
        connection->open();

        shared_ptr<SqlCommand> command= make_shared<SqlCommand>();
        
        command->CommandText("select...");
        command->SetConnection(connection);//关联

        vector<EmployeeDO> employees;

        shared_ptr<SqlDataReader> reader = //关联
            command->ExecuteReader();
        while (reader->Read()){
            //...
        }

    }

    void UpdateEmployee()
    {

    }

    void DeleteEmployee()
    {

    }
};
