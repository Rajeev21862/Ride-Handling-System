#include <iostream> // Purpose: Input/Output operations

#include <cstdlib> // Gives: rand(), system()
#include <ctime> // to use time (0) in the program

#include<vector> // to use dynamic arrays
#include<string>  // to use operations like .size(), .empty(), basically gives functions to perform on arrays
#include<cmath> //  for math functions, for distance basically

#include<conio.h>  // for getch(), getche()
#include<windows.h> // for using sleep()

using namespace std;

// some constant credentials of the admin...
const string ADMIN_USER = "admin";
const string ADMIN_PASS = "1234";

// string& means instead of copying the message, we use the reference to the original message, and const is there to prevent modifications in the original message, keeping it safe
void typeWriterPrint(const string& message, int delay = 50) {

    // this is a range based loop, actually used to print the characters of the string (message), one by one , giving a typewrite style of printing eventually... MODERN CPP...
    for (char ch : message) {
        cout<< ch;
    // actually the break that comes in between, to simulate real life loading... for better UI/UX
        Sleep(delay);
    }
}

// it has default values if user doesnt pass and just call the function, and same const string& as above function, to keep the original message secure...
void loadingAnimation(const string& loadingText = "Loading", int delay = 200, int dots = 3) {
    system("cls");

    cout << "\n " << loadingText;
    // the dot printing effect in the UI
    for (int i = 0; i < dots; ++i) {
        cout << ".";
        Sleep(delay);
    }
    cout << "\n";
    system("cls");
}

// the name tells it all
bool adminLogin() {
    string username, password;
    int attempts = 0;

    // just a basic while loop to give user only 3 attempts to login, and just basic CPP
    // and sleep spamming is done to give a natural loading effect, like the system is fetching the info from the DB
    while (attempts < 3) {
        system("cls");

        cout << "\n ===== ADMIN LOGIN =====\n";
        cout << "\n Attempt " << (attempts + 1) << " of 3\n";

        cout << "\n Username: ";
        cin >> username;

        cout << " Password: ";
        cin >> password;

        cout << "\n\n Verifying credentials";
        for (int i = 0; i < 3; i++) {
            cout << ".";
            Sleep(500);
        }

        if (username == ADMIN_USER && password == ADMIN_PASS) {
            cout << "\n\n Login successful!\n";
            Sleep(1000);
            return true;
        }

        attempts++;
        cout << "\n\n Invalid credentials!";

        if (attempts < 3) {
            cout << " Try again...\n";
            Sleep(1200);
        } else {
            cout << "\n\n Too many failed attempts. Access blocked.\n";
            Sleep(1500);
        }
    }

    return false;
}

// name tells the functionality  of this class
class Location {
private:
    int x, y; public:
// parameterized constructor
    Location(int x=0, int y=0) {
    // using this-> to differentiate b/w vars of this class and parameters recieved on object creation
        this->x = x;
        this->y = y;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    void setX(int x) {
        this->x = x;
    }

    void setY(int y) {
        this->y = y;
    }
    // const Location& is getting the reference of the object passed to get the actual values and not copying the object passed, also the second const in the line is used to protect the data members of the class itself, like the calculations we are doing for distance, will not modify the original x and y...
    double distance(const Location& other) const {
        return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
    }
};


// nothing unique, basic class syntax
class Vehicle {
private:
    string type;
    int capacity;

public:
    // yaha par initializer list ka concept use hua hai, instead of writing type = t, we use this shortcut method to initialize data members, just faster in compilation...
    Vehicle(string t, int c) : type(t), capacity(c) {}

    string getType() const {
        return type;
    }

    int getCapacity() const {
        return capacity;
    }
};

class Driver {
private:
    string name;
    Location loc;    // may seem weird, but Location is class (which is a User-Defined DATATYPE also), so loc is the object created
    bool available; // this is toggled in the functions below to change driver's state
    Vehicle vehicle; // same as loc
     double totalEarnings;

public:
    // same initializer list concept...
    Driver(string n, Location l, Vehicle v) : name(n), loc(l), vehicle(v), available(true), totalEarnings(0)  {
    }

    string getName() const {
        return name;
    }

    const Location& getLocation() const {
        return loc;
    }

    bool isAvailable() const {
        return available;
    }

    const Vehicle& getVehicle() const {
        return vehicle;
    }

    double getTotalEarnings() const { return totalEarnings; }
        void setAvailability(bool status) {
            available = status;
        }

    void addEarnings(double amount) { totalEarnings += amount; }
    //  same concept of accessing the orignal object through reference (Location&), and const keeps the original object safe from modifications... read that again if you didn't understand...
    void acceptTrip(const Location& pickup, const Location& drop) {
        available = false;
        cout << "\n\n Driver " << name << " accepted the trip\n";
        // accessing the x , y data members of the pickup and drop objects... they have Location as Datatype ( bcz classes are datatypes), try to understand...
        cout << "\n Pickup: (" << pickup.getX() << ", " << pickup.getY() << ")\n";
        cout << "\n Drop: (" << drop.getX() << ", " << drop.getY() << ")\n";
    }

    void cancelTrip() {
        available = true;
        cout << "Driver " << name << "'s trip has been cancelled\n";
    }

    void finishTrip() {
        available = true;
        cout << "\n Driver " << name << " finished the trip\n";
    }
};

// mostly basic class syntax...
class User {
private:
    string name;
// may seem weird, but Location is class (which is a User-Defined DATATYPE also), so loc is the object created
    Location loc;

public:
// passing the object with x,y coordinates and assigning to the loc object of class using initializer list concept...
    User(string n, Location l) : name(n), loc(l) {}

    string getName() const {
        return name;
    }

    const Location& getLocation() const {
        return loc;
    }
};


// this is an abstract class..., objects from this class cannot be created...
// and this fare section is the example of the concept of POLYMORPHISM in DETAIL...
class FareStrategy {
public:
    // virtual function , the pure one bcz of that "= 0"...
    virtual double calculate(double distance, double baseRate) = 0;

    // virtual destructor to prevent memory leaks when we destroy/delete child class's objects...
    virtual ~FareStrategy() {}
};

class NormalFare : public FareStrategy {
public:

    // using the concept of function overriding...
    // playing with the pricing, nothing too complex...
    double calculate(double distance, double baseRate) {
        return distance * baseRate;
    }
};

class SurgeFare : public FareStrategy {
public:
    // same as above child class, nothing too mch special...
    double calculate(double distance, double baseRate) {
        return distance * baseRate * 1.5;
    }
};

// carpool is like "Chinchi" for easier understanding, multiple people travel together in a group (pool)...
class CarpoolFare : public FareStrategy {
public:
    int passengers;

    CarpoolFare(int p) {
        passengers = p;
    }

    // total fare is split into the passengers
    double calculate(double distance, double baseRate) {
        double total = distance * baseRate;
        return total / passengers;
    }
};

class Trip {
private:
    // using pointers (*) to point to the reference of the original user and driver, trip doesnt really own them here... only referencing them here... and preventing their copies here...
    User* user;
    Driver* driver;
    // this is tricky , this farestrategy here can point to any of the child objects of the fare strategy, three of them there are, in the upcoming code , there is a conditional check, deciding which one should be called...
    FareStrategy* fareStrategy;
    Location pickup, drop;
    double baseRate;
    string status; // this is used to manage the statuses of trip during a full trip lifecycle...
    double fare;

public:
    Trip(User* u, Location p, Location d, double rate)
    : user(u), pickup(p), drop(d), baseRate(rate),
      status("Requested"), driver(nullptr), fare(0), fareStrategy(nullptr) {}
/*
    Trip(User* u, Location p, Location d, double rate) {
        user = u;
        pickup = p;
        drop = d;
        baseRate = rate;
        status = "Requested";
        driver = nullptr;
        fare = 0;
        fareStrategy = nullptr;
    }
*/
    string getStatus() const {
        return status;
    }

    double getFare() const {
        return fare;
    }

    Driver* getDriver() const {
        return driver;
    }

    User* getUser() const {
        return user;
    }

    void setFareStrategy(FareStrategy* strategy) {
        fareStrategy = strategy;
    }

    void assignDriver(Driver* d) {
        driver = d;
        // we are using "->" here to point to the member function of the driver , ".(dot)" is not used bcz it is a pointer, not the original object... read again if u didnt understand... think deeply now..
        driver->acceptTrip(pickup, drop);
        status = "Accepted";
    }

    void startTrip() {
        if (status == "Cancelled") {
            cout << "\n Cannot start a cancelled trip\n";
            return;
        }
        if (status == "Completed") {
            cout << "\n Trip is already completed\n";
            return;
        }
        if (status == "Ongoing") {
            cout << "\n Passenger already picked up, trip is ongoing\n";
            return;
        }
        if (status != "Accepted") {
            cout << "\n Cannot start trip  driver has not accepted yet (current status: " << status << ")\n";
            return;
        }
        status = "Ongoing";
        Sleep(400);
        cout << "\n Trip Started";
    }

    void completeTrip() {
        if (status == "Cancelled") {
            cout << "Cannot complete a cancelled trip\n";
            return;
        }
        status = "Completed";
        double dist = pickup.distance(drop);
        if (fareStrategy == nullptr) {
            cout << "Error: Fare strategy not set\n";
            return;
        }

        fare = fareStrategy->calculate(dist, baseRate);
        // Free the driver
        if (driver != nullptr) {
            driver->addEarnings(fare);
            driver->finishTrip();
        }

//        cout << "\n Trip Completed.";
        cout << "\n\n Your Fare is: " << fare << "Rs." << endl;
    }

    void cancelTrip() {
        status = "Cancelled";
        // this is checking if pointer driver really exists, only then delete it, bcz you cant delete a non-existing thing...
        if (driver != nullptr) {
            driver->cancelTrip();
        }
        cout << "Trip Cancelled\n";
    }

    // cleaning the memory here...
    ~Trip() {

        // here delete is also used , bcz an instance or child object was created also, so "=nullptr" is not enough for farestrategy..., also because trip owns the farestrategy, not just pointing to it, you will understand it later after seeing the overall functionality...
        if (fareStrategy != nullptr) {
            delete fareStrategy;
            fareStrategy = nullptr;
       }
       // to prevent dangling pointers... freeing memory...
        user = nullptr;
        driver = nullptr;
    }
};

// for a temp fake request that goes to the driver in the driver's menu section, bcz we dont want to alter the original user and x,y coordiantes... i know its not understandable right now...you will understand later its actual purpose, not too complex tbh...
struct FakeRequest {
    User* user;
    Location pickup;
    Location drop;
};

class App {
public:
    // vector is just arrays, and App is storing th.e reference only ( the actual arrays ), not copies...meaning using them from outside (the main function), not owning the users, drivers... so the changes are reflected there ...
    vector<Driver>& drivers;
    vector<User>& users;
    // same pointer concept, directly accessing the orignal trip , no copies...
    Trip* trip;

    // member initializer list concept as told in the start of this program...
    App(vector<Driver>& d, vector<User>& u) : drivers(d), users(u) {
        // to cleanup garbage value in the pointer before using it...
        trip = nullptr;
    }

    void run();
    void adminMenu();
    void userMenu();
    void driverMenu();

    // that fake request generation for the driver menu...
    FakeRequest generateFakeRequest() {
        int userIndex = rand() % users.size();

        Location pickup(rand() % 10, rand() % 10);
        Location drop(rand() % 10, rand() % 10);

        return { &users[userIndex], pickup, drop };
    }

    // memory cleanup...
    ~App() {
        if (trip != nullptr) {
            delete trip;
        }
    }
};

void App::run() {
    char roleChoice;

    while(true) {

        loadingAnimation();

        Sleep(300);
        cout << "\n Select Your ROLE To ENTER The Corresponding MENU: ";
        Sleep(300);
        cout << "\n\n  1.Admin";
        cout << "\n  2.User";
        cout << "\n  3.Driver";
        cout << "\n\n Press ESC To Exit The Application...";
        Sleep(300);
        cout << "\n\n Enter Your Choice Here : " ;

        roleChoice = getche();

        switch(roleChoice) {
            case '1' : if (adminLogin()) adminMenu(); break;
            case '2' :  userMenu(); break;
            case '3' :  driverMenu(); break;
            case 27 : loadingAnimation("\n\n Exiting... Be Patient... Keep Your Fingers Away!!!", 700, 5); return;
        }
    }
}

void App::adminMenu() {

    char adminChoice;

    while (true) {
        loadingAnimation("Loading Admin Panel", 200, 3);

        string msg = "\n\n ======== ADMIN DASHBOARD ========\n";
        typeWriterPrint(msg, 30);

        Sleep(300);
        cout << "\n 1. View All Drivers";
        cout << "\n 2. View All Users";

        Sleep(300);
        cout << "\n\n Total Drivers: " << drivers.size();
        cout << "\n Total Users: " << users.size();

        Sleep(300);
        cout << "\n\n Press ESC To Return To MAIN MENU...";
        cout << "\n\n Enter Choice: ";

        adminChoice = getche();

        if (adminChoice == 27) return;

        system("cls");

        switch (adminChoice) {

        case '1':
            loadingAnimation("Fetching Drivers", 150, 3);

            cout << "\n ----- DRIVER DATABASE -----\n";
            cout << "\n Total Drivers: " << drivers.size() << "\n";

            cout << "\n\n [BIKE DRIVERS]\n";
            for (int i = 0; i < drivers.size(); i++) {
                if (drivers[i].getVehicle().getType() == "Bike") {
                    cout << "\n - " << drivers[i].getName();
                    cout << " | Location: (" << drivers[i].getLocation().getX() << ", " << drivers[i].getLocation().getY() << ")";
                    Sleep(150);
                }
            }

            cout << "\n\n [RICKSHAW DRIVERS]\n";
            for (int i = 0; i < drivers.size(); i++) {
                if (drivers[i].getVehicle().getType() == "Rickshaw") {
                    cout << "\n - " << drivers[i].getName();
                    cout << " | Location: (" << drivers[i].getLocation().getX() << ", " << drivers[i].getLocation().getY() << ")";
                    Sleep(150);
                }
            }

            cout << "\n\n [CAR DRIVERS]\n";
            for (int i = 0; i < drivers.size(); i++) {
                if (drivers[i].getVehicle().getType() == "Car") {
                    cout << "\n - " << drivers[i].getName();
                    cout << " | Location: (" << drivers[i].getLocation().getX() << ", " << drivers[i].getLocation().getY() << ")";
                    Sleep(150);
                }
            }

            break;

        case '2':
            loadingAnimation("Fetching Users", 150, 3);

            cout << "\n ----- USER LIST -----\n";
            cout << "\n Total Users: " << users.size() << "\n";

            for (int i = 0; i < users.size(); i++) {
                cout << "\n " << i + 1 << ". " << users[i].getName();
                cout << " | Location: (" << users[i].getLocation().getX() << ", " << users[i].getLocation().getY() << ")";
                Sleep(150);
            }

            break;

        default:
            cout << "\n Invalid choice";
        }

        cout << "\n\n Press any key to continue...";
        getch();
    }
}

void App::userMenu() {
    char userChoice;
    int choice;
    double baseRate;

    loadingAnimation();

    string inputName;
    cout << "\n Enter Your Name: ";
    cin >> inputName;

    // no user assigned yet, so assuring cleanup of garbage values...
    User* currentUser = nullptr;

    // this is a range based for loop like we used in the typewriter style printing function, but there was a string treated as a an array of characters, here is a real arrays of users...

    for (auto &u : users) { // auto means decide the datatype by yourself... here &u again means a reference to the actual element in the array of users, not a copy of that element

        if (u.getName() == inputName) {
            // again &u is used to reflect changes on the actual element of the array, not doing the operations on a copy...
            currentUser = &u;
            break;
        }
    }

    // overall the above loop is finding the "typed username" in the array of users...

    if (!currentUser) {
        cout << "\n User not found\n";
        cout << "\n Press Any Key To Go Back To MAIN MENU...";
        getch();
        return;
    }

    string welcomeMsg = "\n\n ============ Welcome, " + currentUser->getName() + "! ============\n";
    typeWriterPrint(welcomeMsg, 30);

    typeWriterPrint("\n Are You Ready to book your next ride? \n", 20);

    while (true) {
        cout << "\n Press Any Key To Request A Ride";
        cout << "\n\n Press ESC To Go Back To The MAIN MENU...";
        userChoice = getche();

        if (userChoice == 27) return;
        system("cls");

        if (trip != nullptr && trip->getStatus() != "Completed" && trip->getStatus() != "Cancelled") {
            cout << "Trip already in progress!\n";
            getch();
            continue;
        }

        Location drop;
        Location pickup;
        int x, y;

        while (true) {
            cout << "\n Enter pickup location (x y) [grid coordinates]: ";
            cout << "\n\n Enter X first : ";
            cin >> x;
            pickup.setX(x);
            cout << "\n Now Enter Y : ";
            cin >> y;
            pickup.setY(y);

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\n Invalid coordinates. Try again.\n";
                continue;
            }
            break;
        }

        while (true) {
            cout << "\n Enter drop location (x y) [grid coordinates]: ";
            cout << "\n\n Enter X first : ";
            cin >> x;
            drop.setX(x);
            cout << "\n Now Enter Y : ";
            cin >> y;
            drop.setY(y);

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\n Invalid coordinates. Try again.\n";
                continue;
            }
            break;
        }

        int vehicleChoice;

        while (true) {
            cout << "\n Select Vehicle Type:";
            cout << "\n 1. Bike";
            cout << "\n 2. Rickshaw";
            cout << "\n 3. Car";
            cout << "\n\n Enter Choice: ";

            cin >> vehicleChoice;

            if (cin.fail() || vehicleChoice < 1 || vehicleChoice > 3) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\n Invalid input. Try again.\n";
                continue;
            }
            break;
        }

        string selectedType;
        if (vehicleChoice == 1) selectedType = "Bike";
        else if (vehicleChoice == 2) selectedType = "Rickshaw";
        else if (vehicleChoice == 3) selectedType = "Car";

        // overall, this is a loop to print the list of available drivers to the user...
        vector<Driver*> validDrivers; // pointer to the drivers...
        for (int i = 0; i < drivers.size(); i++) {
            if (drivers[i].getVehicle().getType() == selectedType && drivers[i].isAvailable()) {
                validDrivers.push_back(&drivers[i]); // storing the refrence of the original driver from drivers array, no copies, again the same thing...
                cout << "\n " << validDrivers.size() << ". " << drivers[i].getName();
            }
        }

        if (validDrivers.empty()) {
            cout << "\n No drivers available for selected vehicle type\n";
            delete trip;
            trip = nullptr;
            break;
        }

        while (true) {
            cout << "\n\n Enter Choice: ";
            cin >> choice;

            if (cin.fail() || choice < 1 || choice > validDrivers.size()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\n Invalid choice. Try again.\n";
                continue;
            }
            break;
        }

        if (choice < 1 || choice > validDrivers.size()) {
            cout << "\n Invalid choice\n";
            delete trip;
            trip = nullptr;
            break;
        }

        // this is just done to use the correct indexing, because arrays starts from 0 not 1, if user enters 3, it would be converted to 2 automatically...
        Driver* d = validDrivers[choice - 1];

        int fareChoice;

        while (true) {
            cout << "\n Select Your Ride Type:";
            if (selectedType != "Bike") cout << "\n 1. Normal  2. Surge  3. Carpool";
            else cout << "\n 1. Normal  2. Surge ";
            cout << "\n\n Enter Your Choice: ";
            cin >> fareChoice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\n Invalid input. Try again.\n";
                continue;
            }

            if (selectedType == "Bike" && (fareChoice < 1 || fareChoice > 2)) {
                cout << "\n Invalid choice for Bike.\n";
                continue;
            }

            if (selectedType != "Bike" && (fareChoice < 1 || fareChoice > 3)) {
                cout << "\n Invalid choice.\n";
                continue;
            }
            break;
        }

        if (selectedType == "Bike") baseRate = 5;
        else if (selectedType == "Rickshaw") baseRate = 8;
        else baseRate = 10;

        if (trip != nullptr) {
            delete trip;
            trip = nullptr;
        } // to delete the existing garbage values...

        trip = new Trip(currentUser, pickup, drop, baseRate);

        // we created a pointer farestrategy, pointing to a derived class... , different cases mein different child classes ka object ban raha, is se jab hum ->calculate run karenge toh us faretype ke object mein jo calculate hai woh run hoga...
        if (fareChoice == 1) trip->setFareStrategy(new NormalFare());
        else if (fareChoice == 2) trip->setFareStrategy(new SurgeFare());
        else trip->setFareStrategy(new CarpoolFare(2)) ;

        string msg1 = "\n\n [Sending the Offer To " + d->getName() + "...Be Patient!] \n";
        typeWriterPrint(msg1, 25);
        Sleep(2000);
        loadingAnimation("",200,10);

        // calling the functions of Trip class, and trip was a pointer to the original object...
        trip->assignDriver(d);

        string msg2 = "\n [" + d->getName()+ " is arriving in 2 minutes] \n";
        typeWriterPrint(msg2, 15);
        Sleep(3000);
        trip->startTrip();

        typeWriterPrint("\n\n [Travelling to Your Destination...Will Reach Soon!] \n", 15);
        Sleep(2000);
        // yaha pe Trip class mein jo function pada hai complete trip woh call horaha aur usi mein calculate pada hai , jo ke same farestrategy ka pointer use karraha , aur woh jo calculate use karega woh humne yaha upar ^ decide kiya tha if .. else mein...
        trip->completeTrip();

        cout << "\n Press Any Key To Go Back To USER MENU...";
        cout << "\n Press ESC Key To Go Back To MAIN MENU...";

        char postRideChoice = getche();
        if (postRideChoice == 27) {
            return;   // go back to main menu
        }

        system("cls");
    }
}

void App::driverMenu() {

    // READ THIS: overall , driver menu is almost same functionality like usermenu, difference is driver has control over ride, whereas user just sees a simulation of ride acceptance, travelling and reaching, driver can accept , cancel , start the ride , everything by his will, like real world, user is a bit weaker in our program...

    string inputName;
    loadingAnimation("Loading Driver Panel", 150, 4);

    cout << "\n Enter Driver Name: ";
    cin >> inputName;

    Driver* currentDriver = nullptr;

    // same mechanics as the above user menu, for finding the typed drivername...
    for (auto &d : drivers) {
        if (d.getName() == inputName) {
            currentDriver = &d;
            break;
        }
    }

    if (!currentDriver) {
        cout << "\n Driver not found\n";
        getch();
        return;
    }
    char driverChoice;

    // this is done to not lose the values of the pointer activetrip , otherwise we would lose the values between different function call, it is for value persistance between function calls...
    static Trip* activeTrip = nullptr;

    loadingAnimation("Fetching Driver Dashboard", 300, 3);
    string welcomeMsg = "\n\n ============ Welcome, " + currentDriver->getName() + "! ============\n";
    typeWriterPrint(welcomeMsg, 30);
    cout << "\n Get on the Road NOW!...\n";


    while (true) {
        if (activeTrip && activeTrip->getStatus() == "Completed") {
            delete activeTrip;
            activeTrip = nullptr;
        }

        Sleep(300);
        cout << "\n 1. View Status";
        cout << "\n 2. Toggle Availability";
        cout << "\n 3. Check Incoming Ride";
        Sleep(300);
        cout << "\n 4. Accept Ride";
        cout << "\n 5. Start Ride";
        cout << "\n 6. Reach Destination";
        cout << "\n\n Press ESC To Return To MAIN MENU...";

        Sleep(300);
        cout << "\n\n Enter Choice: ";
        driverChoice= getche();

        if (driverChoice == 27) return;
        system("cls");

        switch (driverChoice) {

        case '1':
            loadingAnimation("Checking Status", 100, 2);
            cout << "\n Status: "
                 << (currentDriver->isAvailable() ? "Available" : "Busy") << endl;

            cout << "\n Location: (" << currentDriver->getLocation().getX()
                 << ", " << currentDriver->getLocation().getY() << ")";
            break;

        case '2':
            loadingAnimation("Updating Availability", 100, 3);
            Sleep(500);

            currentDriver->setAvailability(!currentDriver->isAvailable());

            cout << "\n Availability Updated: "
                 << (currentDriver->isAvailable() ? "Available" : "Busy");
            break;

        case '3': {

            if (activeTrip && activeTrip->getStatus() != "Completed") {
                cout << "\n You already have an active trip!\n";
                break;
            }

            loadingAnimation("Scanning Nearby Requests", 150, 4);
            Sleep(800);

            // below : rand is being used with other things to randomize the user requesting for ride, making it dynamic instead of fixed user... rand % 10 is actually generating a fake grid system (city map simulation, a bit complex, just let it work, dont overthink),

            // overall a random user ride request is being generated for the the driver...
            User* randomUser = &users[rand() % users.size()];

            Location pickup(rand() % 10, rand() % 10);
            Location drop(rand() % 10, rand() % 10);

            cout << "\n --- Incoming Ride Request --- \n";
            typeWriterPrint("\n Incoming request detected...\n", 20);
            Sleep(300);

            cout << "\n User: " << randomUser->getName();
            cout << "\n Pickup: (" << pickup.getX() << ", " << pickup.getY() << ")";
            cout << "\n Drop: (" << drop.getX() << ", " << drop.getY() << ")";

            if (activeTrip != nullptr) {
                delete activeTrip;
                activeTrip = nullptr;
            }

            activeTrip = new Trip(randomUser, pickup, drop, 10);
            activeTrip->setFareStrategy(new NormalFare());
            break;
        }

        case '4':
            if (activeTrip && (activeTrip->getStatus() == "Accepted" || activeTrip->getStatus() == "Ongoing")) {
                cout << "\n You already have an active trip!\n";
                break;
            }

            if (!activeTrip) {
                cout << "\n No active request available\n";
                break;
            }

            if (!currentDriver->isAvailable()) {
                cout << "\n You are currently busy\n";
                break;
            }

            loadingAnimation("Sending Acceptance", 120, 4);
            Sleep(500);

            activeTrip->assignDriver(currentDriver);
            currentDriver->setAvailability(false);

            typeWriterPrint("\n Driver assigned successfully...\n", 20);
            typeWriterPrint("\n Rider is on the way...\n", 20);

            break;

        case '5':
            if (!activeTrip) {
                cout << "\n No active trip found\n";
                break;
            }

            if (activeTrip && (activeTrip->getStatus() != "Ongoing")) {
                loadingAnimation("Picking Up Passenger", 120, 4);
                Sleep(600);
                typeWriterPrint("\n\n Passenger picked up successfully...\n", 20);
            }

            activeTrip->startTrip();

            break;

        case '6':
            if (!activeTrip) {
                cout << "\n No active trip found\n";
                break;
            }

            loadingAnimation("Reaching Destination", 120, 5);
            Sleep(800);

            typeWriterPrint("\n Trip completed...\n", 20);
            activeTrip->completeTrip();

            cout << "\n --- DRIVER SUMMARY ---";
            cout << "\n This trip earned: " << activeTrip->getFare() << " Rs";
            cout << "\n Total earnings: " << currentDriver->getTotalEarnings() << " Rs";

            delete activeTrip;
            activeTrip = nullptr;

            break;
        }

        cout << "\n\n Press any key to continue...";
        getch();

        system("cls");
    }
}

int main() {

    // this is to make the rand() truly random, otherwise it only uses one random number across different program executions, which no longer remains random, so this is a seed setup using time's value to randomize truly... i know a lot of info , just understand the concept and working...
    srand(time(0));
    rand(); rand(); rand();

    // keep this constructor in mind while reading the array below, its not that complex...

    // Driver(string n, Location l, Vehicle v),

    vector<Driver> drivers = {
        Driver("shamir", Location(3,4), Vehicle("Bike",1)),
        Driver("zaid", Location(5,1), Vehicle("Bike",1)),
        Driver("faizan", Location(2,6), Vehicle("Bike",1)),
        Driver("fahad", Location(7,3), Vehicle("Bike",1)),
        Driver("muneeb", Location(4,5), Vehicle("Bike",1)),

        Driver("agha", Location(8,4), Vehicle("Rickshaw",2)),
        Driver("tanzeel", Location(5,6), Vehicle("Rickshaw",2)),
        Driver("hamza", Location(6,5), Vehicle("Rickshaw",2)),
        Driver("tahir", Location(7,7), Vehicle("Rickshaw",2)),
        Driver("rana", Location(3,7), Vehicle("Rickshaw",2)),

        Driver("usman", Location(1,2), Vehicle("Car",4)),
        Driver("sufyan", Location(2,5), Vehicle("Car",4)),
        Driver("zain", Location(4,3), Vehicle("Car",4)),
        Driver("wahab", Location(3,6), Vehicle("Car",4)),
        Driver("sheraz", Location(6,2), Vehicle("Car",4)),
    };

    // constructor below, try to understand the concept ...
    // User(string n, Location l)
    vector<User> users = {
        User("abdullah", Location(2,3)),
        User("hassaan", Location(5,1)),
        User("maryam", Location(7,4)),
        User("ata", Location(3,6)),
        User("laiba", Location(8,2))
    };

    // the main App class is used to create app object, which then uses the function run inside it to show the main menu, and the above defined arrays are passed into the app object, easy right?
    App app(drivers, users);
    app.run();

    return 0;
}
