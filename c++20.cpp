#include <map>
#include <iostream>


int main() {
    std::map mp = {{1, 2}, {2, 3}, {3, 4}};
    for(auto& [k, v] : mp) {
        std::cout << k << ", " << v << '\n';
    }
    return 0;
}
