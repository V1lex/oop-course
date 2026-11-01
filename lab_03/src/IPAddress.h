#pragma once

#include <iostream>

class IPAddress {
public:
    IPAddress();
    IPAddress(int a, int b, int c, int d);

    bool operator==(const IPAddress& other) const;
    bool operator<(const IPAddress& other) const;

    friend std::ostream& operator<<(std::ostream& os, const IPAddress& ip);

private:
    bool valid() const;

    int a_;
    int b_;
    int c_;
    int d_;

    friend class IPAddressSet;
};
