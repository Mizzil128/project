#pragma once
#include "IEmloyeerepo.h"
#include "Employee.h"
#include <string>
#include <sqlite3.h>

struct sqlite3; // Forward declaration of sqlite3 struct to avoid including the entire sqlite3.h header in this header file, which can help reduce compilation dependencies and improve build times.

namespace CRUD {
	class SQLiteEmployeeRepository : public IEmployeeRepository {
		public:
			//dbPath: filesystem path to the SQLite database file, which allows the repository to connect to the database and perform CRUD operations on employee data stored in that database.
			explicit SQLiteEmployeeRepository(const std::string& dbPath);
			~SQLiteEmployeeRepository() override;

			void create(const Employee& emp) override;
			Employee getByID(unsigned int id) const override;
			std::vector<Employee> getAll() const override;
		private:
			sqlite3* db_; // Pointer to the SQLite database connection
			std::string dbPath_; // Path to the SQLite database file
			void ensureSchema(); // Ensures the database schema is set up correctly (e.g., creates the employees table if it doesn't exist)

	};
}