/*
* Build: g++ -g *.cpp *.hpp -o redteam -lmariadbcpp
* sql::Connection 		 - Establish a connection to MariaDB Enterprise. A Connection can be closed by calling close(), or there is an implicit close when using a smart pointer.
* sql::DatabaseMetaData  - Provides detailed information about the database metadata, such as database name, version, schemas, tables, columns, procedures, and support for various features.
* sql::Driver 			 - Implements the non-static connect() method, which is a connection method.
* sql::DriverManager 	 - Implements the static getConnection() method, which is a connection method.
* sql::PreparedStatement - Execute a query that contains variable text. Prepared statements can be used to sanitize input. Therefore, using prepared statements reduces the risk of SQL injection attacks. 
* 						   A PreparedStatement can be closed by calling close(), or there is an implicit close when using a smart pointer. By default, the connector will use client-side prepared statements. 
* 						   To use server-side prepared statements, set the useServerPrepStmts optional connection parameter to true.
* sql::ResultSet 		 - Fetch query results. A ResultSet can be closed by calling close(), or there is an implicit close when using a smart pointer.
* sql::ResultSetMetaData - Provides detailed information about a result set, such as schema name, table name, column names and types, and column attributes; whether a column is auto increment, and nullable.
* sql::Statement 		 - Execute a query that does not contain variable text. A Statement can be closed by calling close(), or there is an implicit close when using a smart pointer.
*
* Connect Link: https://mariadb.com/docs/clients/mariadb-connectors/connector-cpp/connect/
* DML Link    : https://mariadb.com/docs/clients/mariadb-connectors/connector-cpp/dml/
* json		  : https://bestofcpp.com/repo/nlohmann-json-cpp-json#json-as-first-class-data-type
*/
#include "db_header.hpp"

#define MAX_CAT_SIZE 50

int main(int argc, char **argv) {
	std::string server = "";
	std::string port = "";
	std::string user = "";
	std::string pass = "";
	std::string db = "";
	db::Configuration config;
    db::Category category;
    db::Users users;
    db::Commands commands;
	//config.create_config("config.json");
	// std::string server, int port, std::string user, std::string pass, std::string db
	//config.upd_config("config.json","localhost",3306,"redtem", "Password123!", "redteam_app");
	config.dsp_config("config.json", server, port, user, pass, db);
	try {
        //instantiate driver
        sql::Driver* driver = sql::mariadb::get_driver_instance();

        // configure connection
        sql::SQLString url("jdbc:mariadb://" + server + ":" + port + "/" + db);
        sql::Properties properties({{"user", user},{"password", pass}});

        // establish connection
		std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
		int choice = 0;
			std::string answer = "";
			std::string cat_name = "";
			int sub_choice = 0;
		do {
			
			std::cout << "1. Display Categories, 2. Display Users, 3. Display Commands, 4. Quit" << std::endl;
			std::cout << "Please make a selection: ";
			std::cin >> choice;
			
			if (choice == 1) {
				category.dsp_categories(conn);
				std::cout << "Would you like to update a category? ";
				std::cin >> answer;
				if (answer == "y") {
					std::cout << "What category would you like to update? ";
					std::cin >> sub_choice;
					std::cout << "What would you like to update the category name to? ";
					std::cin >> cat_name;
					if (sub_choice == 1) {
						category.upd_category(conn, sub_choice, cat_name);
					}		
				}
				choice = 0;
			}
			else if (choice == 2) {
        		users.dsp_users(conn);
				choice = 0;
			}
			else if (choice == 3) {
				commands.dsp_commands(conn);
				choice = 0;

			}
			else if (choice > 4) {
				std::cout << "Please make a valid selection 1-4" << std::endl;
				choice = 0;
			}
		
		} while (choice != 4 && choice == 0);
		std::cout << "\n";
        // close connection
        conn->close();
    } catch (sql::SQLException& e) {
		std::cerr << "Error Connecting to database: " << e.what() << std::endl;
        // exit (failed)
        return 1;
    }
	// exit (success)
	return 0;
}
