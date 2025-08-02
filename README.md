# RouteRide - A Simple Ride Sharing System

**RouteRide** is a basic console-based ride-sharing simulation system implemented in C++. It mimics a simplified version of real-world ride-hailing services like Ola and Uber, supporting multiple users, drivers, and distance-based fare calculations.

---

## Features

- **User Registration**: Riders can register with their name and ID. 
- **Driver and Vehicle Details**: Preloaded drivers with vehicle registration and types.
- **Location-Based Rides**: Choose from predefined locations to start and end your ride.
- **Fare Calculation**: Charges ₹20 per kilometer based on location distances.
- **Ride History**: Both riders and drivers can view their ride history.
- **Data Persistence**: Drivers can save their ride histories to local `.txt` files.

---

## Tech Stack

- **Language**: C++
- **Concepts Used**:
  - Object-Oriented Programming (OOP)
  - Inheritance and Polymorphism
  - File Handling
  - Vectors and Dynamic Memory Allocation

---

## How It Works

1. **Register Riders** using option `1`.
2. **Request a Ride** by choosing a source and destination.
3. **Automatic Driver Assignment** if available.
4. **View Ride History** anytime.
5. **Persist Driver Ride History** to a file for records.

---

## Example Locations

| Location          | Distance from Center (km) |
|-------------------|---------------------------|
| Brigade Road      | 7                         |
| MG Road           | 2                         |
| Outer Ring Road   | 9                         |
| Bellary Road      | 11                        |

---

## File Structure 
RouteRide/
│
├── main.cpp           # Main C++ source file
├── driver_XXX_history.txt  # Generated ride history files for drivers
├── README.md          # Project Documentation

---

## Sample Output
--------------RouteRide Selection-------------
1) Register Ride
2) Request Ride
3) Show Rider History
4) Show Driver History
5) Save Driver History
6) Exit
Enter choice: 1
Enter name and ID: Alice 201
Rider Registered Successfully.

--------------RouteRide Selection-------------
1) Register Ride
2) Request Ride
3) Show Rider History
4) Show Driver History
5) Save Driver History
6) Exit
Enter choice: 2
Select Rider Index:
0: Alice
Enter source index: 1
Enter destination index: 3
Ride Started.
Ride ended.

--------------RouteRide Selection-------------
1) Register Ride
2) Request Ride
3) Show Rider History
4) Show Driver History
5) Save Driver History
6) Exit
Enter choice: 3

Ride history for Rider: Alice
FromMG Road to Bellary Road | Price: Rs. 180

--------------RouteRide Selection-------------
Enter choice: 4

Driver: Rahul, ID: 101
Vehicle: Tata Tiago | Reg#: KA 03 AB 1234
Unavailable

Ride history for Driver: Rahul
FromMG Road to Bellary Road | Price: Rs. 180


