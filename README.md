# redteam_app


## Dependencies
+ conncpp.hpp
+ json.hpp

## To install MariaDB Connector/C++ on Linux:

### Install MariaDB Connector/C. 

1. Go to the MariaDB Connector C++ download page.
2. In the "OS" dropdown, select the Linux distribution you want to use.
3. Click the "Download" button to download the binary tarball.

#### Extract the tarball:
1. tar -xvzf mariadb-connector-cpp-*.tar.gz
2. Change into the relevant directory:
3. cd mariadb-connector-cpp-*/

#### Install the directories for the header files:


1. sudo install -d /usr/include/mariadb/conncpp
2. sudo install -d /usr/include/mariadb/conncpp/compat

#### Install the header files:
1. sudo install include/mariadb/* /usr/include/mariadb/
2. sudo install include/mariadb/conncpp/* /usr/include/mariadb/conncpp
3. sudo install include/mariadb/conncpp/compat/* /usr/include/mariadb/conncpp/compat

#### Install the directories for the shared libraries:
**On CentOS/RHEL**
+ sudo install -d /usr/lib64/mariadb
+ sudo install -d /usr/lib64/mariadb/plugin

**On Debian/Ubuntu**
+ sudo install -d /usr/lib/mariadb
+ sudo install -d /usr/lib/mariadb/plugin

#### Install the shared libraries:
**On CentOS/RHEL**
+ sudo install lib/mariadb/libmariadbcpp.so /usr/lib64
+ sudo install lib/mariadb/plugin/* /usr/lib64/mariadb/plugin

**On Debian/Ubuntu**
+ sudo install lib/mariadb/libmariadbcpp.so /usr/lib
+ sudo install lib/mariadb/plugin/* /usr/lib/mariadb/plugin


# To install MariaDB Connector/C++ on Windows:
### MariaDB Connector/C dependency will be installed when Connector/C++ is installed.

1. Go to the MariaDB Connector C++ download page for MS Windows.
2. Click the "Download" button to download the MSI package.
3. Run the MSI package and click "Next" to start the Setup Wizard.
4. On the second screen, click the license agreement checkbox, then click "Next."
5. On the third screen, click "Typical."
6. On the fourth screen, click "Install."
7. Click "Finish."
8. Add the directory path that contains the mariadbcpp LIB file (example "C:\Program Files\MariaDB\MariaDB C++ Connector 64-bit") to PATH environment variable.

> Source: [MariaDB Connector/C++](https://mariadb.com/docs/connect/programming-languages/cpp/install/)

### Installing json.hpp on a Linux Machine
