// voter.c - Student 2 - Voter Registration + CRUD
#include "common.h"

int findVoterByID(int id) {
    Voter *ptr = voters; // Pointer usage for rubric
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
    if (voterCount >= MAX_VOTERS) { printf("Voter list full!\n"); return; }
    Voter v;
    printf("\n--- Add New Voter ---\n");
    printf("Enter Voter ID: "); scanf("%d", &v.voterID); clearBuffer();
    if (v.voterID <= 0) { printf("Invalid ID!\n"); return; }
    if (findVoterByID(v.voterID) != -1) { printf("ID already exists!\n"); return; }
    printf("Enter Full Name: "); fgets(v.name, sizeof(v.name), stdin);
    v.name[strcspn(v.name, "\n")] = 0;
    printf("Enter CNIC (13 digits, no dashes): "); fgets(v.cnic, sizeof(v.cnic), stdin);
    v.cnic[strcspn(v.cnic, "\n")] = 0;
    if (strlen(v.cnic) != 13) { printf("Invalid CNIC! Must be 13 digits.\n"); return; }
    if (findVoterByCNIC(v.cnic) != -1) { printf("CNIC already registered!\n"); return; }
    printf("Enter Age: "); scanf("%d", &v.age); clearBuffer();
    if (v.age < 18) { printf("Not eligible! Must be 18+.\n"); return; }
    printf("Enter Constituency (e.g. NA-247): "); fgets(v.constituency, sizeof(v.constituency), stdin);
    v.constituency[strcspn(v.constituency, "\n")] = 0;
    v.hasVoted = 0; v.votedFor = 0;
    voters[voterCount++] = v;
    saveData();
    printf("Voter Registered Successfully!\n");
}

void displayVoters() {
    if (voterCount == 0) { printf("No voters found.\n"); return; }
    printf("\n%-8s %-25s %-15s %-5s %-12s %-10s\n", "ID", "Name", "CNIC", "Age", "Constituency", "Status");
    printf("--------------------------------------------------------------------------------\n");
    for (int i = 0; i < voterCount; i++) {
        printf("%-8d %-25s %-15s %-5d %-12s %-10s\n", voters[i].voterID, voters[i].name, voters[i].cnic, voters[i].age, voters[i].constituency, voters[i].hasVoted ? "Voted" : "Not Voted");
    }
}

void searchVoter() {
    int opt; printf("Search by: 1. ID  2. CNIC\nEnter: "); scanf("%d", &opt); clearBuffer();
    if (opt == 1) {
        int id; printf("Enter Voter ID: "); scanf("%d", &id);
        int idx = findVoterByID(id);
        if (idx == -1) printf("Not found!\n");
        else printf("Found: %s | CNIC %s | %s | %s\n", voters[idx].name, voters[idx].cnic, voters[idx].constituency, voters[idx].hasVoted ? "Voted" : "Not Voted");
    } else if (opt == 2) {
        char cnic[20]; printf("Enter CNIC: "); fgets(cnic, sizeof(cnic), stdin); cnic[strcspn(cnic, "\n")] = 0;
        int idx = findVoterByCNIC(cnic);
        if (idx == -1) printf("Not found!\n");
        else printf("Found: ID %d - %s | %s\n", voters[idx].voterID, voters[idx].name, voters[idx].constituency);
    }
}

void updateVoter() {
    int id; printf("Enter Voter ID to update: "); scanf("%d", &id); clearBuffer();
    int idx = findVoterByID(id);
    if (idx == -1) { printf("Not found!\n"); return; }
    printf("Current Name: %s\nEnter New Name: ", voters[idx].name);
    fgets(voters[idx].name, sizeof(voters[idx].name), stdin);
    voters[idx].name[strcspn(voters[idx].name, "\n")] = 0;
    printf("Enter New Constituency: ");
    fgets(voters[idx].constituency, sizeof(voters[idx].constituency), stdin);
    voters[idx].constituency[strcspn(voters[idx].constituency, "\n")] = 0;
    saveData(); printf("Voter updated!\n");
}

void deleteVoter() {
    int id; printf("Enter Voter ID to delete: "); scanf("%d", &id);
    int idx = findVoterByID(id);
    if (idx == -1) { printf("Not found!\n"); return; }
    for (int i = idx; i < voterCount - 1; i++) voters[i] = voters[i + 1];
    voterCount--; saveData(); printf("Voter deleted!\n");
}