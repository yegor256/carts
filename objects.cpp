#include <iostream>

#include "stocks.h"

class Item {
public:
    virtual ~Item() = default;
    virtual Item* prepare(int country) = 0;
    virtual int deliver() = 0;
};

class Stocked : public Item {
public:
    explicit Stocked(stock* s) : stk(s) {}
    Item* prepare(int country) override {
        return new Stocked(stk);
    }
    int deliver() override {
        this->stk->total--;
        return this->stk->price;
    }
private:
    stock* stk;
};

class Digital : public Stocked {
public:
    explicit Digital(stock *s) : Stocked(s) {}
    int deliver() override {
        return Stocked::deliver() / 2;
    }
};

class Tangible : public Stocked {
public:
    explicit Tangible(stock *s) : Tangible(Stocked(s), 0) {};
    Item* prepare(int country) override {
        if (country == 7) {
            return new Tangible(*this, 25);
        }
        return new Tangible(*this, 0);
    }
    int deliver() override {
        return Stocked::deliver() * (1 - this->discount / 100);
    }
private:
    Tangible(const Stocked &s, int d) : Stocked(s), discount(d) {};
    int discount;
};

class Cart {
public:
    virtual ~Cart() = default;
    virtual Cart* add(Item* i) = 0;
    virtual Cart* recalc(int country) = 0;
    virtual int deliver() = 0;
};

class FullCart : public Cart {
public:
    FullCart(Cart* c, Item* i) : before(c), item(i) {}
    ~FullCart() override {
        delete this->before;
        delete this->item;
    }
    Cart* add(Item* i) override {
        return new FullCart(this, i);
    }
    Cart* recalc(int country) override {
        return new FullCart(
            this->before->recalc(country),
            this->item->prepare(country)
        );
    }
    int deliver() override {
        return this->before->deliver() + this->item->deliver();
    }
private:
    Cart* before;
    Item* item;
};

class EmptyCart : public Cart {
public:
    Cart* add(Item* i) override {
        return new FullCart(this, i);
    }
    Cart* recalc(int country) override {
        return new EmptyCart();
    }
    int deliver() override {
        return 0;
    }
};

int main() {
    int max = sizeof(stocks) / sizeof(stocks[0]);
    std::cout << "There are " << max << " items in stocks\n";
    int total = 0;
    for (int r = 0; r < 1000000; ++r) {
        Cart* cart = new EmptyCart();
        for (int i = 0; i < max / 2; ++i) {
            Item *item = new Digital(&stocks[i]);
            cart = cart->add(item);
        }
        for (int i = max / 2; i < max; ++i) {
            Item *item = new Tangible(&stocks[i]);
            cart = cart->add(item);
        }
        Cart *re = cart->recalc(7);
        total += re->deliver();
        delete cart;
        delete re;
    }
    std::cout << "Total charge is " << total << "\n";
    return total;
}
