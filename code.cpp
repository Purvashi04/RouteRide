//RouteRide : A Ride Sharing System with multiple users and distance based fare.
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

//---Location Class---
class Location{
    string name;
    int distanceFromCenter;
public:
    Location(string n, int d): name(n), distanceFromCenter(d) {}
    string getName() const { return name; }
    int getDistance() const { return distanceFromCenter; }
};

//---User base Class---
class User{
protected:
   string name;
   int id;
public:
    User(string n, int i): name(n), id(i) {}
    virtual void display() const = 0;
    virtual ~User() = default;
    string getName() const { return name; }
    int getId() const { return id; }
};

//---Vehicle class---
class Vehicle{
    string name;
    string type;
public:
   Vehicle(string n, string t): name(n), type(t) {}
   void display() const{
     cout << "Vehicle: " << type << " | Reg#: " << name << endl;
   }
};

class Ride;

//---Rider Class---
class Rider : public User{
    vector<Ride*> rideHistory;
public:
    Rider(string n, int i): User(n, i) {}
    void display() const override{
        cout << "Rider: " << name << ", ID: " << id << endl;
    }
    void addRideToHistory(Ride* r){ rideHistory.push_back(r); }
    void showRideHistory() const;
};

//---Driver Class---
class Driver : public User{
    Vehicle* vehicle;
    bool available;
    vector<Ride*> rideHistory;
    public:
        Driver(string n, int i, Vehicle* v): User(n, i), vehicle(v), available(true) {}
        void display() const override{
            cout << "Driver: " << name << ", ID: " << id << endl;
            vehicle->display();
            cout << (available ? "Available" : "Unavailable") << endl;
        }
        void setAvailable(bool a) { available = a;}
        bool isAvailable() const { return available; }
        void addRideToHistory(Ride* r) { rideHistory.push_back(r); }
        void showRideHistory() const;
        void saveRideHistoryToFile() const;
};

//---Ride Class---
class Ride{
   Rider* rider;
   Driver* driver;
   Location source;
   Location destination;
   double price;
public:
   Ride(Rider* r, Driver* d, Location s, Location e): rider(r), driver(d), source(s), destination(e){
        abs(source.getDistance()-destination.getDistance())* 20.0; //Rs.20 per km
    }
    void startRide() {cout << "Ride Started." << endl;}
    void endRide() {cout << "Ride ended." << endl;} 
    void displayRideDetails() const {
        cout << "From" << source.getName() << " to " << destination.getName() << " | Price: Rs.  " << price << endl;
    }
    Driver* getDriver() const { return driver; }
    Location getSource() const { return source; }
    Location getDestination() const { return destination; }
    double getPrice() const { return price; }
};

void Rider :: showRideHistory() const{
    cout << "\nRide history for Rider: " << name << endl;
    for( const auto& ride: rideHistory){
        ride->displayRideDetails();
    }
}

void Driver :: showRideHistory() const{
     cout << "\nRide history for Driver: " << name << endl;
     for( const auto& ride : rideHistory){
        ride->displayRideDetails();
     }
}

void Driver:: saveRideHistoryToFile() const{
    ofstream file("driver_" + to_string(id) + "_history.txt");
    for( const auto& ride : rideHistory){
        file << "From" << ride->getSource().getName()
             << "to" << ride->getDestination().getName()
             << ", Price: Rs. " << ride->getPrice() << endl;
    }
    file.close() ;
}

//---Ride Manager---
class RideManager {
    vector<Driver*> drivers;
    vector<Ride*> activeRides;
public:
    void addDriver(Driver* d) { drivers.push_back(d); }
    void requestRide(Rider* rider, const Location& src, const Location& dest){
        for(auto driver : drivers){
            if(driver->isAvailable()){
                Ride* newRide = new Ride(rider, driver, src, dest);
                activeRides.push_back(newRide);
                driver->setAvailable(false);
                newRide->startRide();
                newRide->endRide();
                driver->addRideToHistory(newRide);
                rider->addRideToHistory(newRide);
                return;
            }
        }
        cout << "Drivers are Not Available." << endl;
    }
    void listDrivers() const{
        for(auto d : drivers) d->display();
    }
};

//---Main Screen---
int main(){
    RideManager manager;
    vector<Rider*> riders;

    //Seed drivers
    manager.addDriver(new Driver("Rahul", 101, new Vehicle("KA 03 AB 1234", "Tata Tiago")));
    manager.addDriver(new Driver("Kamala", 102 , new Vehicle("KA 03 CD 5678", "Hyundai Santro")));
    manager.addDriver(new Driver("Mani", 103 , new Vehicle("KA 03 HL 6754", "Hyundai Santro")));

    //Predefined Locations
    vector<Location> locations = {
        Location("Brigade Road", 7),
        Location("MG Road", 2),
        Location("Outer Ring Road", 9), 
        Location("Bellary Road", 11)
    };

    int choice;
    do{
        cout << "\n--------------RouteRide Selection-------------" << endl;
        cout << "1) Register Ride\n2) Request Ride\n3) Show Rider History\n4) Show Driver History\n5) Save Driver History\n6) Exit\nEnter choice: ";
        cin>> choice;

        switch(choice){
            case 1: {
                string name;
                int id;
                cout << "Enter name and ID: ";
                cin >> name >> id;
                riders.push_back(new Rider(name, id));
                cout << "Rider Registered Successfully. \n";
                break;
            }
            case 2:{
                if(riders.empty()){
                    cout << "Register a rider first.\n" ;
                    break;
                }
                int rindex;
                cout << "Select Rider Index: ";
                for(int i=0; i < riders.size(); ++i)
                    cout << i << ": " << riders[i]->getName() << "\n";
                    cin >> rindex;

                cout << "Available Locations:\n";
                for(int i=0; i< locations.size(); ++i)
                    cout << i << ": " << locations[i].getName() <<" (" << locations[i].getDistance() << "km)\n";

                    int src, dest;
                    cout << "Enter source index: "; cin>> src;
                    cout << "Enter destination index: "; cin >> dest;

                    manager.requestRide(riders[rindex], locations[src], locations[dest]);
                    break;
            }
            case 3:{
                for(auto r : riders) r-> showRideHistory();
                break;
            }
            case 4:
                 manager.listDrivers();
                 break;
            case 5:
               cout << "Saving all driver histories...\n";
               break;
            case 6:
               cout << "--Exiting RouteRide--\n";
               break;
            default:
               cout << "Inavlid Input!\n";
        }
    }while (choice != 6);
    //Clean up 
    for (auto r : riders) delete r;
    return 0;
}