#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdbool.h>

#define MAX_STR         64
#define MAX_RUNS        50
#define BOREDOM_MAX     100
#define C_TRUE          1
#define C_FALSE         0
#define HUNTER_WAIT     5000
#define GHOST_WAIT      600
#define NUM_HUNTERS     4
#define FEAR_MAX        10
#define LOGGING         C_TRUE

typedef enum EvidenceType EvidenceType;
typedef enum GhostClass GhostClass;
typedef struct Room RoomType;  // Forward declaration for self-referencing


enum EvidenceType { EMF, TEMPERATURE, FINGERPRINTS, SOUND, EV_COUNT, EV_UNKNOWN };
enum GhostClass { POLTERGEIST, BANSHEE, BULLIES, PHANTOM, GHOST_COUNT, GH_UNKNOWN };
enum LoggerDetails { LOG_FEAR, LOG_BORED, LOG_EVIDENCE, LOG_SUFFICIENT, LOG_INSUFFICIENT, LOG_UNKNOWN };

typedef struct HunterType{
    char name[MAX_STR];          // Hunter's name, using MAX_STR for the maximum length
    RoomType *currentRoom;       // Pointer to the room the hunter is currently in
    EvidenceType equipmentType;  // Type of evidence the hunter's equipment can read
    EvidenceType *sharedEvidence;// Pointer to a shared collection of Evidence
    int fear;                    // Fear level, starting at 0
    int boredom;                 // Boredom level, starting at 0
} HunterType;

typedef struct GhostType{
    GhostClass ghostClass;  // Enumerated type representing the type of ghost
    RoomType *currentRoom;  // Pointer to the room the ghost is currently in
    int boredomTimer;       // Boredom timer, initially set to 0
} GhostType;

typedef struct EvidenceNode {
    EvidenceType evidence;
    struct EvidenceNode *next;
} EvidenceNode;

typedef struct RoomNode {
    RoomType *room;                 // Pointer to the room
    struct RoomNode *next;          // Pointer to the next node in the linked list
} RoomNode;

struct Room {
    char name[MAX_STR];           // Room's name, using MAX_STR for the maximum length
    RoomNode *connectedRooms;     // Linked list of other rooms that it is connected to
    EvidenceNode *evidenceInRoom; // Linked list of evidence left in the room
    HunterType **huntersInRoom;   // Dynamic array of pointers to hunters currently in the room
    GhostType *ghostInRoom;       // Pointer to the ghost in the room, NULL if no ghost
    sem_t roomSemaphore;          // Semaphore for thread safety
};

typedef struct HouseType{
    HunterType *hunters[NUM_HUNTERS]; // Array of pointers to hunters, NUM_HUNTERS defined in defs.h
    RoomNode *rooms;                  // Pointer to the first Room in the linked list of all rooms
    EvidenceType sharedEvidence[EV_COUNT]; // Array for shared evidence, EV_COUNT defined in defs.h
} HouseType;

// Helper Utilies
int randInt(int,int);        // Pseudo-random number generator function
float randFloat(float, float);  // Pseudo-random float generator function
enum GhostClass randomGhost();  // Return a randomly selected a ghost type
void ghostToString(enum GhostClass, char*); // Convert a ghost type to a string, stored in output paremeter
void evidenceToString(enum EvidenceType, char*); // Convert an evidence type to a string, stored in output parameter

// Logging Utilities
void l_hunterInit(char* name, enum EvidenceType equipment);
void l_hunterMove(char* name, char* room);
void l_hunterReview(char* name, enum LoggerDetails reviewResult);
void l_hunterCollect(char* name, enum EvidenceType evidence, char* room);
void l_hunterExit(char* name, enum LoggerDetails reason);
void l_ghostInit(enum GhostClass type, char* room);
void l_ghostMove(char* room);
void l_ghostEvidence(enum EvidenceType evidence, char* room);
void l_ghostExit(enum LoggerDetails reason);

// Hunter Functions
void initHunter(HunterType *hunter, const char *name, RoomType *startingRoom, EvidenceType equipmentType, EvidenceType* sharedEvidence);
void moveHunter(HunterType *hunter);
void collectEvidence(HunterType *hunter);
bool reviewEvidence(HunterType *hunter);
void *hunterActions(void *arg);

// Ghost Functions
void initGhost(GhostType *ghost, RoomType *startingRoom);
void leaveEvidence(GhostType *ghost);
void moveGhost(GhostType *ghost);
void *ghostActions(void *arg);
EvidenceType determineEvidenceBasedOnGhost(GhostClass ghostClass);
RoomType *selectRandomRoom(HouseType *house);

// Room Functions
RoomType *createRoom(const char *name);
void connectRooms(RoomType *room1, RoomType *room2);
void destroyRoom(RoomType *room);
void addHunterToRoom(RoomType *room, HunterType *hunter);
void addEvidenceToRoom(RoomType *room, EvidenceType evidence);

// House Functions
void initHouse(HouseType *house);
void addRoom(RoomNode **roomListHead, RoomType *newRoom);
void populateRooms(HouseType* house);

RoomType *getRandomConnectedRoom(RoomType *currentRoom);