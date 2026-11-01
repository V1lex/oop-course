#include "IPAddress.h"

IPAddress::IPAddress() : a_(0), b_(0), c_(0), d_(0) {}

IPAddress::IPAddress(int a, int b, int c, int d) : a_(a), b_(b), c_(c), d_(d) {}

bool IPAddress::valid() const {
    return a_ >= 0 && a_ <= 255 && b_ >= 0 && b_ <= 255 &&
           c_ >= 0 && c_ <= 255 && d_ >= 0 && d_ <= 255;
}

bool IPAddress::operator==(const IPAddress& other) const {
    return a_ == other.a_ && b_ == other.b_ && c_ == other.c_ && d_ == other.d_;
}

bool IPAddress::operator<(const IPAddress& other) const {
    if (a_ != other.a_) {
        return a_ < other.a_;
    }
    if (b_ != other.b_) {
        return b_ < other.b_;
    }
    if (c_ != other.c_) {
        return c_ < other.c_;
    }
    return d_ < other.d_;
}

std::ostream& operator<<(std::ostream& os, const IPAddress& ip) {
    return os << ip.a_ << '.' << ip.b_ << '.' << ip.c_ << '.' << ip.d_;
}
