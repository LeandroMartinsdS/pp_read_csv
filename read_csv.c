/*For more information see notes.txt in the Documentation folder */
#include <gplib.h>
#include <stdlib.h>
#include <errno.h>

#define _PPScriptMode_		// for enum mode, replace this with #define _EnumMode_
#include "../../Include/pp_proj.h"
#include "read_csv.h"

void write_PVT(FILE **file, int bufferNum)
{
    // USHM PVT buffers
    int *pushm_time;
    int *pushm_user;
    double *pushm_positions[NUM_AXES];
    double *pushm_velocities[NUM_AXES];
    int line_count = 0;
    // Initialize buffers addresses
    pushm_time = (int *) pushm + USHM_INT_BASE_IDX + (bufferNum * USHM_BUFF_OFFSET_INT_IDX);
    pushm_user = (int *) pushm + USHM_INT_BASE_IDX + (bufferNum * USHM_BUFF_OFFSET_INT_IDX)+1;

    int axis;
    for (axis = 0; axis < NUM_AXES; axis++) {
        pushm_positions[axis] = (double *) pushm + (USHM_DOUBLE_BASE_IDX + axis) + (bufferNum * USHM_BUFF_OFFSET_DOUBLE_IDX);
    }
    for (axis = 0; axis < NUM_AXES; axis++) {
        pushm_velocities[axis] = (double *) pushm + (USHM_DOUBLE_BASE_IDX+NUM_AXES + axis) + (bufferNum * USHM_BUFF_OFFSET_DOUBLE_IDX);
    }

    char line[MAX_LINE_SIZE];
    // Read the first line
    if (fgets(line, sizeof(line), *file) != NULL) {
        char *token = strtok(line, ",");
        while (token != NULL) {
			// Store header Data
			// ...
	        token = strtok(NULL, ",");
        }
    }

    while (fgets(line, sizeof(line), *file) && line_count < USHM_BUFF_SIZE) {
        char *field = strtok(line, ",");

        *pushm_time = atoi(field);
        field = strtok(NULL, ",");
        pushm_time += USHM_LINE_OFFSET_INT_IDX;
        *pushm_user = atoi(field);
        field = strtok(NULL, ",");
        pushm_user += USHM_LINE_OFFSET_INT_IDX;

        for (axis = 0; axis < NUM_AXES; axis++) {
            *pushm_positions[axis] = atof(field);
            field = strtok(NULL, ",");
            pushm_positions[axis] += USHM_LINE_OFFSET_DOUBLE_IDX;
        }
        for (axis = 0; axis < NUM_AXES; axis++) {
            *pushm_velocities[axis] = atof(field);
            field = strtok(NULL, ",");
            pushm_velocities[axis] += USHM_LINE_OFFSET_DOUBLE_IDX;
        }

        line_count++;
    }
}

int write_positions(FILE **file, int bufferNum)
{
    // USHM Motor positions buffers
    int *pushm_user;
    double *pushm_positions[NUM_AXES];
    int line_count = 0;      

    // Initialize buffers addresses
    pushm_user = (int *) pushm + USHM_INT_BASE_IDX + (bufferNum * USHM_BUFF_OFFSET_INT_IDX)/*+1*/;

    int axis;
    for (axis = 0; axis < NUM_AXES; axis++) {
        pushm_positions[axis] = (double *) pushm + (USHM_DOUBLE_BASE_IDX + axis) + (bufferNum * USHM_BUFF_OFFSET_DOUBLE_IDX);
    }

    char line[MAX_LINE_SIZE];
    // Read the first line
    if (fgets(line, sizeof(line), *file) != NULL) {
        char *token = strtok(line, ",");
        while (token != NULL) {
			// Store header Data
			// ...
	        token = strtok(NULL, ",");
        }
    }
    
    while (fgets(line, sizeof(line), *file) && line_count < USHM_BUFF_SIZE) {
        char *field = strtok(line, ",");

        *pushm_user = atoi(field);
        field = strtok(NULL, ",");
        pushm_user += USHM_LINE_OFFSET_INT_IDX;

        for (axis = 0; axis < NUM_AXES; axis++) {
            *pushm_positions[axis] = atof(field);
            field = strtok(NULL, ",");
            pushm_positions[axis] += USHM_LINE_OFFSET_DOUBLE_IDX;
        }
        line_count++;
    }
}

int read_csv(char **filename, int profileType, int bufferNum)
{
    FILE *file = fopen(*filename, "r");
    if (file == NULL) {
        printf("Could not open file %s", filename);
        return 1;
    }
    if (profileType == 0) {
        write_PVT(&file, bufferNum);
    } 
    else if (profileType == 1) {
        write_positions(&file, bufferNum);
    }

    fclose(file);
}

int main(int argc, char *argv[])
{
	InitLibrary();  // Required for accessing Power PMAC library
    double exec_time = GetCPUClock(); // Evaluation purposes only

    // TODO: Add argc checks, and set defaults values for profileType and bufferNum
    char *filename = argv[1];
    int profileType = atoi(argv[2]);    // 0: PVT, 1:Motors positions + User Commands
    int bufferNum = atoi(argv[3]);      // 0:BufferA, 1:BufferB, [2:BufferC]

//    int line_count;
    read_csv(&filename, profileType, bufferNum);

	exec_time = GetCPUClock()-exec_time;
//	printf("Lines number: %d\n", line_count);
	printf("Execution time: %f us\n",exec_time);
	CloseLibrary();

	return 0;
}