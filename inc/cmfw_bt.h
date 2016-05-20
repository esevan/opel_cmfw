#ifndef __CMFW_BT_H__
#define __CMFW_BT_H__
#include <cmfw_base.h>
void bt_init();
void bt_try_connect( void *main_loop, ActionListener *action_listener );
#endif //?__CMFW_BT_H__


