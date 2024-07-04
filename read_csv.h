#define MAX_LINE_SIZE 1024
#define MAX_FIELD_SIZE 20

#define USHM_BASE_ADDR			4000
#define BUFF_SIZE				1000
#define USHM_INT_BASE_IDX		(int)(USHM_BASE_ADDR/sizeof(int))
#define USHM_DOUBLE_BASE_IDX	(int)(USHM_BASE_ADDR/sizeof(int) + 2)*sizeof(int)/sizeof(double)