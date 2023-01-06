#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
	char chunk[128];
	size_t len = sizeof(chunk);
	char* backup = "";
	char* line = malloc(len);
	FILE* fp = fopen("input.txt", "r");
	file = fopen("output.txt", "a");

	fopen("output.txt", "w");


	/*backup = malloc(len); what is this*/
	if (line == NULL) {
		perror("Unable to allocate memory for the line buffer.");
		exit(1);
	}

	line[0] = '\0';
	

	while (fgets(chunk, sizeof(chunk), fp) != NULL) {
		size_t len_used = strlen(line);
		
		size_t chunk_used = strlen(chunk);

		if (len - len_used < chunk_used) {
			len *= 2;
			if ((line = realloc(line, len)) == NULL) {
				perror("Unable to reallocate memory for the line buffer.");
				free(line);
				exit(1);

			}
		}
		/*strncpy(line + len_used, chunk, len - len_used);*/
		strncpy(line +len_used, chunk, len - len_used);
		len_used += chunk_used;

		if (strcmp(backup,chunk) != 0)
		{
			FILE* file;
			/*return line;*/
			file = fopen("output.txt", "a");
			fprintf(file, "%s",chunk); /*chunk print*/
			/*fprintf(file, "%s", "\n");*/
			backup = malloc(len); /*what is this bogus*/
			strcpy(backup, chunk); /*swapped to chunk*/

		}

		
	}
	
	fclose(fp);
	fclose("output.txt");
	free(line);

	return 0;
	
}





