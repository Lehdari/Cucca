#include "../../include/UnitTests/UnitTest3.hpp"


#if CURRENT_TEST == 3


#include "../../include/Core/Device.hpp"
#include "../../include/CoreExtensions/Canvas_SFML.hpp"


int unitTest(void) {
    Device<Canvas_SFML> device;
    device.renderLoop();
    return 0;
}


#endif // CURRENT_TEST
