#include "Header1.h"
#include "SQLiteEmployeerepo.h"
#include "Employee.h"
#include "IEmloyeerepo.h" // Include the header file where EmployeeRepository is declared
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

CRUD::EmployeeServices::EmployeeServices() :ownedrepository(std::make_unique<SQLiteEmployeeRepository>("Employees.db")), repository(ownedrepository.get()) {
	std::cout << "\n[EMPLOYEE SERVICES] Initializing Employee Services...\n";
	//repository = new EmployeeRepository();        //EmployeeServices creates its own instance of EmployeeRepository to manage employee data, demonstrating composition and encapsulation
	//repository = new SQLiteEmployeeRepository("Employees.db");    // EmployeeServices can also use a different repository implementation (e.g., SQLiteEmployeeRepository) to manage employee data, demonstrating flexibility and the ability to switch between different data storage mechanisms without changing the EmployeeServices class, adhering to the Open/Closed Principle
}

/*
CRUD::EmployeeServices::~EmployeeServices() {
	std::cout << "\n[EMPLOYEE SERVICES] Cleaning up Employee Services...\n";
	delete repository;        //EmployeeServices is responsible for cleaning up its own resources, ensuring proper memory management and preventing leaks
}
*/

CRUD::EmployeeServices::EmployeeServices(IEmployeeRepository* repo, bool takeOwnership=false) {
	std::cout << "\n[EMPLOYEE SERVICES] Initializing Employee Services with provided repository(Decpendency Injection)...\n";
	if(takeOwnership) {
		ownedrepository.reset(repo);        //If EmployeeServices takes ownership of the provided repository, it will manage its lifetime and ensure proper cleanup when EmployeeServices is destroyed, demonstrating proper ownership semantics and resource management
	}else {
		repository = repo;        //If EmployeeServices does not take ownership of the provided repository, it will simply use the provided instance without managing its lifetime, allowing for greater flexibility and separation of concerns, as the caller is responsible for managing the repository's lifetime
	}
	//repository = repo;       //EmployeeServices can also accept an external repository instance, allowing for flexibility and dependency injection, which promotes loose coupling and easier testing
}

void CRUD::EmployeeServices::addEmployee(Employee& emp) {
	repository->create(emp);
}

CRUD::Employee CRUD::EmployeeServices::getemp(unsigned int id) const {
	return repository->getByID(id);
}