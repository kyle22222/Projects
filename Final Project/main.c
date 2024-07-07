#include "defs.h"
#include <pthread.h> // For threading

int main() {
    // Initialize the random number generator
    srand(time(NULL));

    // Create and initialize the house
    HouseType house;
    initHouse(&house);
    populateRooms(&house); // Populate the house with rooms

    // Collect hunter names and initialize them
    char hunterNames[NUM_HUNTERS][MAX_STR];
    printf("Enter the names of %d hunters:\n", NUM_HUNTERS);
    for (int i = 0; i < NUM_HUNTERS; i++) {
        printf("Hunter %d name: ", i + 1);
        fgets(hunterNames[i], MAX_STR, stdin);
        hunterNames[i][strcspn(hunterNames[i], "\n")] = '\0'; // Remove newline character
        // Initialize each hunter with a name, starting room (the first room in the house), 
        // equipment type, and shared evidence array
        house.hunters[i] = (HunterType *)malloc(sizeof(HunterType));
        if (house.hunters[i] != NULL) {
            initHunter(house.hunters[i], hunterNames[i], house.rooms->room, i % EV_COUNT, house.sharedEvidence);
        }
    }

    // Create and initialize the ghost
    GhostType ghost;
    RoomType *startingRoom = selectRandomRoom(&house);
    initGhost(&ghost, startingRoom);

    // Create threads for the ghost and each hunter
    pthread_t ghostThread, hunterThreads[NUM_HUNTERS];

    pthread_create(&ghostThread, NULL, ghostActions, (void *)&ghost);
    for (int i = 0; i < NUM_HUNTERS; i++) {
        pthread_create(&hunterThreads[i], NULL, hunterActions, (void *)house.hunters[i]);
    }

    // Wait for all threads to complete
    pthread_join(ghostThread, NULL);
    for (int i = 0; i < NUM_HUNTERS; i++) {
        pthread_join(hunterThreads[i], NULL);
    }

    // Clean up resources and memory allocations
    // This includes deallocating any dynamically allocated memory and other cleanup tasks.
    // Example: free(house.hunters[i]);

    // Finalize the simulation, such as printing results or freeing remaining resources
    // ...

    bool allHighFearOrBoredom = true;
    int uniqueEvidence[EV_COUNT] = {0}; // To track unique evidence collected

    // Checking hunters' status
    for (int i = 0; i < NUM_HUNTERS; i++) {
        if (house.hunters[i]->fear < FEAR_MAX && house.hunters[i]->boredom < BOREDOM_MAX) {
            allHighFearOrBoredom = false;
        }
        printf("Hunter %s has %s.\n", house.hunters[i]->name, 
            (house.hunters[i]->fear >= FEAR_MAX) ? "high fear" : 
            ((house.hunters[i]->boredom >= BOREDOM_MAX) ? "high boredom" : "continued"));
    }

    // Check if ghost won
    if (allHighFearOrBoredom) {
        printf("All hunters have left. The ghost has won!\n");
    }

    // Print collected evidence
    printf("Collected evidence by hunters:\n");
    for (int i = 0; i < EV_COUNT; i++) {
        if (house.sharedEvidence[i] != EV_UNKNOWN) {
            char evidenceStr[16];
            evidenceToString(house.sharedEvidence[i], evidenceStr);
            printf("%s\n", evidenceStr);
            uniqueEvidence[i] = 1; // Mark this evidence as collected
        }
    }

    // Identify the ghost based on evidence
    int evidenceCollected = 0;
    for (int i = 0; i < EV_COUNT; i++) {
        evidenceCollected += uniqueEvidence[i];
    }
    if (evidenceCollected >= 3) {
        // Print if three different pieces of evidence were collected
        char ghostStr[16];
        ghostToString(ghost.ghostClass, ghostStr); // Convert ghost enum to string
        printf("The identified ghost is: %s\n", ghostStr);
        printf("The hunters have identified the ghost correctly.\n");
    } else {
        printf("Insufficient evidence to identify the ghost.\n");
    }

    // Clean up resources and memory allocations
    for (int i = 0; i < NUM_HUNTERS; i++) {
        if (house.hunters[i] != NULL) {
            free(house.hunters[i]);
        }
    }
    // Additional cleanup for house and its rooms

    return 0;
}