#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Print Menu options */
void printMenu() {
    printf("Main Menu:\n");
    printf("1. Load RAW DNA data\n");
    printf("2. Display RAW Data\n");
    printf("3. Count Chromosome Records\n");
    printf("4. Display Chromosome Data\n");
    printf("5. Search for DNA at Position\n");
    printf("6. Exit System\n");
}

/* Define struct DNASequence to represent DNA at a particular location */
typedef struct {
    char rsid[12];
    int chromosome;
    long position;
    char allele1;
    char allele2;
} DNASequence;

DNASequence sequences[160];

/* Load data from file called “dna_data.txt," counts the number of records
and displays them in sequences array */
int loadData() {
    FILE *dnaPtr = fopen("dna_data.txt", "r");

    if (dnaPtr == NULL) {
        printf("Error: dna_data.txt file does not exist. Exiting application.\n");
        return 1;
    }

    /* Count the number of lines in the file and display the result on screen. */
    int count = 0;
    char data[200];

    while (fgets(data, 200, dnaPtr) != NULL) {
        count++;
    }

    printf("Number of records in file: %d\n", count);

    /* Rewind the file pointer to the start of the file */
    rewind(dnaPtr);

    int i = 0;

    while (fgets(data, 200, dnaPtr) != NULL) {
        sscanf(data, "%s %d %ld %c %c", sequences[i].rsid,
               &sequences[i].chromosome, &sequences[i].position,
               &sequences[i].allele1, &sequences[i].allele2);
        i++;
    }

    fclose(dnaPtr);

    return 0;
}

/* Displays the data in dna_data.txt 40 records at a time in a formatted list */
void displayData() {
    int start = 0;
    int count = 40;

    while (start <= 160) {
        printf("RSID\tChromosome\tPosition\tAllele1\t\tAllele2\n");
        printf("===============================================================\n");

        for (int i = start; i < start + count && i < 160; i++) {
            printf("%s\t%d\t\t%ld\t\t%c\t\t%c\n", sequences[i].rsid,
                   sequences[i].chromosome, sequences[i].position,
                   sequences[i].allele1, sequences[i].allele2);
        }

        start += count;
    }
}

/* Count the number of records for a given chromosome */
void countChromosomes() {
    int chromosome;
    printf("Enter a chromosome number: ");
    scanf("%d", &chromosome);

    int count = 0;

    for (int i = 0; i < 160; i++) {
        if (sequences[i].chromosome == chromosome) {
            count++;
        }
    }

    printf("There are %d records for chromosome %d\n", count, chromosome);
}

/* Display data associated with a given chromosome */
void displayChromosomes() {
    int chromosome;
    printf("Enter a chromosome number: ");
    scanf("%d", &chromosome);

    printf("RSID\tChromosome\tPosition\tAllele1\tAllele2\n");
    printf("===============================================================\n");

    for (int i = 0; i < 160; i++) {
        if (sequences[i].chromosome == chromosome) {
            printf("%s\t%d\t\t%ld\t\t%c\t\t%c\n", sequences[i].rsid,
                   sequences[i].chromosome, sequences[i].position,
                   sequences[i].allele1, sequences[i].allele2);
        }
    }
}

/* Display allele1 and allele2 of a given rsid */
void searchRSID() {
    char rsid[12];
    printf("Enter an rsid: \n");
    scanf("%s", rsid);

    for (int i = 0; i < 160; i++) {
        if (strcmp(sequences[i].rsid, rsid) == 0) {
            printf("Allele1: %c\n", sequences[i].allele1);
            printf("Allele2: %c\n", sequences[i].allele2);
            return;
        }
    }
}

/* Exit application */
void exitDDAA() {
    /* Save chromosome data to a file */
    FILE *dnaPtr2 = fopen("dna_data_saved.txt", "w");

    if (dnaPtr2 == NULL) {
        printf("Could not open dna_data_saved.txt for writing.\n");
        return;
    }

    for (int i = 0; i < 160; i++) {
        fprintf(dnaPtr2, "%s %d %ld %c %c\n", sequences[i].rsid,
                sequences[i].chromosome, sequences[i].position,
                sequences[i].allele1, sequences[i].allele2);
    }

    /* Close the file */
    fclose(dnaPtr2);

    printf("Chromosome data saved to dna_data_saved.txt\n");

    /* Exit the program */
    exit(0);
}

/* Function main begins program execution */
int main() {
    if (loadData() != 0) {
        return 1;
    }

    int choice;

    while (1) {
        printMenu();
        printf
("Please enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                loadData();
                break;
            case 2:
                displayData();
                break;
            case 3:
                countChromosomes();
                break;
            case 4:
                displayChromosomes();
                break;
            case 5:
                searchRSID();
                break;
            case 6:
                exitDDAA();
                return 0;
            default:
                printf("Invalid choice. Please try again\n");
                break;
        }
    }

    return 0;
}
