#include<bits/stdc++.h>
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
    int getId() const
    {
        return id;
    }
    bool isAvailable() const
    {
        return avail;
    }
    double calRent(int hours) const
    {
        return rentPerHr * hours;
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
class Car : public Vehicle
{
public:
    Car(int id, string brand, double rent) : Vehicle(id, brand, rent) {}
};
class Bike : public Vehicle
{
public:
    Bike(int id, string brand, double rent) : Vehicle(id, brand, rent) {}
};
class Bus : public Vehicle
{
public:
    Bus(int id, string brand, double rent) : Vehicle(id, brand, rent) {}
};
class Truck : public Vehicle
{
public:
    Truck(int id, string brand, double rent) : Vehicle(id, brand, rent) {}
};

//VEHICLE MANAGER
class VehicleManager
{
    vector<Vehicle*> vehicles;
public:
    void addVehicle(Vehicle* v)
    {
        vehicles.push_back(v);
    }
    Vehicle* findById(int id)
    {
        for (auto v : vehicles)
            if (v->getId() == id)
                return v;
        return nullptr;
    }
    ~VehicleManager()
    {
        for (auto v : vehicles)
            delete v;
    }
};

//PARKING LOT
class ParkingSlot
{
    int slotNumber;
    bool occupied;
    Vehicle* vehicle;
public:
    ParkingSlot(int num) : slotNumber(num), occupied(false), vehicle(nullptr) {}
    bool isFree() const
    {
        return !occupied;
    }
    void park(Vehicle* v)
    {
        vehicle = v;
        occupied = true;
        v->rentVehicle();
    }
    void removeVehicle()
    {
        if(vehicle)
            vehicle->returnVehicle();
        vehicle = nullptr;
        occupied = false;
    }
    Vehicle* getVehicle() const
    {
        return vehicle;
    }
    int getSlotNumber() const
    {
        return slotNumber;
    }
};

//PARKING LOT
class ParkingLot
{
    vector<ParkingSlot> carSlots, bikeSlots, busSlots, truckSlots;
public:
    ParkingLot()
    {
        for(int i=1; i<=10; i++)
        {
            carSlots.push_back(ParkingSlot(i));
            bikeSlots.push_back(ParkingSlot(i));
            busSlots.push_back(ParkingSlot(i));
            truckSlots.push_back(ParkingSlot(i));
        }
    }
    vector<ParkingSlot>* getSlots(const string& type)
    {
        if (type == "car")
            return &carSlots;
        else if (type == "bike")
            return &bikeSlots;
        else if (type == "bus")
            return &busSlots;
        else if (type == "truck")
            return &truckSlots;
        else
            return nullptr;
    }
    void parkVehicle(Vehicle* v, const string& type)
    {
        auto slots = getSlots(type);
        if(!slots)
        {
            cout<<"Invalid type."<<endl;
            return;
        }
        for(auto &s : *slots)
        {
            if (s.isFree())
            {
                s.park(v);
                cout<<type <<" parked in slot "<<s.getSlotNumber()<<"."<<endl;
                return;
            }
        }
        cout<<"No free slot available for "<<type<<"."<<endl;
    }
    void removeVehicle(Vehicle* v, const string& type)
    {
        auto slots = getSlots(type);
        if(!slots)
        {
            cout<<"Invalid type."<<endl;
            return;
        }
        for (auto &s : *slots)
        {
            if(s.getVehicle() == v)
            {
                s.removeVehicle();
                cout<<type<<" removed from parking."<<endl;
                return;
            }
        }
        cout<<"Vehicle not found in parking."<<endl;
    }
    void showSlotInfo(const string& type)
    {
        auto slots = getSlots(type);
        if(!slots)
        {
            cout<<"Invalid type."<<endl;
            return;
        }
        int total = slots->size(), freeCount = 0;
        for (auto &s : *slots)
            if (s.isFree())
                freeCount++;
        cout<<type<<" slots: Total = "<<total<<", Free = "<<freeCount<<", Occupied = "<<total - freeCount<<endl;
    }
};
int main()
{
    VehicleManager vm;
    ParkingLot lot;
    vm.addVehicle(new Car(1, "Toyota", 50));
    vm.addVehicle(new Car(2, "Honda", 40));
    vm.addVehicle(new Bike(3, "Yamaha", 20));
    vm.addVehicle(new Bus(4, "Volvo", 100));
    vm.addVehicle(new Truck(5, "Tata", 120));
    int choice;
    while (true)
    {
        cout << "\n**** PARKING MENU ****\n";
        cout << "1. Park a vehicle"<<endl;
        cout << "2. Remove a vehicle"<<endl;
        cout << "3. Show slot info"<<endl;
        cout << "4. Exit"<<endl;
        cout << "Choice: ";
        cin >> choice;
        if (choice == 1)
        {
            int vid, hours;
            string type;
            cout << "Enter Vehicle ID: ";
            cin >> vid;
            cout << "Enter Vehicle Type (car/bike/bus/truck): ";
            cin >> type;
            cout << "Enter hours to rent: ";
            cin >> hours;
            Vehicle* v = vm.findById(vid);
            if (!v)
                cout<<"Vehicle ID not found!"<<endl;
            else if (!v->isAvailable())
                cout<<"Vehicle already rented!"<<endl;
            else
            {
                lot.parkVehicle(v, type);
                cout << "You need to pay: $" << v->calRent(hours) << "\n";
            }
        }
        else if (choice == 2)
        {
            int vid;
            string type;
            cout << "Enter Vehicle ID to remove: ";
            cin >> vid;
            cout << "Enter Vehicle Type: ";
            cin >> type;
            Vehicle* v = vm.findById(vid);
            if (!v)
                cout<<"Vehicle ID not found!"<<endl;
            else
                lot.removeVehicle(v, type);
        }
        else if (choice == 3)
        {
            string type;
            cout << "Enter vehicle type: ";
            cin >> type;
            lot.showSlotInfo(type);
        }
        else if(choice == 4)
        {
            cout<<"Thank you! Program ended."<<endl;
            break;
        }
    }
    return 0;
}
