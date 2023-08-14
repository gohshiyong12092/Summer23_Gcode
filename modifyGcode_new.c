#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include <stdlib.h>

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
int main(){
    void modifyLayer(char *str, int num);
    void modifyZValue(char *line, double newValue);
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
    // numberOfLayers = numberOfLayers;
    float ModifyVal = 0.15 * (numberOfLayers);
    int count_remove = 0;
    
    //find the line to remove 
    while(fgets(line,sizeof(line), inputFile) != NULL){
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

        if(current == layerToRemove && Flag_Found == 0){
            Flag_Target = 1;
            current = 0;
        }
        if(Flag_Target == 0){
            if(Flag_Found == 1 && (strstr(line,";LAYER:") != NULL)){
                // printf("%s\n", line);
                modifyLayer(line,numberOfLayers);
            }
            else if(Flag_Found == 1){
                modifyZValue(line,ModifyVal);
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
            }
        }
    }

    fclose(inputFile);
    return 0;

}