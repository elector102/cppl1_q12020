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
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type almost_equal(T x, T y, int ulp) {
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::fabs(x - y) <= std::numeric_limits<T>::epsilon() * std::fabs(x + y) * ulp
           // unless the result is subnormal
           || std::fabs(x - y) < std::numeric_limits<T>::min();
}


class Vector3 {
    public:
        Vector3();
        Vector3(const double &x, const double &y, const double &z);
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

}
}

#endif