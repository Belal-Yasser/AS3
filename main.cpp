#include <string>
#include <iostream>
#include <queue>
using namespace std;

class Appointment {
public:
    int hours;
    int mins;
    Appointment() :hours(0), mins(0){};
    Appointment(int h, int m) : hours(h), mins(m){};
};

class Person {

private:
    string name;
    int id;
    int age;

public:
    Person() : name(""), id(0), age(0) {} //no args constructor
    
    Person(string n, int i, int a) : name(n), id(i), age(a) {}; //args constructor
    
    virtual ~Person() {}

    void setName(const string& n) {
        name = n;
    }

    void setId(int i) {
        id = i;
    }

    void setAge(int a) {
        age = a;
    }

    string getName() const {
        return name;
    }

    int getId() const {
        return id;
    }

    int getAge() const {
        return age;
    }

};

class Customer : public Person {

private:
    int mechanicId;
    Appointment appointment;

public:
    Customer() : mechanicId(0), appointment({ 0, 0 }) {}
    
    Customer(string n, int i, int a, int mid, Appointment appoint) : Person(n, a, i){
        this->mechanicId = mid;
        this->appointment.hours = appoint.hours;
        this->appointment.mins = appoint.mins;
    };

    void setMechanicId(int mechId) {
        mechanicId = mechId;
    }

    void setAppointment(const Appointment& appoint) {
        appointment = appoint;
    }

    int getMechanicId() const {
        return mechanicId;
    }

    Appointment getAppointment() const {
        return appointment;
    }

    bool operator<(const Customer& c) const {
        if (appointment.hours < c.appointment.hours) {
            return true;
        }
        else if (appointment.hours == c.appointment.hours) {
            return (appointment.mins < c.appointment.mins);
        }
        else
            return false;
    }

    bool operator>(const Customer& c) const {
       if (appointment.hours > c.appointment.hours) {
            return true;
        }
        else if (appointment.hours == c.appointment.hours) {
            return (appointment.mins > c.appointment.mins);
        }
        else
            return false;
    }

    bool operator==(const Customer& c ) const {
        return (appointment.hours == c.appointment.hours &&
            appointment.mins == c.appointment.mins);
    }
};

class Mechanic : public Person {

private:
    int counter;
    Appointment appointments[];

public:
    Mechanic() : counter(0) {}
    Mechanic(string name, int id, int age, int c) : Person(name, id, age){
        this->counter=c;
        
    }
    
    void setCounter(int counter) {
        counter = counter;
    }

    void setAppointments(const Appointment* appoint) {
        for (int i = 0; i < counter; ++i) {
            appointments[i] = appoint[i];
        }
    }

    int getCounter() const {
        return counter;
    }

    Appointment* getAppointments() {
        return appointments;
    }

    const Appointment* getAppointments() const {
        return appointments;
    }
    bool isAvailable(const Appointment& appointment) const {
        for (int i = 0; i < counter; ++i) {
            if (appointments[i].hours == appointment.hours && appointments[i].mins == appointment.mins) {
                // Mechanic is busy at the given appointment time
                return false;
            }
        }
        return true;
    }

};

template<typename T>
class Queue {

private:
    queue<T> queue;
public:
    Queue() {}

    void push(const T& v) {
        queue.push_back(v);
    }

    void pop() {
        queue.pop_front();
    }
    
    T top() {
        return queue.top();
    }

};

int main() {
    
    //Ahmed at 1:00, Sara at 4:00, Kareem at 3:00, Mohammed at 1:00
    //Ayman, Khaled, Mai
    Mechanic mechanicarray[3];
    Customer customerarray[4];
    
    for (int j = 0; j < 3; j++) {
        string name; int age, id;
        cout << "Enter name for the mechanic " << endl;
        cin >> name;
        cout << "Enter age for the mechanic " << endl;
        cin >> age;
        cout << "Enter ID for the mechanic " << endl;
        cin >> id;
        mechanicarray[j] = Mechanic(name, age, id, 0);
        
    }
    queue <Customer> customerQueue;
    
    for (int i = 0; i < 4; i++) {
        string name; int age, id, hours, mins;
        
        cout << "Enter name for the customer: " << endl;
        cin >> name;
        cout << "Enter age for the customer: " << endl;
        cin >> age;
        cout << "Enter ID for the customer: " << endl;
        cin >> id;
        cout << "Enter appointment time for the customer: " << endl;
        cin >> hours >> mins;
        Appointment a = Appointment(hours, mins);
        
        customerarray[i] = Customer(name, age, id, 0, a);
    }
    bool sorted = false;
    for(int i = 0; i < 2; i++){
        int change = 0;
        if((customerarray[i]) > (customerarray[i+1])){
            
            Customer temp = customerarray[i];
            customerarray[i] = customerarray[i+1];
            customerarray[i+1] = temp;
            change++;
        }
        if(change ==0){
            sorted = true;
            break;
        }
        
    }
    
    for(int i =0; i<3 ; i++){
        if (mechanicarray[i].isAvailable(customerarray[i].getAppointment())){
            cout << customerarray[i].getName() << " should be assigned to " << mechanicarray[i].getName() << endl;
        }
        else{
            cout << customerarray[i].getName() << " should be assigned to " << mechanicarray[i+1].getName() << endl;
        }
    
        }
    }


