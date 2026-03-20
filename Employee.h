#pragma once
#include <string>
//#include <vector>
#include <memory>

namespace CRUD{
	class IEmployeeRepository; // forward-declare to avoid circular include
	
	//Employee here's a data model(Employee ? holds employee data.)
	class Employee {
		public:
			Employee() = default;
			~Employee();
		private:
			unsigned int empID;
			std::string department;
			const char* name;
			double salary;
		public:
			const unsigned int getID() const;           //const to getters for ready-0nly methods
			const char* getName() const;
			const double getSalary() const;
			const std::string& getDepartment() const;
			void setID(const unsigned int id);
			void setName(const char*);        //no const at setters bcz value changes/write-0nly method
			void setDepartment(const std::string&);
			void setSalary(double);
	};

	class EmployeeServices {
		public:
			EmployeeServices();
			// Inject repository to share the same storage instance (no ownership).
			explicit EmployeeServices(IEmployeeRepository*, bool takeOwnership);
			~EmployeeServices() = default; //No need to delete repository here since it's not owned by EmployeeServices when injected, demonstrating proper ownership semantics and avoiding double deletion issues
		private:
			IEmployeeRepository* repository = nullptr;        //EmployeeServices depends on IEmployeeRepository for data management, demonstrating dependency inversion and separation of concerns, allowing EmployeeServices to focus on business logic while delegating data management to the repository
			std::unique_ptr<IEmployeeRepository> ownedrepository;

		public:
			void addEmployee(Employee&);
			Employee getemp(unsigned int id) const;
			void updateemp(Employee&);
			void Deleteemp(unsigned int);
	};
}