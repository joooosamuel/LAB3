#include <stdio.h>
#include <string.h>

#define NUM_TEAMS 5  
#define SQUAD_SIZE 11

typedef struct{
    int day;
    int month;
    int year;
} date_t;

typedef struct{
    char full_name[26];
    int kit_number;
    char club[40];
    date_t dob;
    char position[20];
} player_t;

typedef struct{
    char club_name[21];
    player_t players[SQUAD_SIZE];
    int player_count;
} team_deets;

team_deets teams[NUM_TEAMS];
int num_enrolled_teams = 0;

void display_menu();
void enroll_club();
// void add_player();
// void search_update();
// void display_club_stats();
void handle_error(const char *message);

int main(){
    int selection;

    for(int i = 0; i < NUM_TEAMS; i++){
        teams[i].player_count = 0;
    }

    while (1){
        display_menu();
        scanf("%d", &selection);
        while (getchar() != '\n');  // Clear input buffer
        if(selection == 1){
            enroll_club();
        }else if(selection == 2){
            // add_player();
        }else if(selection == 3){
            // search_update();
        }else if(selection == 4){
            // display_club_stats();
        }else if(selection == 0){
            printf("Exiting...\n");
            break;
        }else{
            printf("Invalid choice. Try again.\n");
        }
    }
}

//Function Definitions
void display_menu(){
   printf("1. Enroll Club\n");
   printf("2. Add a player\n");
   printf("3. Search and update a player\n");
   printf("4. Club Stats\n");
   printf("0. Exit\n");
   printf("Enter your choice (0-4): ");
}

void enroll_club(){
    if(num_enrolled_teams >= NUM_TEAMS){
        handle_error("Maximum number of teams enrolled.");
        return;
    }
    char club_name[21];
    printf("Enter club name: ");
    if(fgets(club_name, sizeof(club_name), stdin) == NULL){
        handle_error("Error reading team name.");
        return;
    }
    club_name[strcspn(club_name, "\n")] = '\0'; 
    if(strlen(club_name) == 0){
        handle_error("You must enter a team name.");
        return;
    }
    for(int i = 0; i < num_enrolled_teams; i++){
        if(strcasecmp(teams[i].club_name, club_name) == 0){
            handle_error("A team with the same name already exists.");
            return;
        }
    }
    strcpy(teams[num_enrolled_teams].club_name, club_name);
    teams[num_enrolled_teams].player_count = 0;
    num_enrolled_teams++;
    printf("Club %s has been enrolled.\n", club_name);
}

void handle_error(const char *message){
    printf("Error: %s\n", message);
}
