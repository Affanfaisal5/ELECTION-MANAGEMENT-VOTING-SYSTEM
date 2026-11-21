// main.c - Student 1 - Main Menu + Integration + File Handling
#include "common.h"

Voter voters[MAX_VOTERS];
int voterCount = 0;
Candidate candidates[MAX_CANDIDATES];
int candidateCount = 0;

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void loadData() {
    FILE *fp = fopen(VOTER_FILE, "rb");
    if (fp != NULL) {
        fread(&voterCount, sizeof(int), 1, fp);
        fread(voters, sizeof(Voter), voterCount, fp);
        fclose(fp);
    }
    fp = fopen(CANDIDATE_FILE, "rb");
    if (fp != NULL) {
        fread(&candidateCount, sizeof(int), 1, fp);
        fread(candidates, sizeof(Candidate), candidateCount, fp);
        fclose(fp);
    }
    printf("Loaded %d voter(s) and %d candidate(s).\n", voterCount, candidateCount);
}

void saveData() {
    FILE *fp = fopen(VOTER_FILE, "wb");
    if (fp != NULL) {
        fwrite(&voterCount, sizeof(int), 1, fp);
        fwrite(voters, sizeof(Voter), voterCount, fp);
        fclose(fp);
    }
    fp = fopen(CANDIDATE_FILE, "wb");
    if (fp != NULL) {
        fwrite(&candidateCount, sizeof(int), 1, fp);
        fwrite(candidates, sizeof(Candidate), candidateCount, fp);
        fclose(fp);
    }
}

void sortCandidatesByVotes() {
    for (int i = 0; i < candidateCount - 1; i++) {
        for (int j = 0; j < candidateCount - i - 1; j++) {
            if (candidates[j].votes < candidates[j + 1].votes) {
                Candidate temp = candidates[j];
                candidates[j] = candidates[j + 1];
                candidates[j + 1] = temp;
            }
        }
    }
}

void showWinner() {
    if (candidateCount == 0) { printf("%sNo candidates.\n%s", RED, RESET); return; }
    printf("%s\n========== ELECTION WINNERS ==========\n%s", YELLOW, RESET);
    char constituencies[100][50];
    int constCount = 0;
    for (int i = 0; i < candidateCount; i++) {
        int found = 0;
        for (int j = 0; j < constCount; j++) {
            if (strcmp(constituencies[j], candidates[i].constituency) == 0) { found = 1; break; }
        }
        if (!found) {
            strcpy(constituencies[constCount], candidates[i].constituency);
            constCount++;
        }
    }
    char parties[100][50];
    int partyWins[100] = {0};
    int partyCount = 0;
    for (int c = 0; c < constCount; c++) {
        int bestIdx = -1;
        int bestVotes = -1;
        for (int i = 0; i < candidateCount; i++) {
            if (strcmp(candidates[i].constituency, constituencies[c]) == 0) {
                if (candidates[i].votes > bestVotes) { bestVotes = candidates[i].votes; bestIdx = i; }
            }
        }
        if (bestIdx != -1) {
            printf("\nWinner %s: %s (%s) - %d Votes",
                   constituencies[c], candidates[bestIdx].name,
                   candidates[bestIdx].party, candidates[bestIdx].votes);
            int pFound = 0;
            for (int p = 0; p < partyCount; p++) {
                if (strcmp(parties[p], candidates[bestIdx].party) == 0) { partyWins[p]++; pFound = 1; break; }
            }
            if (!pFound) {
                strcpy(parties[partyCount], candidates[bestIdx].party);
                partyWins[partyCount] = 1;
                partyCount++;
            }
        }
    }
    printf("\n\n--------------------------------\n");
    printf("--- PARTY RESULTS (Constituencies Won) ---\n");
    int bestParty = 0;
    for (int p = 0; p < partyCount; p++) {
        printf("%s : %d constituency(s) won\n", parties[p], partyWins[p]);
        if (partyWins[p] > partyWins[bestParty]) bestParty = p;
    }
    printf("%s\n>>> OVERALL WINNER (Party): %s with %d constituency(s) <<<\n%s",
           GREEN, parties[bestParty], partyWins[bestParty], RESET);
    printf("This party forms the government.\n");
    printf("\n--------------------------------\n");
    printf("Press Enter to return to menu");
    getchar();
}

int main() {
    int choice;
    loadData();
    while (1) {
        printf("%s\n================================================\n", YELLOW);
        printf("   ELECTION VOTING MANAGEMENT SYSTEM - CS-112\n");
        printf("================================================\n%s", RESET);
        printf("1. Add New Voter (S2)\n2. Display All Voters (S2)\n3. Search Voter (S2)\n4. Update Voter (S2)\n5. Delete Voter (S2)\n");
        printf("6. Add New Candidate (S3)\n7. Display All Candidates (S3)\n8. Search Candidate (S3)\n9. Update Candidate (S3)\n10. Delete Candidate (S3)\n");
        printf("11. Cast Vote (S4)\n12. Show Election Results (S1)\n13. Show Winner (S1)\n14. Save & Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) { printf("%sInvalid input!\n%s", RED, RESET); clearBuffer(); continue; }
        clearBuffer();
        switch (choice) {
            case 1: addVoter(); break;
            case 2: displayVoters(); break;
            case 3: searchVoter(); break;
            case 4: updateVoter(); break;
            case 5: deleteVoter(); break;
            case 6: addCandidate(); break;
            case 7: displayCandidates(); break;
            case 8: searchCandidate(); break;
            case 9: updateCandidate(); break;
            case 10: deleteCandidate(); break;
            case 11: castVote(); break;
            case 12: showResults(); break;
            case 13: showWinner(); break;
            case 14: saveData(); printf("%sData saved. Bye!\n%s", GREEN, RESET); return 0;
            default: printf("%sInvalid choice!\n%s", RED, RESET);
        }
    }
}
