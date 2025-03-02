// File definitions
#define _RT_MODE_
#define MAX_LINES       1001
#define NUM_AXES        8
#define INT_CHARS       2*11
#define DOUBLE_CHARS    NUM_AXES*25 // 2*NUM_AXES*25  for PVT
#define COMMA_CHARS     NUM_AXES+2  // 2*NUM_AXES+2 for PVT
#ifdef _RT_MODE
    #define DOUBLE_CHARS    NUM_AXES*25
#elif _PVT_MODE
    #define DOUBLE_CHARS    2*NUM_AXES*25 // 2*NUM_AXES*25  for PVT
#endif
#define MAX_LINE_SIZE   INT_CHARS+DOUBLE_CHARS+COMMA_CHARS+1

// Buffer definitions
// Base Address
#define USHM_BASE_ADDR              4000
// Base indices
#define USHM_INT_BASE_IDX           (int)(USHM_BASE_ADDR/sizeof(int))
#define USHM_DOUBLE_BASE_IDX        (int)((USHM_INT_BASE_IDX+ 2)/(sizeof(double)/sizeof(int)))

// 2*NUM_AXES is only when writing PVT
#ifdef _RT_MODE_
    #define USHM_LINE_OFFSET_ADDR            (int)(2*sizeof(int)+NUM_AXES*sizeof(double))
#elif _PVT_MODE_
    #define USHM_LINE_OFFSET_ADDR            (int)(2*sizeof(int)+2*NUM_AXES*sizeof(double))
#endif

#define USHM_LINE_OFFSET_INT_IDX         (int)(USHM_LINE_OFFSET_ADDR/sizeof(int))
#define USHM_LINE_OFFSET_DOUBLE_IDX      (int)(USHM_LINE_OFFSET_ADDR/sizeof(double))

#define USHM_BUFF_SIZE                   1000

#define USHM_BUFF_OFFSET_ADDR            (int)((USHM_BUFF_SIZE)*USHM_LINE_OFFSET_ADDR)
#define USHM_BUFF_OFFSET_INT_IDX         (int)(USHM_BUFF_OFFSET_ADDR/sizeof(int))
#define USHM_BUFF_OFFSET_DOUBLE_IDX      (int)(USHM_BUFF_OFFSET_ADDR/sizeof(double))
