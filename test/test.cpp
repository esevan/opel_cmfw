#include <cmfw_log.h>
#include <uv.h>
#include <stdio.h>

static void on_create(uv_work_t *req){
	__ENTER__;

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
	uv_queue_work(uv_default_loop(), &main_req, after_create);
	uv_run(uv_default_loop(), UV_RUN_DEFAULT);
	return 0;
}
