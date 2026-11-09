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

void showResults() {
    if (candidateCount == 0) { printf("No candidates.\n"); return; }
    sortCandidatesByVotes();
    printf("\n--- LIVE RESULTS (Sorted by Votes) ---\n");
    displayCandidates();
    int total = 0;
    for (int i = 0; i < candidateCount; i++) total += candidates[i].votes;
    printf("\nTotal Votes Cast: %d / %d Voters\n", total, voterCount);
}

void showWinner() {
    if (candidateCount == 0) { printf("No candidates.\n"); return; }
    sortCandidatesByVotes();
    printf("\n--- WINNER ---\n");
    printf("WINNER: %s (%s) - %s - %d Votes - Symbol: %s\n",
        candidates[0].name, candidates[0].party,
        candidates[0].constituency, candidates[0].votes, candidates[0].symbol);
    if (candidateCount > 1 && candidates[1].votes == candidates[0].votes)
        printf("Note: TIE with %s!\n", candidates[1].name);
}

int main() {
    int choice;
    loadData();
    while (1) {
        printf("\n================================================\n");
        printf("   ELECTION VOTING MANAGEMENT SYSTEM - CS-112\n");
        printf("================================================\n");
        printf("1. Add New Voter (S2)\n2. Display All Voters (S2)\n3. Search Voter (S2)\n4. Update Voter (S2)\n5. Delete Voter (S2)\n");
        printf("6. Add New Candidate (S3)\n7. Display All Candidates (S3)\n8. Search Candidate (S3)\n9. Update Candidate (S3)\n10. Delete Candidate (S3)\n");
        printf("11. Cast Vote (S4)\n12. Show Election Results (S1)\n13. Show Winner (S1)\n14. Save & Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) { printf("Invalid input!\n"); clearBuffer(); continue; }
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
            case 14: saveData(); printf("Data saved. Bye!\n"); return 0;
            default: printf("Invalid choice!\n");
        }
    }
}