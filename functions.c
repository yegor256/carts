#include "stocks.h"
#include <stdlib.h>
#include <stdio.h>

int discounts[sizeof(stocks) / sizeof(stocks[0])];


int Digitals(int begin, int end, int country) {
    if (begin == end) {
        return 0;
    } else {
        discounts[begin] = 0;
        return Digitals(begin + 1, end, country) + stocks[begin].price;
    }
}

int Tangibles(int begin, int end, int country) {
    if (begin == end) {
        return 0;
    } else {
        discounts[begin] = (country == 7) ? 25 : 0;
        return Tangibles(begin + 1, end, country) + stocks[begin].price;
    }
}

int DeliverDigitals(int begin, int end) {
    if (begin == end) {
        return 0;
    } else {
        return DeliverDigitals(begin + 1, end) + stocks[begin].price / 2;
    }
}

int DeliverTangibles(int begin, int end) {
    if (begin == end) {
        return 0;
    } else {
        return DeliverTangibles(begin + 1, end) + stocks[begin].price * (1 - discounts[begin] / 100);
    }
}

int main() {
    const int max = sizeof(stocks) / sizeof(stocks[0]);

    int total = 0;
    for (int r = 0; r < 1000000; ++r) {
        int digitals = Digitals(0, max / 2, 0);
        int tangibles = Tangibles(max / 2, max, 0);

        digitals = Digitals(0, max / 2, 7);
        tangibles = Tangibles(max / 2, max, 7);

        total += DeliverDigitals(0, max / 2);
        total += DeliverTangibles(max / 2, max);
    }
    printf("%d\n", total);
    return total;
}
