#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 20
#define MAX_FLIGHTS 50
#define NAME_LEN 64

typedef struct {
    char name[NAME_LEN];
    int start_min; // minutes since midnight
    int end_min;
} Employee;

typedef struct {
    char number[NAME_LEN];
    int time_min; // minutes since midnight
    char assigned_to[NAME_LEN];
} Flight;

// Helper to convert "HH:MM" to minutes since midnight
int parse_time(const char *str) {
    int h, m;
    sscanf(str, "%d:%d", &h, &m);
    return h * 60 + m;
}

// Helper to convert minutes since midnight to "HH:MM"
void format_time(int min, char *out) {
    sprintf(out, "%02d:%02d", min / 60, min % 60);
}

// Read employees from file
int read_employees(const char *filename, Employee *emps) {
    FILE *f = fopen(filename, "r");
    if (!f) { perror("employees.txt"); exit(1); }
    int count = 0;
    char line[256], name[NAME_LEN], start[8], end[8];
    while (fgets(line, sizeof(line), f)) {
        if (sscanf(line, "employee \"%[^\"]\" start %7s end %7s", name, start, end) == 3) {
            strcpy(emps[count].name, name);
            emps[count].start_min = parse_time(start);
            emps[count].end_min = parse_time(end);
            count++;
        }
    }
    fclose(f);
    return count;
}

// Read flights from file
int read_flights(const char *filename, Flight *flights) {
    FILE *f = fopen(filename, "r");
    if (!f) { perror("flights.txt"); exit(1); }
    int count = 0;
    char line[256], number[NAME_LEN], at[8];
    while (fgets(line, sizeof(line), f)) {
        if (sscanf(line, "flight \"%[^\"]\" at %7s", number, at) == 2) {
            strcpy(flights[count].number, number);
            flights[count].time_min = parse_time(at);
            flights[count].assigned_to[0] = '\0'; // unassigned
            count++;
        }
    }
    fclose(f);
    return count;
}

int main() {
    Employee employees[MAX_EMPLOYEES];
    Flight flights[MAX_FLIGHTS];
    int emp_count = read_employees("employees.txt", employees);
    int flt_count = read_flights("flights.txt", flights);

    // Assign flights to employees (simple round-robin)
    int last_assigned = 0;
    for (int i = 0; i < flt_count; ++i) {
        int assigned = 0;
        for (int j = 0; j < emp_count; ++j) {
            int idx = (last_assigned + j) % emp_count;
            if (flights[i].time_min >= employees[idx].start_min &&
                flights[i].time_min <= employees[idx].end_min) {
                strcpy(flights[i].assigned_to, employees[idx].name);
                last_assigned = idx + 1;
                assigned = 1;
                break;
            }
        }
        if (!assigned) strcpy(flights[i].assigned_to, "UNASSIGNED");
    }

     FILE *out = fopen("schedule.csv", "w");
    if (!out) {
        perror("schedule.csv");
        return 1;
    }

    // Write CSV header
    fprintf(out, "Flight,Time,Assigned To\n");
    for (int i = 0; i < flt_count; ++i) {
        char t[8];
        format_time(flights[i].time_min, t);
        fprintf(out, "%s,%s,%s\n", flights[i].number, t, flights[i].assigned_to);
    }
    fclose(out);
    printf("Schedule written to schedule.csv\n");
    return 0;
}




    // Output as CSV
   /* printf("Flight,Time,Assigned To\n");
    for (int i = 0; i < flt_count; ++i) {
        char t[8];
        format_time(flights[i].time_min, t);
        printf("%s,%s,%s\n", flights[i].number, t, flights[i].assigned_to);
    }
    return 0;
}*/
