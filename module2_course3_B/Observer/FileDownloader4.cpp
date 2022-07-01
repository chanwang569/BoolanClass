class IProgress{
public:
	virtual void DoProgress(float value)=0;
	virtual ~IProgress(){}
};


class Subject
{
private:
	list<shared_ptr<IProgress>>  m_iprogressList;//共享引用

	//list<weak_ptr<IProgress>> m_iprogressList;//弱引用

public:
	void addIProgress(const shared_ptr<IProgress>& iprogress){
		m_iprogressList.push_back(iprogress);
	}
	void removeIProgress(const shared_ptr<IProgress>& iprogress){
		m_iprogressList.remove(iprogress);
	}

protected:
	virtual void onProgress(float value)  
	{
		for (auto& progress : m_iprogressList){
			progress->DoProgress(value);



			/* 弱引用检查生命周期是否存在？
			auto s_progress=progress.lock();
			if ( s_progress ) {
                s_progress->notify();
            }*/ 
		}
	}
};


class FileDownloader: public Subject
{
	string m_filePath;
	int m_fileNumber;

public:
	FileDownloader(const string& filePath, int fileNumber) :
		m_filePath(filePath), 
		m_fileNumber(fileNumber){

	}
	void download(){
		//1.下载动作

		//2.设置进度
		for (int i = 0; i < m_fileNumber; i++){
			//...
			float progressValue = m_fileNumber;
			progressValue = (i + 1) / progressValue;
			Subject::onProgress(progressValue);
		}

	}
};