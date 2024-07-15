// File definitions
#define MAX_LINE_SIZE   1024
#define MAX_LINES       1000
#define NUM_AXES        9


// Buffer definitions
// Base Address
#define USHM_BASE_ADDR              4000
// Base indices
#define USHM_INT_BASE_IDX           (int)(USHM_BASE_ADDR/sizeof(int))
#define USHM_DOUBLE_BASE_IDX        (int)((USHM_INT_BASE_IDX+ 2)*sizeof(int)/sizeof(double))

#define USHM_LINE_OFFSET_ADDR            (int)(2*sizeof(int)+2*NUM_AXES*sizeof(double))
#define USHM_LINE_OFFSET_INT_IDX         (int)(USHM_LINE_OFFSET_ADDR/sizeof(int))
#define USHM_LINE_OFFSET_DOUBLE_IDX      (int)(USHM_LINE_OFFSET_ADDR/sizeof(double))


#define USHM_BUFF_SIZE                   1000

#define USHM_BUFF_OFFSET_ADDR            (int)((USHM_BUFF_SIZE)*USHM_LINE_OFFSET_ADDR)
#define USHM_BUFF_OFFSET_INT_IDX         (int)(USHM_BUFF_OFFSET_ADDR/sizeof(int))
#define USHM_BUFF_OFFSET_DOUBLE_IDX      (int)(USHM_BUFF_OFFSET_ADDR/sizeof(double))