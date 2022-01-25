#include "mysql_connector.h"

/// <summary>
///	Established the MySQL Connection.
/// </summary>
/// <param name="host">ip-address of the server.</param>
/// <param name="username">mysql username.</param>
/// <param name="password">mysql password.</param>
/// <param name="database">selects an database.</param>
mysql_connector::mysql_connector(const std::string host, const std::string username, const std::string password, std::string database)
{
	fmt::print("[mysql_connector::mysql_connector] Connecting to MySQL Server!\n");

	try
	{
		this->driver = get_driver_instance();
		this->conn = this->driver->connect(host.c_str(), username.c_str(), password.c_str());
		fmt::print("[mysql_connector::mysql_connector] Connection was successful!\n");

		this->conn->setSchema(database);
		this->stmt = this->conn->createStatement();

		fmt::print("[mysql_connector::mysql_connector] Selected the database {} successfully!\n", database);
	}
	catch (sql::SQLException err)
	{
		fmt::print("[mysql_connector::mysql_connector] SQLException Error: {}\n", err.getSQLStateCStr());
	}
}

/// <summary>
/// Creates an table that contains id, username and password.
/// </summary>
/// <param name="table_name">the name the table will be assigned.</param>
void mysql_connector::create_table(std::string table_name)
{
	fmt::print("[mysql_connector::show_table_content] Creating an table.\n");

	try
	{
		// The table contains rows such as id, name and message.
		this->stmt->execute(fmt::format("CREATE TABLE IF NOT EXISTS {} ({});", table_name, "id INT PRIMARY KEY AUTO_INCREMENT, username VARCHAR(20) DEFAULT NULL, password VARCHAR(20) DEFAULT NULL"));
		fmt::print("[mysql_connector::create_table] The table {} has been created!\n", table_name);
	}
	catch (sql::SQLException err)
	{
		fmt::print("[mysql_connector::create_table] SQLException Error: {}\n", err.getSQLStateCStr());
	}
}

/// <summary>
/// Adding an user into the table. The table must contain id, username and password.
/// </summary>
/// <param name="table_name">selected table</param>
/// <param name="username">will be assigned in username column.</param>
/// <param name="password">will be assigned in password column.</param>
void mysql_connector::add_user(std::string table_name, std::string username, std::string password)
{
	fmt::print("[mysql_connector::add_user] Adding an user into {}.\n", table_name);

	try
	{
		this->pstmt = conn->prepareStatement(fmt::format("INSERT INTO {}(username, password) VALUES(?,?);", table_name));
		this->pstmt->setString(1, username);
		this->pstmt->setString(2, password);
		this->pstmt->execute();
		fmt::print("[mysql_connector::add_user] Added {}:{}\n", username, password);
	}
	catch (sql::SQLException err)
	{
		fmt::print("[mysql_connector::add_user] SQLException Error: {}\n", err.getSQLStateCStr());
	}
}

/// <summary>
/// Prints all the rows inside the created table.
/// </summary>
/// <param name="table_name">is the table that will be printed</param>
void mysql_connector::print_table(std::string table_name)
{
	fmt::print("[mysql_connector::show_rows] Getting all rows.\n");

	try
	{
		this->res = this->stmt->executeQuery(fmt::format("SELECT * FROM {};", table_name));

		while (res->next())
		{
			fmt::print("Username: {} | Password: {} \n", res->getString("username"), res->getString("password"));
		}
	}
	catch (sql::SQLException err)
	{
		fmt::print("[mysql_connector::add_user] SQLException Error: {}\n", err.getSQLStateCStr());
	}
}