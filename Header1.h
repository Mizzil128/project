/*Who owns the memory ?
Who controls object lifetime ?
Who depends on whom ?
*/
#pragma once
#include "IEmloyeerepo.h" // Include the header file where IEmployeeRepository is declared
#include "Employee.h"
//#include <vector>
//#include <string>
//#include <memory>

//Layered CRUD system
namespace CRUD {
	//EmployeeRepository here's a data manager(collection manager for employees)
	//EmployeeRepository ? manages employee storage and retrieval.
	class EmployeeRepository : public IEmployeeRepository {       //Here inheritance IEmployeeRespository means "is a repository" 
		public:
			EmployeeRepository() = default;
			~EmployeeRepository() override = default;
		private:
			std::vector <Employee> employees;          //has a collection of Employee objects
		public:
			void create(const Employee&) override;       //override
			Employee getByID(unsigned int id) const override;          //override
			std::vector<Employee> getAll() const override;
			//void update(const Employee &emp) override;
			//void Delete(unsigned int id) override;

	};
}