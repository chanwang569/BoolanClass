export module Square; // 声明模块

export class Square {
private:
    int value;
public:
    Square(int i): value{i*i} {
    }
    int getValue() const {
        return value;
    }
};

export template<typename T>
Square toSquare(const T& x) {
    return Square{x};
}

