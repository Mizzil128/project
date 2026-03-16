#include "Header1.h"
#include "SQLiteEmployeerepo.h"
#include <exception>
#include <iostream>

//CRUD::Employee::Employee() {
	//std::cout << "\n[EMPLOYEE] loading data...\n";
//}

CRUD::Employee::~Employee() {
	std::cout << "\n[EMPLOYEE] Unloading data...\n";
}

const unsigned int CRUD::Employee::getID() const {
	return empID;
}

const char* CRUD::Employee::getName() const {
	return name;
}

const double CRUD::Employee::getSalary() const {
	return salary;
}

const std::string& CRUD::Employee::getDepartment() const {
	return department;
}

void CRUD::Employee::setID(const unsigned int id) {
	empID = id;
}

void CRUD::Employee::setName(const char* name_) {
	name = name_;
}

void CRUD::Employee::setDepartment(const std::string& dep_) {
	department = dep_;
}

void CRUD::Employee::setSalary(double sal_) {
	salary = sal_;
}

void CRUD::EmployeeRepository::create(const Employee& emp) {
	employees.push_back(emp);
}

CRUD::Employee CRUD::EmployeeRepository::getByID(unsigned int id) const {
	for (const auto& emp:employees)
		//use here if condtion to check if employee with given id exists in the repository and then call getByID method to retrieve employee details, else print employee not found message
		if (emp.getID() == id) {
			std::cout << "Employee ID:" << emp.getID() << "\t\t" <<emp.getName() << "\t\t" << emp.getDepartment() << "\t\t\t" << emp.getSalary() << std::endl;
			return emp;
		}
	throw std::runtime_error("Employee not found");      //for now return default employee object, later we can implement search logic to find employee by id in the employees vector and return it
}

std::vector<CRUD::Employee> CRUD::EmployeeRepository::getAll() const {

	std::cout << "\nEmpID\t\tName\t\tDepartment\t\tSalary\n";
	
		for (const auto& emp : employees) {
			std::cout << emp.getID() << "\t\t" << emp.getName() << "\t\t" << emp.getDepartment() << "\t\t" << emp.getSalary() << std::endl;
		}
	
		return employees;
}

CRUD::EmployeeServices::EmployeeServices() {
	std::cout << "\n[EMPLOYEE SERVICES] Initializing Employee Services...\n";
	repository = new EmployeeRepository();        //EmployeeServices creates its own instance of EmployeeRepository to manage employee data, demonstrating composition and encapsulation
	repository = new SQLiteEmployeeRepository("Employees.db");    // EmployeeServices can also use a different repository implementation (e.g., SQLiteEmployeeRepository) to manage employee data, demonstrating flexibility and the ability to switch between different data storage mechanisms without changing the EmployeeServices class, adhering to the Open/Closed Principle
}

CRUD::EmployeeServices::~EmployeeServices() {
	std::cout << "\n[EMPLOYEE SERVICES] Cleaning up Employee Services...\n";
	delete repository;        //EmployeeServices is responsible for cleaning up its own resources, ensuring proper memory management and preventing leaks
}

CRUD::EmployeeServices::EmployeeServices(IEmployeeRepository* repo) {
	std::cout << "\n[EMPLOYEE SERVICES] Initializing Employee Services with provided repository(Decpendency Injection)...\n";
	repository = repo;       //EmployeeServices can also accept an external repository instance, allowing for flexibility and dependency injection, which promotes loose coupling and easier testing
}

//CRUD::EmployeeServices::~EmployeeServices() {
//	std::cout << "\n[EMPLOYEE SERVICES] Cleaning up Employee Services...\n";
	 //No need to delete repository here since it's not owned by EmployeeServices when injected, demonstrating proper ownership semantics and avoiding double deletion issues
//}

void CRUD::EmployeeServices::addEmployee(Employee& emp) {
	repository->create(emp);
}

CRUD::Employee CRUD::EmployeeServices::getemp(unsigned int id) const {
	return repository->getByID(id);
}

void CRUD::Application::run() {

	bool isrunning = true;
	EmployeeRepository emprep;
	IEmployeeRepository* repo = &emprep;        //Interface pointer to EmployeeRepository object for abstraction and flexibility
	Employee emp_;
	EmployeeServices empserv;
	EmployeeServices empserv2(repo);        //EmployeeServices can also accept an external repository instance, allowing for flexibility and dependency injection, which promotes loose coupling and easier testing
	
	unsigned int id;
	char nameBuffer[100];
	std::string department;
	double salary;
	unsigned int choice;

	while (isrunning == true) {
		std::cout << "\n\t--------------CRUD OPERATIONS-------------\n";
		std::cout << "1.Create\n";
		std::cout << "2.View All\n";
		std::cout << "3.View/Search by ID\n";
		std::cout << "4.Update\n";
		std::cout << "5.Delete\n";

		std::cout << "\nEnter Choice(1-5):\n";
		if (!(std::cin >> choice)) {
			std::cin.clear();// clear the error state
			std::cin.ignore(1000, '\n'); // discard invalid input
			continue;
		}

		switch (choice) {
		case 1: {
			std::cout << "\nEnter Employee ID:";
			std::cin >> id;
			std::cin.ignore(100, '\n');   //clear new line from input buffer

			//Prompt user fro employee name
			std::cout << "\nEnter Employee Name:";
			std::cin.getline(nameBuffer, 100); //read employee name from user input
			
			std::cout << "\nEnter Employee department:";
			std::cin >> department;
			std::cin.ignore(1000, '\n');   //clear new line from input buffer
			
			std::cout << "\nEnter Employee salary:";
			std::cin >> salary;
			std::cin.ignore(1000, '\n');   //clear new line from input buffer
			
			emp_.setID(id);
			emp_.setName(nameBuffer);
			emp_.setDepartment(department);
			emp_.setSalary(salary);

			empserv.addEmployee(emp_);        //use EmployeeServices to add employee to repository, demonstrating separation of concerns and single responsibility principle
			std::cout << "\nEmployee created successfully\n";
			break;
			}
		case 2: {
			repo->getAll();
			break;
			}
		case 3: {
			//unsigned int id;
			std::cout << "\nEnter Employee ID to search:";
			std::cin >> id;
			std::cout << "\nID:" << id <<std::endl;
			//use here if condtion to check if employee with given id exists in the repository and then call getByID method to retrieve employee details, else print employee not found message
			try {
				emp_ = empserv.getemp(id);        //use EmployeeServices to get employee details by id, demonstrating separation of concerns and single responsibility principle
			}
			catch (...)
			{
				std::cerr << "\nEmployee not found\n";
			}
			break;
			}

		default:
			std::cout << "\nNothing for now\n";
			isrunning = false;
			break;
		}
	}
	return;
}