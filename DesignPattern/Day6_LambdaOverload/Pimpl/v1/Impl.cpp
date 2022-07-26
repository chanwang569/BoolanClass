
	virtual void MyClass::invoke()
	{
		cout << "invoke" << endl;
	}

	MyClass::~Impl(){
		cout<<"Impl dtor"<<endl;
	}

    MyClass::Impl(){
		cout<<"Impl ctor"<<endl;
	}