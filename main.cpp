#include <bits/stdc++.h>
#define ll long long
#define f(n1,n2) for(int i=n1;i<n2;i++)
#define pb push_back
using namespace std;
class Customer_database{
    public:
        int cust_id;
        string name;
        string password;
        vector<pair<int,string>> rented_cars;
        int fine_due;
        int cust_record;
        Customer_database(){};
        Customer_database(int cust_id1,string name1,string password1,int fine_due1,int cust_record1);
};
Customer_database:: Customer_database(int cust_id1,string name1,string password1,int fine_due1,int cust_record1){
cust_id=cust_id1;
name=name1;
password=password1;
fine_due=fine_due1;
cust_record=cust_record1;
}
class Employee_database{
    public:
        int empl_id;
        string name;
        string password;
        vector<pair<int,string>> rented_cars;
        float fine_due;
        int empl_record;
        Employee_database(){};
        Employee_database(int empl_id1,string name1,string password1,int fine_due1,int empl_record1);
};
Employee_database:: Employee_database(int empl_id1,string name1,string password1,int fine_due1,int empl_record1){
empl_id=empl_id1;
name=name1;
password=password1;
fine_due=fine_due1;
empl_record=empl_record1;
}
class Car_database{
    public:
        int car_id;
        string name;
        int rent_per_day;
        bool available;
        string model;
        Car_database(){};
};
vector<Customer_database> customers;
vector<Car_database> cars;
vector<Employee_database> employees;
int num_days(string date1,string date2){
            int num;
            int day1=stoi(date1.substr(0,2));
            int day2=stoi(date2.substr(0,2));
            int month1=stoi(date1.substr(2,4));
            int month2=stoi(date2.substr(2,4));
            int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            int num1=0,num2=0;
            f(0,month1) num1+=daysInMonth[i];
            f(0,month2) num2+=daysInMonth[i];
            num1+=day1;
            num2+=day2;
            num=num2-num1;
            return num;
        }
int calc(int record){
            int max_cars=record/5;
            if(max_cars==0) max_cars=1;
            return max_cars;
        }
class Customer_functions:public Customer_database, public Car_database{
    private:
        int id;
        void view_cars(){
            cout<<"Car id\tName\tModel\tRent Per Day\tAvailable\n";
            f(0,cars.size()){
                string s;
                s=cars[i].available?"true":"false";
                cout<<cars[i].car_id<<"\t"<<cars[i].name<<"\t"<<cars[i].model<<"\t"<<cars[i].rent_per_day<<"\t"<<s<<"\n";
            }
            navigate();
        }
        void view_records(){
            int choice;
            cout<<"Enter your choice, Press:-\n";
            cout<<"1 : For viewing your rented cars"<<"\n";
            cout<<"2 : To know your record and maximum number of cars rentable"<<"\n";
            cout<<"3 : To know your due fine\n";
            cout<<"Any other key to  go back\n";
            cin>>choice;
            if(choice==1){
                if(customers[id].rented_cars.size()==0){
                    cout<<"--------------No cars rented right now--------------\n";
                    return navigate();
                }
                cout<<"Car id\t"<<"Name\t"<<"Model\t"<<"Return Date"<<"\n";
                f(0,customers[id].rented_cars.size()){
                    int j=customers[id].rented_cars[i].first;
                    cout<<cars[j].car_id<<"\t"<<cars[j].name<<"\t"<<cars[j].model<<"\t"<<customers[id].rented_cars[i].second<<"\n";
                }
            }
            else if(choice==2){
                cout<<"Your customer record value is : "<<customers[id].cust_record<<"\n";
                int max_num_cars=0;
                max_num_cars=calc(customers[id].cust_record);
                cout<<"Maximum number of cars you can rent at a time : "<<max_num_cars<<"\n";
            }
            else if(choice==3){
                cout<<"Your due fine is : Rs "<<customers[id].fine_due<<"\n";
            }
            navigate();
        }
        void rent_car(){
            int max_num_cars=calc(customers[id].cust_record);
            cout<<"--------------Checking your record--------------\n\n";
            if(max_num_cars<=customers[id].rented_cars.size()){
                cout<<"You have reached your limit of renting cars. Return a car or try to improve your record in order to rent more cars at the same time.\n";
                return navigate();
            }
            cout<<"You can rent a car!, please go ahead and enter the ID of the car you want to rent:\n";
            int car_id;
            cin>>car_id;
                if(car_id<cars.size()){
                    if(cars[car_id].available==true){
                        string date;
                        cout<<"Enter the date when you plan to return this car in ddmm format :"<<"\n";
                        cin>>date;
                        if(date.size()!=4 || stoi(date.substr(0,2))>31 || stoi(date.substr(2,4))>12){
                            cout<<"Enter a valid date in the specified ddmm format :"<<"\n";
                            cin>>date;
                            if(date.size()!=4 || stoi(date.substr(0,2))>31 || stoi(date.substr(2,4))>12){
                            cout<<"--------------Too many wrong attempts--------------"<<"\n";
                            return navigate();
                        }
                        }
                        int num_of_days=num_days("0403",date);
                        if(num_of_days<=0 || num_of_days>12){
                            cout<<"--------------Invalid date entered--------------\n";
                            return navigate();
                        }
                        cout<<"Total amount payable : Rs "<<cars[car_id].rent_per_day*num_of_days<<"\n";
                        cars[car_id].available=false;
                        (customers[id].rented_cars).pb({car_id,date});
                        customers[id].fine_due+=cars[car_id].rent_per_day*num_of_days;
                        cout<<"Return date is "<<date.substr(0,2)<<"/"<<date.substr(2,4)<<"\n";
                        cout<<"--------------"<<cars[car_id].name<<" has been rented successfully--------------\n";
                    }
                    else cout<<"--------------The car id entered is not available right now--------------\n";
                }
                else cout<<"--------------Invalid car id entered--------------\n";
            navigate();
        }
    public:
        int get_id(){
            cout<<"Enter your cust_id:\n";
            cin>>id;
            if(id<customers.size()&&id>=0){
                cout<<"--------------Welcome "<<customers[id].name<<"--------------\n";
                return 1;
            }
            else{
                cout<<"--------------Invalid customer id entered--------------\n";
                return 0;
            }
        }
        int verify(){
            string password;
            cout<<"Enter your password:\n";
            cin>>password;
            if(password==customers[id].password) return 1;
            cout<<"--------------Wrong password entered--------------\n";
            return 0;
        }
        void navigate(){
            cout<<"What would you like to do:\n";
            cout<<"1 : View the cars in our store\n";
            cout<<"2 : View your personal records and profile\n";
            cout<<"3 : Rent a car\n";
            cout<<"Any other key to exit\n";
            int ch1;
            cin>>ch1;
            if(ch1==1) view_cars();
            else if(ch1==2) view_records();
            else if(ch1==3) rent_car();
            else return;
        }
};
class Employee_functions:public Employee_database, public Car_database{
    private:
        int id;
        void view_cars(){
            cout<<"Car id\tName\tModel\tRent Per Day\tAvailable\n";
            f(0,cars.size()){
                string s;
                s=cars[i].available?"true":"false";
                cout<<cars[i].car_id<<"\t"<<cars[i].name<<"\t"<<cars[i].model<<"\t"<<cars[i].rent_per_day<<"\t"<<s<<"\n";
            }
            navigate();
        }
        void view_records(){
            int choice;
            cout<<"Enter your choice, Press:-\n";
            cout<<"1 : For viewing your rented cars"<<"\n";
            cout<<"2 : To know your record and maximum number of cars rentable"<<"\n";
            cout<<"3 : To know your due fine\n";
            cout<<"Any other key to go back\n";
            cin>>choice;
            if(choice==1){
                if(employees[id].rented_cars.size()==0){
                    cout<<"--------------No cars rented right now--------------\n";
                    return navigate();
                }
                cout<<"Car id\t"<<"Name\t"<<"Model\t"<<"Return Date"<<"\n";
                f(0,employees[id].rented_cars.size()){
                    int j=employees[id].rented_cars[i].first;
                    cout<<cars[j].car_id<<"\t"<<cars[j].name<<"\t"<<cars[j].model<<"\t"<<employees[id].rented_cars[i].second<<"\n";
                }
            }
           else if(choice==2){
                cout<<"Your employee record value is : "<<employees[id].empl_record<<"\n";
                int max_num_cars=0;
                max_num_cars=calc(employees[id].empl_record);
                cout<<"Maximum number of cars you can rent at a time is "<<max_num_cars<<"\n";
            }
            else if(choice==3){
                cout<<"Your due fine is : Rs "<<employees[id].fine_due<<"\n";
            }
            navigate();
        }
        void rent_car(){
            int max_num_cars=calc(employees[id].empl_record);
            if(max_num_cars<=employees[id].rented_cars.size()){
                cout<<"You have reached your limit of renting cars. Return a car or try to improve your record in order to rent more cars at the same time.\n";
                return navigate();
            }
            cout<<"--------------Checking your record--------------\n\n";
            cout<<"You can rent a car!, please go ahead and enter the ID of the car you want to rent:-\n";
            int car_id;
            cin>>car_id;
            f(0,cars.size()){
                if(cars[i].car_id==car_id){
                    if(cars[i].available==true){
                        string date;
                        cout<<"Enter the date when you plan to return this car in ddmm format :"<<"\n";
                        cin>>date;
                        if(date.size()!=4 || stoi(date.substr(0,2))>31 || stoi(date.substr(2,4))>12){
                            cout<<"Enter a valid date in the specified ddmm format :"<<"\n";
                            cin>>date;
                            if(date.size()!=4 || stoi(date.substr(0,2))>31 || stoi(date.substr(2,4))>12){
                            cout<<"--------------Too many wrong attempts--------------\n";
                            return navigate();
                        }
                    }
                        int num_of_days=num_days("0403",date);
                        if(num_of_days<=0 || num_of_days>12){
                            cout<<"--------------Invalid date entered--------------\n";
                            return navigate();
                        }
                        cout<<"Total amount payable : Rs "<<cars[i].rent_per_day*num_of_days*0.85<<"\n";
                        cars[i].available=false;
                        (employees[id].rented_cars).pb({car_id,date});
                        employees[id].fine_due+=cars[i].rent_per_day*num_of_days*0.85;
                        cout<<"Return date is "<<date.substr(0,2)<<"/"<<date.substr(2,4)<<"\n";
                        cout<<"--------------"<<cars[i].name<<" has been rented successfully--------------\n";
                    }
                    else cout<<"--------------The car id entered is not available right now--------------\n";
                    break;
                }
            }
            navigate();
        }
    public:
       int get_id(){
            cout<<"Enter your empl_id:\n";
            cin>>id;
            if(id<employees.size()&&id>=0){
                cout<<"--------------"<<"Welcome "<<employees[id].name<<"--------------\n";
                return 1;
            }
            else{
                cout<<"--------------Invalid employee id entered--------------\n";
                return 0;
            }
        }
        int verify(){
            string password;
            cout<<"Enter your password:\n";
            cin>>password;
            if(password==employees[id].password) return 1;
            cout<<"--------------Wrong password entered--------------\n";
            return 0;
        }
        void navigate(){
            cout<<"What would you like to do:\n";
            cout<<"1 : View the cars in our store\n";
            cout<<"2 : View your personal records and profile\n";
            cout<<"3 : Rent a car\n";
            cout<<"Any other key to exit\n";
            int ch1;
            cin>>ch1;
            if(ch1==1) view_cars();
            else if(ch1==2) view_records();
            else if(ch1==3) rent_car();
            else return;
        }
};
class Manager_functions: public Customer_database,public Employee_database,public Car_database{
    public:
    int verify(){
        cout<<"Enter the manager's code : \n";
        cin>>managers_code;
        if(managers_code==148235) return 1;
        return 0;
    }
    Manager_functions():Customer_database(),Employee_database(),Car_database(){};
    void navigate(){
        cout<<"What would you like to do:\n";
        cout<<"1 : To manage customers' database\n2 : To manage employees' database\n3 : To manage cars' database\nAny other key to exit\n";
        int ch;
        cin>>ch;
        if(ch==1){
            int ch1;
            cout<<"1 : To add a new customer\n2 : To delete a customer's data\n3 : To update details of a customer\nAny other key to exit\n";
            cin>>ch1;
            if(ch1==1) add_cust();
            else if(ch1==2) delete_cust();
            else if(ch1==3) update_cust();
        }
        else if(ch==2){
            int ch1;
            cout<<"1 : To add a new employee\n2 : To delete a employee's data\n3 : To update details of an employee\nAny other key to exit\n";
            cin>>ch1;
            if(ch1==1) add_empl();
            else if(ch1==2) delete_empl();
            else if(ch1==3) update_empl();
        }
        else if(ch==3){
            int ch1;
            cout<<"1 : View all cars' details\n2 : To add a new car\n3 : To delete a car's data\n4 : To update details of a car\nAny other key to exit\n";
            cin>>ch1;
            if(ch1==1) view_cars();
            if(ch1==2) add_car();
            else if(ch1==3) delete_car();
            else if(ch1==4) update_car();
        }
    }
    private:
    int managers_code;
    void add_cust(){
        string name;
        string password;
        cout<<"Enter the name of the new customer to be added\n";
        cin>>name;
        cout<<"Enter the password of the new customer profile to be added\n";
        cin>>password;
        Customer_database new_cust(customers.size(),name,password,0,10);
        new_cust.rented_cars={};
        customers.pb(new_cust);
        cout<<"--------------The new customer profile has been created successfully--------------\n";
        navigate();
    }
    void delete_cust(){
        int id;
        cout<<"Enter the ID of the customer, whose profile has to be deleted\n";
        cin>>id;
        int j=-1;
        for(int i=0;i<customers.size();i++){
            if(customers[i].cust_id==id){
                j=i;
                break;
            }
        }
        if(j==-1){
            cout<<"--------------No customer exists with the entered ID--------------\n";
            return navigate();
        }
        if(customers[j].rented_cars.size()==0){
            cout<<"--------------This customer has rented cars curently, please wait untill all cars are returned--------------\n";
            return navigate();
        }
        customers.erase(customers.begin()+j);
        cout<<"--------------The customer profile has been deleted successfully--------------\n";
        navigate();
    }
    void update_cust(){
        int id;
        cout<<"Enter the ID of the customer, whose profile has to be updated\n";
        cin>>id;
        int j=-1;
        for(int i=0;i<customers.size();i++){
            if(customers[i].cust_id==id){
                j=i;
                break;
            }
        }
        if(j==-1){
            cout<<"--------------No customer exists with the entered ID--------------\n";
            return navigate();
        }
        int ch;
        cout<<"Enter a choice:-"<<"\n";
        cout<<"1 : password\n2 : execute return of a car\n3 : Name\nAny other key to go back\n";
        cin>>ch;
        if(ch==1){
            string password;
            cout<<"Enter the new password\n";
            cin>>password;
            customers[id].password=password;
            cout<<"--------------Password changed successfully--------------\n";
        }
        else if(ch==2){
            int car_id;
            cout<<"Enter the ID of the car returned:\n";
            cin>>car_id;
            int j=-1;
            f(0,customers[id].rented_cars.size()){
                if(customers[id].rented_cars[i].first==car_id){
                    j=i;
                    break;
                }
            }
            if(j==-1){
                cout<<"--------------The entered car id was not rented by this customer--------------\n";
                return navigate();
            }
            int fine_per_day=500;
            int amount_paid;
            string date_when_returned;
            int condition_rating;
            cout<<"Enter the date when it was returned:\n";
            cin>>date_when_returned;
            cout<<"Rate the condition of the car returned on a scale of 1 to 10:\n";
            cin>>condition_rating;
            cout<<"Enter the amount paid on return\n";
            cin>>amount_paid;
            int change=0;
            int m=num_days(customers[id].rented_cars[j].second,date_when_returned);
            customers[id].fine_due+=m>0?m*fine_per_day:0;
            customers[id].fine_due-=amount_paid;
            change+=m>0?(-5*m):10;
            change+=condition_rating>6?condition_rating:(condition_rating-7);
            customers[id].cust_record+=change;
            cars[customers[id].rented_cars[j].first].available=true;
            customers[id].rented_cars.erase(customers[id].rented_cars.begin()+j);
            cout<<"--------------The car return has been executed successfully and records have been updated--------------\n";
        }
        else if(ch==3){
            string name;
            cout<<"Enter the name to be set\n";
            cin>>name;
            customers[id].name=name;
            cout<<"--------------Customer name updated successfully--------------\n";
        }
        else return navigate();
        navigate();
    }
     void add_empl(){
        string password;
        string name;
        cout<<"Enter the name of the new employee to be added\n";
        cin>>name;
        cout<<"Enter the password of the new employee profile to be added\n";
        cin>>password;
        Employee_database new_empl(employees.size(),name,password,0,15);
        new_empl.rented_cars={};
        employees.pb(new_empl);
        cout<<"--------------The new employee has been successfully added--------------\n";
        navigate();
    }
    void delete_empl(){
        int id;
        cout<<"Enter the ID of the employee, whose profile has to be deleted\n";
        cin>>id;
        int j=-1;
        for(int i=0;i<employees.size();i++){
            if(employees[i].empl_id==id){
                j=i;
                break;
            }
        }
        if(j==-1){
            cout<<"--------------No employee exists with the entered ID--------------\n";
            return navigate();
        }
        if(employees[j].rented_cars.size()==0){
            cout<<"--------------This employee has rented cars curently, please wait untill all cars are returned--------------\n";
            return navigate();
        }
        employees.erase(employees.begin()+j);
        cout<<"--------------The employee profile has been deleted successfully--------------\n";
        navigate();
    }
    void update_empl(){
        int id;
        cout<<"Enter the ID of the employee, whose profile needs to be updated : \n";
        cin>>id;
        int j=-1;
        for(int i=0;i<employees.size();i++){
            if(employees[i].empl_id==id){
                j=i;
                break;
            }
        }
        if(j==-1){
            cout<<"--------------No employee exists with the entered ID--------------\n";
            return navigate();
        }
        int ch;
        cout<<"Enter a choice:-\n";
        cout<<"1 : password\n2 : rexecute return of a car\n3 : name\nAny other key to go back\n";
        cin>>ch;
        if(ch==1){
            string password;
            cout<<"Enter the new password\n";
            cin>>password;
            employees[id].password=password;
            cout<<"--------------Password changed successfully--------------\n"; 
        }
        else if(ch==2){
            int car_id;
            cout<<"Enter the ID of the car returned:\n";
            cin>>car_id;
            int j=-1;
            f(0,employees[id].rented_cars.size()){
                if(employees[id].rented_cars[i].first==car_id){
                    j=i;
                    break;
                }
            }
            if(j==-1){
                cout<<"--------------The entered car id was not rented by this employee--------------\n";
                return navigate();
            }
            int fine_per_day=500;
            int amount_paid;
            string date_when_returned;
            int condition_rating;
            cout<<"Enter the date when it was returned:\n";
            cin>>date_when_returned;
            cout<<"Rate the condition of the car returned on a scale of 1 to 10:\n";
            cin>>condition_rating;
            cout<<"Enter the amount paid on return\n";
            cin>>amount_paid;
            int change=0;
            int m=num_days(employees[id].rented_cars[j].second,date_when_returned);
            employees[id].fine_due+=m>0?m*fine_per_day:0;
            employees[id].fine_due-=amount_paid;
            change+=m>0?(-5*m):10;
            change+=condition_rating>6?condition_rating:(condition_rating-7);
            employees[id].empl_record+=change;
            cars[employees[id].rented_cars[j].first].available=true;
            employees[id].rented_cars.erase(employees[id].rented_cars.begin()+j);
            cout<<"--------------The car return has been executed successfully and records have been updated--------------\n";
        }
        else if(ch==3){
            string name;
            cout<<"Enter the name to be set\n";
            cin>>name;
            employees[id].name=name;
            cout<<"--------------Employee name updated successfully--------------\n";
        }
        else return navigate();
        navigate();
    }
    void view_cars(){
            cout<<"Car id\tName\tModel\tRent Per Day\tAvailable\n";
            f(0,cars.size()){
                string s;
                s=cars[i].available?"true":"false";
                cout<<cars[i].car_id<<"\t"<<cars[i].name<<"\t"<<cars[i].model<<"\t"<<cars[i].rent_per_day<<"\t"<<s<<"\n";
            }
            navigate();
        }
    void add_car(){
        int car_id;
        string name;
        int rent_per_day;
        bool available;
        string model;
        car_id=cars.size();
        cout<<"Enter the name of the car:-\n";
        cin>>name;
        cout<<"Enter the model name of the car:-\n";
        cin>>model;
        cout<<"Enter the rent per day for the car:-\n";
        cin>>rent_per_day;
        cout<<"Enter the availablity status of the car(1 for true or 0 for false):-\n";
        cin>>available;
        Car_database new_car;
        new_car.car_id=car_id;
        new_car.name=name;
        new_car.rent_per_day=rent_per_day;
        new_car.available=available;
        new_car.model=model;
        cars.pb(new_car);
        cout<<"--------------The new car, "<<name<<" has been successfully added to the database:)--------------\n";
        navigate();
    }
    void delete_car(){
        int car_id;
        cout<<"Enter the id of the car you want to delete\n";
        cin>>car_id;
        int j=-1;
        f(0,cars.size()){
            if(cars[i].car_id==car_id){
                j=i;
                break;
            }
        }
        if(j==-1){
            cout<<"--------------The entered car id does not exist--------------\n";
            return navigate();
        }
        if(cars[j].available==0){
            cout<<"--------------This car is currently rented, please wait for it to be returned before deleting--------------\n";
            return navigate();
        }
        cars.erase(cars.begin()+j);
        cout<<"--------------The specified car's data has been deleted--------------\n";
        navigate();
    }
    void update_car(){
        int car_id;
        cout<<"Enter the ID of the car, that you want to update\n";
        cin>>car_id;
        int j=-1;
        f(0,cars.size()){
            if(cars[i].car_id==car_id){
                j=i;
                break;
            }
        }
        if(j==-1){
            cout<<"--------------The entered car id does not exist--------------\n";
            return navigate();
        }
        int ch;
        cout<<"What would you like to update:-\n";
        cout<<"1 : Name\n2 : Model\n3 : rent per day\n4 : availability status\nAny other key to go back\n";
        cin>>ch;
        if(ch==1){
            cout<<"Enter the new name to be updated without spaces:-\n";
            string name;
            cin>>name;
            cars[j].name=name;
            cout<<"--------------The name has been updated--------------\n";
        }
        else if(ch==2){
            cout<<"Enter the new model name to be updated without spaces:-\n";
            string model;
            cin>>model;
            cars[j].model=model;
            cout<<"--------------The model name has been updated--------------\n";
        }
        else if(ch==3){
            cout<<"Enter the new value for rent per day:-\n";
            int rent_per_day;
            cin>>rent_per_day;
            cars[j].rent_per_day=rent_per_day;
            cout<<"--------------The rent per day has been updated--------------\n";
        }
        else if(ch==4){
            cout<<"Enter the new availability status(1 for true or 0 for false):-\n";
            int available;
            cin>>available;
            if(available!=0 && available!=1){
                cout<<"--------------Invalid availability entered--------------\n";
                return navigate();
            }
            cars[j].available=available;
            cout<<"--------------The availability status has been changed--------------\n";
        }
        navigate();
    }
};
int main(){
    f(0,10){
        Customer_database customer(i,"Customer"+to_string(i),"password"+to_string(i),500+10*i,10);
        customer.rented_cars={};
        if(i>5 && i%2==0) customer.rented_cars.pb({i,"0"+to_string(i+1)+"03"});
        if(i==6) customer.cust_record=2;
        customers.pb(customer);
    }
    f(0,10){
        Employee_database employee(i,"Employee"+to_string(i),"password"+to_string(i),300+10*i,15);
        employee.rented_cars={};
        if(i<5 && i%2!=0) employee.rented_cars.pb({i,"0"+to_string(i+1)+"03"});
        if(i==1) employee.empl_record=2;
        employees.pb(employee);
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(1,10);
    for (int i=0;i<10;++i) {
        Car_database car;
        car.car_id=i;
        switch (i) {
            case 0: car.name = "Toyota Camry"; car.available = true; break;
            case 1: car.name = "Honda Accord"; car.available = false; break;
            case 2: car.name = "Ford Mustang"; car.available = true; break;
            case 3: car.name = "Chevrolet"; car.available = false; break;
            case 4: car.name = "BMW 3 Series"; car.available = true; break;
            case 5: car.name = "Mercedes"; car.available = true; break;
            case 6: car.name = "Audi A4\t"; car.available = false; break;
            case 7: car.name = "Nissan Altima"; car.available = true; break;
            case 8: car.name = "Kia Optima"; car.available = false; break;
            case 9: car.name = "Hyundai Sonata"; car.available = true; break;
            default: car.name = "Unknown Car";
        }
        car.rent_per_day = 400 + ((i%2+1)*i*40)-((i%2)*i*15);
        car.model = "Model" + to_string(distribution(gen));
        cars.pb(car);
    }
    cout<<"--------------Welcome to Car Rental System :)--------------\n\n";
    cout<<"Please enter your designation:\n1 : Manager\n2 : Customer\n3 : Employee\n";
    int des;
    cin>>des;
    if(des==1){
        Manager_functions man;
        if(man.verify()==1) cout<<"--------------Welcome dear Manager--------------\n";
        else{
            cout<<"--------------Wrong manager's code entered--------------\n";
            return 0;
        }
        man.navigate();
    }
    else if(des==2){
        Customer_functions cus;
        int chh;
        cout<<"1 : Create a new profile\n2 : Login to your account\n";
        cin>>chh;
        if(chh==1){
        string name;
        string password;
        cout<<"Enter your first name\n";
        cin>>name;
        cout<<"Create a password\n";
        cin>>password;
        Customer_database new_cust(customers.size(),name,password,0,10);
        new_cust.rented_cars={};
        customers.pb(new_cust);
        cout<<"--------------Your profile has been created successfully--------------\n\n";
        cout<<"Your cust_id is : "<<customers.size()-1;
        cout<<"\nPlease login with the provided details\n\n";
        }
        if(cus.get_id()==0) return 0;
        if(cus.verify()==0) return 0;
        cus.navigate();
    }
    else if(des==3){
        Employee_functions emp;
        int chh;
        cout<<"1 : Create a new profile\n2 : Login to your account\n";
        cin>>chh;
        if(chh==1){
        string name;
        string password;
        cout<<"Enter your first name\n";
        cin>>name;
        cout<<"Create a password\n";
        cin>>password;
        Employee_database new_empl(employees.size(),name,password,0,10);
        new_empl.rented_cars={};
        employees.pb(new_empl);
        cout<<"--------------Your profile has been created successfully--------------\n\n";
        cout<<"Your empl_id is : "<<employees.size()-1;
        cout<<"\nPlease login with the provided details\n\n";
        }
        if(emp.get_id()==0) return 0;
        if(emp.verify()==0) return 0;
        emp.navigate();
}
else cout<<"--------------Invalid designation entered--------------\n";
}
