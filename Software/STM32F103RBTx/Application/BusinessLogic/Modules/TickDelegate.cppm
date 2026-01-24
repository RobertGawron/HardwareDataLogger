module;

#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>
#include <cassert>

export module BusinessLogic.TickDelegate;

import BusinessLogic.TickableConcept;

export namespace BusinessLogic
{
    /**
     * @brief Non-owning, allocation-free delegate that calls tick() on a TickableConcept object.
     *
     * @details
     * Stores a type-erased object pointer plus a function pointer that invokes `tick()`.
     * This avoids virtual dispatch and avoids std::function (which may allocate).
     *
     * Lifetime: non-owning. The bound object must outlive the TickDelegate.
     *
     * Invariant: TickDelegate is always bound (objectPtr != nullptr and wrapperFn != nullptr).
     */
    class TickDelegate final
    {
    public:
        using WrapperFn = bool (*)(void *) noexcept;

        TickDelegate() = delete;

        TickDelegate(const TickDelegate &) = default;
        TickDelegate &operator=(const TickDelegate &) = default;
        TickDelegate(TickDelegate &&) = default;
        TickDelegate &operator=(TickDelegate &&) = default;

        template <TickableConcept T>
        explicit TickDelegate(T &obj) noexcept
            : objectPtr(std::addressof(obj)), wrapperFn(&wrapper<T>)
        {
            assert(objectPtr != nullptr);
            assert(wrapperFn != nullptr);
        }

        [[nodiscard]] auto operator()() const noexcept -> bool
        {
            // Bound-only invariant: no runtime checks required in normal operation.
            const bool result = wrapperFn(objectPtr);
            return result;
        }

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
            assert(objPtr != nullptr);
            const bool result = static_cast<T *>(objPtr)->tick();
            return result;
        }
    };

    static_assert(std::is_trivially_copyable_v<TickDelegate>,
                  "TickDelegate should be trivially copyable (two pointers) for simple storage and use.");

    static_assert(std::is_trivially_destructible_v<TickDelegate>,
                  "TickDelegate must be trivially destructible (non-owning).");

    static_assert(noexcept(std::declval<TickDelegate &>()()),
                  "TickDelegate invocation must be noexcept.");

    static_assert(sizeof(TickDelegate) == (sizeof(void *) + sizeof(TickDelegate::WrapperFn)),
                  "TickDelegate is expected to be exactly two pointers in size.");
}