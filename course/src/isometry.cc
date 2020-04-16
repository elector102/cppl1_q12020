#include <cmath>
#include <cstdint>
#include "isometry.h"

namespace ekumen {
namespace math {

Vector3::Vector3(const double& x, const double& y, const double& z) : x_(x), y_(y), z_(z) {}

Vector3::Vector3() {}

Vector3::~Vector3() {}

// Class constants
const Vector3 Vector3::kUnitX = Vector3(1., 0., 0.);
const Vector3 Vector3::kUnitY = Vector3(0., 1., 0.);
const Vector3 Vector3::kUnitZ = Vector3(0., 0., 1.);
const Vector3 Vector3::kZero = Vector3(0., 0., 0.);

Vector3 Vector3::operator+(const Vector3& vec) const {
    return Vector3(this->x() + vec.x(), this->y() + vec.y(), this->z() + vec.z());
}
Vector3 Vector3::operator-(const Vector3& vec) const {
    return Vector3(this->x() - vec.z(), this->y() - vec.y(), this->z() - vec.z());
}
Vector3 Vector3::operator*(const double& value) const {
    return Vector3(this->x() * value, this->y() * value, this->z() * value);
}
Vector3 Vector3::operator*(const Vector3& vec) const {
    return Vector3(this->x() * vec.x(), this->y() * vec.y(), this->z() * vec.z());
}
Vector3 Vector3::operator/(const Vector3& vec) const {
    return Vector3(this->x() / vec.x(), this->y() / vec.y(), this->z() / vec.z());
}

const double& Vector3::operator[](const int &index) const {
    switch (index) {
        case 0:
            return this->x();
        case 1:
            return this->y();
        case 2:
            return this->z();
        default:
            throw std::overflow_error("index out of range, Vector3 only have three elements");
    }
}

double& Vector3::operator[](const int &index) {
    switch (index) {
        case 0:
            return this->x_;
        case 1:
            return this->y_;
        case 2:
            return this->z_;
        default:
            throw std::overflow_error("index out of range, Vector3 only have three elements");
    }
}

bool Vector3::operator==(const std::initializer_list<double>& vector) const {
    if (vector.size() != 3) return false;
    auto it = vector.begin();
    if (!almost_equal(this->x(), *it, resolution))
        return false;
    ++it;
    if (!almost_equal(this->y(), *it, resolution))
        return false;
    ++it;
    if (!almost_equal(this->z(), *it, resolution))
        return false;
    return true;
}

bool Vector3::operator==(const Vector3& a) const {
    return (Vector3(x_, y_, z_) == std::initializer_list<double>({a.x_, a.y_, a.z_}));
}
bool ekumen::math::Vector3::operator != (const Vector3& v) const {
    return !(*this == v);
}

bool ekumen::math::Vector3::operator != (const std::initializer_list<double>& list) const {
    return !(*this == list);
}

double Vector3::norm() const {
    return std::sqrt(std::pow(this->x(), 2.0) + std::pow(this->y(), 2.0) + std::pow(this->z(), 2.0));
};

double Vector3::dot(const Vector3& v) const {
    return ((this->x() * v.x()) + (this->y() * v.y()) + (this->z() * v.z()));
};

Vector3 Vector3::cross(const Vector3& v) const {
    auto i = (this->y() * v.z()) - (v.y() * this->z());
    auto j = (this->x() * v.z()) - (v.x() * this->z());
    auto k = (this->x() * v.y()) - (v.x() * this->y());

    return Vector3(i, j, k);
}

}
}