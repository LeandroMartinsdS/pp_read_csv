/*For more information see notes.txt in the Documentation folder */
#include <gplib.h>
#include <stdlib.h>
#include <errno.h>

#define _PPScriptMode_		// for enum mode, replace this with #define _EnumMode_
#include "../../Include/pp_proj.h"
#include "read_csv.h"

int main(int argc, char *argv[])
{
	InitLibrary();  // Required for accessing Power PMAC library
	double exec_time = GetCPUClock(); // Evaluation purposes only

    // TODO: Add argc checks, and set defaults values for profileType and bufferNum
    char *filename = argv[1];
    int profileType = atoi(argv[2]);  // 0: PVT, 1:Motors positions + User Commands
    int bufferNum = atoi(argv[3]); // 0:BufferA, 1:BufferB, [2:BufferC]

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s", filename);
        return 1;
    } // TODO: try perror instead

    char line[MAX_LINE_SIZE];
    int line_count;
    
    if (profileType == 0) {
        // TODO refactor to a  function
        // USHM PVT buffers
        int *pushm_time;
        int *pushm_user;
        double *pushm_positions[NUM_AXES];
        double *pushm_velocities[NUM_AXES];
    

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

        line_count=0;

        // Read the first line
        if (fgets(line, sizeof(line), file) != NULL) {
            char *token = strtok(line, ",");
            while (token != NULL) {
			    // Store header Data
			    // ...
	            token = strtok(NULL, ",");
            }
        }

        while (fgets(line, sizeof(line), file) && line_count < USHM_BUFF_SIZE) {
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
    else if (profileType == 1) {
        // TODO: Refactor into a function
        // USHM Motor positions buffers
        
        int *pushm_user;
        double *pushm_positions[NUM_AXES];
       
        // Initialize buffers addresses
        pushm_user = (int *) pushm + USHM_INT_BASE_IDX + (bufferNum * USHM_BUFF_OFFSET_INT_IDX);

        int axis;
        for (axis = 0; axis < NUM_AXES; axis++) {
            pushm_positions[axis] = (double *) pushm + (USHM_DOUBLE_BASE_IDX + axis) + (bufferNum * USHM_BUFF_OFFSET_DOUBLE_IDX);
        }

        line_count=0;

        // Read the first line
        if (fgets(line, sizeof(line), file) != NULL) {
            char *token = strtok(line, ",");
            while (token != NULL) {
			    // Store header Data
			    // ...
	            token = strtok(NULL, ",");
            }
        }

        while (fgets(line, sizeof(line), file) && line_count < USHM_BUFF_SIZE) {
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

    fclose(file);
	exec_time = GetCPUClock()-exec_time;
	printf("Lines number: %d\n", line_count);
	printf("Execution time: %f us\n",exec_time);
	CloseLibrary();

	return 0;
}