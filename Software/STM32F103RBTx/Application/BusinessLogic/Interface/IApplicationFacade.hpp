#ifndef IApplicationComponentFactory_h
#define IApplicationComponentFactory_h

#include <array>

namespace BusinessLogic
{

    class IApplicationFacade
    {
    public:
        /**
         * @brief Default constructor.
         */
        IApplicationFacade() = default;

        /**
         * @brief Default destructor.
         */
        virtual ~IApplicationFacade() = default;

        /**
         * @brief Initializes the application components.
         * @return true if initialization was successful, false otherwise.
         */
        virtual bool initialize() = 0;

        virtual bool start() = 0;
        virtual bool stop() = 0;

        virtual bool tick() = 0;
    };

}

#endif
