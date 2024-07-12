// File definitions
#define MAX_LINE_SIZE   5000
#define NUM_AXES        9

// Buffer definitions
#define USHM_BASE_ADDR              4000
#define USHM_INT_BASE_IDX           (int)(USHM_BASE_ADDR/sizeof(int))
#define USHM_DOUBLE_BASE_IDX        (int)(USHM_INT_BASE_IDX + 2)*sizeof(int)/sizeof(double)
#define USHM_OFFSET_ADDR            2*sizeof(int) + 2*NUM_AXES*sizeof(double)
#define USHM_OFFSET_INT_IDX         USHM_OFFSET_ADDR/sizeof(int)
#define USHM_OFFSET_DOUBLE_IDX      USHM_OFFSET_ADDR/sizeof(double)