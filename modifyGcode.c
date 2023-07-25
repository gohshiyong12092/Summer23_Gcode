#include<stdio.h>

#define MAX_LINE_LENGTH 1024

int main(){
    FILE* inputFile;
    FILE* outputFile;
    char inputFileName[100];
    char outputFileName[100];
    char line[MAX_LINE_LENGTH];
    int layerToRemove;
    int numberOfLayers;
    char currentLayer[10];
    // int currentLayer;

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

    //find the line to remove 
    while(fgets(line,sizeof(line), inputFile) != NULL){
        if(strstr(line,";LAYER:") != NULL){
            sscanf(line,";LAYER:%s",&currentLayer);
            printf("%s\n",currentLayer);
        }

        if(currentLayer == layerToRemove){
            printf("Found Line: %d\n",line);
            break;
        }
    }

    fclose(inputFile);
    return 0;

}