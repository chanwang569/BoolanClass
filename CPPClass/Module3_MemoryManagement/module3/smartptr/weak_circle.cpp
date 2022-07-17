class foo {
    public:
    explicit foo(const shared_ptr<bar>& front): front_(front) { }
    private:
    shared_ptr<bar> front_;
};

class bar {
public:
    explicit bar(const weak_ptr<foo>& back): back_(back) { }
    void do_something() {
    if (shared_ptr<foo> shared_back = back_.lock()) {
        // 使用 *shared_back
    }
    }
private:
    weak_ptr<foo> back_;
};

