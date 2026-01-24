module;

#include <cstddef>
#include <memory>

export module BusinessLogic.TickDelegate;

import BusinessLogic.TickableConcept;

export namespace BusinessLogic
{
    /**
     * @brief Lightweight, non-owning callable wrapper for objects that satisfy TickableConcept.
     *
     * @details
     * TickDelegate stores a reference to an object together with a small static wrapper function
     * that knows how to call `tick()` on that object. This provides a single uniform callable type
     * (`bool operator()() noexcept`) suitable for fixed-size containers such as `std::array`.
     *
     * This design avoids:
     * - forcing a common base class (virtual interface),
     * - using `std::function` (type erasure with potential dynamic allocation),
     * - using `std::vector` (dynamic allocation by design).
     *
     * The delegate is non-owning: the referenced object must outlive the TickDelegate.
     */
    class TickDelegate final
    {
    public:
        /**
         * @brief Type of the stored wrapper function.
         *
         * The wrapper receives the stored object as a type-erased pointer and invokes `tick()`.
         */
        using WrapperFn = bool (*)(void *) noexcept;

        /**
         * @brief Creates an unbound delegate.
         *
         * An unbound delegate reports not bound via isBound() and returns false when invoked.
         * This is useful when TickDelegate is stored in fixed-size arrays that are later populated.
         */
        TickDelegate() noexcept
            : objectPtr(nullptr), wrapperFn(nullptr)
        {
        }

        TickDelegate(const TickDelegate &) = default;
        TickDelegate &operator=(const TickDelegate &) = default;

        TickDelegate(TickDelegate &&) = default;
        TickDelegate &operator=(TickDelegate &&) = default;

        /**
         * @brief Binds this delegate to an object instance.
         * @tparam T Concrete type that satisfies TickableConcept.
         * @param obj Object instance to invoke tick() on.
         */
        template <TickableConcept T>
        explicit TickDelegate(T &obj) noexcept
            : objectPtr(std::addressof(obj)), wrapperFn(&wrapper<T>)
        {
        }

        /**
         * @brief Invokes tick() on the bound object.
         * @return The value returned by the underlying tick(), or false if unbound.
         */
        [[nodiscard]] auto operator()() const noexcept -> bool
        {
            bool result = false;

            if (wrapperFn != nullptr)
            {
                result = wrapperFn(objectPtr);
            }

            return result;
        }

        /**
         * @brief Indicates whether this delegate is bound to an object.
         */
        [[nodiscard]] auto isBound() const noexcept -> bool
        {
            const bool result = (objectPtr != nullptr) && (wrapperFn != nullptr);
            return result;
        }

    private:
        void *objectPtr;
        WrapperFn wrapperFn;

        template <TickableConcept T>
        static auto wrapper(void *objPtr) noexcept -> bool
        {
            const bool result = static_cast<T *>(objPtr)->tick();
            return result;
        }
    };
}