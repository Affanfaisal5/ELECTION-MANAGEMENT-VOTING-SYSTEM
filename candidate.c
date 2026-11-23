// candidate.c - Student 3 - Candidate Management
#include "common.h"

int findCandidateByID(int id) {// function declaration
    Candidate *ptr = candidates;// creating a pointer that point to the first position of candidate array
    for (int i = 0; i < candidateCount; i++) {
        if ((ptr + i)->candidateID == id) return i;//condition to access individual element and compare it
    }
    return -1;
}

void addCandidate() {
    if (candidateCount >= MAX_CANDIDATES) {
        printf("%sCandidate list is full!\n%s", RED, RESET);//red is used to display message in red color which reset
        printf("\n--------------------------------\n");
        printf("Press Enter to return to menu");
        getchar();//used so that they input enter scanf doesnot consume new line
        return;
    }

    Candidate c;//variable for sttucture type candidate
    printf("Enter Candidate ID: ");
    scanf("%d", &c.candidateID);
    clearBuffer();//remove the new line input

    if (findCandidateByID(c.candidateID) != -1) {//find candidate previous function which search for candidate id takes our input if it returns anything means candidate found 
        printf("%sCandidate ID already exists!\n%s", RED, RESET);
        printf("\n--------------------------------\n");
        printf("Press Enter to return to menu");
        getchar();
        return;
    }

    printf("Enter Candidate Name: ");
    fgets(c.name, sizeof(c.name), stdin);//takes input
    c.name[strcspn(c.name, "\n")] = 0;//remove new line first find 

    printf("Enter Party: ");
    fgets(c.party, sizeof(c.party), stdin);
    c.party[strcspn(c.party, "\n")] = 0;

    printf("Enter Constituency: ");
    fgets(c.constituency, sizeof(c.constituency), stdin);
    c.constituency[strcspn(c.constituency, "\n")] = 0;

    printf("Enter Symbol: ");
    fgets(c.symbol, sizeof(c.symbol), stdin);
    c.symbol[strcspn(c.symbol, "\n")] = 0;

    c.votes = 0;//for all new member 
    candidates[candidateCount] = c;//go in candidate array and store in this podition
    candidateCount++;
    saveData();//save file 

    printf("%sCandidate Added! Name: %s | Party: %s | Constituency: %s | Symbol: %s\n%s",
           GREEN, c.name, c.party, c.constituency, c.symbol, RESET);//green change colour it print like
    //name affan
    //PTI
    //na-235
    //symbol laptop 

    printf("\n--------------------------------\n");
    printf("Press Enter to return to menu");
    getchar();
}
//display candidate display all candidate list
void displayCandidates() {
    if (candidateCount == 0) { printf("No candidates found.\n"); return; }
    printf("\n%-8s %-25s %-15s %-12s %-12s %-6s\n", "ID", "Name", "Party", "Constituency", "Symbol", "Votes");//make heading above
    printf("------------------------------------------------------------------------------------\n");
    for (int i = 0; i < candidateCount; i++) {
        printf("%-8d %-25s %-15s %-12s %-12s %-6d\n", candidates[i].candidateID, candidates[i].name, candidates[i].party, candidates[i].constituency, candidates[i].symbol, candidates[i].votes);
    }
    printf("\n--------------------------------\n");
    printf("Press Enter to return to menu");
    getchar();
}
//it searches by either id or party
void searchCandidate() {
    int opt;
    printf("Search by: 1. ID  2. Party\nEnter: ");
    scanf("%d", &opt);
    clearBuffer();
    if (opt == 1) {
        int id; printf("Enter Candidate ID: "); scanf("%d", &id); clearBuffer();
        int idx = findCandidateByID(id);
        if (idx == -1) printf("%sNot found!\n%s", RED, RESET);
        else printf("%sFound: %s | %s | %s | Symbol: %s | Votes: %d\n%s", GREEN, candidates[idx].name, candidates[idx].party, candidates[idx].constituency, candidates[idx].symbol, candidates[idx].votes, RESET);
    } if(opt ==2){
        char party[50]; printf("Enter Party: "); fgets(party, sizeof(party), stdin); party[strcspn(party, "\n")] = 0;
        int found = 0;
        for (int i = 0; i < candidateCount; i++) {
            if (strstr(candidates[i].party, party) != NULL) {//strstr compare stings means if in party is tiger and party also have tiger it diidnot return null
                printf("Found: ID %d - %s | %s | Votes %d\n", candidates[i].candidateID, candidates[i].name, candidates[i].constituency, candidates[i].votes);
                found = 1;
            }
        }
    }
        else{
             printf("%sNo candidate of that party.\n%s", RED, RESET);
    }
    printf("\n--------------------------------\n");
    printf("Press Enter to return to menu");
    getchar();
}
//searches for candidate id
//update new party and new symbol matlab bande ko agar naya symbol dlana ho tu update karsakta ha
void updateCandidate() {
    int id; printf("Enter Candidate ID to update: "); scanf("%d", &id); clearBuffer();
    int idx = findCandidateByID(id);
    if (idx == -1) { printf("%sNot found!\n%s", RED, RESET); return; }
    printf("Enter New Party: "); fgets(candidates[idx].party, sizeof(candidates[idx].party), stdin); candidates[idx].party[strcspn(candidates[idx].party, "\n")] = 0;
    printf("Enter New Symbol: "); fgets(candidates[idx].symbol, sizeof(candidates[idx].symbol), stdin); candidates[idx].symbol[strcspn(candidates[idx].symbol, "\n")] = 0;
    saveData(); printf("%sCandidate updated!\n%s", GREEN, RESET);
    printf("\n--------------------------------\n");
    printf("Press Enter to return to menu");
    getchar();
}
//delete it first take id input compare it shift right that we want to delete
void deleteCandidate() {
    int id; printf("Enter Candidate ID to delete: "); scanf("%d", &id); clearBuffer();
    int idx = findCandidateByID(id);
    if (idx == -1) { printf("%sNot found!\n%s", RED, RESET); return; }
    for (int i = idx; i < candidateCount - 1; i++)
        candidates[i] = candidates[i + 1];//remove that want to delete means shift it into most right
    candidateCount--; saveData(); printf("%sCandidate deleted!\n%s", GREEN, RESET);
    printf("\n--------------------------------\n");
    printf("Press Enter to return to menu");
    getchar();
}
