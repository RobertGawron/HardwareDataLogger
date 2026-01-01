#ifndef IAPPLICATION_FACADE_HPP
#define IAPPLICATION_FACADE_HPP

namespace BusinessLogic
{
    /**
     * @class IApplicationFacade
     * @brief Interface for application lifecycle management.
     *
     * Defines the contract for initializing, starting, stopping, and updating
     * the application components through a unified facade.
     */
    class IApplicationFacade
    {
    public:
        constexpr IApplicationFacade() noexcept = default;
        virtual ~IApplicationFacade() = default;

        // Non-copyable and non-movable
        IApplicationFacade(const IApplicationFacade &) = delete;
        IApplicationFacade(IApplicationFacade &&) = delete;
        IApplicationFacade &operator=(const IApplicationFacade &) = delete;
        IApplicationFacade &operator=(IApplicationFacade &&) = delete;

        /**
         * @brief Initializes the application components.
         * @return true if initialization was successful, false otherwise.
         */
        [[nodiscard]] virtual bool initialize() noexcept = 0;

        /**
         * @brief Starts the application.
         * @return true if start was successful, false otherwise.
         */
        [[nodiscard]] virtual bool start() noexcept = 0;

        /**
         * @brief Stops the application.
         * @return true if stop was successful, false otherwise.
         */
        [[nodiscard]] virtual bool stop() noexcept = 0;

        /**
         * @brief Performs periodic update of application state.
         * @return true if tick was successful, false otherwise.
         */
        [[nodiscard]] virtual bool tick() noexcept = 0;
    };

} // namespace BusinessLogic

#endif // IAPPLICATION_FACADE_HPP