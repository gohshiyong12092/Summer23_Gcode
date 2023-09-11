#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() {
    FILE *file = fopen("UMS5_Bunny.gcode", "r");  // Replace "your_gcode_file.gcode" with your actual file name
    
    if (file == NULL) {
        perror("Unable to open file");
        return 1;
    }
    
    int lineCount = 0;
    char ch;
    bool headerFinished = false;
    char line[1000]; 

    while (fgets(line, sizeof(line), file)) {
        // Remove leading whitespaces
        char *trimmedLine = line;
        while (*trimmedLine == ' ' || *trimmedLine == '\t') {
            trimmedLine++;
        }
        
        // Exclude comment lines and empty lines
        if (trimmedLine[0] != ';' && trimmedLine[0] != '\n') {
            lineCount++;
        }
    }


    printf("Total lines in the file: %d\n", lineCount);

    fclose(file);

    return 0;
}