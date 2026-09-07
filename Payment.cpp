#ifndef PAYMENT_CPP
#define PAYMENT_CPP

class Payment {
protected:
    double amount;

public:
    virtual bool pay(double amount) = 0;
    virtual ~Payment() {}
};

#endif