#include <stdio.h>
#include <stdlib.h>

#define STOCKS_TOTAL 100

struct stock { int price; int total; };
stock stocks[STOCKS_TOTAL];

/**
 * A abstract shippable item in the stock.
 */
class Item {
    /**
     * Make a new item prepared to be delivered to this country.
     * @param country Country code, like 'US' or 'RU'
     * @return New item, reconfigured
     */
    virtual Item* prepare(char country[2]) = 0;
    /**
     * Deliver this item to the customer and return the total
     * amount of money to charge for it.
     * @return The price the customer has to pay
     */
    virtual int deliver() = 0;
};

class Stocked : public Item {
public:
    Stocked(stock* s) : stk(s) {};
    virtual int deliver() override {
        this->stk->total--;
        return this->stk->price;
    }
private:
    stock* stk;
};

class Digital : public Stocked {
public:
    Digital(Stocked s) : Stocked(s) {};
    virtual int deliver() override {
        return Stocked::deliver() / 2;
    }
};

class Tangible : public Stocked {
public:
    Tangible(Stocked s) : Tangible(s, 0) {};
    Item* prepare(char country[2]) {
        if (country[0] != 'U' || country[1] != 'S') {
            return new Tangible(*this, 10);
        }
        return new Tangible(*this);
    }
    int deliver() {
        return Stocked::deliver() * (1 - this->discount / 100);
    }
private:
    Tangible(Stocked s, int d) : Stocked(s), discount(d) {};
    int discount;
};

class Cart {
    virtual Cart* add(Item i) = 0;
    virtual Cart* recalc(int zip) = 0;
    virtual int deliver() = 0;
};

class FullCart;

class EmptyCart : public Cart {
    virtual Cart* add(Item i) {
        return FullCart(*this, i);
    }
    virtual Cart* recalc(int zip) {
        return this;
    }
    virtual int deliver() {
        return 0;
    }
};

class FullCart : public Cart {
public:
    FullCart(Cart* c, Item* i) : before(c), item(i) {};
    virtual Cart* add(Item i) {
        return FullCart(*this, i);
    }
    virtual Cart* recalc(int zip) {
        return FullCart(this->before, this->item.discount(d));
    }
    int deliver() {
        return this->before.deliver() + this->item.deliver();
    }
private:
    Cart* before;
    Item* item;
};

class EmptyCart : public Cart {
public:
    EmptyCart() {};
};

int main() {
    Cart cart = Cart();
    for (int i = 0; i < 10; ++i) {
        int pos = ITEMS_TOTAL * rand() / RAND_MAX;
        Item item = Item(&items[pos]);
        cart = cart.add(item);
    }
    cart = cart.shipTo(1);
    int total = cart.deliver();
    printf("Total: %d\n", total);
}
