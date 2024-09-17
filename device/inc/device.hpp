#ifndef _DEVICE_INCLUDED_
#define _DEVICE_INCLUDED_

#define STATE_INIT              0
#define STATE_INIT_ERROR        1
#define STATE_RUN               2
#define STATE_APP_INIT          3

void DeviceInit(void);
void DeviceStep(void);
void DeviceDeInit(void);

#endif //_DEVICE_INCLUDED_