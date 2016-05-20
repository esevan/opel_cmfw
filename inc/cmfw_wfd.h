#ifndef __CMFW_WFD_H__
#define __CMFW_WFD_H__
#include <cmfw_base.h>

#define WFD_PORT_NUM 9488

enum {
	WFD_ERR_NONE = 0,
	WFD_SOCKET_FAIL = -1,
	WFD_BIND_FAIL = -2,
	WFD_LISTEN_FAIL = -3,
	WFD_ACCEPT_FAIL = -4
};
void wfd_init();
void wfd_deinit();

//This listeners should be freed in after_work_cb
void wfd_on( void *main_loop, ActionListener *action_listener );
void wfd_off();
void wfd_accept( void *main_loop, AcceptListener *accept_listener);

void wfd_read( void *main_loop, int sock, ReadListener *read_listener );

#endif //?__CMFW_WFD_H__
