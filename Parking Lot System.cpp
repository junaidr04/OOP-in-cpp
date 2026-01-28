#include<bits/stdc++.h>
using namespace std;
class Vehicle
{
protected:
    int id;
    string brand;
    double rentPerHr;
public:
    Vehicle(int id, string brand, double rent): id(id), brand(brand), rentPerHr(rent) {}
    int getId() const
    {
        return id;
    }
    double getRate() const
    {
        return rentPerHr;
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

//PARKING SLOT
class ParkingSlot
{
    int slotNumber;
    bool occupied;
    Vehicle* vehicle;
    int entryHour;
public:
    ParkingSlot(int num) : slotNumber(num), occupied(false), vehicle(nullptr), entryHour(0) {}
    bool isFree() const
    {
        return !occupied;
    }
    void park(Vehicle* v, int hour)
    {
        vehicle = v;
        occupied = true;
        entryHour = hour;
    }
    void removeVehicle(int exitHour)
    {
        int totalHours = exitHour - entryHour;
        if (totalHours <= 0)
            totalHours = 1;
        double bill = totalHours * vehicle->getRate();
        cout << "\n===== BILL DETAILS =====\n";
        cout << "Vehicle ID      : " << vehicle->getId() << endl;
        cout << "Parking Time    : " << totalHours << " hour(s)\n";
        cout << "Rate per Hour   : " << vehicle->getRate() << " tk\n";
        cout << "---------------------------\n";
        cout << "TOTAL AMOUNT    : " << bill << " tk\n";
        cout << "===========================\n\n";
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
        return nullptr;
    }
    void parkVehicle(Vehicle* v, const string& type, int entryHour)
    {
        auto slots = getSlots(type);
        if(!slots)
        {
            cout<<"Invalid type.\n";
            return;
        }
        for(auto &s : *slots)
        {
            if (s.isFree())
            {
                s.park(v, entryHour);
                cout<<type <<" parked in slot "<<s.getSlotNumber()<<".\n";
                return;
            }
        }
        cout<<"No free slot available for "<<type<<".\n";
    }
    void removeVehicle(Vehicle* v, const string& type, int exitHour)
    {
        auto slots = getSlots(type);
        if(!slots)
        {
            cout<<"Invalid type.\n";
            return;
        }
        for (auto &s : *slots)
        {
            if(s.getVehicle() == v)
            {
                s.removeVehicle(exitHour);
                return;
            }
        }
        cout<<"Vehicle not found in parking.\n";
    }
    void showSlotInfo(const string& type)
    {
        auto slots = getSlots(type);
        if(!slots)
        {
            cout<<"Invalid type.\n";
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
            int vid, hour;
            string type;
            cout << "Enter Vehicle ID: ";
            cin >> vid;
            cout << "Enter Vehicle Type: ";
            cin >> type;
            cout << "Enter Entry Hour (0-23): ";
            cin >> hour;
            Vehicle* v = vm.findById(vid);
            if (!v)
                cout<<"Vehicle ID not found!\n";
            else
                lot.parkVehicle(v, type, hour);
        }
        else if (choice == 2)
        {
            int vid, hour;
            string type;
            cout << "Enter Vehicle ID: ";
            cin >> vid;
            cout << "Enter Vehicle Type: ";
            cin >> type;
            cout << "Enter Exit Hour (0-23): ";
            cin >> hour;
            Vehicle* v = vm.findById(vid);
            if (!v)
                cout<<"Vehicle ID not found!\n";
            else
                lot.removeVehicle(v, type, hour);
        }
        else if (choice == 3)
        {
            string type;
            cout << "Enter vehicle type: ";
            cin >> type;
            lot.showSlotInfo(type);
        }
        else
            break;
    }
    return 0;
}
