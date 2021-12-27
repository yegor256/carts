#include "stocks.h"
#include <stdlib.h>

enum ItemType {
    Stoked,
    Digital,
    Tangible
};

struct Item {
    struct stock stk;
    int discount;
    enum ItemType type;
};

int PrepareItem(int country, struct Item* item, struct Item* result) {
    if (item->type == Tangible) {
        result = (struct Item*) malloc(sizeof (struct Item));

        result->discount = (item->discount == 7) ? 25 : item->discount;
        result->stk = item->stk;
        result->type = item->type;
    } else {
        result = item;
    }
    return 0;
}

int DeliverItem(struct Item* item, int* result) {
    item->stk.total--;
    int tmp = item->stk.price;
    if (item->type == Digital) {
        tmp /= 2;
    }
    if (item->type == Tangible) {
        tmp *= (1 - item->discount / 100);
    }
    *result += tmp;
    return 0;
}

struct Cart {
    struct Cart* before;
    struct Item item;
    short empty;
};

int CartAdd(struct Cart* cart, struct Item* item, struct Cart* new) {
    new = (struct Cart*) malloc(sizeof(struct Cart));
    new->item = *item;
    new->before = cart;

    return 0;
}

int CartRecalc(struct Cart* cart, int country, struct Cart* res) {
    if (cart->empty) {
        res = cart;
        return 0;
    } else {
        res = (struct Cart*) malloc(sizeof(struct Cart));
        CartRecalc(cart->before, country, res->before);
        PrepareItem(country, &cart->item, &res->item);
    }
    return 0;
}

int CartDeliver(struct Cart* cart, int* result) {
    if (cart->empty) {
        *result += 0;
    } else {
        CartDeliver(cart->before, result);
        DeliverItem(&cart->item, result);
    }
    return 0;
}

int DeleteCart(struct Cart* cart) {
    if (!cart->empty) {
        free((void*)&cart->item);
        DeleteCart(cart->before);
        free((void*)cart->before);
    }
    return 0;
}


int main() {
    int max = sizeof(stocks) / sizeof(stocks[0]);
    int total = 0;
    for (int r = 0; r < 1000000; ++r) {
        struct Cart *cart = (struct Cart*)malloc(sizeof(struct Cart));
        cart->empty = 1;
        for (int i = 0; i < max / 2; ++i) {
            struct Item *item = (struct Item*)malloc(sizeof(struct Item));
            item->type = Digital;
            item->stk = stocks[i];
            CartAdd(cart, item, cart);
        }
        for (int i = max / 2; i < max; ++i) {
            struct Item *item = (struct Item*)malloc(sizeof(struct Item));
            item->type = Tangible;
            item->stk = stocks[i];
            item->discount = 0;
            CartAdd(cart, item, cart);
        }
        CartRecalc(cart, 7, cart);
        CartDeliver(cart, &total);
        DeleteCart(cart);
    }
    return total;
}
