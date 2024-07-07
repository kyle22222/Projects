#include "defs.h"

//Initializes ghost
void initGhost(GhostType *ghost, RoomType *startingRoom){
    if (ghost == NULL){
        return; // Handle null pointer
    }

    // Assign a random ghost class
    ghost->ghostClass = randomGhost();

    // Set the starting room for the ghost
    ghost->currentRoom = startingRoom;

    // Initialize the boredom timer
    ghost->boredomTimer = 0;

    l_ghostInit(ghost->ghostClass, startingRoom->name);
}

//Leaves evidence in the current room of ghost
void leaveEvidence(GhostType *ghost){
    if (ghost == NULL || ghost->currentRoom == NULL)
    {
        return; // Handle NULL pointers
    }

    // Logic for determining the type of evidence based on the ghost class
    EvidenceType evidence = determineEvidenceBasedOnGhost(ghost->ghostClass);

    // Add the evidence to the room's evidence collection
    addEvidenceToRoom(ghost->currentRoom, evidence);
    l_ghostEvidence(evidence, ghost->currentRoom->name);
}

//moves the ghost to a random connected room
void moveGhost(GhostType *ghost){
    if (ghost == NULL || ghost->currentRoom == NULL || ghost->currentRoom->connectedRooms == NULL)
    {
        return; // Handle NULL pointers and no connected rooms
    }

    // Logic to move the ghost to a random connected room
    ghost->currentRoom = getRandomConnectedRoom(ghost->currentRoom);
    l_ghostMove(ghost->currentRoom->name);
}

//randomly selects evidence based on the ghost type
EvidenceType determineEvidenceBasedOnGhost(GhostClass ghostClass) {
    int randomChoice; // Variable to store the intermediate random choice

    switch (ghostClass) {
    case POLTERGEIST:
        randomChoice = randInt(0, 3); // Generates 0, 1, or 2
        if (randomChoice == 0) return EMF;
        if (randomChoice == 1) return TEMPERATURE;
        return FINGERPRINTS;
    case BANSHEE:
        randomChoice = randInt(0, 3); // Generates 0, 1, or 2
        if (randomChoice == 0) return EMF;
        if (randomChoice == 1) return TEMPERATURE;
        return SOUND;
    case BULLIES:
        randomChoice = randInt(0, 3); // Generates 0, 1, or 2
        if (randomChoice == 0) return EMF;
        if (randomChoice == 1) return FINGERPRINTS;
        return SOUND;
    case PHANTOM:
        randomChoice = randInt(0, 3); // Generates 0, 1, or 2
        if (randomChoice == 0) return TEMPERATURE;
        if (randomChoice == 1) return FINGERPRINTS;
        return SOUND;
    default:
        return EV_UNKNOWN; // Default case for unknown ghost class
    }
}

//randomly selects a room for initial spawn
RoomType *selectRandomRoom(HouseType *house) {
    if (house == NULL || house->rooms == NULL) {
        return NULL; // Safety check
    }

    // Count the number of rooms
    int roomCount = 0;
    RoomNode *currentRoomNode = house->rooms;
    while (currentRoomNode != NULL) {
        roomCount++;
        currentRoomNode = currentRoomNode->next;
    }

    if (roomCount == 0) {
        return NULL; // No rooms available
    }

    // Select a random room index
    int randomRoomIndex = randInt(0, roomCount);
    currentRoomNode = house->rooms;
    for (int i = 0; i < randomRoomIndex; i++) {
        currentRoomNode = currentRoomNode->next;
    }

    return currentRoomNode->room;
}

//ghost thread manages ghost behaviour
void *ghostActions(void *arg) {
    GhostType *ghost = (GhostType *)arg;
    if (ghost == NULL) {
        pthread_exit(NULL);
    }

    while (1) {
        if (ghost->currentRoom->huntersInRoom != NULL) {
            ghost->boredomTimer = 0; // Reset boredom timer
            // Randomly choose to leave evidence or do nothing
            int action = randInt(0, 1);
            if (action == 0) {
                leaveEvidence(ghost); // Log inside the function
            }
        } else {
            ghost->boredomTimer++;
            if (ghost->boredomTimer >= BOREDOM_MAX) {
                l_ghostExit(LOG_BORED); // Log exit due to boredom
                pthread_exit(NULL);
            }
            // Randomly move or leave evidence

            int action = randInt(0, 3);
            if (action == 0) {
                moveGhost(ghost); // Log inside the function
            } else if (action == 1) {
                leaveEvidence(ghost); // Log inside the function
            }
        }
        usleep(GHOST_WAIT); // Sleep to simulate time passing
    }

    return NULL;
}

