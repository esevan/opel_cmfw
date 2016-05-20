#ifndef __CMFW_BASE_H__
#define __CMFW_BASE_H__
typedef struct {
	void (*on_success)(void);
	void (*on_failure)(int reason);
	int res;
} ActionListener;

typedef struct {
	void (*on_success)(int sock);
	void (*on_failure)(int reason);
	int res;
} AcceptListener;

typedef struct{
	unsigned int file_size;
	unsigned char src_file_name_len;
	unsigned char *src_file_name;
	unsigned char dest_file_name_len;
	unsigned char *dest_file_name;
} FileHeader;

typedef union {
	unsigned int total_data_size;
	unsigned char *data;
} MessageHeader;

typedef struct {
	unsigned char header_id;
	unsigned char header_info;
	unsigned short payload_size;
	unsigned int curr_offset;
	void *header_ptr;
} CmfwHeader;

#define __file_bit 0x80
#define __data_bit 0x40
#define __end_bit 0x20
#define __reserved_mask 0x1F

#define IsFile(x) ((((x)->header_info) & __file_bit) == __file_bit)
#define IsMsg(x) ((((x)->header_info) & __file_bit) == 0x00)

#define IsData(x) ((((x)->header_info) & __data_bit) == __data_bit)
#define IsHeader(x) ((((x)->header_info) & ___data_bit) == 0x00)

#define IsLast(x) ((((x)->header_info) & __end_bit) == __end_bit)

#define ReservedInfo (((x)->header_info) & __reserved_mask)

typedef struct {
	void (*on_success_msg)(char *data, int len);
	void (*on_success_file)(FileHeader *header, unsigned int curr_offset, char *data, int len);
	void (*on_failure)(int reason);
	void *__private;
} ReadListener;
#endif //?__CMFW_BASE_H__
