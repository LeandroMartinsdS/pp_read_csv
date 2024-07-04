/*For more information see notes.txt in the Documentation folder */
#include <gplib.h>
#include <stdlib.h>

#define _PPScriptMode_		// for enum mode, replace this with #define _EnumMode_
#include "../../Include/pp_proj.h"
#include "read_csv.h"

int main(void)
{
	InitLibrary();  // Required for accessing Power PMAC library

	char *filename = "/var/ftp/csv_test.csv";
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Could not open file %s", filename);
        return -1;
    }


    char line[MAX_LINE_SIZE];
	int line_count, column_count;

	double exec_time = GetCPUClock();
	int axis;
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

	column_count=0;
    while (fgets(line, MAX_LINE_SIZE, file)) {
        char *field = strtok(line, ",");
        column_count=0;
        while (field) {
            pshm->P[(int)(line_count+column_count*1000)]=atof(field);
            printf("P[%d]=%s ", (int)(line_count+column_count*1000),field);
            field = strtok(NULL, ",");
			column_count++;
	    }
		line_count++;
//        printf("\n");
    }
    fclose(file);
	exec_time = GetCPUClock()-exec_time;
	printf("Lines number: %d\n", line_count);
	printf("Execution time: %f us\n",exec_time);
	CloseLibrary();

	return 0;
