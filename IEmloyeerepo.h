#pragma once
#include "vector"
#include "Employee.h"

namespace CRUD {
	//Interface class(Repository for database access and crud operations) 
	class IEmployeeRepository
	{
	public:
		//virtual IEmployeeRepository()=default;
		virtual ~IEmployeeRepository() = default;

		virtual void create(const Employee&) = 0;           // passing Employee objects by const reference to avoid unnecessary copies
		virtual Employee getByID(unsigned int id) const = 0;
		virtual std::vector<Employee> getAll() const = 0;
		//virtual void update(const Employee&)=0;
		//virtual void Delete(unsigned int id)=0;
	};
}