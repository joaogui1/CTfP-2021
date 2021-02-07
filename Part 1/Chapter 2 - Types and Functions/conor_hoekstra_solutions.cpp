// https://www.godbolt.org/z/G8WzE4

#include <map>
#include <chrono>
#include <iostream>

// Challenge 1

auto memoize(auto fn) {
    return [done = std::map<int,int>{}, fn](auto n) mutable  {
        if (auto it = done.find(n); it != done.end())
            return it->second;
        auto const val = fn(n);
        done[n] = val;
        return val;
    };
}

// Challenge 2
// rand is not a pure function so it definitely won't work

// Challenge 3
// https://en.wikipedia.org/wiki/Linear_congruential_generator

struct lcg {
    auto operator()(int seed) {
        return (seed * 8121 + 28411) % 134456;
    }
};

// Challenge 4
// 1) factorial is pure
// 2) getchar is not pure
// 3) f is not pure
// 4) f is not pure

// Challenge 5

auto same_(bool b) -> bool { return b;     }
auto diff_(bool b) -> bool { return !b;    }
auto true_(bool b) -> bool { return true;  }
auto fals_(bool b) -> bool { return false; }

// Challenge 6

// ¯\_(ツ)_/¯


// Fib
int fib(int n){
    if(n < 2)   return 1;
    return fib(n - 1) + fib(n - 2);
}

auto main() -> int {

    auto plus1_memo = memoize([](auto e) { return e + 1; });

    std::cout << plus1_memo(1) << "\n";
    std::cout << plus1_memo(2) << "\n";
    std::cout << plus1_memo(1) << "\n";

    auto lcg_memo = memoize(lcg{});

    std::cout << lcg_memo(1) << "\n"; // 36532
    std::cout << lcg_memo(1) << "\n"; // 36532
    std::cout << lcg_memo(2) << "\n"; // 44653

    auto f = memoize(fib);
    auto t1 = std::chrono::high_resolution_clock::now();
    f(30);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << duration << "\n";
    
    t1 = std::chrono::high_resolution_clock::now();
    f(30);
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << duration << "\n";

    t1 = std::chrono::high_resolution_clock::now();
    f(31);
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << duration << "\n";
    return 0;
}
