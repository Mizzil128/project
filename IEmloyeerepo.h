#pragma once
//#include "Employee.h"
#include <vector>

namespace CRUD {
	class Employee;     //forward declaration to avoid cicular includes
	//Interface class(Repository for database access and crud operations) 
	class IEmployeeRepository
	{
	public:
		//virtual IEmployeeRepository()=default;
		virtual ~IEmployeeRepository() = default;

		virtual void create(const Employee&) = 0;           //pure virtual function for creating an employee record in the repository, to be implemented by concrete repository classes 
		virtual Employee getByID(unsigned int id) const = 0;
		virtual std::vector<Employee>getAll() const = 0;
		//virtual void update(const Employee&)=0;
		//virtual void Delete(unsigned int id)=0;
	};
}