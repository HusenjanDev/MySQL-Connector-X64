#pragma once
#include <cppconn/driver.h>
#include <mysql_connection.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

#include <fmt/os.h>
#include <fmt/ostream.h>

class mysql_connector
{
private:
	sql::Driver* driver;
	sql::Connection* conn;
	sql::Statement* stmt;
	sql::PreparedStatement* pstmt;
	sql::ResultSet* res;
public:
	mysql_connector(std::string host, std::string username, std::string password, std::string database);
	void create_table(std::string table_name);
	void add_user(std::string table_name, std::string username, std::string password);
	void print_table(std::string table_name);
};