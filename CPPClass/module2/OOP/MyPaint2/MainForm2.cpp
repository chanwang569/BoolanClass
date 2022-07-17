class MainForm : public Form {
private:
	Point p1;
	Point p2;

	//std::vector<Shape> shapes;
	std::vector<Shape*> shapes;
	//std::vector<std::unique_ptr<Shape>> shapes;
	
	//std::unique_ptr<ShapeFactory> shapeFactory;
	//std::unique_ptr<Shape> prototype;

public:
	MainForm(){
		//...
		
		prototype=...
	}
protected:

	void MainForm::OnMouseDown(const MouseEventArgs& e) override {
		p1.x = e.X;
		p1.y = e.Y;

		//...
		Form::OnMouseDown(e);
	}

	void MainForm::OnMouseUp(const MouseEventArgs& e) override {
		p2.x = e.X;
		p2.y = e.Y;
		
		//...

		shapes->push_back(new Line(...));

		shapes->push_back(new Rect(...));

		


		//...
		this->Refresh();

		Form::OnMouseUp(e);
	}

	void MainForm::OnPaint(const PaintEventArgs& e) override {

		for ( auto& shape : shapes){
			shape->Draw(e.Graphics); //虚函数调用-->多态


		}

		Form::OnPaint(e);
	}
};
