/*Who owns the memory ?
Who controls object lifetime ?
Who depends on whom ?
*/
#pragma once
#include "IEmloyeerepo.h"
#include "Employee.h"
#include <vector>
#include <string>

//Layered CRUD system
namespace CRUD {
	//EmployeeRepository here's a data manager(collection manager for employees)
	//EmployeeRepository ? manages employee storage and retrieval.
	class EmployeeRepository : public IEmployeeRepository {       //Here inheritance IEmployeeRespository means "is a repository" 
		public:
			EmployeeRepository()=default;
			~EmployeeRepository() override=default;
		private:
			std::vector <Employee> employees;          //has a collection of Employee objects
		public:
			void create(const Employee&) override;       //override
			Employee getByID(unsigned int id) const override;          //override
			std::vector<Employee> getAll() const override;
			//void update(const Employee &emp) override;
			//void Delete(unsigned int id) override;

	};

	class EmployeeServices {
		public:
			EmployeeServices();
			~EmployeeServices();
			// Inject repository to share the same storage instance (no ownership).
			explicit EmployeeServices(IEmployeeRepository*);
			//~EmployeeServices();
		private:
			IEmployeeRepository* repository;
		public:
			void addEmployee(Employee&);
			Employee getemp(unsigned int id) const;
			void updateemp(Employee&);
			void Deleteemp(unsigned int);
	};

	class Application {
		public:
			Application()=default;          //here =default means compiler generates constructor automatically 
			~Application()=default;
			void run();
			void displayMenu();
	};
}	