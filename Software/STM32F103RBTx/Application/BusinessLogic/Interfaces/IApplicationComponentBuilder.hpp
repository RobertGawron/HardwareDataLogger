/**
 * @file IApplicationComponentBuilder.hpp
 * @brief Declares the IApplicationComponentBuilder interface for building and managing application components.
 */

#ifndef IApplicationComponentBuilder_h
#define IApplicationComponentBuilder_h

namespace BusinessLogic
{
    /**
     * @class IApplicationComponentBuilder
     * @brief Interface for building and managing application components.
     *
     * The IApplicationComponentBuilder class provides an interface for application component builders.
     * It defines a set of methods for initializing, starting, stopping, and ticking components, which must
     * be implemented by any derived class.
     */
    class IApplicationComponentBuilder
    {
    public:
        /**
         * @brief Default constructor.
         */
        IApplicationComponentBuilder() = default;

        /**
         * @brief Default destructor.
         */
        virtual ~IApplicationComponentBuilder() = default;

        /**
         * @brief Initializes the application components.
         * @return true if initialization was successful, false otherwise.
         */
        virtual bool initialize() = 0;
    };

}

#endif // IApplicationComponentBuilder_h