#include <stdlib.h>
#include <iostream>
/*
 Include directly the different
 headers from cppconn/ and mysql_driver.h + mysql_util.h
 (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
using namespace std;

// This program retrieves all of the musicians

// Compile:
// g++ -I/usr/include spadesapp.cpp -o spadesapp -I /usr/local/lib -lmysqlcppconn
// 
// Execute:
// ./spadesapp
// 
 sql::Driver *driver;
 sql::Connection *con;
 sql::Statement *stmt;
 sql::ResultSet *res;
 sql::PreparedStatement  *prep_stmt;

void findall();
void findbyPlayerId();
void createPlayer();
void findrounds();
void findAccount();
void findbyTricks();
void findplayer();
void deletePlayer();
void updatePlayerInfo();
void calculateTotalGamesPlayed();
int main(void)
{

try {

   
 /* Create a connection */
 driver = get_driver_instance();

  
con = driver->connect("tcp://127.0.0.1:3306", "root", "");

/* Connect to the MySQL music database */
    
 con->setSchema("Spades");
 //stmt = con->createStatement();
    
 int option = 6;
 
 while (option != 5) {
     
     cout << endl;
     cout << "1. Add a player" << endl;
     cout << "2. Find a player by id" << endl;
     cout << "3. Find a game by Player's tricks" << endl;
     cout << "4. Show all players" << endl;
     cout << "6. Show all rounds played" << endl;
     cout << "7. Show all accounts" << endl;
     cout << "8. Find player data by ID" << endl;
     cout << "9. Delete player account" << endl;
     cout << "10. Update player Information" << endl;
     cout << "11. Calculate total games played by two players" << endl;
     cout << "5. Exit" << endl << endl;
     
     cout << "Choice : ";
     cin >> option;
     
     switch(option) {
        case 1: createPlayer();
                break;
        
        case 2: findbyPlayerId();
                 break;
          
        case 3: findbyTricks();
                 break;   
                 
        case 4: findall();
                 break;

        case 6: findrounds();
                break;

        case 7: findAccount();
                break;
        
        case 8: findplayer();
                break;
                
        case 9: deletePlayer();
                        break;
        
        case 10: updatePlayerInfo();
         break;

        case 11: calculateTotalGamesPlayed();
         break;
             
             
     }
 }
 

 delete res;
 delete stmt;
 delete con;
} catch (sql::SQLException &e) {
 cout << "# ERR: SQLException in " << __FILE__;
 cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
 cout << "# ERR: " << e.what();
 cout << " (MySQL error code: " << e.getErrorCode();
 cout << ", SQLState: " << e.getSQLState() << " )" << endl;
}
cout << endl;
return EXIT_SUCCESS;

}

 void findall() {
     
 stmt = con->createStatement();
 res = stmt->executeQuery("SELECT * from personalInformation");
    
 while (res->next()) {
 
 /* Access column data by alias or column name */
     
     cout << res->getString("PlayerId") << " ";
     cout << res->getString("firstName") << " ";
     cout << res->getString("LastName") << " ";
     cout << res->getString("email") << endl;
     cout << res->getString("dateJoined") << endl;
     cout << res->getString("PHONE") << endl;
     
 
 }
     
 }

void findbyPlayerId() {
     
 
 int PlayerId;
    
 cout << "Enter the player ID : ";
 cin >> PlayerId;
    
 
prep_stmt = con->prepareStatement("SELECT * FROM personalInformation WHERE PlayerId = ?");
prep_stmt->setInt(1, PlayerId);
res = prep_stmt->executeQuery();


 while (res->next()) {

 /* Access column data by alias or column name */
     
     cout << res->getString("PlayerId") << " ";
     cout << res->getString("firstName") << " ";
     cout << res->getString("LastName") << " ";
     cout << res->getString("email") << endl;
     cout << res->getString("dateJoined") << endl;
     cout << res->getString("PHONE") << endl;
 }
     
 }
 void createPlayer() {
    string firstname, lastname,email,dateJoined, PHONE;
 bool b;
    
 cout << "Firstname : ";
 cin >> firstname;
 
 cout << "Lastname : ";
 cin >> lastname;
 
 cout << "Email : ";
 cin >> email;
 
 cout << "Date Joined (YEAR-MO-XX): ";
 cin >> dateJoined;
 
 cout << "Phone Number (XXX-XXX-XXXX): ";
 cin >> PHONE;

 prep_stmt = con->prepareStatement("INSERT INTO personalInformation (firstname, lastname, email, dateJoined, PHONE) " \
                                   "VALUES(?,?,?,?,?) ");
                                                                    
                                   
prep_stmt->setString(1, firstname);
prep_stmt->setString(2, lastname);
prep_stmt->setString(3, email);
prep_stmt->setString(4, dateJoined);
prep_stmt->setString(5, PHONE);

prep_stmt->execute();

stmt = con->createStatement();

res = stmt->executeQuery("SELECT LAST_INSERT_ID() as PlayerId");
    res->next();
    int personalInformationPlayerID = res->getInt("PlayerId");
    cout << "Last ID: " << personalInformationPlayerID << endl;

    prep_stmt = con->prepareStatement("INSERT INTO accountInformation (playerId) VALUES (?)");
    prep_stmt->setInt(1, personalInformationPlayerID);
    prep_stmt->execute();

    // Your remaining code...


 }
 void findrounds() {

stmt = con->createStatement();
 res = stmt->executeQuery("SELECT * from roundsTable");
    
 while (res->next()) {
 
 /* Access column data by alias or column name */

 cout << "Gamesid " << "roundNum " << "firstTeamScore " << "secondTeamScore " << "DatePlayed " << "TimePlayed " << endl;
     
     cout << res->getInt("Gamesid") << " " << "       ";
     cout << res->getInt("roundNum") << " " << "         ";
     cout << res->getInt("firstTeamScore") << " " << "                ";
     cout << res->getInt("secondTeamScore") <<  "         ";
     cout << res->getString("DatePlayed") << " " << "     ";
     cout << res->getString("TimePlayed") << " " << endl;

 }
 }
 void findAccount() {

stmt = con->createStatement();
 res = stmt->executeQuery("SELECT * from accountInformation");
    
 while (res->next()) {
 
 /* Access column data by alias or column name */

 cout << "Player ID " <<  "  Username " << "    Rank   "  "Games Played " << "Games won " << "Games Lost " << "MostUsedScore" << endl;

     cout << res->getInt("playerId") << "            ";
     cout << res->getString("Username") << "    ";
     cout << res->getString("Rank") << "          ";
     cout << res->getInt("gamesPlayed") << " " << "          ";
     cout << res->getInt("gamesWon") << " " << "         ";
     cout << res->getInt("gamesLost") << " " << "       ";
     cout << res->getInt("MostUsedScore") <<  endl;
 
 }
 }
 void findbyTricks() {
     
 
 int Tricks;
    
 cout << "Enter the player's Tricks : ";
 cin >> Tricks;
    
 
prep_stmt = con->prepareStatement("SELECT * FROM gameInformation WHERE Tricks = ?");
prep_stmt->setInt(1, Tricks);
res = prep_stmt->executeQuery();


 while (res->next()) {

 /* Access column data by alias or column name */

 cout << " Game ID " << "Player ID " << "Date Times " << "Match Score " << "Tricks " << "Bags" << "StatusWL" << endl;
     cout << "    ";
     cout << res->getString("gameId") << "        ";
     cout << res->getString("Playerid") << "    ";
     cout << res->getString("dateTimes") << "      ";
     cout << res->getString("matchScore") << "        ";
     cout << res->getString("Tricks") << "          ";
     cout << res->getString("Bags") << "   ";
     cout << res->getString("StatusWL") << endl;
 }    
 }
 void findplayer() {

     int PlayerId;

    cout << "Enter the Player ID : ";
    cin >> PlayerId;

    prep_stmt = con->prepareStatement("SELECT firstname, lastname, gamesPlayed, gamesLost, gamesWon " \
                                   "FROM personalInformation p join accountInformation a " \
                                   "ON p.PlayerId = a.playerId " \
                                   "WHERE p.PlayerId = ?");

    prep_stmt->setInt(1, PlayerId);
    res = prep_stmt->executeQuery();

    while (res->next()) {
        /* Access column data by alias or column name */
         cout << " First Name "<< "Last name " << "Games Played " << "Games won " << "Games Lost " << endl;
         cout << "    ";
        cout << res->getString("firstname") << "     ";
        cout << res->getString("lastname") << "       ";
        cout << res->getInt("gamesPlayed") << "           ";
        cout << res->getInt("gamesWon") << "        ";
        cout << res->getInt("gamesLost") << endl;
    }
 }
   void deletePlayer() {

    int playerIdToDelete;
    cout << "Enter the Player ID to delete: ";
    cin >> playerIdToDelete;

    // Delete records from child table first
    prep_stmt = con->prepareStatement("DELETE FROM accountInformation WHERE playerId = ?");
    prep_stmt->setInt(1, playerIdToDelete);
    prep_stmt->execute();

    // Now, delete the record from the parent table
    prep_stmt = con->prepareStatement("DELETE FROM personalInformation WHERE PlayerId = ?");
    prep_stmt->setInt(1, playerIdToDelete);
    prep_stmt->execute();

    cout << "Player account deleted successfully." << endl;
}
void updatePlayerInfo() {
    int playerIdToUpdate;
    cout << "Enter the Player ID to update: ";
    cin >> playerIdToUpdate;

    string newFirstname, newLastname, newEmail;
    int newPhone;

    cout << "Enter the new Firstname: ";
    cin >> newFirstname;

    cout << "Enter the new Lastname: ";
    cin >> newLastname;

    cout << "Enter the new Email: ";
    cin >> newEmail;

    cout << "Enter the new Phone Number: ";
    cin >> newPhone;

    prep_stmt = con->prepareStatement("UPDATE personalInformation SET firstname = ?, lastname = ?, email = ?, PHONE = ? WHERE PlayerId = ?");
    prep_stmt->setString(1, newFirstname);
    prep_stmt->setString(2, newLastname);
    prep_stmt->setString(3, newEmail);
    prep_stmt->setInt(4, newPhone);
    prep_stmt->setInt(5, playerIdToUpdate);

    prep_stmt->execute();

    cout << "Player information updated successfully." << endl;
}
 void calculateTotalGamesPlayed() {
    int playerId1, playerId2;

    cout << "Enter the first Player ID: ";
    cin >> playerId1;

    cout << "Enter the second Player ID: ";
    cin >> playerId2;

    // Query for player 1
    prep_stmt = con->prepareStatement("SELECT firstname, lastname FROM personalInformation WHERE PlayerId = ?");
    prep_stmt->setInt(1, playerId1);
    res = prep_stmt->executeQuery();

    if (res->next()) {
        cout << "Player 1: " << res->getString("firstname") << " " << res->getString("lastname") << endl;
    } else {
        cout << "Player 1 not found." << endl;
        return;
    }

    // Query for player 2
    prep_stmt = con->prepareStatement("SELECT firstname, lastname FROM personalInformation WHERE PlayerId = ?");
    prep_stmt->setInt(1, playerId2);
    res = prep_stmt->executeQuery();

    if (res->next()) {
        cout << "Player 2: " << res->getString("firstname") << " " << res->getString("lastname") << endl;
    } else {
        cout << "Player 2 not found." << endl;
        return;
    }

    // Calculate total games played for both players
    prep_stmt = con->prepareStatement("SELECT SUM(gamesPlayed) as totalGamesPlayed FROM accountInformation WHERE playerId IN (?, ?)");
    prep_stmt->setInt(1, playerId1);
    prep_stmt->setInt(2, playerId2);
    res = prep_stmt->executeQuery();

    if (res->next()) {
        cout << "Total Games Played: " << res->getInt("totalGamesPlayed") << endl;
    } else {
        cout << "Error calculating total games played." << endl;
    }
}
 










 