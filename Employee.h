#pragma once
#include <string>
#include <vector>

namespace CRUD{
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
}