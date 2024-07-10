/*For more information see notes.txt in the Documentation folder */
#include <gplib.h>
#include <stdlib.h>

#define _PPScriptMode_		// for enum mode, replace this with #define _EnumMode_
#include "../../Include/pp_proj.h"
#include "read_csv.h"

int main(void)
{
	InitLibrary();  // Required for accessing Power PMAC library
	double exec_time = GetCPUClock();

	char *filename = "/var/ftp/csv_test.csv";
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Could not open file %s", filename);
        return -1;
    }
	
    // USHM buffers
    int *pushm_time;
    int *pushm_user;
    double *pushm_positions[9];
    double *pushm_velocities[9];

    pushm_time = (int *) pushm + 1000;
    pushm_user = (int *) pushm + 1001;
    
    int axis;
    for (axis = 0; axis < 9; axis++) {
        pushm_positions[axis] = (double *)(pushm + 501 + axis);
    }
    
    for (axis = 0; axis < 9; axis++) {
        pushm_velocities[axis] = (double *)(pushm + 510 + axis);
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

    #define NUM_FIELDS 19 // Actually is 20, but the increment is 19 because time and user are integers
    while (fgets(line, sizeof(line), file)) {
        char *field = strtok(line, ",");
        
        *pushm_time = atoi(field);
        field = strtok(NULL, ",");
        pushm_time += NUM_FIELDS;
        *pushm_user = atoi(field);
        field = strtok(NULL, ",");
        pushm_user += NUM_FIELDS;

        for (axis = 0; axis < 9; axis++) {
            *pushm_positions[axis] = atof(field);
            field = strtok(NULL, ",");
            pushm_positions[axis] += NUM_FIELDS;
        }
        for (axis = 0; axis < 9; axis++) {
            *pushm_velocities[axis] = atof(field);
            field = strtok(NULL, ",");
            pushm_velocities[axis] += NUM_FIELDS;
        }
        line_count++;
    }
        
    fclose(file);
	exec_time = GetCPUClock()-exec_time;
	printf("Lines number: %d\n", line_count);
	printf("Execution time: %f us\n",exec_time);
	CloseLibrary();

	return 0;
}