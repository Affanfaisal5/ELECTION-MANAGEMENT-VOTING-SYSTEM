// voter.c - Student 2 - Voter Registration + CRUD
#include "common.h"

int findVoterByID(int id) {
    Voter *ptr = voters;
    for (int i = 0; i < voterCount; i++) {
        if ((ptr + i)->voterID == id) return i;
    }
    return -1;
}
int findVoterByCNIC(char *cnic) {
    for (int i = 0; i < voterCount; i++) {
        if (strcmp(voters[i].cnic, cnic) == 0) return i;
    }
    return -1;
}

void addVoter() {
    if (voterCount >= MAX_VOTERS) { printf(RED "Voter list full!\n" RESET); return; }
    Voter v;
    printf(YELLOW "\n--- Add New Voter ---\n" RESET);
    printf("Enter Voter ID: ");
    if(scanf("%d", &v.voterID) != 1){ printf(RED "Invalid ID input!\n" RESET); clearBuffer(); return; }
    clearBuffer();
    if (v.voterID <= 0) { printf(RED "Invalid ID! Must be > 0\n" RESET); return; }
    if (findVoterByID(v.voterID) != -1) { printf(RED "ID already exists! Try ID %d\n" RESET, v.voterID + 1); return; }

    printf("Enter Full Name: ");
    fgets(v.name, sizeof(v.name), stdin);
    v.name[strcspn(v.name, "\n")] = 0;
    if(strlen(v.name) == 0){ printf(RED "Name cannot be empty! Try again.\n" RESET); return; }

    printf("Enter CNIC (13 digits, no dashes): ");
    fgets(v.cnic, sizeof(v.cnic), stdin);
    v.cnic[strcspn(v.cnic, "\n")] = 0;
    printf("You entered CNIC: '%s' Length = %d\n", v.cnic, (int)strlen(v.cnic));
    if (strlen(v.cnic) != 13) { printf(RED "Invalid CNIC! Must be exactly 13 digits.\n" RESET); return; }
    if (findVoterByCNIC(v.cnic) != -1) { printf(RED "CNIC already registered! Use different CNIC.\n" RESET); return; }

    printf("Enter Age: ");
    if(scanf("%d", &v.age) != 1){ printf(RED "Invalid Age!\n" RESET); clearBuffer(); return; }
    clearBuffer();
    if (v.age < 18) { printf(RED "Not eligible! Must be 18+.\n" RESET); return; }

    printf("Enter Constituency (e.g. NA-247): ");
    fgets(v.constituency, sizeof(v.constituency), stdin);
    v.constituency[strcspn(v.constituency, "\n")] = 0;

    v.hasVoted = 0; v.votedFor = 0;
    voters[voterCount++] = v;
    saveData();
    printf(GREEN "Voter Registered Successfully! Total voters now = %d\n" RESET, voterCount);
    printf("\n--------------------------------\n");
    printf("Press Enter to return to menu");
    getchar();
}

void displayVoters() {
    if (voterCount == 0) { printf("No voters found.\n"); return; }
    printf("\n%-8s %-25s %-15s %-5s %-12s %-10s\n", "ID", "Name", "CNIC", "Age", "Constituency", "Status");
    printf("--------------------------------------------------------------------------------\n");
    for (int i = 0; i < voterCount; i++) {
        printf("%-8d %-25s %-15s %-5d %-12s %-10s\n", voters[i].voterID, voters[i].name, voters[i].cnic, voters[i].age, voters[i].constituency, voters[i].hasVoted ? "Voted" : "Not Voted");
    }
    printf("\n-------------------------------------------------------------------------\n");
    printf("Press Enter to return to menu");
    getchar();
}

void searchVoter() {
    int opt;
    printf("Search by: 1. ID  2. CNIC\nEnter: ");
    scanf("%d", &opt);
    clearBuffer();

    if (opt == 1) {
        int id;
        printf("Enter Voter ID: ");
        scanf("%d", &id);
        clearBuffer();
        int idx = findVoterByID(id);
        if (idx == -1) {
            printf(RED "Not found!\n" RESET);
        } else {
            printf(GREEN "Found: %s | CNIC %s | %s | %s\n" RESET,
                   voters[idx].name,
                   voters[idx].cnic,
                   voters[idx].constituency,
                   voters[idx].hasVoted ? "Voted" : "Not Voted");
        }
    }
    else if (opt == 2) {
        char cnic[20];
        printf("Enter CNIC: ");
        fgets(cnic, sizeof(cnic), stdin);
        cnic[strcspn(cnic, "\n")] = 0;
        int idx = findVoterByCNIC(cnic);
        if (idx == -1) {
            printf(RED "Not found!\n" RESET);
        } else {
            printf(GREEN "Found: ID %d - %s | %s\n" RESET,
                   voters[idx].voterID,
                   voters[idx].name,
                   voters[idx].constituency);
        }
    }
    else {
        printf(RED "Invalid option!\n" RESET);
    }
    printf("\nPress Enter to return to menu");
    getchar();
}


void updateVoter() {
    int id;
    printf("Enter Voter ID to update: ");
    scanf("%d", &id);
    clearBuffer();

    int idx = findVoterByID(id);
    if (idx == -1) {
        printf("%sNot found!\n%s", RED, RESET);
        printf("\n--------------------------------\n");
        printf("Press Enter to return to menu");
        getchar();
        return;
    }

    printf("Current Name: %s | Constituency: %s\n",
           voters[idx].name, voters[idx].constituency);

    printf("Enter New Name: ");
    fgets(voters[idx].name, sizeof(voters[idx].name), stdin);
    voters[idx].name[strcspn(voters[idx].name, "\n")] = 0;

    printf("Enter New Constituency: ");
    fgets(voters[idx].constituency, sizeof(voters[idx].constituency), stdin);
    voters[idx].constituency[strcspn(voters[idx].constituency, "\n")] = 0;

    saveData();
    printf("%sVoter Updated! Name updated to: %s\n%s", GREEN, voters[idx].name, RESET);

    printf("\n--------------------------------\n");
    printf("Press Enter to return to menu");
    getchar();
}

void deleteVoter() {
    int id;
    printf("Enter Voter ID to delete: ");
    scanf("%d", &id);
    clearBuffer();

    int idx = findVoterByID(id);
    if (idx == -1) {
        printf("%sNot found!\n%s", RED, RESET);
        printf("\n--------------------------------\n");
        printf("Press Enter to return to menu");
        getchar();
        return;
    }

    for (int i = idx; i < voterCount - 1; i++) {
        voters[i] = voters[i + 1];
    }
    voterCount--;
    saveData();
    printf("%sVoter deleted!\n%s", GREEN, RESET);

    printf("\n--------------------------------\n");
    printf("Press Enter to return to menu");
    getchar();
}
