#include "SQLiteEmployeerepo.h"
#include <iostream>
#include <stdexcept>
//#include <string>
//#include <sqlite3.h>

using namespace CRUD;

SQLiteEmployeeRepository::SQLiteEmployeeRepository(const std::string& dbPath) : dbPath_(dbPath), db_(nullptr) {
	// Here we would normally open the SQLite database connection using sqlite3_open and handle any errors that may occur during the connection process.
	std::cout << "\n[SQLiteEmployeeRepository] Initializing repository with database path: " << dbPath_ << std::endl;
	if (sqlite3_open(dbPath.c_str(), &db_) != SQLITE_OK) {
		std::cout << "Failed to open database\n";
	}
	ensureSchema(); // Ensure the database schema is set up correctly (e.g., create employees table if it doesn't exist)
	// For demonstration purposes, we'll just print a message instead of actually connecting to a database.
}

SQLiteEmployeeRepository::~SQLiteEmployeeRepository() {
	// Here we would normally close the SQLite database connection using sqlite3_close to ensure that all resources are properly released.
	std::cout << "\n[SQLiteEmployeeRepository] Closing database connection and cleaning up resources.\n";
	if (db_) {        //if there database file exists clean and close it and make database emplty
		sqlite3_close(db_);
		db_ = nullptr;
	}
	// For demonstration purposes, we'll just print a message instead of actually closing a database connection.
}

void SQLiteEmployeeRepository::ensureSchema() {
	// Here we would normally execute an SQL statement to create the employees table if it doesn't already exist, ensuring that the database schema is set up correctly for storing employee data.
	std::cout << "\n[SQLiteEmployeeRepository] Ensuring database schema is set up correctly (e.g., creating employees table if it doesn't exist).\n";
	const char* sql = "CREATE TABLE IF NOT EXISTS EMPLOYEE("
		"ID INTEGER PRIMARY KEY,"
		"NAME TEXT NOT NULL,"
		"DEPARTMENT TEXT,"
		"SALARY REAL);";
	executeQuery(sql);

	// For demonstration purposes, we'll just print a message instead of actually executing SQL statements to manage the database schema.
}

void SQLiteEmployeeRepository::create(const Employee& emp) {
	// Here we would normally execute an SQL INSERT statement to add the employee data to the SQLite database, using sqlite3_exec or a prepared statement.
	std::cout << "\n[SQLiteEmployeeRepository] Creating employee with ID: " << emp.getID() << ", Name: " << emp.getName() << ", Department: " << emp.getDepartment() << ", Salary: " << emp.getSalary() << std::endl;

	const std::string sql = "INSERT OR REPLACE INTO EMPLOYEE(ID, NAME, DEPARTMENT, SALARY) VALUES( " + std::to_string(emp.getID()) + ", '" + emp.getName() + "', '" + emp.getDepartment() + "', " + std::to_string(emp.getSalary()) + ");";
	executeQuery(sql);
}

void SQLiteEmployeeRepository::executeQuery(const std::string& query) {
	// Here we would normally execute the provided SQL query against the SQLite database using sqlite3_exec or a prepared statement, and handle any errors that may occur during query execution.
	std::cout << "\n[SQLiteEmployeeRepository] Executing SQL query: " << query << std::endl;
	char* errMsg = nullptr;
	int result = sqlite3_exec(db_, query.c_str(), 0, nullptr, &errMsg);
	if (result != SQLITE_OK) {
		std::cerr << "SQL error: " << errMsg << std::endl;
		sqlite3_free(errMsg);
		throw std::runtime_error("Failed to execute SQL query");
	}
	// For demonstration purposes, we'll just print a message instead of actually executing SQL queries against a database.
}

Employee SQLiteEmployeeRepository::getByID(unsigned int id) const {
	// Here we would normally execute an SQL SELECT statement to retrieve the employee data with the specified ID from the SQLite database, and then construct and return an Employee object based on the retrieved data.
	//std::cout << "\n[SQLiteEmployeeRepository] Retrieving employee with ID: " << id << std::endl;
	// For demonstration purposes, we'll just print a message and return a default Employee object instead of actually querying a database.
	return Employee();
}

std::vector<Employee> SQLiteEmployeeRepository::getAll() const {
	// Here we would normally execute an SQL SELECT statement to retrieve all employee records from the SQLite database, and then construct and return a vector of Employee objects based on the retrieved data.
	//std::cout << "\n[SQLiteEmployeeRepository] Retrieving all employees from the database.\n";
	// For demonstration purposes, we'll just print a message and return an empty vector instead of actually querying a database.
	return std::vector<Employee>();
}