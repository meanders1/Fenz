#ifndef FENZ_OPTION_HPP
#define FENZ_OPTION_HPP

namespace fenz
{
    /// @brief A simple optional value container, representing either a value or no value.
    /// @tparam T The type of the value to store.
    template <typename T>
    class Option
    {
    private:
        union
        {
            T value_;
            char dummy_;
        };

        bool hasValue_;

    public:
        /// @brief Constructs an Option with no value.
        Option() : hasValue_(false) {}

        /// @brief Constructs an Option containing a value.
        /// @param value The value to store.
        Option(T value) : value_(value), hasValue_(true) {}

        /// @brief Copy constructor.
        /// @param other The Option to copy from.
        Option(const Option &other)
        {
            if (other.hasValue())
            {
                hasValue_ = true;
                value_ = other.value_;
            }
            else
            {
                hasValue_ = false;
            }
        }

        /// @brief Destructor. If a value is present, it's destructor is called.
        ~Option()
        {
            if (hasValue())
            {
                value_.~T();
                hasValue_ = false;
            }
        }

        /// @brief Assignment operator. Copies the value of `other`.
        /// @note If this value already has a value, it is destroyed.
        /// @param other The Option to assign from.
        /// @return Reference to this Option.
        Option &operator=(const Option &other)
        {
            if (hasValue())
            {
                value_.~T();
            }

            if (other.hasValue())
            {
                hasValue_ = true;
                value_ = other.value_;
            }
            else
            {
                hasValue_ = false;
            }
            return *this;
        }

        /// @brief Checks if the Option contains a value.
        /// @return True if a value is present, false otherwise.
        bool hasValue() const
        {
            return hasValue_;
        }

        /// @brief Implicit conversion to bool, true if a value is present.
        operator bool() const
        {
            return hasValue();
        }

        /// @brief Returns the value if present, otherwise assigns as value to `this` and returns a fallback value.
        /// @param ifNone The value to assign and return if no value is present.
        /// @return Reference to the contained or assigned value.
        T &valueOrAssign(const T &ifNone)
        {
            if (!hasValue())
            {
                *this = ifNone;
            }
            return value_;
        }

        /// @brief Returns the value if present, otherwise returns a fallback value.
        /// @param ifNone The value to return if no value is present.
        /// @return Reference to the contained value or the fallback value.
        const T &valueOr(const T &ifNone) const
        {
            if (hasValue())
                return value_;
            else
                return ifNone;
        }
    };

}

#endif // FENZ_OPTION_HPP
