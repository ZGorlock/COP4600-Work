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
  int index;
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
	FILE *input = fopen("processes.in", "r");

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
				ps[pcount].index = pcount;
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
		fprintf(output, "Using First Come First Served\n\n");
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
	int p = 0;
	while (p < processCount) {
		int i;
			for (i = 0; i < processCount; i++) {
				if (ps[i].index == p) {
				fprintf(output, "%s wait %d turnaround %d\n", ps[i].name, ps[i].wait, ps[i].turnaround);
				p++;
			}
		}
	}

	fclose(output);
}

void fcfs() {

	int i,j;
	int currProcess = 0;
	int arrived = -1;
	int running = -1;
	struct process temp;

	//Sort processes by arrival time
	for(i=0;i<processCount;i++)
	{
		temp = ps[i];
		for(j=i+1;j<processCount;j++)
		{
			if(ps[i].arrival > ps[j].arrival)
			{
				ps[i] = ps[j];
				ps[j] = temp;
			}
		}
	}

	//Time frame for processes to run
	for(i=0;i<runFor;i++)
	{
		//Loop through processes
		for(j=0;j<processCount;j++)
		{
			//Print arrival of a process and signal arrival
			if(ps[j].arrival == i)
			{
				fprintf(output,"Time %d: %s arrived\n",i,ps[j].name);
				arrived = 0;
			}
		}

		//Select process to run
		if(arrived != -1 && running == -1)
		{
			fprintf(output,"Time %d: %s selected (burst %d)\n",i,ps[currProcess].name,ps[currProcess].burst);
			running = 0;
		}

		//Run Process
		if(running != -1)
		{
			ps[currProcess].burst--;
			if(ps[currProcess].burst == 0)
			{
				fprintf(output,"Time %d: %s finished\n", i+1, ps[currProcess].name);
				ps[currProcess].turnaround = (i+1) - ps[currProcess].arrival;
				ps[currProcess].wait = ps[currProcess].turnaround - ps[currProcess].run;
				running = -1;
				currProcess++;
			}
		}
	}

	fprintf(output, "Finished at time %d\n", i);
}

void sjf() {
	int t;
	int i;
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
	int i, j;
	struct process temp;

	//Sort processes by arrival time
	for (i = 0;i<processCount;i++) {
		temp = ps[i];
		for (j = i + 1;j<processCount;j++) {
			if (ps[i].arrival > ps[j].arrival) {
				ps[i] = ps[j];
				ps[j] = temp;
			}
		}
	}

  int t;
  int p = -1;
  int oldp = -1;
  int q = 0;
  int finished = 0;
  for (t = 0; t < runFor; t++) {

    if (p != -1) {
      ps[p].burst--;
      q++;

      int done = 0;
      if (ps[p].burst == 0) {
        fprintf(output, "Time %d: %s finished\n", t, ps[p].name);
        ps[p].turnaround = t - ps[p].arrival;
        ps[p].wait = ps[p].turnaround - ps[p].run;
        done = 1;
      }
      else if (q == quantum) {
        done = 1;
      }

      if (done == 1) {
        oldp = p;
        p = -1;
        q = 0;

        finished = 1;
        for (i = 0; i < processCount; i++) {
          if (ps[i].burst > 0) {
            finished = 0;
            break;
          }
        }
      }
    }

    if (finished == 0) {
      for (i = 0; i < processCount; i++) {

        if (ps[i].arrival == t) {
          fprintf(output, "Time %d: %s arrived\n", t, ps[i].name);
        }
      }

      if (p == -1) {
        if (oldp == -1) {
          for (i = 0; i < processCount; i++) {
            if (ps[i].arrival <= t && ps[i].burst > 0) {
              p = i;
              fprintf(output, "Time %d: %s selected (burst %d)\n", t, ps[p].name, ps[p].burst);
              break;
            }
          }
        } else {
          int hit = 0;
          for (i = oldp + 1; i < processCount; i++) {
            if (ps[i].arrival <= t && ps[i].burst > 0) {
              p = i;
              fprintf(output, "Time %d: %s selected (burst %d)\n", t, ps[p].name, ps[p].burst);
              hit = 1;
              break;
            }
          }
          if (hit == 0) {
            for (i = 0; i <= oldp; i++) {
              if (ps[i].arrival <= t && ps[i].burst > 0) {
                p = i;
                fprintf(output, "Time %d: %s selected (burst %d)\n", t, ps[p].name, ps[p].burst);
                break;
              }
            }
          }
        }
      }

    } else {
      fprintf(output, "Time %d: IDLE\n", t);
    }

  }

  fprintf(output, "Finished at time %d\n", t);
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
