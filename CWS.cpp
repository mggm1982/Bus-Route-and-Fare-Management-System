// BUS TOUR AND FARE MANAGEMENT SYSTEM

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
using namespace std;

const int STOPS = 15; // total bus stops
const int MAX_BOOKINGS = 100; // max bookings in one run
const int MAX_PASSENGERS = 100; // max passengers in one booking
const double STUDENT_DISCOUNT = 0.10; // student discount

// Bus stop names
string stops[STOPS] = {
    "Karnal", "Panipat", "Sonipat", "Delhi", "Murthal",
    "Rohtak", "Ambala", "Kurukshetra", "Chandigarh",
    "Yamunanagar", "Pehowa", "Kaithal", "Jind", "Hisar",
    "Gurugram"
};

// Distance matrix (in kilometres)
int distanceMatrix[STOPS][STOPS] = {
    {0,35,90,135,65,120,40,35,125,80,75,65,95,150,150},
    {35,0,55,100,30,85,75,70,140,115,105,110,85,130,100},
    {90,55,0,45,25,50,130,125,175,170,140,145,100,155,100},
    {135,100,45,0,70,70,175,170,220,215,180,180,125,170,30},
    {65,30,25,70,0,55,105,100,150,145,130,140,110,160,105},
    {120,85,50,70,55,0,160,155,205,170,170,100,60,90,75},
    {40,75,130,175,105,160,0,45,110,70,70,95,150,245,260},
    {35,70,125,170,100,155,45,0,95,45,25,45,95,170,210},
    {125,140,175,220,150,205,110,95,0,140,105,125,180,260,260},
    {80,115,170,215,145,170,70,45,140,0,85,115,160,200,260},
    {75,105,140,180,130,170,70,25,105,85,0,45,95,160,190},
    {65,110,145,180,140,100,95,45,125,115,45,0,75,120,175},
    {95,85,100,125,110,60,150,95,180,160,95,75,0,100,135},
    {150,130,155,170,160,90,245,170,260,200,160,120,100,0,190},
    {150,100,100,30,105,75,260,210,260,260,190,175,135,190,0}
};

// Booking structure
struct Booking {
    string passengerNames[MAX_PASSENGERS];
    double passengerFares[MAX_PASSENGERS];
    double passengerDiscounts[MAX_PASSENGERS];
    int passengerCount;
    string source;
    string destination;
    int totalDistance;
    bool roundTrip;
    double totalFare;
};

Booking bookings[MAX_BOOKINGS];
int bookingCount = 0;
double totalCollection = 0;

// Display all bus stops
void displayStops() {
    cout << "\n------ AVAILABLE BUS STOPS ------\n";

    for (int i = 0; i < STOPS; i++) {
        cout << i + 1 << ". " << stops[i] << endl;
    }
}

// Get valid stop number
int getStopNumber(string message) {
    int choice;

    while (true) {
        cout << message;

        if (cin >> choice && choice >= 1 && choice <= STOPS) {
            return choice - 1;
        }

        cout << "Invalid input! Enter a number from 1 to "
             << STOPS << ".\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Calculate fare according to distance
double calculateFare(int km) {
    if (km == 0) {
        return 0;
    }
    else if (km <= 20) {
        return 20;
    }
    else if (km <= 50) {
        return 20 + (km - 20) * 1.5;
    }
    else if (km <= 100) {
        return 65 + (km - 50) * 1.2;
    }
    else {
        return 125 + (km - 100);
    }
}

// Display route and distance
void showJourney(int source, int destination) {
    cout << "\nRoute: " << stops[source]
         << " -> " << stops[destination] << endl;

    cout << "Distance: "
         << distanceMatrix[source][destination]
         << " km\n";
}

// Calculate one-way fare
void singleFare() {
    displayStops();

    int source = getStopNumber("\nEnter source stop number: ");
    int destination = getStopNumber("Enter destination stop number: ");

    if (source == destination) {
        cout << "Source and destination cannot be the same.\n";
        return;
    }

    int km = distanceMatrix[source][destination];

    showJourney(source, destination);

    cout << fixed << setprecision(2);
    cout << "One-way fare: Rs. " << calculateFare(km) << endl;
}

// Calculate fare for multiple passengers
void multipleFare() {
    displayStops();

    int source = getStopNumber("\nEnter source stop number: ");
    int destination = getStopNumber("Enter destination stop number: ");

    if (source == destination) {
        cout << "Source and destination cannot be the same.\n";
        return;
    }

    int count;

    cout << "Enter number of passengers: ";

    if (!(cin >> count) || count < 1 ||
        count > MAX_PASSENGERS) {
        cout << "Invalid passenger count.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    int km = distanceMatrix[source][destination];
    double fare = calculateFare(km);

    showJourney(source, destination);

    cout << fixed << setprecision(2);
    cout << "Fare per passenger: Rs. " << fare << endl;
    cout << "Total fare for " << count
         << " passengers: Rs. " << fare * count << endl;
}

// Calculate round-trip fare
void roundTripFare() {
    displayStops();

    int source = getStopNumber("\nEnter source stop number: ");
    int destination = getStopNumber("Enter destination stop number: ");

    if (source == destination) {
        cout << "Source and destination cannot be the same.\n";
        return;
    }

    int km = distanceMatrix[source][destination];
    int roundDistance = km * 2;

    showJourney(source, destination);

    cout << "Round-trip distance: "
         << roundDistance << " km\n";

    cout << fixed << setprecision(2);
    cout << "Round-trip fare: Rs. "
         << calculateFare(roundDistance) << endl;
}

// Generate ticket with individual student discounts
void generateTicket() {
    if (bookingCount >= MAX_BOOKINGS) {
        cout << "Booking limit reached!\n";
        return;
    }

    displayStops();

    int source = getStopNumber("\nEnter source stop number: ");
    int destination = getStopNumber("Enter destination stop number: ");

    if (source == destination) {
        cout << "Source and destination cannot be the same.\n";
        return;
    }

    int count;

    cout << "Enter number of passengers: ";

    if (!(cin >> count) || count < 1 ||
        count > MAX_PASSENGERS) {
        cout << "Invalid passenger count.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    char tripChoice;

    cout << "Is this a round trip? (Y/N): ";
    cin >> tripChoice;

    if (tripChoice != 'Y' && tripChoice != 'y' &&
        tripChoice != 'N' && tripChoice != 'n') {
        cout << "Invalid trip choice.\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    bool isRoundTrip =
        (tripChoice == 'Y' || tripChoice == 'y');

    // Clear newline before reading passenger names
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int km = distanceMatrix[source][destination];

    if (isRoundTrip) {
        km = km * 2;
    }

    double baseFare = calculateFare(km);

    Booking newBooking;

    newBooking.source = stops[source];
    newBooking.destination = stops[destination];
    newBooking.totalDistance = km;
    newBooking.passengerCount = count;
    newBooking.roundTrip = isRoundTrip;
    newBooking.totalFare = 0;

    cout << "\n------ PASSENGER DETAILS ------\n";

    for (int i = 0; i < count; i++) {

        cout << "\nEnter name of passenger "
             << i + 1 << ": ";

        getline(cin, newBooking.passengerNames[i]);

        while (newBooking.passengerNames[i].empty()) {
            cout << "Name cannot be empty. Enter again: ";
            getline(cin, newBooking.passengerNames[i]);
        }

        char studentChoice;

        while (true) {
            cout << "Is " << newBooking.passengerNames[i]
                 << " a student? (Y/N): ";

            cin >> studentChoice;

            if (studentChoice == 'Y' || studentChoice == 'y' ||
                studentChoice == 'N' || studentChoice == 'n') {
                break;
            }

            cout << "Please enter Y or N.\n";

            // Clear invalid input before asking again
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // IMPORTANT FIX:
        // Remove the Enter key left by cin before next getline()
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        double discount = 0;

        if (studentChoice == 'Y' || studentChoice == 'y') {
            discount = baseFare * STUDENT_DISCOUNT;
        }

        newBooking.passengerDiscounts[i] = discount;

        newBooking.passengerFares[i] =
            baseFare - discount;

        newBooking.totalFare +=
            newBooking.passengerFares[i];
    }

    // Save booking
    bookings[bookingCount] = newBooking;
    bookingCount++;

    totalCollection += newBooking.totalFare;

    // Print ticket
    cout << "\n\n========== BUS TICKET ==========\n";

    cout << "From: " << newBooking.source << endl;
    cout << "To: " << newBooking.destination << endl;

    cout << "Trip type: "
         << (isRoundTrip ? "Round Trip" : "One Way")
         << endl;

    cout << "Total distance: "
         << km << " km\n";

    cout << "--------------------------------\n";

    for (int i = 0; i < count; i++) {

        cout << "\nPassenger: "
             << newBooking.passengerNames[i] << endl;

        cout << "Original fare: Rs. "
             << baseFare << endl;

        cout << "Student discount: Rs. "
             << newBooking.passengerDiscounts[i] << endl;

        cout << "Final fare: Rs. "
             << newBooking.passengerFares[i] << endl;
    }

    cout << "\n--------------------------------\n";

    cout << "Total passengers: " << count << endl;

    cout << "Total ticket fare: Rs. "
         << newBooking.totalFare << endl;

    cout << "================================\n";
}

// Calculate student discount
void discountFare() {
    double fare;

    cout << "\nEnter original fare: Rs. ";

    if (!(cin >> fare) || fare < 0) {
        cout << "Invalid fare.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    double discount = fare * STUDENT_DISCOUNT;
    double finalFare = fare - discount;

    cout << fixed << setprecision(2);

    cout << "Student discount (10%): Rs. "
         << discount << endl;

    cout << "Final fare: Rs. "
         << finalFare << endl;
}

// Display total fare collection
void showCollection() {
    cout << fixed << setprecision(2);

    cout << "\n------ FARE COLLECTION ------\n";

    cout << "Total bookings: "
         << bookingCount << endl;

    cout << "Total fare collection: Rs. "
         << totalCollection << endl;
}

// Main function
int main() {
    int choice;

    do {
        cout << "\n\n====================================\n";
        cout << " BUS ROUTE AND FARE MANAGEMENT SYSTEM\n";
        cout << "====================================\n";

        cout << "1. Display Bus Stops\n";
        cout << "2. Calculate Distance\n";
        cout << "3. Calculate One-Way Fare\n";
        cout << "4. Calculate Multiple Passenger Fare\n";
        cout << "5. Calculate Round-Trip Fare\n";
        cout << "6. Generate Ticket\n";
        cout << "7. Calculate Student Discount\n";
        cout << "8. Display Total Fare Collection\n";
        cout << "9. Exit\n";

        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Enter a number.\n";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            continue;
        }

        switch (choice) {
            case 1:
                displayStops();
                break;

            case 2: {
                displayStops();

                int source = getStopNumber(
                    "\nEnter source stop number: ");

                int destination = getStopNumber(
                    "Enter destination stop number: ");

                if (source == destination) {
                    cout << "Source and destination cannot be the same.\n";
                }
                else {
                    showJourney(source, destination);
                }

                break;
            }

            case 3:
                singleFare();
                break;

            case 4:
                multipleFare();
                break;

            case 5:
                roundTripFare();
                break;

            case 6:
                generateTicket();
                break;

            case 7:
                discountFare();
                break;

            case 8:
                showCollection();
                break;

            case 9:
                cout << "\nThank you for using the system!\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 9);

    return 0;
}
