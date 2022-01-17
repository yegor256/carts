#include "stocks.h"
#include <stdlib.h>
#include <stdio.h>


int Digitals(int begin, int end, int country, int* discounts) {
    if (begin == end) {
        return 0;
    }
    discounts[begin] = 0;
    return Digitals(begin + 1, end, country, discounts) + 1;
}

int Tangibles(int begin, int end, int country, int* discounts) {
    if (begin == end) {
        return 0;
    }
    discounts[begin] = (country == 7) ? 25 : 0;
    return Tangibles(begin + 1, end, country, discounts) + 1;
}

int PrepareDigitals(int begin, int end, int* discounts) {
    return Digitals(begin, end, 0, discounts) +
           Digitals(begin, end, 7, discounts);
}

int PrepareTangibles(int begin, int end, int* discounts) {
    return Tangibles(begin, end, 0, discounts) +
           Tangibles(begin, end, 7, discounts);
}

int DeliverDigitals(int begin, int end, int* discounts, int* requests) {
    (*requests)++;
    if (begin == end) {
        return 0;
    }
    stocks[begin].total--;
    return DeliverDigitals(begin + 1, end, discounts, requests) +
           stocks[begin].price / 2;
}

int DeliverTangibles(int begin, int end, int* discounts, int* requests) {
    (*requests)++;
    if (begin == end) {
        return 0;
    }
    stocks[begin].total--;
    return DeliverTangibles(begin + 1, end, discounts, requests) +
           stocks[begin].price * (1 - discounts[begin] / 100);
}

int Deliver(int begin, int border, int end, int* discounts, int* requests) {
    *requests += (PrepareDigitals(begin, border, discounts) +
                  PrepareTangibles(border, end, discounts));
    return DeliverDigitals(begin, border, discounts, requests) +
           DeliverTangibles(border, end, discounts, requests);
}

int Left(int begin, int end, int* requests) {
    (*requests)++;
    if (begin == end) {
        return stocks[begin].total;
    }
    return stocks[begin].total + Left(begin + 1, end, requests);
}

int main() {
    int max = sizeof(stocks) / sizeof(stocks[0]);
    int discounts[sizeof(stocks) / sizeof(stocks[0])];
    printf("There are %d items in stocks\n", max);
    int total = 0;
    int left = 0;
    int requests = 0;
    for (int r = 0; r < 1e6; ++r) {
        total += Deliver(0, max / 2, max, discounts, &requests);
        left += Left(0, max, &requests);
    }
    printf("Total charge is %d\n", total);
    printf("%d items left in carts\n", left);
    printf("There was %d requests to carts\n", requests);
    return total;
}
