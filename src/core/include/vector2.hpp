#pragma once

#include "Core.h"

/**
 * @brief Utility template  class for 2-dimensional vectors.
 * 
 */

namespace CustomVector{
    template <typename T>
    class Vector2
    {
        public:
        /**
         * @brief Construct a new Vector 2 object
         * 
         */
        Vector2();
        /**
         * @brief Construct a new Vector 2 object from ots coordinatesx
         * 
         * @param X X coordinate
         * @param Y Y coordinate
         */
        Vector2(T X, T Y);
        /**
         * @brief Construct a new Vector 2 object from another type of vector
         * 
         * It's called only when U != T.
         * A call to this constructor will fail to compile if U is not comvertible to T.
         * 
         * 
         * @tparam U 
         * @param vector Vector to convert
         */
        template <typename U>
        explicit Vector2(const Vector2<U>& vector);

        // Member datas
        T x;
        T y;
    };

    /**
     * @brief Overload unary operator -
     * 
     * @tparam T 
     * @param right Vector to negate
     * @return Memberwise opposite of the vector
     */
    template <typename T>
    Vector2<T> operator -(const Vector2<T>& right);

    /**
     * @brief Overload binary operator +=
     * 
     * This operator performs a memberwise addition of both vectors,
     * and assigns the result to \a left.
     * 
     * @tparam T 
     * @param left Left operand (a vector)
     * @param right Right operand (a vector)
     * @return Reference to \a left
     */
    template <typename T>
    Vector2<T>& operator += (Vector2<T>& left, const Vector2<T>& right);

    /**
     * @brief Overload of binary operator -=
     * 
     * This operator perform a memberwise subtraction of both vectors,
     * and assigns the result to \a left.
     * 
     * @tparam T 
     * @param left Left operand (a vector)
     * @param right Right operand (a vector)
     * @return Reference to \a left
     */
    template <typename T>
    Vector2<T> operator -=(Vector2<T>& left, const Vector2<T>& right);

    /**
     * @brief Overload of binary operator +
     * 
     * @tparam T 
     * @param left Left operand (a vector)
     * @param right Right operand (a vector)
     * @return Memberwise addition of both vectors
     */
    template <typename T>
    Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right);

    /**
     * @brief Overload of binary operator -
     * 
     * @tparam T 
     * @param left Left operand (a vector)
     * @param right Right operand (a vector)
     * @return Memberwise subtraction of both vectors
     */
    template <typename T>
    Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right);

    /**
     * @brief Overload of binary operator *
     * 
     * @tparam T 
     * @param left Left operand (a vector)
     * @param right Right operand (a scalar value)
     * @return Memberwise multiplication by \a right.
     */
    template <typename T>
    Vector2<T> operator *(const Vector2<T>& left, T right);

    /**
     * @brief Overload of binary operator *
     * 
     * @tparam T 
     * @param left Left operand (a scalar value)
     * @param right Right operand (a vector)
     * @return Memberwise multiplication by left
     */
    template <typename T>
    Vector2<T> operator *(T left, const Vector2<T>& right);

    /**
     * @brief Overload of binary operator *=
     * 
     * This operator performs a memberwise nultiplication by right,
     * and assigns the result to Left.
     * 
     * @tparam T 
     * @param left Left operand (a vector)
     * @param right Right operand (a scalar value)
     * @return Reference to left
     */
    template <typename T>
    Vector2<T>& operator *=(Vector2<T>& left, T right);

    /**
     * @brief Overload of binary operator /
     * 
     * @tparam T 
     * @param left Left operand (a vector)
     * @param right Right operand (a scalar value)
     * @return Memberwise division by right
     */
    template <typename T>
    Vector2<T> operator /(const Vector2<T>& left, T right);

    /**
     * @brief Overload of binary operator /=
     * 
     * This operator performs a memberwise division by right,
     * and assigns the result to left.
     * 
     * @tparam T 
     * @param left Left operand (a vector)
     * @param right Right operand (a scalar value)
     * @return Reference to left
     */
    template <typename T>
    Vector2<T>& operator /=(Vector2<T>& left, T right);

    /**
     * @brief Overload of binary operator ==
     * 
     * This operator compares strict equality between two vectors.
     * 
     * @tparam T 
     * @param left Left operand (a vector)
     * @param right Right operand (a vector)
     * @return true if left is equal to right
     */
    template <typename T>
    bool operator ==(const Vector2<T>& left, const Vector2<T>& right);

    /**
     * @brief Overload of binary operator !=
     * 
     * This operator compares strict difference two vectors.
     * 
     * @tparam T 
     * @param left Left operand (a vector)
     * @param right Right operand (a vector)
     * @return true if left is not equal to right
     */
    template <typename T>
    bool operator !=(const Vector2<T>& left, const Vector2<T>& right);

    #include "vector2.inl"

    typedef Vector2<int>            Vector2_int;
    typedef Vector2<unsigned int>   Vector2_uint;
    typedef Vector2<float>          Vector2_float;
}