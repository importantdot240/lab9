#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
    struct RecordType *next;// create a next pointer (for linkedlist structure)

};

// Fill out this structure
struct HashType
{
    struct RecordType *p;// create a pointer to a RecordType
};

// Compute the hash function
int hash(int x, int tableSize)
{
    // hash function is x % tableSize
    int i = x % tableSize;

    return i;
}

// parses input file to an integer array
int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
            pRecord->next = NULL;
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// insert record into the hash table
void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
    int index = hash(record->id, tableSize);// call the hash function to get the index

    if(hashTable[index].p == NULL){// if the RecordType at that index is NULL
        hashTable[index].p = record;
    }
    else{
        struct RecordType *temp = (hashTable + index)->p;
        while(temp->next != NULL){
            temp = temp->next;
        }
        // traverse to the end of the linkedlist and add 'record' to the end of it
        temp->next = record;
        temp->next->next = NULL;
    }
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *hashTable, int tableSize)
{
    int i;
    for(i = 0; i<tableSize; i++){
        if((hashTable + i)->p != NULL){
            struct RecordType *t = (hashTable + i)->p;
            printf("\nIndex %d", i+1);

            while(t != NULL){
                printf("-> %d, %c, %d", t->id, t->name, t->order);
                t = t->next;
            }
            printf(" -> NULL");
        }

    }// for each entry in the table
    // print the contents in that index
    // The output should look like this (for example): "Index 1 -> 21715, Q, 16 -> 28876, a, 26 -> NULL"
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords); // parse returns the amount of data inside of input txt
    printRecords(pRecords, recordSz);


    // Initialize the hash table
    // create a variable hashTableSize and assign it a value
    // initialize a hashTable, use calloc (so everything is assigned to NULL)
    int hashTableSize = 11;
    struct HashType *hash_table = calloc(hashTableSize, sizeof(struct HashType)); //hashtype has recordtype structs in it

    // for each record in pRecords, insert it into the hash table using the insertRecord function
    // call the display records function
    int x;
    for(x=0; x<recordSz; x++){
        insertRecord(hash_table, &pRecords[x], hashTableSize);
    }
    displayRecordsInHash(hash_table,hashTableSize);
    // free all the allocated memory
    free(hash_table);
    free(pRecords);

    return 0;
}
