//#include "IEmloyeerepo.h"
#include "Employee.h"
#include "Header1.h"
#include "Application.h"
#include <string>
#include <iostream>

using namespace CRUD;

void Application::run() {

	bool isrunning = true;
	EmployeeRepository emprep;
	IEmployeeRepository* repo = &emprep;        //Interface pointer to EmployeeRepository object for abstraction and flexibility
	Employee emp_;
	EmployeeServices empserv;
	EmployeeServices empserv2(repo, false);        //EmployeeServices can also accept an external repository instance, allowing for flexibility and dependency injection, which promotes loose coupling and easier testing

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
			std::cout << "\nID:" << id << std::endl;
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