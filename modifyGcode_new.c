#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include <stdlib.h>
#define MAX_SIZE 100

#define MAX_LINE_LENGTH 1024

void modifyLayer(char *str, int num) {
    char *layerPtr = strstr(str, ";LAYER:"); // Find the occurrence of ";LAYER:"
    if (layerPtr != NULL) {
        int layerNumber = atoi(layerPtr + 7);
        layerNumber -= num;
        //update the string 
        snprintf(layerPtr + 7, 10, "%d\n",layerNumber);
    }
}

void modifyZValue(char* line, double newValue) {
    // Find the position of 'Z' in the string
    char* zPosition = strchr(line, 'Z');
    // printf("%s\n",line);
    if (zPosition != NULL) {
        // Move the pointer to the position after 'Z'
        zPosition++;
        
        // Convert the substring after 'Z' to a double and modify it
        double currentValue = strtod(zPosition, NULL);
        sprintf(zPosition, "%.2f\n", currentValue - newValue);
        // printf("%s\n",line);
    }
}

void modifyEValue(char* line, float currentValue, float previousValue, float initialValue, char* ePosition ) {

    // printf("%s\n",line);
    if (ePosition != NULL) {
        // Move the pointer to the position after 'Z'
        ePosition++;
        float newValue = initialValue + currentValue - previousValue;
        sprintf(ePosition, "%.2f\n", newValue);
        // printf("%s\n",line);
    }
}

int countLine(char* fileName){
    FILE *file = fopen(fileName, "r");
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
    return lineCount;
}

float getE(char* line){
    char *e_value_start = strstr(line, "E");
        
        if (e_value_start) {
            float e_value;
            if (sscanf(e_value_start, "E%f", &e_value) == 1) {
                // printf("E value: %.5f\n", e_value);
                return e_value;
            }
        }
    return -1;
}


int main(){
    void modifyLayer(char *str, int num);
    void modifyZValue(char *line, double newValue);
    void modifyEValue(char* line, float currentValue, float previousValue, float initialValue, char* ePosition ) ;
    FILE* inputFile;
    FILE* outputFile;
    char inputFileName[100];
    char outputFileName[100];
    char line[MAX_LINE_LENGTH];
    int layerToRemove;
    int numberOfLayers;
    char currentLayer[10];
    int current;

    //prompt user to enter the input file name 
    printf("Enter the input G-code file name: ");
    scanf("%99s", inputFileName);
    //prompt user to enter the output file name 
    printf("Enter the output G-code file name: ");
    scanf("%99s", outputFileName);
    //prompt user to key in the layer to remove
    printf("Enter the layer number to remove: ");
    scanf("%d", &layerToRemove);
    //prompt user to key in the number to remove
    printf("Enter the number of layer to remove: ");
    scanf("%d", &numberOfLayers);

    // int totalLine = countLine(inputFileName);
    //open the file to read 
    inputFile = fopen(inputFileName,"r");
    if(inputFile == NULL){
        perror("Error opening the input file");
        return 1;
    }
    //open the file to write
    outputFile = fopen(outputFileName,"w");
    if(outputFile == NULL){
        perror("Error opening the output file");
        return 1;
    }
    bool Flag_Target = 0;
    bool Flag_Found = 0;
    bool Flag_EReset= 0;
    // numberOfLayers = numberOfLayers;
    float ModifyVal = 0.15 * (numberOfLayers);
    int count_remove = 0;
    //tracking thte e value
    float e_before = 0;
    float e_after = 0;
    float e_current = 0;
    float e_latest = 0;
    
    // int count_RemoveLine = 0;
    // float percentage = 0;
    //find the line to remove 
    while(fgets(line,sizeof(line), inputFile) != NULL){
        char *e_value_start = strstr(line, "E");
        char *y_value_start = strstr(line, "Y");
        char *f2700_value_start = strstr(line, "F2700");
        if(strstr(line,";LAYER:") != NULL){
            sscanf(line,";LAYER:%s",&currentLayer);
            current = atoi(currentLayer);
        }
        else if(strstr(line,";LAYER_COUNT:") != NULL){
            int layerCount = atoi(line + 13);
            layerCount -= numberOfLayers;
            //update the string 
            snprintf(line +13, 15, "%d\n",layerCount);
        }
        //get the E value 
        else if (e_value_start && (line[0] != ';' ) && y_value_start) {
            float e_value;
            if (sscanf(e_value_start, "E%f", &e_value) == 1) {
                e_current = e_value;
            }
        }
        else if (strstr(line,"E0") != NULL && Flag_Found == 1){
            Flag_EReset = 1;
        }
        //found the layer to remove 
        if(current == layerToRemove && Flag_Found == 0){
            Flag_Target = 1;
            current = 0;
            e_before = e_current;
        }
        if(Flag_Target == 0){ 
            if(Flag_Found == 1 && (strstr(line,";LAYER:") != NULL)){ 
                // printf("%s\n", line);
                modifyLayer(line,numberOfLayers);
            }
            else if(Flag_Found == 1){
                //check if the string has a z value need to be updated
                modifyZValue(line,ModifyVal);
                //check if thhe string has a e value, need to look for the next e to find how much value need to add 
            //    void modifyEValue(char* line, float currentValue, float previousValue, float initialValue, char* ePosition ) 
                if (!Flag_EReset && e_value_start != NULL && y_value_start != NULL && line[0] != ';' ) {
                    
                    e_value_start++;
                    float newValue = e_before + (e_current - e_after);
                    // printf("current: %.5f, before: %.5f, after: %.5f\n",e_current, e_before, e_after);
                    sprintf(e_value_start, "%.5f\n", newValue);
                    e_after = e_current;
                    e_latest = newValue;
                }
                else if (!Flag_EReset && e_value_start != NULL && f2700_value_start != NULL &&(line[0] != ';') && y_value_start == NULL ){
                    e_value_start++;
                    float newValue = e_latest - 6.5;
                    sprintf(e_value_start, "%.5f\n", newValue);
                    printf("current: %.5f, before: %.5f, after: %.5f\n",e_current, e_before, e_after);
                }
            }
            
            fputs(line, outputFile);
        }
        else if(Flag_Target == 1){
            if(strstr(line,"TIME_ELAPSED:") != NULL && (count_remove < numberOfLayers)){
                count_remove += 1;
                
                
            }

            if((strstr(line,"TIME_ELAPSED:") != NULL) && (count_remove == numberOfLayers)){
                
                Flag_Target = 0;
                Flag_Found = 1;
                e_after = e_current;
                
            }
        }
    }

    fclose(inputFile);
    return 0;

}