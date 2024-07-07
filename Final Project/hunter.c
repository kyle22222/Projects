#include "defs.h"

// Function for a hunter to move to a random connected room
void moveHunter(HunterType *hunter){
    if (hunter == NULL || hunter->currentRoom == NULL){
        return;
    }

    RoomType *newRoom = getRandomConnectedRoom(hunter->currentRoom);
    if (newRoom != NULL){
        hunter->currentRoom = newRoom;
        hunter->boredom = 0;                       // Reset boredom
        l_hunterMove(hunter->name, newRoom->name); // Log the move
    }
}

//function for hunter to collect evidence
void collectEvidence(HunterType *hunter) {
    if (hunter == NULL || hunter->currentRoom == NULL) {
        return; // Handle NULL pointers
    }

    EvidenceNode *prevEvidenceNode = NULL;
    EvidenceNode *evidenceNode = hunter->currentRoom->evidenceInRoom;

    while (evidenceNode != NULL) {
        if (evidenceNode->evidence == hunter->equipmentType) {
            // Check if evidence is not already in shared collection
            if (hunter->sharedEvidence[evidenceNode->evidence] == EV_UNKNOWN) {
                // Add evidence to shared collection
                hunter->sharedEvidence[evidenceNode->evidence] = evidenceNode->evidence;
                l_hunterCollect(hunter->name, evidenceNode->evidence, hunter->currentRoom->name); // Log evidence collection
            }

            // Remove evidence from room
            EvidenceNode *nodeToRemove = evidenceNode;
            if (prevEvidenceNode == NULL) { // First node in the list
                hunter->currentRoom->evidenceInRoom = evidenceNode->next;
            } else {
                prevEvidenceNode->next = evidenceNode->next;
            }
            evidenceNode = evidenceNode->next; // Move to next node

            free(nodeToRemove); // Free the memory of the removed evidence node
        } else {
            prevEvidenceNode = evidenceNode;
            evidenceNode = evidenceNode->next; // Move to next node
        }
    }
}

// Function for a hunter to review evidence
bool reviewEvidence(HunterType *hunter) {
    int uniqueEvidenceCount = 0;
    int foundEvidence[EV_COUNT] = {0}; // Array to track found evidence types

    // Iterate through the shared evidence array
    for (int i = 0; i < EV_COUNT; i++) {
        if (hunter->sharedEvidence[i] != EV_UNKNOWN && !foundEvidence[hunter->sharedEvidence[i]]) {
            foundEvidence[hunter->sharedEvidence[i]] = 1; // Mark this evidence type as found
            uniqueEvidenceCount++;
        }
    }

    if (uniqueEvidenceCount >= 3) {
        // Log sufficient evidence found
        l_hunterReview(hunter->name, LOG_SUFFICIENT);
        return true;
    } else {
        // Log insufficient evidence
        l_hunterReview(hunter->name, LOG_INSUFFICIENT);
        return false;
    }
}

// Initialize the hunter
void initHunter(HunterType *hunter, const char *name, RoomType *startingRoom, EvidenceType equipmentType, EvidenceType *sharedEvidence){
    if (hunter == NULL){
        return;
    }

    strncpy(hunter->name, name, MAX_STR - 1);
    hunter->currentRoom = startingRoom;
    hunter->equipmentType = equipmentType;
    hunter->sharedEvidence = sharedEvidence;
    hunter->fear = 0;
    hunter->boredom = 0;

    l_hunterInit(hunter->name, equipmentType); // Log hunter initialization
}

//hunter thread that manages hunter behaviour
void *hunterActions(void *arg) {
    HunterType *hunter = (HunterType *)arg;
    if (hunter == NULL) {
        pthread_exit(NULL);
    }

    while (1) {
        if (hunter->currentRoom->ghostInRoom != NULL) {
            hunter->fear++; // Increase fear
            hunter->boredom = 0; // Reset boredom
        } else {
            hunter->boredom++;
        }

        if (hunter->fear >= FEAR_MAX) {
            l_hunterExit(hunter->name, LOG_FEAR); // Log exit due to fear
            pthread_exit(NULL);
        } else if (hunter->boredom >= BOREDOM_MAX) {
            l_hunterExit(hunter->name, LOG_BORED); // Log exit due to boredom
            pthread_exit(NULL);
        }

        // Random action
        int action = randInt(0, 3);
        switch (action) {
            case 0:
                moveHunter(hunter); // Log inside the function
                break;
            case 1:
                collectEvidence(hunter); // Log inside the function
                break;
            case 2:
                if (reviewEvidence(hunter)){
                    pthread_exit(NULL);
                }; // Log inside the function
                break;
        }
        usleep(HUNTER_WAIT); // Sleep to simulate time passing
    }

    return NULL;
}
