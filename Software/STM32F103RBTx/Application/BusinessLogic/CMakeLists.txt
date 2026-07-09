add_library(BusinessLogic STATIC)

# Module interface files
target_sources(BusinessLogic
    PUBLIC 
        FILE_SET CXX_MODULES 
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/Modules"
        FILES
            Modules/TickableConcept.cppm
            Modules/TickDelegate.cppm
            Modules/SlotTableScheduler.cppm
            Modules/TaskId.cppm
            Modules/ApplicationComponent.cppm
            Modules/ApplicationFacade.cppm
            Modules/MeasurementCoordinator.cppm
)

target_sources(BusinessLogic 
    PRIVATE
        Src/ApplicationFacade.cpp
)

target_link_libraries(BusinessLogic PUBLIC # todo PUBLIC for unit tests, but should be PRIVATE
    Device
    Driver
#    u8g2
)

#target_include_directories(BusinessLogic PRIVATE
#    ../Library/u8g2/cppsrc
#)
