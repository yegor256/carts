#include <cstdio>
#include <cstdlib>

#define STOCKS_TOTAL 100

struct stock { int price; int total; };
stock stocks[STOCKS_TOTAL];

/**
 * A abstract shippable item in the stock.
 */
class Item {
public:
    /**
     * Make a new item prepared to be delivered to this country.
     * @param country Country code, like 1 for 'USA' or 7 for 'Russia'
     * @return New item, reconfigured
     */
    virtual Item* prepare(int country) = 0;
    /**
     * Deliver this item to the customer and return the total
     * amount of money to charge for it.
     * @return The price the customer has to pay
     */
    virtual int deliver() = 0;
};

class Stocked : public Item {
public:
    explicit Stocked(stock* s) : stk(s) {};
    Item* prepare(int country) override {
        return this;
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
    explicit Digital(Stocked* s) : Stocked(*s) {};
    int deliver() override {
        return Stocked::deliver() / 2;
    }
};

class Tangible : public Stocked {
public:
    explicit Tangible(Stocked* s) : Tangible(s, 0) {};
    Item* prepare(int country) override {
        if (country != 1) {
            return new Tangible(this, 10);
        }
        return new Tangible(*this);
    }
    int deliver() override {
        return Stocked::deliver() * (1 - this->discount / 100);
    }
private:
    Tangible(Stocked* s, int d) : Stocked(*s), discount(d) {};
    int discount;
};

class Cart {
public:
    virtual Cart* add(Item* i) = 0;
    virtual Cart* recalc(int country) = 0;
    virtual int deliver() = 0;
};

class FullCart : public Cart {
public:
    FullCart(Cart* c, Item* i) : before(c), item(i) {};
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
    Cart* add(Item* i) override {
        return new FullCart(this, i);
    }
    Cart* recalc(int country) override {
        return this;
    }
    int deliver() override {
        return 0;
    }
};

int main() {
    Cart* cart = new EmptyCart();
    for (int i = 0; i < 10; ++i) {
        int pos = STOCKS_TOTAL * rand() / RAND_MAX;
        Item* item = new Digital(new Stocked(&stocks[pos]));
        cart = cart->add(item);
    }
    cart = cart->recalc(1);
    int total = cart->deliver();
    printf("Total: %d\n", total);
}
