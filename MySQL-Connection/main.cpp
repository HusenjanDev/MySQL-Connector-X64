#include <stdio.h>
#include "mysql_connector.h"
#include "fmt/core.h"

int main()
{
	try
	{
		// Establishing the connection.
		mysql_connector mysql("tcp://127.0.0.1:3306", "username", "password", "database");

		// Creating an table.
		mysql.create_table("table_name");

		// Adding an user onto the table.
		mysql.add_user("table_name", "username", "password");

		// Printing all the table elements.
		mysql.print_table("table_name");
	}
	catch (...)
	{
		fmt::print("An error occurred!\n");
	}

	// Quits.
	return 0;
}