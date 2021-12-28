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

void PrepareItem(int country, struct Item* item) {
    if (item->type == Tangible) {
        item->discount = (item->discount == 7) ? 25 : item->discount;
        item->stk = item->stk;
        item->type = item->type;
    }
}

int DeliverItem(struct Item* item) {
    item->stk.total--;
    int res = item->stk.price;
    if (item->type == Digital) {
        res /= 2;
    }
    if (item->type == Tangible) {
        res *= (1 - item->discount / 100);
    }
    return res;
}

struct Cart {
    struct Cart* before;
    struct Item* item;
    short empty;
};

struct Cart* CartAdd(struct Cart* cart, struct Item* item) {
    struct Cart* new = (struct Cart*) malloc(sizeof(struct Cart));
    new->item = item;
    new->before = cart;
    new->empty = 0;
    return new;
}

void CartRecalc(struct Cart* cart, int country) {
    if (cart->empty) {
        return;
    } else {
        CartRecalc(cart->before, country);
        PrepareItem(country, cart->item);
    }
}

int CartDeliver(struct Cart* cart) {
    if (cart->empty) {
        return 0;
    } else {
        return CartDeliver(cart->before) + DeliverItem(cart->item);
    }
}

int DeleteCart(struct Cart* cart) {
    if (!cart->empty) {
        DeleteCart(cart->before);
        free((void*)cart->before);
    }
    free((void*)cart->item);
    return 0;
}
#include <stdio.h>

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
            cart = CartAdd(cart, item);
        }
        for (int i = max / 2; i < max; ++i) {
            struct Item *item = (struct Item*)malloc(sizeof(struct Item));
            item->type = Tangible;
            item->stk = stocks[i];
            item->discount = 0;
            cart = CartAdd(cart, item);
        }
        CartRecalc(cart, 7);
        total += CartDeliver(cart);
        DeleteCart(cart);
    }
    printf("%d\n", total);
    return total;
}
