#include "stocks.h"
#include <stdlib.h>
#include <stdio.h>


int Digitals(int begin, int end, int country, int* discounts) {
    if (begin == end) {
        return 0;
    } else {
        discounts[begin] = 0;
        return Digitals(begin + 1, end, country, discounts) + stocks[begin].price;
    }
}

int Tangibles(int begin, int end, int country, int* discounts) {
    if (begin == end) {
        return 0;
    } else {
        discounts[begin] = (country == 7) ? 25 : 0;
        return Tangibles(begin + 1, end, country, discounts) + stocks[begin].price;
    }
}

void PrepareDigitals(int begin, int end, int* discounts) {
    Digitals(begin, end, 0, discounts);
    Digitals(begin, end, 7, discounts);
}

int DeliverDigitals(int begin, int end, int* discounts) {
    PrepareDigitals(begin, end, discounts);

    if (begin == end) {
        return 0;
    } else {
        int tmp = DeliverDigitals(begin + 1, end, discounts) + stocks[begin].price / 2;
        return tmp;
    }
}

void PrepareTangibles(int begin, int end, int* discounts) {
    Tangibles(begin, end, 0, discounts);
    Tangibles(begin, end, 7, discounts);
}

int DeliverTangibles(int begin, int end, int* discounts) {
    PrepareTangibles(begin, end, discounts);

    if (begin == end) {
        return 0;
    } else {
        int tmp = DeliverTangibles(begin + 1, end, discounts) + stocks[begin].price * (1 - discounts[begin] / 100);

        return tmp;
    }
}

int Deliver(int begin, int border, int end, int* discounts) {
    return DeliverDigitals(begin, border, discounts) + DeliverTangibles(border, end, discounts);
}

int main() {
    int max = sizeof(stocks) / sizeof(stocks[0]);
    int discounts[sizeof(stocks) / sizeof(stocks[0])];
    printf("There are %d items in stocks\n", max);
    int total = 0;
    for (int r = 0; r < 1000000; ++r) {
        total += Deliver(0, max / 2, max, discounts);

    }
    printf("Total charge is %d\n", total);
    return total;
}
