#include <ctime>
#include <iostream>
#include <random>
#ifdef __cplusplus
#endif

int main(void) {
    using namespace std;
    default_random_engine engine;
    engine.seed(time(nullptr));
    uniform_int<unsigned short> ran(0, 99);
    cout << ran(engine);
    return 0;
}