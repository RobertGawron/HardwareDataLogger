/**
 * @file IApplicationComponentFactory.hpp
 * @brief Declares the IApplicationComponentFactory interface for building and managing application components.
 */

#ifndef IApplicationComponentFactory_h
#define IApplicationComponentFactory_h

namespace BusinessLogic
{
    /**
     * @class IApplicationComponentFactory
     * @brief Interface for building and managing application components.
     *
     * The IApplicationComponentFactory class provides an interface for application component builders.
     * It defines a set of methods for initializing, starting, stopping, and ticking components, which must
     * be implemented by any derived class.
     */
    class IApplicationComponentFactory
    {
    public:
        /**
         * @brief Default constructor.
         */
        IApplicationComponentFactory() = default;

        /**
         * @brief Default destructor.
         */
        virtual ~IApplicationComponentFactory() = default;

        /**
         * @brief Initializes the application components.
         * @return true if initialization was successful, false otherwise.
         */
        virtual bool initialize() = 0;
    };

}

#endif // IApplicationComponentFactory_h
