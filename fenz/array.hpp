#pragma once

namespace fenz
{
    /// @brief A non-owning view of a portion of an array.
    /// @tparam T Type of the elements in the array.
    /// @tparam N Size of view portion of the array.
    template <typename T, int N>
    class Iterable
    {
        static_assert(N > 0, "Array size must be greater than zero");

    private:
        // A pointer to the first element of the array.
        T *data_;

    public:
        /// @brief Constructs a Iterable from a pointer to data.
        /// @param data Pointer to the data.
        /// @warning It is assumed that the data pointer points to an array of at least N elements.
        Iterable(T *data) : data_(data) {}

        /// @brief Returns a reference to the element at the specified index.
        /// @tparam i Index of the element to access.
        /// @return Reference to the element at the specified index.
        template <int i>
        T &at()
        {
            static_assert(i >= 0 && i < N, "Index out of bounds");
            return data_[i];
        }

        /// @brief Returns a const reference to the element at the specified index.
        /// @tparam i Index of the element to access.
        /// @return Const reference to the element at the specified index.
        template <int i>
        const T &at() const
        {
            static_assert(i >= 0 && i < N, "Index out of bounds");
            return data_[i];
        }

        /// @brief Performs an operation on each element of the array.
        /// @param func Function pointer to the operation to perform on each element. The parameters to the function are the element and its index.
        void enumerate(void (*func)(T &, int))
        {
            for (int i = 0; i < N; ++i)
            {
                func(data_[i], i);
            }
        }

        /// @brief Performs a const operation on each element of the array.
        /// @param func Function pointer to the const operation to perform on each element. The parameters to the function are the element and its index.
        void enumerate(void (*func)(const T &, int)) const
        {
            for (int i = 0; i < N; ++i)
            {
                func(data_[i], i);
            }
        }

        // Range-based for support
        T *begin() { return data_; }
        T *end() { return data_ + N; }
        const T *begin() const { return data_; }
        const T *end() const { return data_ + N; }

        /// @brief Returns a view of this Iterable's data.
        /// @details This function returns an Iterable that starts at the specified index of this Iterable's data and has the specified size.
        /// @tparam Start Start index.
        /// @tparam End End index.
        /// @return An Iterable with the specified start index and end index.
        /// @note This function does not create a copy.
        template <int Start, int End>
        Iterable<T, End - Start> view()
        {
            static_assert(Start >= 0 && End <= N, "Iterable out of bounds");
            static_assert(End > Start, "Size must be positive");

            return Iterable<T, End - Start>(data_ + Start);
        }
    };

    /// @brief A fixed-size array that owns its data.
    /// @tparam T Type of the elements in the array.
    /// @tparam N Size of the array.
    template <typename T, int N>
    class Array : public Iterable<T, N>
    {
    private:
        /// @brief The owned storage for the array elements.
        T ownedData_[N];

    public:
        /// @brief Default constructor.
        Array() : Iterable<T, N>(ownedData_) {}

        Array(const Array &) = delete;
        Array &operator=(const Array &) = delete;

        /// @brief Constructs an Array with a default value for all elements.
        /// @param defaultValue The default value to initialize all elements of the array.
        Array(T defaultValue) : Iterable<T, N>(ownedData_)
        {
            for (int i = 0; i < N; ++i)
            {
                ownedData_[i] = defaultValue;
            }
        }
    };

}
