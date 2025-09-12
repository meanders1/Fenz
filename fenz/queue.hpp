// A copy of Option is included, since the queue implementation depends on it.

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

#ifndef FENZ_QUEUE_HPP
#define FENZ_QUEUE_HPP

namespace fenz
{
    /// @brief A simple circular queue with a max capacity.
    /// @tparam T The type of elements in the queue.
    /// @tparam Capacity The maximum number of elements the queue can hold.
    template <typename T, unsigned int Capacity>
    class Queue
    {
    private:
        Option<T> data[Capacity];
        unsigned int front;
        unsigned int rear;
        unsigned int count;

    public:
        /// @brief Constructs an empty Queue.
        Queue() : front(0), rear(0), count(0) {}

        /// @brief Adds an item to the back of the queue.
        /// @return True if the item was added, false if the queue is full.
        /// @param item The item to add.
        bool enqueue(const T &item)
        {
            if (isFull())
            {
                return false;
            }
            data[rear] = item;
            rear = (rear + 1) % Capacity;
            count++;
            return true;
        }

        /// @brief Adds an item to the back of the queue, overwriting the oldest item if the queue is full.
        /// @param item The item to add.
        void forceEnqueue(const T &item)
        {
            if (isFull())
            {
                front = (front + 1) % Capacity; // Overwrite the oldest item
                count--;
            }
            enqueue(item);
        }

        /// @brief Removes and returns the item at the front of the queue.
        /// @return An Option containing the item if the queue is not empty, or an empty Option if the queue is empty.
        Option<T> dequeue()
        {
            if (isEmpty())
            {
                return Option<T>();
            }
            Option<T> item = data[front];
            front = (front + 1) % Capacity;
            count--;
            return item;
        }

        /// @brief Returns the number of elements in the queue.
        /// @return The number of elements in the queue.
        constexpr unsigned int size() const
        {
            return count;
        }

        /// @brief Returns the maximum capacity of the queue.
        /// @return The maximum capacity of the queue.
        constexpr unsigned int capacity() const
        {
            return Capacity;
        }

        /// @brief Checks if the queue is full.
        /// @return True if the queue is full, false otherwise.
        bool isFull() const
        {
            return count == Capacity;
        }

        /// @brief Checks if the queue is empty.
        /// @return True if the queue is empty, false otherwise.
        bool isEmpty() const
        {
            return count == 0;
        }
    };
}
#endif // FENZ_QUEUE_HPP
