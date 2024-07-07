#include "defs.h"

//initializes house
void initHouse(HouseType *house) {
    // Check if the house pointer is valid
    if (house == NULL) {
        return;
    }

    // Initialize the array of hunters
    for (int i = 0; i < NUM_HUNTERS; i++) {
        house->hunters[i] = NULL; // Set each hunter pointer to NULL initially
    }

    // Initialize the linked list of rooms
    house->rooms = NULL; // Set the head of the rooms list to NULL

    // Initialize the shared evidence array
    for (int i = 0; i < EV_COUNT; i++) {
        house->sharedEvidence[i] = EV_UNKNOWN; // Set each evidence type to EV_UNKNOWN initially
    }
}

//adds a room to the house list
void addRoom(RoomNode **roomListHead, RoomType *newRoom)
{
    RoomNode *newNode = (RoomNode *)malloc(sizeof(RoomNode));
    newNode->room = newRoom;
    newNode->next = NULL;

    if (*roomListHead == NULL)
    {
        *roomListHead = newNode;
    }
    else
    {
        RoomNode *current = *roomListHead;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newNode;
    }
}

/*
    Dynamically allocates several rooms and populates the provided house.
    Note: You may modify this as long as room names and connections are maintained.
        out: house - the house to populate with rooms. Assumes house has been initialized.
*/

void populateRooms(HouseType *house)
{
    // First, create each room

    // createRoom assumes that we dynamically allocate a room, initializes the values, and returns a RoomType*
    // create functions are pretty typical, but it means errors are harder to return aside from NULL
    struct Room *van = createRoom("Van");
    struct Room *hallway = createRoom("Hallway");
    struct Room *master_bedroom = createRoom("Master Bedroom");
    struct Room *boys_bedroom = createRoom("Boy's Bedroom");
    struct Room *bathroom = createRoom("Bathroom");
    struct Room *basement = createRoom("Basement");
    struct Room *basement_hallway = createRoom("Basement Hallway");
    struct Room *right_storage_room = createRoom("Right Storage Room");
    struct Room *left_storage_room = createRoom("Left Storage Room");
    struct Room *kitchen = createRoom("Kitchen");
    struct Room *living_room = createRoom("Living Room");
    struct Room *garage = createRoom("Garage");
    struct Room *utility_room = createRoom("Utility Room");

    // This adds each room to each other's room lists
    // All rooms are two-way connections
    connectRooms(van, hallway);
    connectRooms(hallway, master_bedroom);
    connectRooms(hallway, boys_bedroom);
    connectRooms(hallway, bathroom);
    connectRooms(hallway, kitchen);
    connectRooms(hallway, basement);
    connectRooms(basement, basement_hallway);
    connectRooms(basement_hallway, right_storage_room);
    connectRooms(basement_hallway, left_storage_room);
    connectRooms(kitchen, living_room);
    connectRooms(kitchen, garage);
    connectRooms(garage, utility_room);

    // Add each room to the house's room list
    addRoom(&house->rooms, van);
    addRoom(&house->rooms, hallway);
    addRoom(&house->rooms, master_bedroom);
    addRoom(&house->rooms, boys_bedroom);
    addRoom(&house->rooms, bathroom);
    addRoom(&house->rooms, basement);
    addRoom(&house->rooms, basement_hallway);
    addRoom(&house->rooms, right_storage_room);
    addRoom(&house->rooms, left_storage_room);
    addRoom(&house->rooms, kitchen);
    addRoom(&house->rooms, living_room);
    addRoom(&house->rooms, garage);
    addRoom(&house->rooms, utility_room);
}