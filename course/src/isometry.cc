#include <cmath>
#include <cstdint>
#include "isometry.h"

namespace ekumen {
namespace math {

Vector3::Vector3() {
    x_ = 0;
    y_ = 0;
    z_ = 0;
}

Vector3::Vector3(const double& x, const double& y, const double& z) : x_(x), y_(y), z_(z) {}

Vector3::~Vector3() {}

// Class constants
const Vector3 Vector3::kUnitX = Vector3(1., 0., 0.);
const Vector3 Vector3::kUnitY = Vector3(0., 1., 0.);
const Vector3 Vector3::kUnitZ = Vector3(0., 0., 1.);
const Vector3 Vector3::kZero = Vector3(0., 0., 0.);

Vector3 Vector3::operator+(const Vector3& vector) const {
    return Vector3(x() + vector.x(), y() + vector.y(), z() + vector.z());
}
Vector3 Vector3::operator-(const Vector3& vector) const {
    return Vector3(x() - vector.x(), y() - vector.y(), z() - vector.z());
}
Vector3 Vector3::operator*(const double& value) const {
    return Vector3(x() * value, y() * value, z() * value);
}
Vector3 Vector3::operator*(const Vector3& vector) const {
    return Vector3(x() * vector.x(), y() * vector.y(), z() * vector.z());
}
Vector3 Vector3::operator/(const Vector3& vector) const {
    return Vector3(x() / vector.x(), y() / vector.y(), z() / vector.z());
}

const double& Vector3::operator[](const int &index) const {
    switch (index) {
        case 0:
            return x();
        case 1:
            return y();
        case 2:
            return z();
        default:
            throw std::overflow_error("index out of range, Vector3 only have three elements");
    }
}

double& Vector3::operator[](const int &index) {
    switch (index) {
        case 0:
            return x_;
        case 1:
            return y_;
        case 2:
            return z_;
        default:
            throw std::overflow_error("index out of range, Vector3 only have three elements");
    }
}

bool Vector3::operator==(const std::initializer_list<double>& vector) const {
    if (vector.size() != 3) {
        return false;
    }
    auto it = vector.begin();
    if (!almost_equal(x(), *it, resolution)) {
        return false;
    }
    ++it;
    if (!almost_equal(y(), *it, resolution)) {
        return false;
    }
    ++it;
    if (!almost_equal(z(), *it, resolution)) {
        return false;
    }
    return true;
}

bool Vector3::operator==(const Vector3& vector) const {
    return (Vector3(x_, y_, z_) == std::initializer_list<double>({vector.x_, vector.y_, vector.z_}));
}
bool ekumen::math::Vector3::operator != (const Vector3& vector) const {
    return !(*this == vector);
}

bool ekumen::math::Vector3::operator != (const std::initializer_list<double>& list) const {
    return !(*this == list);
}

double Vector3::norm() const {
    return std::sqrt(dot(*this));
};

double Vector3::dot(const Vector3& vector) const {
    return ((x() * vector.x()) + (y() * vector.y()) + (z() * vector.z()));
};

Vector3 Vector3::cross(const Vector3& vector) const {
    auto i = (y() * vector.z()) - (vector.y() * z());
    auto j = (x() * vector.z()) - (vector.x() * z());
    auto k = (x() * vector.y()) - (vector.x() * y());

    return Vector3(i, j, k);
}

}
}
