#ifndef FENZ_ARRAY_HPP
#define FENZ_ARRAY_HPP

namespace fenz
{
    template <typename T, int N>
    class Iterable;

    /// @brief A non-owning view of a portion of an array.
    /// @tparam T Type of the elements in the array.
    /// @tparam N Size of view portion of the array.
    template <typename T, int N>
    class ConstIterable
    {
        static_assert(N > 0, "Array size must be greater than zero");

    private:
        // A pointer to the first element of the array.
        const T *data_;

    public:
        /// @brief Constructs a ConstIterable from a pointer to data.
        /// @param data Pointer to the data.
        /// @warning It is assumed that the data pointer points to an array of at least N elements.
        ConstIterable(const T *data);

        /// @brief Constructs a ConstIterable from an Iterable.
        /// @param other The Iterable to construct from.
        ConstIterable(const Iterable<T, N> &other);

        /// @brief Returns a const reference to the element at the specified index.
        /// @tparam i Index of the element to access.
        /// @return Const reference to the element at the specified index.
        template <int i>
        const T &at() const;

        /// @brief Performs a const operation on each element of the array.
        /// @param func Function pointer to the const operation to perform on each element. The parameters to the function are the element and its index.
        void enumerate(void (*func)(const T &, int)) const;

        // Range-based for support
        const T *begin() const { return data_; }
        const T *end() const { return data_ + N; }

        /// @brief Returns a view of this ConstIterable's data.
        /// @details This function returns an ConstIterable that starts at the specified index of this ConstIterable's data and has the specified size.
        /// @tparam Start Start index.
        /// @tparam End End index.
        /// @return An ConstIterable with the specified start index and end index.
        /// @note This function does not create a copy of the data.
        template <int Start, int End>
        ConstIterable<T, End - Start> constView() const;
    };

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
        Iterable(T *data);

        /// @brief Returns a reference to the element at the specified index.
        /// @tparam i Index of the element to access.
        /// @return Reference to the element at the specified index.
        template <int i>
        T &at();

        /// @brief Returns a const reference to the element at the specified index.
        /// @tparam i Index of the element to access.
        /// @return Const reference to the element at the specified index.
        template <int i>
        const T &at() const;

        /// @brief Performs an operation on each element of the array.
        /// @param func Function pointer to the operation to perform on each element. The parameters to the function are the element and its index.
        void enumerate(void (*func)(T &, int));

        /// @brief Performs a const operation on each element of the array.
        /// @param func Function pointer to the const operation to perform on each element. The parameters to the function are the element and its index.
        void enumerate(void (*func)(const T &, int)) const;

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
        /// @note This function does not create a copy of the data.
        template <int Start, int End>
        Iterable<T, End - Start> view();

        /// @brief Returns a view of this Iterable's data.
        /// @details This function returns an Iterable that starts at the specified index of this Iterable's data and has the specified size.
        /// @tparam Start Start index.
        /// @tparam End End index.
        /// @return A ConstIterable with the specified start index and end index.
        /// @note This function does not create a copy of the data.
        template <int Start, int End>
        ConstIterable<T, End - Start> constView() const;
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
        Array();

        /// @brief Constructs an Array with a default value for all elements.
        /// @param defaultValue The default value to initialize all elements of the array.
        Array(T defaultValue);

        Array(const Array &) = delete;
        Array &operator=(const Array &) = delete;
    };

    // =======================================
    //  Implementations only below this point
    // =======================================

    template <typename T, int N>
    inline ConstIterable<T, N>::ConstIterable(const T *data) : data_(data)
    {
    }

    template <typename T, int N>
    inline fenz::ConstIterable<T, N>::ConstIterable(const Iterable<T, N> &other) : data_(other.data_)
    {
    }

    template <typename T, int N>
    template <int i>
    inline const T &ConstIterable<T, N>::at() const
    {
        static_assert(i >= 0 && i < N, "Index out of bounds");
        return data_[i];
    }

    template <typename T, int N>
    inline void ConstIterable<T, N>::enumerate(void (*func)(const T &, int)) const
    {
        for (int i = 0; i < N; ++i)
        {
            func(data_[i], i);
        }
    }

    template <typename T, int N>
    template <int Start, int End>
    inline ConstIterable<T, End - Start> ConstIterable<T, N>::constView() const
    {
        static_assert(Start >= 0 && End <= N, "Iterable out of bounds");
        static_assert(End > Start, "Size must be positive");

        return ConstIterable<T, End - Start>(data_ + Start);
    }

    template <typename T, int N>
    inline Iterable<T, N>::Iterable(T *data) : data_(data)
    {
    }

    template <typename T, int N>
    template <int i>
    inline T &Iterable<T, N>::at()
    {
        static_assert(i >= 0 && i < N, "Index out of bounds");
        return data_[i];
    }

    template <typename T, int N>
    template <int i>
    inline const T &Iterable<T, N>::at() const
    {
        static_assert(i >= 0 && i < N, "Index out of bounds");
        return data_[i];
    }

    template <typename T, int N>
    inline void Iterable<T, N>::enumerate(void (*func)(T &, int))
    {
        for (int i = 0; i < N; ++i)
        {
            func(data_[i], i);
        }
    }

    template <typename T, int N>
    inline void Iterable<T, N>::enumerate(void (*func)(const T &, int)) const
    {
        for (int i = 0; i < N; ++i)
        {
            func(data_[i], i);
        }
    }

    template <typename T, int N>
    template <int Start, int End>
    inline Iterable<T, End - Start> Iterable<T, N>::view()
    {
        static_assert(Start >= 0 && End <= N, "Iterable out of bounds");
        static_assert(End > Start, "Size must be positive");

        return Iterable<T, End - Start>(data_ + Start);
    }

    template <typename T, int N>
    template <int Start, int End>
    inline ConstIterable<T, End - Start> Iterable<T, N>::constView() const
    {
        static_assert(Start >= 0 && End <= N, "Iterable out of bounds");
        static_assert(End > Start, "Size must be positive");

        return ConstIterable<T, End - Start>(data_ + Start);
    }

    template <typename T, int N>
    inline Array<T, N>::Array()
        : Iterable<T, N>(ownedData_)
    {
    }

    template <typename T, int N>
    inline Array<T, N>::Array(T defaultValue)
        : Iterable<T, N>(ownedData_)
    {
        for (int i = 0; i < N; ++i)
        {
            ownedData_[i] = defaultValue;
        }
    }
}

#endif // FENZ_ARRAY_HPP
