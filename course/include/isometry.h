#ifndef ISOMETRY_H
#define ISOMETRY_H

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <initializer_list>

namespace ekumen {
namespace math {

class Vector3 {
public:
  static const Vector3 kZero;
  static const Vector3 kUnitX;
  static const Vector3 kUnitY;
  static const Vector3 kUnitZ;

  Vector3(double x, double y, double z) : x_{x}, y_{y}, z_{z} {}

  Vector3() : Vector3(0.0, 0.0, 0.0) {}

  Vector3(std::initializer_list<double> &&list) {
    auto it = list.begin();
    x_ = *(it++);
    y_ = *(it++);
    z_ = *it;
  }

  double &x() { return x_; }
  double &y() { return y_; }
  double &z() { return z_; }

  double x() const { return x_; }
  double y() const { return y_; }
  double z() const { return z_; }

  double norm() const { return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_); }

  double dot(const Vector3 &rhs) const {
    Vector3 scalar_prod = *this * rhs;
    return scalar_prod.x() + scalar_prod.y() + scalar_prod.z();
  }

  Vector3 cross(const Vector3 &rhs) const {
    return Vector3(this->y() * rhs.z() - this->z() * rhs.y(),
                   this->z() * rhs.x() - this->x() * rhs.z(),
                   this->x() * rhs.y() - this->y() * rhs.x());
  }

  double &operator[](const std::size_t index) {
    switch (index) {
    case 0:
      return x_;
    case 1:
      return y_;
    case 2:
    default:
      return z_;
    }
  }

  double operator[](const std::size_t index) const {
    switch (index) {
    case 0:
      return x_;
    case 1:
      return y_;
    case 2:
    default:
      return z_;
    }
  }

  bool operator==(const Vector3 &rhs) const {
    auto within_delta = [this](double opa, double opb) {
      return std::abs(opa - opb) < kTolerance;
    };

    return within_delta(x_, rhs.x()) && within_delta(y_, rhs.y()) &&
           within_delta(z_, rhs.z());
  }

  bool operator==(const std::initializer_list<double> &list) const {
    return *this == Vector3(list);
  }

  Vector3(const std::initializer_list<double> &list) {
    auto it = list.begin();
    x_ = *(it++);
    y_ = *(it++);
    z_ = *it;
  }

  bool operator!=(const Vector3 &rhs) const { return !(*this == rhs); }

  bool operator!=(const std::initializer_list<double> &list) const {
    return *this != Vector3(list);
  }

  Vector3 &operator+=(const Vector3 &rhs) {
    x_ += rhs.x();
    y_ += rhs.y();
    z_ += rhs.z();
    return *this;
  }

  Vector3 operator+(const Vector3 &rhs) const {
    Vector3 lhs(x_, y_, z_);
    lhs += rhs;
    return lhs;
  }

  Vector3 &operator-=(const Vector3 &rhs) {
    x_ -= rhs.x();
    y_ -= rhs.y();
    z_ -= rhs.z();
    return *this;
  }

  Vector3 operator-(const Vector3 &rhs) const {
    Vector3 lhs(x_, y_, z_);
    lhs -= rhs;
    return lhs;
  }

  Vector3 operator*(const double &rhs) const {
    Vector3 lhs(rhs * x_, rhs * y_, rhs * z_);
    return lhs;
  }

  Vector3 operator*(const Vector3 &rhs) const {
    Vector3 lhs(x_ * rhs.x(), y_ * rhs.y(), z_ * rhs.z());
    return lhs;
  }

  Vector3 operator/(const Vector3 &rhs) const {
    Vector3 lhs(x_ / rhs.x(), y_ / rhs.y(), z_ / rhs.z());
    return lhs;
  }

private:
  const double kTolerance{1e-6};

  double x_;
  double y_;
  double z_;
};

inline Vector3 operator*(const double &lhs, const Vector3 &rhs) {
  return rhs * lhs;
}

} // math
} // ekumen

#endif