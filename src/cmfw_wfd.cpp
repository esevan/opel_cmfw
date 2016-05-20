#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <cmfw_log.h>
#include <cmfw_base.h>
#include <cmfw_wfd.h>
#include <uv.h>

void wfd_init()
{
	__ENTER__;
	__EXIT__;
}

void wfd_deinit()
{
	__ENTER__;
	__EXIT__;
}


//// wfd_on
static void _wfd_on_before_work_cb(uv_work_t *req)
{
	__ENTER__;


	__EXIT__;
}
static void _wfd_on_after_work_cb(uv_work_t *req, int status)
{
	__ENTER__;

	ActionListener *action_listener = (ActionListener *)req->data;
	
	//TODO Depending on the value of res, the cb should be different
	action_listener->on_success();
	
	free(action_listener);
	free(req);

	__EXIT__;
}
void wfd_on( void *main_loop, ActionListener *action_listener )
{
	__ENTER__;

	uv_work_t *req = (uv_work_t *)malloc(sizeof(uv_work_t));
	req->data = (void *)action_listener;
	uv_queue_work((uv_loop_t *)main_loop, req,\
			_wfd_on_before_work_cb, \
			_wfd_on_after_work_cb);

	__EXIT__;
}
//// ? wfd_on

//// wfd_off
void wfd_off()
{
	__ENTER__;
	__EXIT__;
}
//// ?wfd_off

//// wfd_accept
static void _wfd_accept_before_work_cb(uv_work_t *req)
{
	__ENTER__;

	int res = WFD_ERR_NONE, listen_fd, cli_fd, caddr_len;
	struct sockaddr_in saddr, caddr;
	struct hostent *h;
	AcceptListener *accept_listener = (AcceptListener *)req->data;

	do{
		if((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
			res = WFD_SOCKET_FAIL;
			break;
		}
		
	
		memset(&saddr, 0, sizeof(saddr));			
		saddr.sin_family = AF_INET;
		saddr.sin_addr.s_addr = inet_addr("192.168.49.1");
		saddr.sin_port = htons(WFD_PORT_NUM);

		int reuse = 1;
		if(setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1){
			//PORT-REUSABLE Socket
			cmfw_log("Reuse socket setting error");
		}

		
		if(bind(listen_fd, (struct sockaddr *)&saddr,\
					sizeof(saddr)) < 0){
			cmfw_log("bind_err:%s", strerror(errno));
			res = WFD_BIND_FAIL;
			break;
		}

		if(listen(listen_fd, 1) < 0){
			res = WFD_LISTEN_FAIL;
			break;
		}
		
		caddr_len = sizeof(caddr);
		cmfw_log("Server now accepting...");
		if((cli_fd = accept(listen_fd, (struct sockaddr *)&caddr,\
						(socklen_t *)&caddr_len)) < 0){
			cmfw_log("accept_err:%s", strerror(errno));
			res = WFD_ACCEPT_FAIL;
			break;
		}
		cmfw_log("Accepted!");
		

		cmfw_log("Server connected to (%s) \n",\
				inet_ntoa(*(struct in_addr *)&caddr.sin_addr));

		close(listen_fd);
		
	} while(0);

	if(res == WFD_ERR_NONE){
		accept_listener->res = cli_fd;
	}
	else{
		accept_listener->res = res;
	}
	
	__EXIT__;
}
static void _wfd_accept_after_work_cb(uv_work_t *req, int status)
{
	__ENTER__;

	AcceptListener *accept_listener = (AcceptListener *)req->data;
	
	//TODO Depending on the value of res, the cb should be different
	int sock = accept_listener->res;
	accept_listener->res = 0;

	if(sock < 0){
		//Failed
		accept_listener->on_failure(sock);
	}
	else{
		accept_listener->on_success(sock);
		close(sock);
	}

	free(accept_listener);
	free(req);

	__EXIT__;
}
void wfd_accept( void *main_loop, AcceptListener *accept_listener)
{
	__ENTER__;

	uv_work_t *req = (uv_work_t *)malloc(sizeof(uv_work_t));
	req->data = (void *)accept_listener;
	uv_queue_work((uv_loop_t *)main_loop, req,\
			_wfd_accept_before_work_cb, \
			_wfd_accept_after_work_cb);

	__EXIT__;
}
//// ?wfd_accept

//// wfd_read
void _wfd_read_before_work_cb(uv_work_t *req)
{
	__ENTER__;

	__EXIT__;
}
void _wfd_read_after_work_cb(uv_work_t *req, int status)
{
	__ENTER__;

	ReadListener *read_listener = (ReadListener *)req->data;

	//TODO Depending on the value of __private, the cb should be different
	read_listener->on_success_msg(NULL, 0);
	read_listener->on_success_file(NULL, 0, NULL, 0);

	free(read_listener);
	free(req);

	__EXIT__;
}
void wfd_read( void *main_loop, int sock, ReadListener *read_listener)
{
	__ENTER__;
	
	uv_work_t *req = (uv_work_t *)malloc(sizeof(uv_work_t));
	req->data = (void *)read_listener;
	uv_queue_work((uv_loop_t *)main_loop, req, \
			_wfd_read_before_work_cb, \
			_wfd_read_after_work_cb);

	__EXIT__;
}
//// ?wfd_read
