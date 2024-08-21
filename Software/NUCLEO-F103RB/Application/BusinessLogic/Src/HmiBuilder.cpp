#include "HmiBuilder.hpp"

#include "DisplayPixelColor.hpp"

namespace BusinessLogic
{

    HmiBuilder::HmiBuilder(IHmiFactory &hmiFactory)
        : hmiDataModel(hmiFactory.getDataModel()),
          hmiInputController(hmiFactory.getInputController()),
          hmiViewManager(hmiFactory.getHmiViewManager())
    {
    }

    bool HmiBuilder::initialize()
    {

        // todo ret value
        hmiDataModel.initialize();
        hmiInputController.initialize();
        hmiViewManager.initialize();

        return true;
    }

    bool HmiBuilder::start()
    {

        // todo ret value
        hmiDataModel.start();
        hmiInputController.start();

        hmiViewManager.start();

        return true;
    }

    bool HmiBuilder::stop()
    {
        /*
        // todo ret value
        hmiDataModel.stop();
        hmiInputController.stop();
        hmiViewManager.stop();
  */
        return true;
    }

    bool HmiBuilder::tick()
    {

        // todo ret value
        // hmiDataModel.tick();
        hmiInputController.tick();
        // hmiViewManager.tick();

        return true;
    }
}
