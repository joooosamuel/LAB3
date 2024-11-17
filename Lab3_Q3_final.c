//Headers
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h> 

//Global Defined variables
#define NUM_TEAMS 5  
#define SQUAD_SIZE 5

//Structure to store the date of birth of playerr
typedef struct{
    int day; //date
    int month; //month
    int year; //year
} date_t;

//Structure to store the details of the player
typedef struct{
    char full_name[26]; //Players full name
    int kit_number; //Players kit number from 1 to 99
    char club[40]; //Club name 
    date_t dob; //Players date of birth
    char position[20]; //Position of the player ex: Goalkeeper, Mid-fielder, Forward etc.
} player_t;

//Strucute to store the details of the club
typedef struct{
    char club_name[21]; //Club name
    player_t players[SQUAD_SIZE]; //Array of players 
    int player_count; //Number of players in the team currently
} team_deets;

team_deets teams[NUM_TEAMS]; //aray of teams 
int num_enrolled_clubs = 0; //counter to track the number of clubs 

//Function Prototypes
void display_menu(); //main menu
void enroll_club(); //function to enroll clubs
void add_player(); //function to add players
int team_selected(); //function called to select the team to add player
int check_player_name(int team_num, char* full_name); //function to check if players name is repeated
int check_kit_no(int team_num, int kit_number); //functon to check if kit number is repeated
void search_update(); //search for a player and if they want to update their details
void update_player(int team_num, int player_num); //fucntion called to update the players details
void display_club_stats(); //displays the stats of each club
int get_current_year(); //function to calculate the year 
double calculate_average_age(int team_num); //function to calculate the average age
void handle_error(const char *message); //function called when theres an error message to be displayed

int main(){
    int selection;

    //setting each team to have 0 players at the start
    for(int i = 0; i < NUM_TEAMS; i++){
        teams[i].player_count = 0;
    }

    while (1){
        display_menu();
        scanf("%d", &selection);
        while (getchar() != '\n');  //clear input buffer
        if(selection == 1){ //calls functions based on value 
            enroll_club(); //enrolls a club
        }else if(selection == 2){
            add_player(); //adds players
        }else if(selection == 3){
            search_update(); //searchs player
        }else if(selection == 4){
            display_club_stats(); //display club stats
        }else if(selection == 0){
            break; //ends the program if selection is 0
        }else{
            handle_error("Invalid choice. Try again.\n"); //message to display if wrong input
            break;
        }
    }
}

//Function Definitions

//The menu displayed 
void display_menu(){
   printf("1. Enroll Club\n");
   printf("2. Add a player\n");
   printf("3. Search and update a player\n");
   printf("4. Club Stats\n");
   printf("0. Exit\n");
   printf("Enter your choice (0-4): ");
}

//Enrolling a club
void enroll_club(){
    if(num_enrolled_clubs >= NUM_TEAMS){ //checking if the maximum number of clubs have been enrolled
        handle_error("Maximum number of clubs enrolled."); //error message to be displayed when max number of clubs reached
        return;
    }
    char club_name[21];
    printf("Enter club name: ");
    if(fgets(club_name, sizeof(club_name), stdin) == NULL){ // reads team name
        handle_error("Error reading club name.");
        return;
    }
    club_name[strcspn(club_name, "\n")] = '\0'; //remove newline character
    if(strlen(club_name) == 0){ //check if club name is empty
        handle_error("You must enter a club name."); //error message to be displayed when club name is empty
        return;
    }
    for(int i = 0; i < num_enrolled_clubs; i++){
        if(strcasecmp(teams[i].club_name, club_name) == 0){ //checks if the club name already exists
            handle_error("A club with the same name already exists."); //error message displayed when there is already an existing club name
            return;
        }
    }

    //stores the clubs name if no errors
    strcpy(teams[num_enrolled_clubs].club_name, club_name);
    teams[num_enrolled_clubs].player_count = 0;
    num_enrolled_clubs++;
    printf("Club %s has been enrolled.\n", club_name);
}

// adding player
void add_player(){
    if(num_enrolled_clubs==0){ //cannot add players if there's no clubs enrolled
        handle_error("No clubs are created yet\n"); //error message displayed when there no clubs created
        return;
    }
    int team_number=team_selected(); //storing the team selected by the user
    if (team_number==-1) return; //exits if invalid selection

    if(teams[team_number].player_count>=SQUAD_SIZE){ //checks if the maximum number of players have been reached
        handle_error("Team has maximum number of players already.\n"); //error messaged displayed when maximum reached
        return;
    }

    player_t new_player; //storing the new players details in the structure
    printf("Enter players name (50 characters): ");
    if(fgets(new_player.full_name, sizeof(new_player.full_name),stdin)==NULL){ //read players name
        handle_error("Error reading name\n"); //error message to be displayed
        return;
    }
    new_player.full_name[strcspn(new_player.full_name,"\n")]='\0'; //remove new line character

    if(check_player_name(team_number, new_player.full_name)){ //checks if theres an exisitng player in the club
        handle_error("A player with this name already is already there.\n"); //error message displayed if there is an existing player
        return;
    }

    printf("Enter a kit number (1-99): "); //enter kit number from 1 to 99
    scanf("%d",&new_player.kit_number); //stores the kit number in the structure
    getchar(); //handle newline

    if(!check_kit_no(team_number, new_player.kit_number)){ //calling the check_kit function
        handle_error("Enter a number between 1 and 99.\n"); //Error message to be displayed when kit number not in the range
        return;
    }

    printf("Enter Birth Date (DD MM YYYY): "); //gets date of birth
    scanf("%d %d %d", &new_player.dob.day, &new_player.dob.month, &new_player.dob.year); //stores them in the dob structure
    getchar(); //handles newline

    printf("Enter player's position: "); //enter the position of the player
    if(fgets(new_player.position, sizeof(new_player.position),stdin)==NULL){ //reads the position of the player
        handle_error("Error reading position.\n"); //error message
        return;
    }
    new_player.position[strcspn(new_player.position, "\n")] = '\0'; //remove new line character


    teams[team_number].players[teams[team_number].player_count++] = new_player; //adds the player to the selected club
    printf("Player %s has been added to team %s \n\n\n", new_player.full_name, teams[team_number].club_name);
}

//user selects the club they want to add the players to
int team_selected(){
    printf("Choose ur team\n");
    for (int i = 0; i < num_enrolled_clubs; i++){
        printf("%d. %s\n", i+1, teams[i].club_name); //prints the list of clubs in the league
    }
    int team_number;
    printf("Enter your team number: "); //user enters the team number
    scanf("%d", &team_number); //stores the team number selected
    getchar(); //handles newline

    if(team_number<1 || team_number>num_enrolled_clubs){ //enusring the right numbers are entered
        handle_error("Wrong input\n"); //error message to be displayed if wrong numbers entered
        return -1;
    }
    return team_number -1; //-1 to convert to 0-based index
}

//checking players name
int check_player_name(int team_num, char* full_name){
    for(int i=0;i<teams[team_num].player_count;i++){
        if(strcasecmp(teams[team_num].players[i].full_name, full_name)==0){
            return 1; //1 is reurned if there is a duplicate
        }
    }
    return 0; //0 is returned if there isnt a duplicate
}

//checking kit numbers
int check_kit_no(int team_num, int kit_number){
    if (kit_number<1 || kit_number>99)
    {
        handle_error("Invalid kit number. Enter number between 1 and 99.\n"); //error message to be displayed when outside the range 1-99
        return 0;
    }
    
    for(int i=0; i<teams[team_num].player_count;i++){
        if(teams[team_num].players[i].kit_number==kit_number){
            handle_error("A player with this number is already there\n"); //error message to be displayed when there are same kit numbers
            return 0;
        }
    }
    return 1; //kit number is valid
}

//searches the player by their name or kit number
void search_update(){
    if (num_enrolled_clubs==0){ //enusres that a club is enrolled first
        handle_error("Enroll Teams First"); //error message to be dislpayed if no clubs enrolled
        return;
    }
    
    int search_choice;
    printf("Search for a player by:\n1. Kit Number\n2. Name\nEnter your choice (1-2):");
    scanf("%d",&search_choice);
    getchar();

    int x=0; //to keep track of the player searched
    if (search_choice == 1){ //user decides to search by kit number
        int kit_number;
        printf("Enter the kit number: ");
        scanf("%d", &kit_number);
        getchar();

        for (int i = 0; i < num_enrolled_clubs && !x; i++){
            for (int j = 0; j < teams[i].player_count; j++){
                if (teams[i].players[j].kit_number == kit_number){ //checking the structure for the same kit number
                    printf("Player found is in the team %s:\n", teams[i].club_name); //shows the found player and their respective club
                    printf("Do you want to update player details\n1. Yes\n2.No\nEnter your choice: "); //prompts the user to want to update player details or not
                    int update_choice;
                    scanf("%d", &update_choice);
                    getchar();
                    if (update_choice == 1){
                        update_player(i, j); //calls the update_player function to update details
                    }
                    x = 1;
                    break;
                }
            }
        }
    }else if (search_choice == 2){ //user decides to search by player name
        char player_name[50];
        printf("Enter the player's name: ");
        if (fgets(player_name, sizeof(player_name), stdin) == NULL){ //reads the player name entered
            handle_error("Error reading player name.\n"); //error message to be displayed
            return;
        }
        player_name[strcspn(player_name, "\n")] = '\0'; //removes new line character

        for (int i = 0; i < num_enrolled_clubs && !x; i++){
            for (int j = 0; j < teams[i].player_count; j++){
                if (strcasecmp(teams[i].players[j].full_name, player_name) == 0){ //checking the structure for same name
                    printf("Player found is in the team %s:\n", teams[i].club_name); //prints the club in which the player is found
                    printf("Do you want to update player details\n1. Yes\n2.No\nEnter your choice: "); //prompts the user to want to update player details or not
                    int update_choice;
                    scanf("%d", &update_choice);
                    getchar();
                    if (update_choice == 1){
                        update_player(i, j); //calls the update_player function to update details
                    }
                    x = 1;
                    break;
                }
            }
        }
    }else{
        handle_error("Wrong input\n"); //error message to be displayed
        return;
    }
    if(!x){
        handle_error("Player not found\n"); //error message to be displayed
    }
}

//called when user decides to update the searched players details (name, kit number, DoB, position)
void update_player(int team_num, int player_num){
    int choice;
    printf("1. Update Name\n2. Update Kit Number\n3. Update DOB\n4. Update Position\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1){ //updating name
        printf("Enter new name: ");
        if (fgets(teams[team_num].players[player_num].full_name, sizeof(teams[team_num].players[player_num].full_name), stdin) == NULL){
            handle_error("Error reading name.\n");
            return;
        }
        teams[team_num].players[player_num].full_name[strcspn(teams[team_num].players[player_num].full_name, "\n")] = '\0';
        printf("Player name updated.\n");
    }else if (choice == 2){ //updating kit number
        printf("Enter new kit number: ");
        int new_kit_no;
        scanf("%d", &new_kit_no);
        getchar();
        if (!check_kit_no(team_num, new_kit_no)){ //checking if the new kit number matches the criterias
            handle_error("Invalid or duplicate kit number.\n");
            return;
        }
        teams[team_num].players[player_num].kit_number = new_kit_no;
        printf("Kit number updated\n");
    }else if (choice == 3){ //updating date of birth
        printf("Enter new DOB (DD MM YYYY): ");
        int day, month, year;
        scanf("%d %d %d", &day, &month, &year);
        getchar();

        //storint the new DoB in the structure
        teams[team_num].players[player_num].dob.day = day;
        teams[team_num].players[player_num].dob.month = month;
        teams[team_num].players[player_num].dob.year = year;
        printf("DOB updated to %02d/%02d/%04d.\n", day, month, year);
    }else if (choice == 4){ //updating the position
        printf("Enter new position: ");
        if (fgets(teams[team_num].players[player_num].position, sizeof(teams[team_num].players[player_num].position), stdin) == NULL) {
            handle_error("Error reading position.\n");
            return;
        }
        teams[team_num].players[player_num].position[strcspn(teams[team_num].players[player_num].position, "\n")] = '\0';
        printf("Position updated.\n");
    } 
    else {
        handle_error("Invalid choice."); //error message to be displayed
    }
}

//displays the clubs stats
void display_club_stats(){
    if (num_enrolled_clubs == 0){
        handle_error("No teams have been enrolled yet.\n");
        return;
    }

    for (int i = 0; i < num_enrolled_clubs; i++){
        printf("\nTeam: %s\n", teams[i].club_name);
        printf("Number of players: %d\n", teams[i].player_count);

        if (teams[i].player_count == 0){
            handle_error("No players in this team.\n");
        }else{
            for (int j = 0; j < teams[i].player_count; j++){
                player_t player = teams[i].players[j];

                printf("  Player %d: Name: %s, Kit Number: %d, DOB: %02d/%02d/%04d, Position: %s\n", j + 1, player.full_name, player.kit_number, player.dob.day, 
                player.dob.month, player.dob.year, player.position); //prints the players stats
            }

            //calculate and prints the average age of the team.
            double avg_age = calculate_average_age(i);
            printf("Average age of the team: %.2f years\n\n", avg_age);
        }
    }
}

//to get the current year for calculating the avg age
int get_current_year(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    return tm.tm_year + 1900;
}

//calculating the current average age
double calculate_average_age(int team_num){
    if (teams[team_num].player_count == 0){
        return 0.0;
    }

    int total_age = 0;
    int current_year = get_current_year();

    for (int i = 0; i < teams[team_num].player_count; i++){
        total_age += (current_year - teams[team_num].players[i].dob.year);
    }

    return (double) total_age / teams[team_num].player_count;
}

//fucntion that prints and handles all the errors messages
void handle_error(const char *message){
    printf("Error: %s\n", message);
}