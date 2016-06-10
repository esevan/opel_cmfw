#include <uv.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <opel_cmfw.h>

int main()
{
	//uv_work_t main_req;
	//uv_queue_work(uv_default_loop(), &main_req, on_create, after_create);
	//uv_run(uv_default_loop(), UV_RUN_DEFAULT);
	//bt_init();
	//int bt_sock = bt_open( CMFW_DEFAULT_PORT );
	//int bt_cli = bt_accept( CMFW_DEFAULT_PORT );

	char buf[4096];

	cmfw_init();
	while(1){
		cmfw_open( CMFW_DEFAULT_PORT );
		cmfw_accept( CMFW_DEFAULT_PORT );
		while(1){
			if(cmfw_recv_msg( CMFW_DEFAULT_PORT, buf, 4096 ) == 0){
				printf("%s\n", buf);
				if(strcmp(buf, "file_transfer") == 0){
					printf("File Transfer request\n");
					if(cmfw_recv_file( CMFW_DEFAULT_PORT, "./res" ) == CMFW_E_NONE)
						printf("File receving done\n");

				}
				/*char *test_str = "OPEL Test String";
				char data[4096];
				int i;
				for(i=0; i<4096; i++){
					data[i] = (char)(i);
				}
				int res = cmfw_send_msg( CMFW_DEFAULT_PORT, test_str, strlen(test_str)+1);
				res = cmfw_send_msg( CMFW_DEFAULT_PORT, data, 4096 );
				*/
			}
			else{
				cmfw_close( CMFW_DEFAULT_PORT );
				printf("Connection closed\n");
				break;
			}

		}
	}



	//cmfw_log("%d connected", bt_cli);

	return 0;
}
