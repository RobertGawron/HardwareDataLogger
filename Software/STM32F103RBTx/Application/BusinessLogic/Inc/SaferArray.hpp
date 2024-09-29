#ifndef SaferArray_h
#define SaferArray_h

/**
 * @file SaferArray.h
 * @brief Definition of the SaferArray class template.
 *
 * A safer array class template that does not crash when trying to access more elements than its capacity.
 */

/**
 * @class SaferArray
 * @brief A class template for managing a fixed-size array of pointers safely.
 *
 * This class provides a way to manage a static array of pointers with bounds checking
 * to prevent out-of-bounds access. The array does not allow adding more elements
 * than its maximum size and provides methods for adding, removing, and accessing elements.
 *
 * @tparam T The type of the elements (pointers) stored in the array.
 * @tparam MaxSize The maximum number of elements (pointers) the array can hold.
 */
namespace BusinessLogic
{

    template <typename T, int MaxSize>
    class SaferArray
    {
    public:
        /**
         * @brief Constructor to initialize the array.
         *
         * Initializes the array with a count of 0.
         */
        SaferArray() : count(0) {}

        /**
         * @brief Add a pointer to the array.
         *
         * Adds a pointer to the array if there is space available. If the array is full,
         * the method returns false.
         *
         * @param ptr The pointer to be added to the array.
         * @return true if the pointer was successfully added, false if the array is full.
         */
        bool add(T *ptr)
        {
            if (count < MaxSize)
            {
                array[count++] = ptr;
                return true; // Successfully added
            }
            return false; // Array is full
        }

        /**
         * @brief Remove a pointer from the array.
         *
         * Removes a pointer from the array if it exists. Shifts the remaining pointers
         * to fill the gap left by the removed pointer.
         *
         * @param ptr The pointer to be removed from the array.
         * @return true if the pointer was successfully removed, false if the pointer was not found.
         */
        bool remove(T *ptr)
        {
            for (int i = 0; i < count; ++i)
            {
                if (array[i] == ptr)
                {
                    // Shift remaining pointers to fill the gap
                    for (int j = i; j < count - 1; ++j)
                    {
                        array[j] = array[j + 1];
                    }
                    count--;
                    return true; // Successfully removed
                }
            }
            return false; // Pointer not found
        }

        /**
         * @brief Get the number of pointers currently stored in the array.
         *
         * @return The number of pointers currently stored in the array.
         */
        int size() const
        {
            return count;
        }

        /**
         * @brief Access an element by index (read-only).
         *
         * Provides read-only access to an element by its index. If the index is out of bounds,
         * returns a nullptr.
         *
         * @param index The index of the element to access.
         * @return The pointer at the specified index, or nullptr if the index is out of bounds.
         */
        T *operator[](int index) const
        {
            if (index >= 0 && index < count)
            {
                return array[index];
            }
            return nullptr; // Out of bounds access
        }

        /**
         * @brief Access an element by index (read-write).
         *
         * Provides read-write access to an element by its index. If the index is out of bounds,
         * returns a reference to a static null pointer.
         *
         * @param index The index of the element to access.
         * @return A reference to the pointer at the specified index, or a reference to a static
         *         null pointer if the index is out of bounds.
         */
        T *&operator[](int index)
        {
            if (index >= 0 && index < count)
            {
                return array[index];
            }
            static T *null_ptr = nullptr;
            return null_ptr; // Out of bounds access
        }

    private:
        T *array[MaxSize]; /**< Static array of pointers */
        int count;         /**< Number of valid pointers stored in the array */
    };
}
#endif
