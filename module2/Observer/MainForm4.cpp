class MainForm : public Form, public IProgress
{
	shared_ptr<TextBox> txtFilePath;
	shared_ptr<TextBox> txtFileNumber;
	shared_ptr<ProgressBar> progressBar;

	

public:
	void Button1_Click(){

		string filePath = txtFilePath->getText();
		int number = atoi(txtFileNumber->getText().c_str());

		shared_ptr<IProgress> ip=make_shared<ConsoleNotifier>();


		FileDownloader downloader(filePath, number);

		downloader.addIProgress(ip); 

		downloader.download();

		splitter.removeIProgress(ip);

	}

	void DoProgress(float value) override {
		progressBar->setValue(value);
	}
};

class ConsoleNotifier : public IProgress {
public:
	void DoProgress(float value) override{
		cout << ".";
	}
};

