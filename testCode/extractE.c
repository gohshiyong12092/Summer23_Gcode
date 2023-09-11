#include <stdio.h>
#include <string.h>

int main() {
        
    char line[100];  // Adjust the buffer size as needed
    printf("Enter G-code lines:\n");
    while (fgets(line, sizeof(line), stdin)) {
        char *e_value_start = strstr(line, "E");
        
        if (e_value_start) {
            float e_value;
            if (sscanf(e_value_start, "E%f", &e_value) == 1) {
                printf("E value: %.5f\n", e_value);
            }
        }
    }

    return 0;
}
