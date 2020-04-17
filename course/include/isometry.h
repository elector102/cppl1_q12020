#ifndef ISOMETRY_H
#define	ISOMETRY_H

// Standard libraries
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

namespace ekumen {
namespace math {

static constexpr int resolution{4};
template <class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type almost_equal(T a, T b, int resolution) {
    return std::fabs(a - b) <= std::numeric_limits<T>::epsilon() * std::fabs(a + b) * resolution
           || std::fabs(a - b) < std::numeric_limits<T>::min();
}

class Vector3 {
    public:
        Vector3(const double &x = 0, const double &y = 0, const double &z = 0);
        ~Vector3();

        // Getter for elements of the vector.
        const double& x() const { return this->x_; };
        const double& y() const { return this->y_; };
        const double& z() const { return this->z_; };

        // Setter for elements of the vector.
        void x(const double &x) { this->x_ = x; };
        void y(const double &y) { this->y_ = y; };
        void z(const double &z) { this->z_ = z; };

        double& x() { return x_; };
        double& y() { return y_; };
        double& z() { return z_; };

        // Operators overloading.
        Vector3 operator+(const Vector3& vec) const;
        Vector3 operator-(const Vector3& vec) const;
        Vector3 operator*(const double& value) const;
        Vector3 operator*(const Vector3& vec) const;
        Vector3 operator/(const Vector3& vec) const;
        const double& operator[](const int &index) const;
        double& operator[](const int &index);
        bool operator==(const std::initializer_list<double>& rhs) const;
        bool operator==(const Vector3& a) const;
        bool operator!=(const std::initializer_list<double>& rhs) const;
        bool operator!=(const Vector3& a) const;


        double dot(const Vector3&) const;
        double norm() const;
        Vector3 cross(const Vector3&) const;

        // Class constants
        static const Vector3 kUnitX;
        static const Vector3 kUnitY;
        static const Vector3 kUnitZ;
        static const Vector3 kZero;

    private:
        double x_, y_, z_;
};

inline Vector3 operator*(const double scalar, const Vector3& vector) {
    Vector3 result(vector.x() * scalar, vector.y() * scalar, (vector.z() * scalar));
    return result;
}

inline std::ostream& operator<<(std::ostream& os, const Vector3& vector) {
    return os << "(x: " << std::to_string(static_cast<int>(vector.x()))
              << ", y: " << std::to_string(static_cast<int>(vector.y()))
              << ", z: " << std::to_string(static_cast<int>(vector.z())) << ")";
}

}
}

#endif