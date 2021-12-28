It's a simple algorithm implemented in C++ with intentionally heavy
usages of classes, inheritance, encapsulation, and polymorphism.

There is a stock of items with prices and total amounts. There is a shopping
cart, where some of the items are placed. Then, the cart is recalculated
with an intent of delivery to certain territory. Some items get a discount.
Then, the cart is sent to the customer and the total price of it is calculated.

To run it, just do:

```bash
$ make
$ ./bin/objects.a
```

To run inside Docker (here `-m=10M` allows the container to use only 10Mb of memory):

```bash
$ docker build . --tag=carts
$ docker run -it -m=10M carts
```

If you want to step into Docker container and run the app manually, do this:

```bash
$ docker run -it --entrypoint=/bin/bash carts
```

