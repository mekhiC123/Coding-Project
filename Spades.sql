 -- Spades DATABASE
--
create database Spades;

use Spades;

-- Drop tables if they exist
DROP TABLE IF EXISTS personalInformation;
DROP TABLE IF EXISTS accountInformation;
DROP TABLE IF EXISTS gameInformation;
DROP TABLE IF EXISTS roundsTable;

-- Create personalInformation table
CREATE TABLE personalInformation (
    PlayerId INT NOT NULL AUTO_INCREMENT,
    firstName VARCHAR(35),
    lastName VARCHAR(35),
    email VARCHAR(35),
    dateJoined DATE,
    PHONE CHAR(15),
    PRIMARY KEY (PlayerId)
);

-- Insert into personalInformation without specifying PlayerId
INSERT INTO personalInformation ( PlayerId, firstName, LastName, email, dateJoined, PHONE) VALUES ( 17,'Mekhi', 'Connor', 'mekhic@mail.com', '2023-11-15', '212-588-5634');
INSERT INTO personalInformation ( PlayerId, firstName, LastName, email, dateJoined, PHONE) VALUES ( 18,'JaDarius', 'Tyler', 'JaDariusT@mail.com', '2023-11-26', '212-303-6738');
INSERT INTO personalInformation ( PlayerId, firstName, LastName, email, dateJoined, PHONE) VALUES ( 19,'Micheal', 'Jordan', 'MichealJ@mail.com', '2023-11-29', '212-588-1092');
INSERT INTO personalInformation ( PlayerId, firstName, LastName, email, dateJoined, PHONE) VALUES ( 20,'Will', 'Smith', 'WillS@mail.com', '2023-12-01', '718-383-5681');
INSERT INTO personalInformation ( PlayerId, firstName, LastName, email, dateJoined, PHONE) VALUES ( 21,'Clement', 'Allen', 'ClementA@mail.com', '2023-11-23', '914-455-2337');
-- Create accountInformation table
CREATE TABLE accountInformation (
    playerId INT NOT NULL,
    Username VARCHAR(25),
    Rank CHAR(15),
    gamesPlayed INT,
    gamesWon INT,
    gamesLost INT,
    MostUsedScore INT,
    PRIMARY KEY (playerId),
    FOREIGN KEY (playerId) REFERENCES personalInformation(PlayerId)
);

-- Insert into accountInformation with existing playerId
INSERT INTO accountInformation (playerId, Username, Rank, gamesPlayed, gamesWon, gamesLost, MostUsedScore) VALUES (17,'MC2023','Beginner', 7, 6, 1, 750);
INSERT INTO accountInformation (playerId, Username, Rank, gamesPlayed, gamesWon, gamesLost, MostUsedScore) VALUES (18,'JD2003','Intermediate', 38, 23, 15, 250);
INSERT INTO accountInformation (playerId, Username, Rank, gamesPlayed, gamesWon, gamesLost, MostUsedScore) VALUES (19,'Mj23','Beginner', 9, 3, 6, 750);
INSERT INTO accountInformation (playerId, Username, Rank, gamesPlayed, gamesWon, gamesLost, MostUsedScore) VALUES (20,'Bel-Air','Starter', 1, 1, 0, 500);
INSERT INTO accountInformation (playerId, Username, Rank, gamesPlayed, gamesWon, gamesLost, MostUsedScore) VALUES (21,'Famu>AUC','Advanced', 100, 95, 5, 750);

CREATE TABLE gameInformation (
    gameId INT NOT NULL AUTO_INCREMENT,
    Playerid INT NOT NULL,
    dateTimes DATETIME,
    matchScore INT,
    Tricks INT,
    Bags INT,
    StatusWL char(10),
    PRIMARY KEY (gameId),
    FOREIGN KEY (Playerid) REFERENCES personalInformation(PlayerId)
);

-- Insert into gameInformation with existing PlayerId
INSERT INTO gameInformation (Playerid, dateTimes, matchScore, Tricks, Bags, StatusWL) VALUES (17, '2023-11-30 15:30:00', 7, 7, 2, 'Winner');
INSERT INTO gameInformation (Playerid, dateTimes, matchScore, Tricks, Bags, StatusWL) VALUES (18, '2023-11-25 12:05:15', 8, 1, 3, 'Loser');
INSERT INTO gameInformation (Playerid, dateTimes, matchScore, Tricks, Bags, StatusWL) VALUES (19, '2023-11-22 10:15:00', 12, 9, 4, 'Winner');
INSERT INTO gameInformation (Playerid, dateTimes, matchScore, Tricks, Bags, StatusWL) VALUES (20, '2023-11-27 19:23:32', 10, 6, 1, 'Loser');
INSERT INTO gameInformation (Playerid, dateTimes, matchScore, Tricks, Bags, StatusWL) VALUES (21, '2023-11-30 15:30:00', 8, 8, 5, 'Winner');

CREATE TABLE roundsTable (
    RoundId INT NOT NULL AUTO_INCREMENT,
    Gamesid INT NOT NULL,
    roundNum INT,
    firstTeamScore INT,
    secondTeamScore INT,
    DatePlayed DATE,
    TimePlayed TIME,
    PRIMARY KEY (RoundId),
    FOREIGN KEY (Gamesid) REFERENCES gameInformation(gameId)
);

-- Insert into roundsTable with existing Gamesid
INSERT INTO roundsTable (Gamesid, roundNum, firstTeamScore, secondTeamScore, DatePlayed, TimePlayed) VALUES (1, 1, 1, 0,'2023-11-30','15:30:00');
INSERT INTO roundsTable (Gamesid, roundNum, firstTeamScore, secondTeamScore, DatePlayed, TimePlayed) VALUES (2, 1, 0, 1,'2023-11-25','12:05:15');
INSERT INTO roundsTable (Gamesid, roundNum, firstTeamScore, secondTeamScore, DatePlayed, TimePlayed) VALUES (3, 13, 9, 4,'2023-11-21','17:05:13');
INSERT INTO roundsTable (Gamesid, roundNum, firstTeamScore, secondTeamScore, DatePlayed, TimePlayed) VALUES (4, 7, 5, 2,'2023-11-07','10:15:15');
INSERT INTO roundsTable (Gamesid, roundNum, firstTeamScore, secondTeamScore, DatePlayed, TimePlayed) VALUES (5, 5, 2, 3,'2023-11-23','11:35:10');

---select COUNT(gamesPlayed) from accountInformation
 --Queries 
--a. Show all of the names of the single player users in the database.
--select firstName, lastName, Username from personalInformation natural join accountInformation;

--b. Show the user that has over five wins and has an intermediate rank.
--select gamesWon, Rank, Username from accountInformation where gamesWon > 5 and Rank = 'Intermediate';

--c. Update the rank of the intermediate player previously selected to adavnced. 
--update accountInformation set Rank = 'Advanced' where Rank = 'Intermediate';

--d. What single player has the lowest amount of tricks placed in a game?
--select Username, min(Tricks) AS LowestTricks from gameInformation NATURAL JOIN accountInformation;
--d. Show the average amount of games played by all users.
--select avg(gamesPlayed) from accountInformation;

--e. Remove player with a atarter rank.
--delete from accountInformation where Rank = 'Starter';

