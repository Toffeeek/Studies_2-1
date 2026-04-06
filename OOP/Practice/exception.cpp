#include <iostream>
using namespace std;

class BaseException {
public:
    virtual const char* message() const {
        return "Base exception";
    }

    virtual ~BaseException() = default;
};

class FileException : public BaseException {
public:
    const char* message() const override {
        return "File exception";
    }
};

class NetworkException : public BaseException {
public:
    const char* message() const override {
        return "Network exception";
    }
};

int main() {
    try {
        throw NetworkException();
    }
    catch (const BaseException& e) {
        cout << e.message() << endl;
    }
}