#include "db_header.hpp"

struct Settings {
	std::string user;
	std::string pass;
	std::string db;
	std::string server;
	std::string port;
};

// config section
void db::Configuration::create_config(std::string filename) {
    auto config = R"(
        {
            "user": "",
            "password": "",
            "database": "",
            "server": "",
            "port": ""
        }
    )"_json;
    std::ofstream wconf(filename);
    wconf << std::setw(2) << config << std::endl;
}
void db::Configuration::dsp_config(std::string filename, std::string &server, std::string &port, std::string &user, std::string &pass, std::string &db) {
	std::ifstream rconf(filename);
    json config;
    rconf >> config;
    //cout << config.dump(2) << endl;
	server = config["server"];
	pass = config["password"];
	user = config["user"];
	db = config["database"];
    port = to_string(config["port"]);
}
void db::Configuration::upd_config(std::string filename, std::string server, int port, std::string user, std::string pass, std::string db) {
    std::ifstream rconf(filename);
    json update;
    rconf >> update;

    json config = {
        {"user", user},
        {"password", pass},
        {"database", db},
        {"server", server},
        {"port", port}
    };
    std::ofstream wconf(filename);
            wconf << std::setw(2) << config << std::endl;
}

// DB Connection
int db::Connector::db_connector(std::string server, std::string port, std::string user, std::string pass, std::string db) {
 return 0;
}

// Command section
// add command
void db::Commands::add_command(std::unique_ptr<sql::Connection> &conn, std::string command, int cat_id, int own_id) {
    try {
        // create a new prepared statement
		std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("insert into commands (command, cate_id, own_id, create_date) values (?, ?, ?, CURDATE())"));
        // bind values to sql statement
        stmnt->setString(1,command);
        stmnt->setInt(2,cat_id);
        stmnt->setInt(3,own_id);
        // execute query
        stmnt->executeQuery();
    } catch(sql::SQLException& e) {
        std::cerr << "Error adding command: " << e.what() << std::endl;
    }
}
// update command
void db::Commands::upd_command(std::unique_ptr<sql::Connection> &conn, int id, std::string command, int cat_id) {
    try {
        // create a new prepared statement
		std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("update commands set command = ?, cat_id = ?, mod_date = CURDATE() where com_id = ?"));
        // bind values to sql statement
        stmnt->setString(1, command);
        stmnt->setInt(2, cat_id);
        stmnt->setInt(3, id);
        // execute query
        stmnt->executeQuery();
    } catch(sql::SQLException& e) {
        std::cerr << "Error updating category name: " << e.what() << std::endl;
    }
}
// delete command
void db::Commands::del_command(std::unique_ptr<sql::Connection> &conn, int id) {
    try {
         // create a new prepared statement
		std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("delete from commands where com_id = ?"));
        // bind value to SQL statement
        stmnt->setInt(1, id);
        // execute query
        stmnt->executeQuery();
    } catch(sql::SQLException& e) {
        std::cerr << "Error deleting command: " << e.what() << std::endl;
    }
}
// display commands
void db::Commands::dsp_commands(std::unique_ptr<sql::Connection> &conn) {
    try {
        // create new statement
		std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
        // execute query
        sql::ResultSet *res = stmnt->executeQuery("select * from commands");
        sql::ResultSet *cname = stmnt->executeQuery("select category.cat_name, commands.cate_id from category inner join commands on commands.cate_id = category.cat_id");
        sql::ResultSet *name = stmnt->executeQuery("select users.username, commands.id from users inner join commands using (id)");
        // loop through and print results
        while (res->next()) {
            std::cout << "Command: " << res->getString(2) << std::endl;
            while (cname->next()) {
            	std::cout << "Category: " << cname->getString(1) << std::endl;
                break;
            }
            while (name->next()) {
                std::cout << "Owner: " << name->getString(1) << std::endl;
                break;
            }
            std::cout << "Created: " << res->getString(5) << std::endl;
            std::cout << "Modified: " << res->getString(6) << std::endl << "\n";
    }
    } catch (sql::SQLException& e) {
        std::cerr << "Error selecting commands: " << e.what() << std::endl;
    }
}

// Category section
// Create a new category
void db::Category::add_category(std::unique_ptr<sql::Connection> &conn, std::string cat_name) {
    try {
        // create a new prepared statement
		std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("insert into category (cat_name) values (?)"));
        // bind values to sql statement
        stmnt->setString(1, cat_name);
        // execute query
        stmnt->executeQuery();
    } catch(sql::SQLException& e) {
        std::cerr << "Error inserting category name: " << e.what() << std::endl;
    }
}
// Update a category
void db::Category::upd_category(std::unique_ptr<sql::Connection> &conn, int id, std::string cat_name) {
    try {
		std::cout << cat_name << std::endl;
        // create a new prepared statement
		std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("update category set cat_name = ? where cat_id = ?"));
        // bind values to sql statement
        stmnt->setString(1, cat_name);
        stmnt->setInt(2, id);
        // execute query
        stmnt->executeQuery();
    } catch(sql::SQLException& e) {
        std::cerr << "Error updating category name: " << e.what() << std::endl;
    }
}
// delete a category
void db::Category::del_category(std::unique_ptr<sql::Connection> &conn, int id) {
    try {
        // create a new prepared statement
		std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("delete from category where cat_id = ?"));
        // bind value to SQL statement
        stmnt->setInt(1, id);
        // execute query
        stmnt->executeQuery();
    } catch(sql::SQLException& e) {
        std::cerr << "Error deleting category: " << e.what() << std::endl;
    }
}
// display all categories
void db::Category::dsp_categories(std::unique_ptr<sql::Connection> &conn) {
    try {
        // create a new statement
		std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
        // execute query
        sql::ResultSet *res = stmnt->executeQuery("select * from category");
        // loop through and print results
        while (res->next()) {
            std::cout  << res->getInt(1) << ": " << res->getString(2) << "\n";
        }
    } catch(sql::SQLException& e) {
        std::cerr << "Error selecting categories: " << e.what() << std::endl;
    }
}

// User section
// add user
void db::Users::add_user(std::unique_ptr<sql::Connection> &conn, std::string username, std::string password, int role, std::string team ) {
    try {
        // create a new prepared statement
		std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("insert into users (username, password, role, team) values (?, AES_ENCRYPT(?,SHA2('',512)), ?, ?)"));
        // bind values to sql statement
        stmnt->setString(1, username);
        stmnt->setString(2, password);
        if(role < 0 || role > 4) {
            std::cerr << "Not a Valid role id: " << role << std::endl;
            return;
        }
        else {
            stmnt->setInt(3, role);
        }
        stmnt->setString(4, team);
        // execute query
        stmnt->executeQuery();
    } catch(sql::SQLException& e) {
        std::cerr << "Error creating user: " << e.what() << std::endl;
    }
}
// update user information
void db::Users::upd_user(std::unique_ptr<sql::Connection> &conn, int id, std::string username, std::string password, int role, std::string team) {
    try {
        // create a new prepared statement
		std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("update users set username = ?, password = AES_ENCRYPT(?,SHA2('',512)), role = ?, team = ? where id = ?"));
        // bind values to sql statement
        stmnt->setString(1, username);
        stmnt->setString(2, password);
        stmnt->setInt(3, role);
        stmnt->setString(4, team);
        stmnt->setInt(5, id);
        // execute query
        stmnt->executeQuery();
    } catch(sql::SQLException& e) {
        std::cerr << "Error updating user: " << e.what() << std::endl;
    }
}
// delete user
void db::Users::del_user(std::unique_ptr<sql::Connection> &conn, int id) {
    try {
        // create a new prepared statement
		std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("delete from users where id = ?"));
        // bind value to SQL statement
        stmnt->setInt(1, id);
        // execute query
        stmnt->executeQuery();
        } catch(sql::SQLException& e) {
        	std::cerr << "Error deleting user: " << e.what() << std::endl;
    }
}
// display users
void db::Users::dsp_users(std::unique_ptr<sql::Connection> &conn) {
    try {
        // create a new statement
		std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
        // execute query
        sql::ResultSet *res = stmnt->executeQuery("select * from users");
        sql::ResultSet *role = stmnt->executeQuery("select role.role_name, users.role from role inner join users on users.role = role.role_id");
        sql::ResultSet *team = stmnt->executeQuery("select team.team_name, users.team from team inner join users on users.team = team.team_id");
        // loop through and print results
        while (res->next()) {
            std::cout << res->getInt(1) << ": " << res->getString(2) << std::endl;
            while (role->next()) {
                std::cout << "Role: " << role->getString(1) << std::endl;
                break;
            }
            while (team->next()) {
                std::cout << "Team: " << team->getString(1) << std::endl;
                break;
            }
            //cout << "Team: " << res->getString(5) << endl << "\n";
            std::cout << "\n";
        }
    } catch (sql::SQLException& e) {
        std::cerr << "Error selecting users: " << e.what() << std::endl;
    }
}
// verify that the user is allowed to access the data. (user login)
void user_login(std::unique_ptr<sql::Connection> &conn) {
}
void user_logout(std::unique_ptr<sql::Connection> &conn) {
}

