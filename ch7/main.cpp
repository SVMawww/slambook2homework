#include <iostream>
#include <vector>

struct X{
    X() { puts("X()"); }
    X(const X&) { puts("X(const X&)"); }
    X(X&&)noexcept { puts("X(X&&)"); }
    ~X() {puts("~X()");}
};

X func(){
    X x;
    puts("-----------");
    return x;
}

int main(){
    auto result = func();
}

