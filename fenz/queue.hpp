#include "option.hpp"

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
