// Database Header File
#ifndef DB_CLASS_H // include guard
#define DB_CLASS_H

#include <iostream>
#include <string>
#include <mariadb/conncpp.hpp>
#include <nlohmann/json.hpp>
#include <iomanip>
#include <fstream>

using json = nlohmann::json;

namespace db {
    class Configuration {
        int db_port;
		std::string db_name;
		std::string db_user;
		std::string db_pass;
		std::string db_host;
        private:
            
        public:
            void create_config(std::string filename);
            void del_config();
            void upd_config(std::string filename, std::string server, int port, std::string user, std::string pass, std::string db);
            void dsp_config(std::string filename, std::string &server, std::string &port, std::string &user, std::string &pass, std::string &db);
    };
	// figure this out for OOP
    class Connector {
        public:
            int db_connector(std::string server, std::string port, std::string pass, std::string user, std::string db);
    };
    class Commands : public Connector {
        public:
            void add_command(std::unique_ptr<sql::Connection> &conn, std::string command, int cat_id, int own_id);
            void del_command(std::unique_ptr<sql::Connection> &conn, int id);
            void upd_command(std::unique_ptr<sql::Connection> &conn, int id, std::string command, int cat_id);
            void dsp_commands(std::unique_ptr<sql::Connection> &conn);
    };
    class Users : public Connector{
        public:
            void add_user(std::unique_ptr<sql::Connection> &conn, std::string username, std::string password, int role, std::string team);
            void del_user(std::unique_ptr<sql::Connection> &conn, int id);
            void upd_user(std::unique_ptr<sql::Connection> &conn, int id, std::string username, std::string password, int role, std::string team);
            void dsp_users(std::unique_ptr<sql::Connection> &conn);
    };
    class Teams : public Connector {
        public:
            int add_team();
            int del_team();
            int upd_team();
            int dsp_teams();
    };
	class Category : public Connector {
		public:
			void add_category(std::unique_ptr<sql::Connection> &conn, std::string cat_name);
			void upd_category(std::unique_ptr<sql::Connection> &conn, int id, std::string cat_name);
			void del_category(std::unique_ptr<sql::Connection> &conn, int id);
			void dsp_categories(std::unique_ptr<sql::Connection> &conn);
	};
}
#endif
