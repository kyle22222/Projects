#include "defs.h"

//initializes room
RoomType *createRoom(const char *name){
    RoomType *newRoom = (RoomType *)malloc(sizeof(RoomType));

    if (newRoom != NULL)
    {
        // Initialize the room's name
        strncpy(newRoom->name, name, MAX_STR - 1);
        newRoom->name[MAX_STR - 1] = '\0';

        // Initialize other properties of the room
        newRoom->connectedRooms = NULL;
        newRoom->evidenceInRoom = NULL;
        newRoom->huntersInRoom = NULL;
        newRoom->ghostInRoom = NULL;

        // Initialize semaphore for thread safety
        if (sem_init(&newRoom->roomSemaphore, 0, 1) != 0)
        {
            // Handle semaphore initialization failure
            free(newRoom);
            return NULL;
        }
    }
    return newRoom;
}

//connects rooms together both ways
void connectRooms(RoomType *room1, RoomType *room2){
    if (room1 == NULL || room2 == NULL)
    {
        return; // Either room is NULL, cannot establish connection
    }

    RoomNode *node1 = (RoomNode *)malloc(sizeof(RoomNode));
    RoomNode *node2 = (RoomNode *)malloc(sizeof(RoomNode));

    if (node1 == NULL || node2 == NULL)
    {
        // Handle memory allocation failure
        free(node1); // Free node1 if it was allocated
        free(node2); // Free node2 if it was allocated
        return;
    }

    // Establish bi-directional connection
    node1->room = room2;
    node1->next = room1->connectedRooms;
    room1->connectedRooms = node1;

    node2->room = room1;
    node2->next = room2->connectedRooms;
    room2->connectedRooms = node2;
}

//deallocates memory of room
void destroyRoom(RoomType *room){
    if (room == NULL) {
        return;
    }

    // Free connected room nodes
    RoomNode *current = room->connectedRooms;
    while (current != NULL) {
        RoomNode *temp = current;
        current = current->next;
        free(temp);
    }

    // Free hunters in room array
    if (room->huntersInRoom != NULL) {
        free(room->huntersInRoom);
    }

    // Destroy semaphore
    sem_destroy(&room->roomSemaphore);

    // Free the room itself
    free(room);
}

//add evidence to the room
void addEvidenceToRoom(RoomType *room, EvidenceType evidence){
    if (room == NULL)
    {
        return;
    }

    // Create a new evidence node
    EvidenceNode *newEvidence = (EvidenceNode *)malloc(sizeof(EvidenceNode));
    if (newEvidence == NULL)
    {
        // Handle memory allocation failure
        return;
    }
    newEvidence->evidence = evidence;
    newEvidence->next = room->evidenceInRoom;
    room->evidenceInRoom = newEvidence;
}

//adds a hunter to the room
void addHunterToRoom(RoomType *room, HunterType *hunter){
    if (room == NULL || hunter == NULL) {
        return;
    }

    // Count the number of hunters already in the room
    int numHunters = 0;
    while (room->huntersInRoom && room->huntersInRoom[numHunters]) {
        numHunters++;
    }

    // Resize the array to accommodate the new hunter plus the NULL terminator
    HunterType **newArray = realloc(room->huntersInRoom, sizeof(HunterType *) * (numHunters + 2));
    if (newArray == NULL) {
        // Handle realloc failure, original room->huntersInRoom is still valid
        return;
    }

    // Update the hunters array if realloc succeeds
    room->huntersInRoom = newArray;
    room->huntersInRoom[numHunters] = hunter;
    room->huntersInRoom[numHunters + 1] = NULL; // Null-terminate the array
}

