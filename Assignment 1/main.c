#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void schedule();
void fcfs();
void sjf();
void rr();
void readInputFile();
void printData();

struct process { //process structure
  char* name;
  int arrival;
  int burst;
  int run;
  int wait;
  int turnaround;
};

int processCount;
int runFor;
char* algorithm;
int quantum;
struct process* ps; //list of processes
FILE* output;

int main(void) {
	readInputFile();
	//printData();
	schedule();

	return 0;
}

void readInputFile() {
	FILE *input = fopen("process.in", "r");

	char data[128];
	int pcount = -1;
	while (fgets(data, 128, input) != NULL) {
		char* token = strtok(data, " ");
		while (token) {
			if (strcmp(token, "#") == 0 || strcmp(token, "end") == 0) {
				break;
			}

			if (strcmp(token, "processcount") == 0) {
				token = strtok(NULL, " ");
				processCount = atoi(token);
				ps = calloc(processCount, sizeof(struct process));
			}
			if (strcmp(token, "runfor") == 0) {
				token = strtok(NULL, " ");
				runFor = atoi(token);
			}
			if (strcmp(token, "use") == 0) {
				token = strtok(NULL, " ");
				algorithm = malloc(strlen(token) + 1);
				strcpy(algorithm, token);
			}
			if (strcmp(token, "quantum") == 0) {
				token = strtok(NULL, " ");
				quantum = atoi(token);
			}

			if (strcmp(token, "process") == 0) {
				pcount++;
			}
			if (strcmp(token, "name") == 0) {
				token = strtok(NULL, " ");
				ps[pcount].name = malloc(strlen(token) + 1);
				strcpy(ps[pcount].name, token);
			}
			if (strcmp(token, "arrival") == 0) {
				token = strtok(NULL, " ");
				ps[pcount].arrival = atoi(token);
			}
			if (strcmp(token, "burst") == 0) {
				token = strtok(NULL, " ");
				ps[pcount].burst = atoi(token);
				ps[pcount].run = ps[pcount].burst;
			}

			token = strtok(NULL, " ");
		}
	}

	fclose(input);
}

void schedule() {
	output = fopen("processes.out", "w");
	fprintf(output, "%d processes\n", processCount);

	if (strcmp(algorithm, "fcfs") == 0) {
		fprintf(output, "Using First Come First Serve\n\n");
		fcfs();
	} else if (strcmp(algorithm, "sjf") == 0) {
		fprintf(output, "Using Shortest Job First (Pre)\n\n");
		sjf();
	} else if (strcmp(algorithm, "rr") == 0) {
		fprintf(output, "Using Round-Robin\n");
		fprintf(output, "Quantum %d\n\n", quantum);
		rr();
	} else {
		fprintf(output, "Unknown Algorithm");
		fclose(output);
		return;
	}

	fprintf(output, "\n");
	int i;
	for (i = 0; i < processCount; i++) {
		fprintf(output, "%s wait %d turnaround %d\n", ps[i].name, ps[i].wait, ps[i].turnaround);
	}

	fclose(output);
}

void fcfs() {

}

void sjf() {
	int t;
	int p = -1;
	int oldp = -1;
	for (t = 0; t < runFor; t++) {

		if (p != -1) {
			ps[p].burst--;
			if (ps[p].burst == 0) {
				fprintf(output, "Time %d: %s finished\n", t, ps[p].name);
				ps[p].turnaround = t - ps[p].arrival;
				ps[p].wait = ps[p].turnaround - ps[p].run;
				p = -1;
			}
		}

		int i;
		for (i = 0; i < processCount; i++) {

			if (ps[i].arrival == t) {
				fprintf(output, "Time %d: %s arrived\n", t, ps[i].name);
			}
			if (ps[i].arrival <= t && ps[i].burst > 0) {
				if (p == -1) {
					p = i;
				} else {
					if (ps[i].burst < ps[p].burst) {
						p = i;
					}
				}
			}
		}

		if (p == -1) {
			fprintf(output, "Time %d: IDLE\n", t);
		} else {
			if (p != oldp) {
				fprintf(output, "Time %d: %s selected (burst %d)\n", t, ps[p].name, ps[p].burst);
				oldp = p;
			}
		}
	}

	fprintf(output, "Finished at time %d\n", t);
}

void rr() {

}

void printData() {
	printf("%d\n", processCount);
	printf("%d\n", runFor);
	printf("%s\n", algorithm);
	printf("%d\n", quantum);
	printf("\n");

	int i;
	for (i = 0; i < processCount; i++) {
		printf("%s\n", ps[i].name);
		printf("%d\n", ps[i].arrival);
		printf("%d\n", ps[i].burst);
		printf("\n");
	}
}
