#include <bits/stdc++.h>
using namespace std;
class Vehicle
{
protected:
    int id;
    string brand;
    double rentPerHr;
    bool avail;

public:
    Vehicle(int id, string brand, double rent)
        : id(id), brand(brand), rentPerHr(rent), avail(true) {}
    virtual void info() const = 0;
    virtual double calculateRent(int hours) const
    {
        return rentPerHr * hours;
    }
    int getId() const
    {
        return id;
    }
    bool isAvailable() const
    {
        return avail;
    }
    void rentVehicle()
    {
        avail = false;
    }
    void returnVehicle()
    {
        avail = true;
    }
    virtual ~Vehicle() {}
};

// Car
class Car : public Vehicle
{
    int seats;

public:
    Car(int id, string brand, double rate, int seats)
        : Vehicle(id, brand, rate), seats(seats) {}
    void info() const override
    {
        cout << "[CAR] ID: " << id
             << ", Brand: " << brand
             << ", Seats: " << seats
             << ", Rate/hr: " << rentPerHr
             << ", Status: " << (avail ? "Available" : "Rented")
             << endl;
    }
};

// Bike
class Bike : public Vehicle
{
    string type;

public:
    Bike(int id, string brand, double rate, string type)
        : Vehicle(id, brand, rate), type(type) {}

    void info() const override
    {
        cout << "[BIKE] ID: " << id
             << ", Brand: " << brand
             << ", Type: " << type
             << ", Rate/hr: " << rentPerHr
             << ", Status: " << (avail ? "Available" : "Rented")
             << endl;
    }
};
class VehicleManager
{
    vector<Vehicle *> vehicles;

public:
    void addVehicle(Vehicle *v)
    {
        vehicles.push_back(v);
    }
    void displayVehicles() const
    {
        for (auto v : vehicles)
            v->info();
    }
    void showAvailableVehicles() const
    {
        for (auto v : vehicles)
            if (v->isAvailable())
                v->info();
    }
    int countAvailableVehicles() const
    {
        int count = 0;
        for (auto v : vehicles)
            if (v->isAvailable())
                count++;
        return count;
    }
    Vehicle *findById(int id)
    {
        for (auto v : vehicles)
            if (v->getId() == id)
                return v;
        return nullptr;
    }

    // memory cleanup
    ~VehicleManager()
    {
        for (auto v : vehicles)
            delete v;
    }
};

int main()
{
    VehicleManager service;

    // Cars
    service.addVehicle(new Car(1, "Toyota", 500, 5));
    service.addVehicle(new Car(2, "Honda", 550, 5));
    service.addVehicle(new Car(3, "Nissan", 480, 4));
    service.addVehicle(new Car(4, "BMW", 800, 5));
    service.addVehicle(new Car(5, "Audi", 850, 5));

    // Bikes
    service.addVehicle(new Bike(6, "Yamaha", 200, "Sports"));
    service.addVehicle(new Bike(7, "Suzuki", 180, "Normal"));
    service.addVehicle(new Bike(8, "Honda", 170, "Scooter"));
    int choice;
    while (true)
    {
        cout << "\n**** VEHICLE RENTAL SYSTEM ****\n";
        cout << "1. Show All Vehicles\n";
        cout << "2. Show Available Vehicles\n";
        cout << "3. Rent a Vehicle\n";
        cout << "4. Count Available Vehicles\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        if (choice == 0)
        {
            cout << "Exiting program... Goodbye!\n";
            break;
        }
        switch (choice)
        {
        case 1:
            service.displayVehicles();
            break;
        case 2:
            service.showAvailableVehicles();
            break;
        case 3:
        {
            int id, hours;
            cout << "Enter Vehicle ID: ";
            cin >> id;
            cout << "Enter hours: ";
            cin >> hours;
            Vehicle *v = service.findById(id);
            if (v && v->isAvailable())
            {
                cout << "Total Rent = " << v->calculateRent(hours) << " tk\n";
                v->rentVehicle();
                cout << "Vehicle rented successfully!\n";
            }
            else
            {
                cout << "Vehicle not available or invalid ID!\n";
            }
            break;
        }
        case 4:
            cout << "Available Vehicles = "
                 << service.countAvailableVehicles() << endl;
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    }
    return 0;
}