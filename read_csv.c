/*For more information see notes.txt in the Documentation folder */
#include <gplib.h>
#include <stdlib.h>

#define _PPScriptMode_		// for enum mode, replace this with #define _EnumMode_
#include "../../Include/pp_proj.h"
#include "read_csv.h"

//int initAddr(int buffer)
//{

//    return 0;
//}

int main(int argc, char *argv[])
{
	InitLibrary();  // Required for accessing Power PMAC library
	double exec_time = GetCPUClock();
    enum ptrM buffers[2] = {BufferFill_A, BufferFill_B/*, BufferFill_C*/};
    char *filename = argv[1];
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Could not open file %s", filename);
        return 1;
    }

    // USHM buffers
    int *pushm_time;
    int *pushm_user;
    double *pushm_positions[NUM_AXES];
    double *pushm_velocities[NUM_AXES];
    int buffer = atoi(argv[2]);

    // Initialize buffers address
    pushm_time = (int *) pushm + USHM_INT_BASE_IDX + (buffer * USHM_BUFF_OFFSET_INT_IDX);
    pushm_user = (int *) pushm + USHM_INT_BASE_IDX + (buffer * USHM_BUFF_OFFSET_INT_IDX) + 1;

    int axis;
    for (axis = 0; axis < NUM_AXES; axis++) {
        pushm_positions[axis] = (double *) pushm + (USHM_DOUBLE_BASE_IDX + axis) + (buffer * USHM_BUFF_OFFSET_DOUBLE_IDX);
    }

    for (axis = 0; axis < NUM_AXES; axis++) {
        pushm_velocities[axis] = (double *) pushm + (USHM_DOUBLE_BASE_IDX+NUM_AXES + axis) + (buffer * USHM_BUFF_OFFSET_DOUBLE_IDX);
    }

    char line[MAX_LINE_SIZE];
	int line_count;
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

        // TO DO: Consider used Axes - need to read M4036
        // Rename macro M4036? Currently defined as 'Axes'
        // Review file structure to have position and velocity in contiguous memory - the loops could me merged then
        for (axis = 0; axis < 9; axis++) {
            *pushm_positions[axis] = atof(field);
            field = strtok(NULL, ",");
            pushm_positions[axis] += USHM_LINE_OFFSET_DOUBLE_IDX;
        }
        for (axis = 0; axis < 9; axis++) {
            *pushm_velocities[axis] = atof(field);
            field = strtok(NULL, ",");
            pushm_velocities[axis] += USHM_LINE_OFFSET_DOUBLE_IDX;
        }
        line_count++;
    }

    fclose(file);

    // Set Buffer fill
    if(buffer < sizeof(buffers)/sizeof(buffers[0])){
        SetPtrVar(buffers[buffer],line_count);
    }

    exec_time = GetCPUClock()-exec_time;
	printf("Lines number: %d\n", line_count);
	printf("Execution time: %f us\n",exec_time);
    CloseLibrary();

	return 0;
}