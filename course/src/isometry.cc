#include <cmath>
#include <cstdint>
#include "isometry.h"

namespace ekumen {
namespace math {

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

Vector3& Vector3::operator+=(const Vector3& vector) {
    *this = *this + vector;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& vector) {
    *this = *this - vector;
    return *this;
}

Vector3& Vector3::operator*=(const double& value) {
    *this = *this * value;
    return *this;
}

Vector3& Vector3::operator*=(const Vector3& vector) {
    *this = *this * vector;
    return *this;
}

Vector3& Vector3::operator/=(const Vector3& vector) {
    *this = *this / vector;
    return *this;
}

Vector3& Vector3::operator=(const Vector3& other) {
    if (&other != this) {
        delete v_;
        v_ = new Elements{*(other.v_)};
    }
    return *this;
};

Vector3& Vector3::operator=(Vector3&& other) {
    std::swap(v_, other.v_);
    return *this;
};

const double& Vector3::operator[](const int &index) const {
    switch (index) {
        case 0:
            return x();
        case 1:
            return y();
        case 2:
            return z();
        default:
            throw std::out_of_range("index out of range, Vector3 only have three elements");
    }
}

double& Vector3::operator[](const int &index) {
    switch (index) {
        case 0:
            return v_->x_;
        case 1:
            return v_->y_;
        case 2:
            return v_->z_;
        default:
            throw std::out_of_range("index out of range, Vector3 only have three elements");
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
    return (Vector3(v_->x_, v_->y_, v_->z_) == std::initializer_list<double>({vector.v_->x_, vector.v_->y_, vector.v_->z_}));
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

Matrix3::Matrix3(const std::initializer_list<double>& values) {
    if(values.size() != 9) {
        throw "Invalid initializer list size";
    }
    std::initializer_list<double>::iterator it = values.begin();
    Vector3 r1, r2, r3;
    r1[0] = *it++;
    r1[1] = *it++;
    r1[2] = *it++;

    r2[0] = *it++;
    r2[1] = *it++;
    r2[2] = *it++;

    r3[0] = *it++;
    r3[1] = *it++;
    r3[2] = *it++;
    m_ = new Rows{r1, r2, r3};
}

const Vector3& Matrix3::row(uint32_t index) const {
    if(index > 2) {
        throw std::out_of_range("index out of range, Matrix3 only have three rows");
    }
    return (*this)[index];
}

const Vector3 Matrix3::col(uint32_t index) const {
    if(index > 2) {
        throw std::out_of_range("index out of range, Matrix3 only have three rows");
    }
    return Vector3(r1()[index], r2()[index], r3()[index]);
}

Vector3& Matrix3::operator[](const uint32_t index) {
    switch(index) {
        case 0:
            return r1();
        case 1:
            return r2();
        case 2:
            return r3();
        default:
            throw std::out_of_range("Error. Invalid row index for Matrix3");
    }
}

const Vector3& Matrix3::operator[](const uint32_t index) const {
    switch(index) {
        case 0:
            return r1();
        case 1:
            return r2();
        case 2:
            return r3();
        default:
            throw std::out_of_range("Error. Invalid row index for Matrix3");
    }
}

Matrix3 Matrix3::operator+(const Matrix3& matrix) const {
    Matrix3 aux(*this);
    aux += matrix;
    return aux;
}

Matrix3 Matrix3::operator-(const Matrix3& matrix) const {
    Matrix3 aux(*this);
    aux -= matrix;
    return aux;
}

Matrix3 Matrix3::operator*(const double& value) const {
    Matrix3 aux(*this);
    aux *= value;
    return aux;
}

Matrix3 Matrix3::operator*(const Matrix3& matrix) const {
    Matrix3 aux(*this);
    aux *= matrix;
    return aux;
}

Matrix3 Matrix3::operator/(const Matrix3& matrix) const {
    Matrix3 aux(*this);
    aux /= matrix;
    return aux;
}

Matrix3& Matrix3::operator+=(const Matrix3& matrix) {
    r1() += matrix.r1();
    r2() += matrix.r2();
    r3() += matrix.r3();
    return *this;
}

Matrix3& Matrix3::operator-=(const Matrix3& matrix) {
    r1() -= matrix.r1();
    r2() -= matrix.r2();
    r3() -= matrix.r3();
    return *this;
}

Matrix3& Matrix3::operator*=(const double& value) {
    r1() *= value;
    r2() *= value;
    r3() *= value;
    return *this;
}

Matrix3& Matrix3::operator*=(const Matrix3& matrix) {
    r1() *= matrix.r1();
    r2() *= matrix.r2();
    r3() *= matrix.r3();
    return *this;
}

Matrix3& Matrix3::operator/=(const Matrix3& matrix) {
    r1() /= matrix.r1();
    r2() /= matrix.r2();
    r3() /= matrix.r3();
    return *this;
}

bool Matrix3::operator==(const Matrix3& matrix) const {
    if ((r1() == matrix.r1()) && (r2() == matrix.r2()) && (r3() == matrix.r3())) {
        return true;
    }
    return false;
}

bool Matrix3::operator!=(const Matrix3& matrix) const {
    return !(*this == matrix);
}

Matrix3& Matrix3::operator=(const Matrix3& matrix){
    r1() = matrix.r1();
    r2() = matrix.r2();
    r3() = matrix.r3();
    return *this;
}

Matrix3& Matrix3::operator=(Matrix3&& matrix) {
    r1() = std::move(matrix.r1());
    r2() = std::move(matrix.r2());
    r3() = std::move(matrix.r3());
    return *this;
}

double Matrix3::det() const {
    double subdet1 = r2()[1] * r3()[2] - r2()[2] * r3()[1];
    double subdet2 = r2()[0] * r3()[2] - r2()[2] * r3()[0];
    double subdet3 = r2()[0] * r3()[1] - r2()[1] * r3()[0];
    return r1()[0] * subdet1 - r1()[1] * subdet2 + r1()[2] * subdet3;
}

const Matrix3 Matrix3::kIdentity = 
    Matrix3(Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, 1));

const Matrix3 Matrix3::kZero = 
    Matrix3(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 0));

const Matrix3 Matrix3::kOnes = 
    Matrix3(Vector3(1, 1, 1), Vector3(1, 1, 1), Vector3(1, 1, 1));

}
}
