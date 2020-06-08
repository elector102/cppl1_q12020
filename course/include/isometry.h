

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

struct Elements {
    Elements() : x_(0), y_(0), z_(0) {};
    Elements(const double &x, const double &y, const double &z) : x_(x), y_(y), z_(z) {}; 
    double x_,y_,z_;
};

class Vector3 {
    public:
        Vector3() : v_(new Elements{}) {};
        Vector3(const double &x, const double &y, const double &z) : v_(new Elements{x, y, z}) {};
        ~Vector3() {
            // deallocate
            delete v_;  
        };

        // copy constructor
        Vector3(const Vector3& other) : v_(new Elements{*(other.v_)}) {};

        // move constructor
        Vector3(Vector3&& other) {
            v_ = other.v_;
            other.v_ = nullptr;
        }

        // Getter for elements of the vector.
        const double& x() const { return v_->x_; };
        const double& y() const { return v_->y_; };
        const double& z() const { return v_->z_; };

        // Setter for elements of the vector.
        double& x() { return v_->x_; };
        double& y() { return v_->y_; };
        double& z() { return v_->z_; };

        // Operators overloading.
        Vector3 operator+(const Vector3& vector) const;
        Vector3 operator-(const Vector3& vector) const;
        Vector3 operator*(const double& value) const;
        Vector3 operator*(const Vector3& vector) const;
        Vector3 operator/(const Vector3& vector) const;
        Vector3& operator+=(const Vector3& vector);
        Vector3& operator-=(const Vector3& vector);
        Vector3& operator*=(const double& value);
        Vector3& operator*=(const Vector3& vector);
        Vector3& operator/=(const Vector3& vector);
        const double& operator[](const int &index) const;
        double& operator[](const int &index);
        bool operator==(const std::initializer_list<double>& rhs) const;
        bool operator==(const Vector3& a) const;
        bool operator!=(const std::initializer_list<double>& rhs) const;
        bool operator!=(const Vector3& a) const;
        Vector3& operator=(const Vector3& other);
        Vector3& operator=(Vector3&& other);
        double dot(const Vector3& vector) const;
        double norm() const;
        Vector3 cross(const Vector3& vector) const;

        // Class constants
        static const Vector3 kUnitX;
        static const Vector3 kUnitY;
        static const Vector3 kUnitZ;
        static const Vector3 kZero;

    private:
        Elements *v_;
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
