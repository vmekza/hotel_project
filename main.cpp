#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>

using namespace std;

//Number of rooms in the hotel
int const hotelSize = 60;
bool allRooms[hotelSize] = {false};

//Arrays to save information about booked rooms
int bookedRoomNumber[hotelSize];
int bookedRoomNight[hotelSize];
int bookedRoomCost[hotelSize];
int bookedReservationID[hotelSize];
string bookedGuestName[hotelSize];
string bookedGuestPhone[hotelSize];
string bookedRoomType[hotelSize];

//Function prototypes
void showMenu();
void bookRoom(int&roomNumber, int&roomNight, string&guestName, int&reservationID);
void chooseRoomNumber(int&roomNumber, int&roomNight, string&guestName, int&reservationID);
void drawRoomNumber(int&roomNumber, int&roomNight, string&guestName, int&reservationID);
void singleRoomBooking(int&roomNumber, int&roomNight, string&guestName, int&reservationID);
void doubleRoomBooking(int&roomNumber, int&roomNight, string&guestName, int&reservationID);
void roomRate (int&roomNumber, int&roomNight);
void saveGuest(int&roomNumber, string&guestName, int&reservationID);
void showAvailableRooms();
void showAllBookings();
void searchBooking(int&roomNumber, string&guestName, int&reservationID);
void searchByRoom(int&roomNumber);
void searchByName(string&guestName);
void searchByReservationID(int&reservationID);
void deleteBooking(int&roomNumber);
void showBookingTable();


int main() {
    int roomNumber, roomNight, reservationID, option;;
    string guestName;

    cout << "------------------------------" << endl;
    cout << "      HOTEL DORIANA ROBO" << endl;
    cout << "      RESERVATION SYSTEM" << endl;
    cout << "------------------------------" << endl;

    //Switch between different actions ih the program
    do {
        showMenu();
        while((!(cin >> option)) || option < 1 || option > 6 ) {
            cout << "ENTER NUMBER FROM 1-6 ";
            cin.clear();
            cin.ignore(123, '\n');
        }
        switch (option) {
            case 1:
                bookRoom(roomNumber, roomNight, guestName, reservationID);
                break;
            case 2:
                showAvailableRooms();
                break;
            case 3:
                showAllBookings();
                break;
            case 4:
                searchBooking(roomNumber, guestName, reservationID);
                break;
            case 5:
                deleteBooking(roomNumber);
                break;
        }
    } while(option!=6);
}

//Display main menu
void showMenu() {
    cout << "             MENU      " << endl;
    cout << "------------------------------" << endl;
    cout << "1. BOOK A ROOM" << endl;
    cout << "2. VIEW AVAILABLE ROOMS" << endl;
    cout << "3. VIEW ALL BOOKINGS" << endl;
    cout << "4. FIND BOOKING" << endl;
    cout << "5. DELETE BOOKING" << endl;
    cout << "6. EXIT" << endl;
    cout << "OPTION: ";
}

//Choose how to book a room: by user's input of a room number or by draw a random room number
void bookRoom (int&roomNumber, int&roomNight, string&guestName, int&reservationID) {
    int option;

    cout << "-----------------------------" << endl;
    cout << "1. CHOOSE A ROOM NUMBER" << endl;
    cout << "2. DRAW A ROOM NUMBER " << endl;
    cout << "OPTION: ";

    //Check that input was a number (1 or 2)
    while(!(cin >> option) || option < 1 || option > 2) {
        cout << "ENTER NUMBER 1 OR 2: ";
        cin.clear();
        cin.ignore(123, '\n');
    }
    if (option == 1) {
        chooseRoomNumber(roomNumber, roomNight, guestName, reservationID); //call function if user wants to enter a room number
    }
    else if (option == 2) {
        drawRoomNumber(roomNumber, roomNight, guestName, reservationID); // call function to draw a random room number
    }
}

//Book a room by user's input of room number
void chooseRoomNumber(int&roomNumber, int&roomNight, string&guestName, int&reservationID) {
    bool check = true;
    int count = 0;

    cout << "-----------------------------" << endl;
    cout << "ENTER ROOM NUMBER FROM 1-" << hotelSize << ": ";

    //Check that input was a number and not larger than total number of rooms
    while (!(cin >> roomNumber)|| roomNumber < 1 || roomNumber > hotelSize) {
        cout << "ENTER ROOM NUMBER FROM 1-" << hotelSize << ": ";
        cin.clear();
        cin.ignore(123, '\n');
    }

    //Check if chosen room is available
    while (check) {
        if (!allRooms[roomNumber - 1]) {
            cout << "ENTER NUMBER OF NIGHTS: ";

            while(!(cin >> roomNight)) {
                cout << "ENTER NUMBER OF NIGHTS: ";
                cin.clear();
                cin.ignore(123, '\n');
            }
            cout << endl;
            cout << "ROOM IS AVAILABLE!" << endl;

            //Call function to calculate room rate
            roomRate(roomNumber, roomNight);
            cout << endl;

            //Call function to save guest's information from user's input
            saveGuest(roomNumber, guestName, reservationID);

            //Add info about booked room to arrays
            allRooms[roomNumber - 1] = true;
            bookedRoomNumber[roomNumber - 1] = roomNumber;
            bookedRoomNight[roomNumber - 1] = roomNight;

            cout << endl;
            cout << bookedRoomType[roomNumber - 1] << " ROOM #" << roomNumber << " WAS SUCCESSFULLY BOOKED!" << endl;
            cout << "RESERVATION NUMBER IS HDR-" << bookedReservationID[roomNumber - 1] << endl;
            cout << "---------------------------------------" << endl;
            cout << endl;
            check = false;

        } else {
            cout << "IT IS BOOKED ALREADY! " << endl;
            cout << "---------------------------" << endl;
            cout << endl;

            //Check if hotel is fully booked
            for (int i = 0; i < hotelSize; i++) {
                if (allRooms[i]) {
                    count++;
                }
                if (count == hotelSize) {
                    cout << "THE HOTEL IS FULLY BOOKED!" << endl;
                    cout << endl;
                    cout << endl;
                    break;
                }
            }
            break;
        }
    }
}

//Choose room type to book by drawing random room number
void drawRoomNumber(int&roomNumber, int&roomNight, string&guestName, int&reservationID) {
    int option;
    int count = 0;

    cout << "------------------------" << endl;
    cout << "CHOOSE ROOM TYPE:" << endl;
    cout << "1. SINGLE ROOM" << endl;
    cout << "2. DOUBLE ROOM" << endl;
    cout << "OPTION: ";

    //Check that input was a number (1 or 2)
    while(!(cin >> option) || option < 1 || option > 2) {
        cout << "ENTER NUMBER 1 OR 2: ";
        cin.clear();
        cin.ignore(123, '\n');
    }

    //Check if there are available single rooms
    if (option == 1) {
        for (int n = 0; n < 30; n++) {
            if (allRooms[n]) {
                count++;
            }
        }
        if (count == 30) {
            cout << "ALL SINGLE ROOMS ARE BOOKED!";
            cout << endl;
        } else {
            singleRoomBooking(roomNumber, roomNight, guestName, reservationID); //Call function to book a single room if there are available ones
        }
    }

    //Check if there are available double rooms
    if (option == 2) {
        for (int n = 30; n < 60; n++) {
            if (allRooms[n]) {
                count++;
            }
        }
        if (count == 30) {
            cout << "ALL DOUBLE ROOMS ARE BOOKED!";
            cout << endl;
        }
        else {
            doubleRoomBooking(roomNumber, roomNight, guestName, reservationID); //Call function to book a double room if there are available ones
        }
    }
}

//Book a single room by drawing a random number
void singleRoomBooking(int&roomNumber, int&roomNight, string&guestName, int&reservationID) {
    bool check = true;
    srand(time(nullptr));

    //Check if drawn single room number is available. If so, it is being booked
    while (check) {
        roomNumber = (rand() % 30) + 1;

        if (!allRooms[roomNumber - 1]) {
            cout << "------------------------" << endl;
            cout << "ENTER NUMBER OF NIGHTS: ";

            while(!(cin >> roomNight)) {
                cout << "ENTER NUMBER OF NIGHTS: ";
                cin.clear();
                cin.ignore(123, '\n');
            }

            roomRate(roomNumber, roomNight); //Call function to calculate room rate
            cout << endl;

            saveGuest(roomNumber, guestName, reservationID); //Call function to save guest's information from user's input
            cout << endl;

            cout << bookedRoomType[roomNumber - 1] << " ROOM #" << roomNumber << " WAS SUCCESSFULLY BOOKED!" << endl;
            cout << "RESERVATION NUMBER IS HDR-" << bookedReservationID[roomNumber - 1] << endl;
            cout << "---------------------------------------" << endl;
            cout << endl;

            allRooms[roomNumber - 1] = true;
            bookedRoomNumber[roomNumber - 1] = roomNumber;
            bookedRoomNight[roomNumber - 1] = roomNight;
            check = false;

        } else {
            continue;
        }
    }
}

//Book a double room by drawing random number
void doubleRoomBooking(int&roomNumber, int&roomNight, string&guestName, int&reservationID) {
    bool check = true;
    srand(time(nullptr));

    //Check if drawn double room number is available. If so, it is being booked
    while (check) {
        roomNumber = (rand() % 30) + 31;

        if (!allRooms[roomNumber - 1]) {
            cout << "------------------------" << endl;
            cout << "ENTER NUMBER OF NIGHTS: ";

            while(!(cin >> roomNight)) {
                cout << "ENTER NUMBER OF NIGHTS: ";
                cin.clear();
                cin.ignore(123, '\n');
            }

            roomRate(roomNumber, roomNight); //Call function to calculate room rate
            cout << endl;

            saveGuest(roomNumber, guestName, reservationID); //Call function to save guest's information from user's input
            cout << endl;

            cout << bookedRoomType[roomNumber - 1] << " ROOM #" << roomNumber << " WAS SUCCESSFULLY BOOKED!" << endl;
            cout << "RESERVATION NUMBER IS DRD-" << bookedReservationID[roomNumber - 1] << endl;
            cout << "---------------------------------------" << endl;
            cout << endl;

            allRooms[roomNumber - 1] = true;
            bookedRoomNumber[roomNumber - 1] = roomNumber;
            bookedRoomNight[roomNumber - 1] = roomNight;
            check = false;

        } else {
            continue;
        }
    }
}

//Calculate room rate depending on room type and number of nights
void roomRate (int&roomNumber, int&roomNight) {
    int singleRate = 100;
    int doubleRate = 150;
    int discount3Nights = 10;
    int discount5Nights = 20;
    int roomCost;

    //Calculate cost of a single room according to number of nights
    if (roomNumber < 31) {
        if (roomNight <= 2) {
            roomCost = roomNight * singleRate;
            cout << "ROOM COST FOR " << roomNight << " NIGHT(S) IS " << roomCost << " EUROS" << endl;
        } else if (roomNight > 2 && roomNight < 6) {
            roomCost = roomNight * singleRate - roomNight * singleRate * discount3Nights / 100;
            cout << "ROOM COST WITH 10% DISCOUNT FOR " << roomNight << " NIGHT(S) IS " << roomCost << " EUROS"<< endl;
        } else {
            roomCost = roomNight * singleRate - roomNight * singleRate * discount5Nights / 100;
            cout << "ROOM COST WITH 20% DISCOUNT FOR " << roomNight << " NIGHT(S) IS " << roomCost << " EUROS" << endl;
        }
    }
    //Calculate cost of a double room according to number of nights
    if (roomNumber > 30 && roomNumber < (hotelSize + 1)) {
        if (roomNight <= 2) {
            roomCost = roomNight * doubleRate;
            cout << "ROOM COST FOR " << roomNight << " NIGHT(S) IS " << roomCost << " EUROS" << endl;
        }
        else if (roomNight > 2 && roomNight < 6) {
            roomCost = roomNight * doubleRate - roomNight * doubleRate * discount3Nights / 100;
            cout << "ROOM COST WITH 10% DISCOUNT FOR " << roomNight << " NIGHT(S) IS " << roomCost << " EUROS" << endl;
        } else {
            roomCost = roomNight * doubleRate - roomNight * doubleRate * discount5Nights / 100;
            cout << "ROOM COST WITH 20% DISCOUNT FOR " << roomNight << " NIGHT(S) IS " << roomCost << " EUROS" << endl;
        }
    }
    //Add info about booked room cost to array
    bookedRoomCost[roomNumber - 1] = roomCost;
}

//Save information about guest from user's input
void saveGuest(int&roomNumber, string&guestName, int&reservationID) {
    string guestPhone;

    cin.ignore();
    cout << "ENTER FULL NAME: ";
    cin.width(25);
    getline(cin, guestName);

    cout << "ENTER PHONE NUMBER: ";
    cin.width(25);
    getline(cin, guestPhone);

    //Add info about guest to arrays
    bookedGuestName[roomNumber - 1] = guestName;
    bookedGuestPhone[roomNumber - 1] = guestPhone;

    if (roomNumber > 0 && roomNumber < 31) {
        bookedRoomType[roomNumber - 1] = "SINGLE";
    }
    else if (roomNumber > 30 && roomNumber < (hotelSize + 1)) {
        bookedRoomType[roomNumber - 1] = "DOUBLE";
    }

    //Draw reservation number of booking and add it to array
    srand(time(nullptr));
    reservationID = (rand() % 99999) + 10000;
    bookedReservationID[roomNumber - 1] = reservationID;
}

//Display all available rooms at any given moment
void showAvailableRooms() {
    cout << endl;
    cout << "AVAILABLE ROOMS" << endl;
    cout << "--------------------------------------------------------------------"  << endl;
    cout << "SINGLE ROOMS" << endl;

    cout << "1 FLOOR: ";
    for (int i = 0; i < 15; i++)
        if (!allRooms[i]) {
            cout << i + 1 << ", ";
        }
    cout << endl;

    cout << "2 FLOOR: ";
    for (int i = 15; i < 30 ; i++)
        if (!allRooms[i]) {
            cout << i + 1 << ", ";
        }
    cout << endl;
    cout << endl;

    cout << "DOUBLE ROOMS" << endl;
    cout << "3 FLOOR: ";
    for (int i = 30; i < 45; i++)
        if (!allRooms[i]) {
            cout << i + 1 << ", ";
        }
    cout << endl;

    cout << "4 FLOOR: ";
    for (int i = 45; i < 60; i++)
        if (!allRooms[i]) {
            cout << i + 1 << ", ";
        }
    cout << endl;
    cout << "--------------------------------------------------------------------" << endl;
    cout << endl;
}

//Display all booking at any given moment
void showAllBookings() {
    int count = 0;

    showBookingTable(); //Call function to display elements of booking table

    for (int i = 0; i < hotelSize; i++) {
        if (bookedRoomNumber[i] != 0) {
            cout << "HDR-" << setw(16) << left << bookedReservationID [i]
                 << setw(11) << left << bookedRoomNumber[i]
                 << setw(14) << left << bookedRoomType[i]
                 << setw(23) << left << bookedGuestName[i]
                 << setw(21) << left<< bookedGuestPhone[i]
                 << setw(14) << left << bookedRoomNight[i]
                 << setw(21) << left << bookedRoomCost[i] << endl;
            cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
            count ++;
        }
    }
    cout << endl;

    if (count == 0) {
        cout << "THERE ARE NO BOOKINGS YET!" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
        cout << endl;
    }
}

//Choose how to find booking: by room number ob by guest's name
void searchBooking(int&roomNumber, string&guestName, int&reservationID) {
    int option;
    cout << "-----------------------------" << endl;
    cout << "FIND BOOKING BY:" << endl;
    cout << "1. ROOM NUMBER" << endl;
    cout << "2. GUEST NAME" << endl;
    cout << "3. RESERVATION NUMBER" << endl;
    cout << "OPTION: ";

//    Check if input is a number from 1-3
    while (!(cin >> option) || option > 3 || option < 1) {
        cout << "ENTER NUMBER FROM 1-3: ";
        cin.clear();
        cin.ignore(123, '\n');
    }
    if (option == 1) {
        searchByRoom(roomNumber); //Call function to find booking by room number
    }
    else if (option == 2) {
        searchByName(guestName); //Call function to find booking by guest name
    }
    else {
        searchByReservationID(reservationID); //Call function to find booking by reservation number
    }
}

//Find room by certain room number
void searchByRoom(int&roomNumber) {
    int count = 0;

    cout << "-----------------------------" << endl;
    cout << "ENTER ROOM NUMBER FROM 1-" << hotelSize << ": ";

    //Check if input is number and not larger than total number of rooms
    while (!(cin >> roomNumber) || roomNumber < 1 || roomNumber > hotelSize) {
        cout << "ENTER ROOM NUMBER FROM 1-" << hotelSize << ": ";
        cin.clear();
        cin.ignore(123, '\n');
    }

    showBookingTable(); //Call function to display elements of booking table

    //Check if room number was booked
    if (roomNumber == bookedRoomNumber[roomNumber - 1]) {
        cout << "HDR-" << setw(16) << left << bookedReservationID[roomNumber - 1]
             << setw(11) << left<< bookedRoomNumber[roomNumber - 1]
             << setw(14) << left  << bookedRoomType[roomNumber - 1]
             << setw(23) << left << bookedGuestName[roomNumber - 1]
             << setw(21) << left << bookedGuestPhone[roomNumber - 1]
             << setw(14) << left  << bookedRoomNight[roomNumber - 1]
             << setw(21) << left  << bookedRoomCost[roomNumber - 1] << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
        cout << endl;
        count++;
    }

    if (count == 0) {
        cout << "ROOM #" << roomNumber << " IS NOT BOOKED!" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
        cout << endl;
    }
}

//Find room by guest's full name
void searchByName(string&guestName) {
    int count = 0;

    cin.ignore();
    cout << "-----------------------------" << endl;
    cout << "ENTER FULL NAME: ";
    cin.width(25);
    getline(cin, guestName);

    showBookingTable(); //Call function to display elements of booking table

    //Check if there is booked room on entered name
    for (int i = 0; i < hotelSize; i++) {
        if (guestName == bookedGuestName[i]) {
            cout << "HDR-" << setw(16) << left << bookedReservationID [i]
                 << setw(11) << left << bookedRoomNumber[i]
                 << setw(14) << left << bookedRoomType[i]
                 << setw(23) << left << bookedGuestName[i]
                 << setw(21) << left<< bookedGuestPhone[i]
                 << setw(14) << left << bookedRoomNight[i]
                 << setw(21) << left << bookedRoomCost[i] << endl;
            cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
            count ++;
        }
    }

    if (count == 0) {
        cout << "THERE IS NO BOOKING ON NAME " << guestName << "!" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
        cout << endl;
    }
    cout << endl;
}

void searchByReservationID(int&reservationID){
    int count = 0;
    cout << "-----------------------------" << endl;
    cout << "ENTER RESERVATION NUMBER: ";

    while (!(cin >> reservationID)) {
        cout << "ENTER RESERVATION NUMBER: ";
        cin.clear();
        cin.ignore(123, '\n');
    }

    showBookingTable();//Call function to display elements of booking table

    //Check if room number was booked
    for (int i = 0; i < hotelSize; i++) {
        if (reservationID == bookedReservationID[i]) {
            cout << "HDR-" << setw(16) << left << bookedReservationID[i]
                    << setw(11) << left << bookedRoomNumber[i]
                    << setw(14) << left << bookedRoomType[i]
                    << setw(23) << left << bookedGuestName[i]
                    << setw(21) << left<< bookedGuestPhone[i]
                    << setw(14) << left << bookedRoomNight[i]
                    << setw(21) << left << bookedRoomCost[i] << endl;
            cout<< "-----------------------------------------------------------------------------------------------------------------------"<< endl;
            cout << endl;
            count++;
        }
    }

    if (count == 0) {
        cout << "THERE IS NO BOOKING #" << reservationID << "!" << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
        cout << endl;
    }
}

//Delete booking by entering certain room number
void deleteBooking(int&roomNumber) {
    string option;

    cout << "ENTER ROOM NUMBER FROM 1-" << hotelSize << ": " ;

    //Check if input is number and not larger than total number of rooms
    while (!(cin >> roomNumber) || roomNumber < 1 || roomNumber > hotelSize) {
        cout << "ENTER ROOM NUMBER FROM 1-" << hotelSize << ": ";
        cin.clear();
        cin.ignore(123, '\n');
    }
    cout << endl;

    //Check if room number was booked
    if (bookedRoomNumber[roomNumber - 1] == roomNumber) {
        cout << "FOLLOWING BOOKING WILL BE DELETED: " << endl;

        showBookingTable();
        cout << "HDR-" << setw(16) << left << bookedReservationID[roomNumber - 1]
             << setw(11) << left<< bookedRoomNumber[roomNumber - 1]
             << setw(14) << left  << bookedRoomType[roomNumber - 1]
             << setw(23) << left << bookedGuestName[roomNumber - 1]
             << setw(21) << left << bookedGuestPhone[roomNumber - 1]
             << setw(14) << left  << bookedRoomNight[roomNumber - 1]
             << setw(21) << left  << bookedRoomCost[roomNumber- 1] << endl;
        cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "TO CONFIRM ENTER YES/NO: ";
        cin >> option;
        cout << endl;
    }
    else if (bookedRoomNumber[roomNumber - 1] != roomNumber) {
        cout << "THERE IS NO BOOKING FOR ROOM #" << roomNumber<< "!" << endl;
        cout << "--------------------------------" << endl;
        cout << endl;
    }
    //Deleting a booking if user confirmed it
    if (option == "Yes" || option == "Y" || option == "yes" || option == "y") {
        allRooms[roomNumber - 1] = false;
        bookedRoomNumber[roomNumber - 1] = 0;
        bookedGuestName[roomNumber - 1] = " ";
        bookedRoomNight[roomNumber - 1] = 0;
        bookedRoomCost[roomNumber- 1] = 0;
        cout << "BOOKING FOR ROOM #" << roomNumber << " WAS SUCCESSFULLY DELETED!" << endl;
        cout << "---------------------------------------------" << endl;
        cout << endl;
    }
}

//Display elements of booking table
void showBookingTable() {
    cout << endl;
    cout << setw(20) << left <<"RESERVATION ID"
         << setw(11) << left << "ROOM"
         << setw(14) << left << "TYPE"
         << setw(23) << left << "NAME"
         << setw(21) << left << "PHONE NUMBER"
         << setw(14) << left << "NIGHTS"
         << setw(21) << left << "ROOM COST (EUR)" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
}


