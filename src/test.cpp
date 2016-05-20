#include <uv.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmfw_log.h>
#include <cmfw_base.h>
#include <cmfw_bt.h>
#include <cmfw_wfd.h>

static void wfd_on_success();
static void wfd_on_failure(int reason);
static void wfd_accept_on_success();
static void wfd_accept_on_failure(int reason);

static void wfd_read_on_success_msg(char *data, int len);
static void wfd_read_on_success_file(FileHeader *header, unsigned int curr_offset, char *data, int len);
static void wfd_read_on_failure(int reason);

static void wfd_read_on_success_msg(char *data, int len)
{
	__ENTER__;
	cmfw_log("Msg transmitted");
	__EXIT__;
}
static void wfd_read_on_success_file(FileHeader *header, unsigned int curr_offset, char *data, int len)
{
	__ENTER__;
	cmfw_log("File transmitted");
	__EXIT__;
}
static void wfd_read_on_failure(int reason)
{
	__ENTER__;
	cmfw_log("read failure");
	__EXIT__;
}
static void wfd_accept_on_success(int sock)
{
	__ENTER__;
	ReadListener *wfd_read_listener = (ReadListener *)malloc(sizeof(ReadListener));
	wfd_read_listener->on_success_msg = wfd_read_on_success_msg;
	wfd_read_listener->on_success_file = wfd_read_on_success_file;
	wfd_read_listener->on_failure = wfd_read_on_failure;
	wfd_read( (void *)uv_default_loop(), 0, wfd_read_listener);
	__EXIT__;
}
static void wfd_accept_on_failure(int reason)
{
	__ENTER__;
	cmfw_log("WFd accept failed");
	__EXIT__;
}
static void wfd_on_success()
{
	__ENTER__;
	AcceptListener *wfd_accept_handler = (AcceptListener *)malloc(sizeof(AcceptListener));
	wfd_accept_handler->on_success = wfd_accept_on_success;
	wfd_accept_handler->on_failure = wfd_accept_on_failure;
	wfd_accept( (void *)uv_default_loop(), wfd_accept_handler );
	__EXIT__;
}
static void wfd_on_failure(int reason)
{
	__ENTER__;
	//wfd_off();
	//wfd_on( (void *)uv_default_loop(), &wfd_on_handler );
	__EXIT__;
}


static void on_create(uv_work_t *req){
	__ENTER__;
	/*
	   When async function call is invoked, the listener should be passed in DYNAMICALLY allocated form.
	*/
	//ActionListener *bt_accept_handler = (ActionListener *)malloc(sizeof(ActionListener));
	ActionListener *wfd_on_handler = (ActionListener *)malloc(sizeof(ActionListener));
	//bt_init();
	wfd_init();
	
	//bt_try_connect((void *)uv_default_loop(), &bt_accept_handler);

	wfd_on_handler->on_success = wfd_on_success;
	wfd_on_handler->on_failure = wfd_on_failure;
	wfd_on((void *)uv_default_loop(), wfd_on_handler);

	__EXIT__;
}
static void after_create(uv_work_t *req, int stat){
	__ENTER__;
	cmfw_log("Application creation done");
	__EXIT__;
}

int main()
{
	uv_work_t main_req;
	uv_queue_work(uv_default_loop(), &main_req, on_create, after_create);
	uv_run(uv_default_loop(), UV_RUN_DEFAULT);
	return 0;
}
