#include "USBTransportPlugin.h"

#define VENDOR_UNITREND 0x5656
#define DEVICE_UT2025C  0x0834

const USBTransportPlugin::device_ids_t USBTransportPlugin::m_devices[] = {
    { VENDOR_UNITREND, DEVICE_UT2025C },
    { 0xF4EC, 0xEE38 },
    { 0, 0 }
};

