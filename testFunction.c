#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

// void modifyZValue(char *line, double newValue) {
//     // Find the position of 'Z' in the string
//     char* zPosition = strchr(line, 'Z');

//     if (zPosition == NULL) {
//         // The substring "Z" was not found in the line
//         return;
//     }

//     // Extract the numeric value after "Z"
//     double currentValue;
//     if (sscanf(zPosition + 1, "%lf", &currentValue) != 1) {
//         // Failed to extract the current numeric value after "Z"
//         return;
//     }
//     printf("newvalue: %lf, current value: %lf\n",newValue, currentValue);
//     // Modify the value
//     currentValue -= newValue;
    
//     // Update the value in the line
//     sprintf(zPosition + 1, "%.2f", currentValue);
//     printf("%s\n",zPosition);
// }


// int main(){
//     void modifyZValue(char *line, double newValue);
//     // char line[MAX_LINE_LENGTH];

//     char *line = "G0 F9000 X163.317 Y112.439 Z2.2";
//     modifyZValue(line,0.2);
//     printf("%s\n",line);

//     char* zPosition = strchr(line, 'Z');
//     printf("%s\n",zPosition);
//     return 0;



// }


void modifyZValue(char* line, double newValue) {
    // Find the position of 'Z' in the string
    char* zPosition = strchr(line, 'Z');

    if (zPosition != NULL) {
        // Move the pointer to the position after 'Z'
        zPosition++;
        printf("%s\n", zPosition);
        // Convert the substring after 'Z' to a double and modify it
        double currentValue = strtod(zPosition, NULL);
        sprintf(zPosition, "%.2f", currentValue - newValue);
    }
}

int main() {
    char myString1[] = "G0 F9000 X163.317 Y112.439 Z2.2";
    char myString2[] = "G1 F600 Z0.35";

    modifyZValue(myString1, 0.5); // Change Z value to 5.0
    modifyZValue(myString2, 0.15); // Change Z value to 1.5

    printf("Modified myString1: %s\n", myString1);
    printf("Modified myString2: %s\n", myString2);

    return 0;
}

