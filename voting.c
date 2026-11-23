// voting.c - Student 4 - Voting Logic (Most Important)
#include "common.h"

void castVote() {
    int voterID, candID;
    printf(YELLOW "\n--- Cast Vote ---\n" RESET);
    printf("Enter Your Voter ID: "); scanf("%d", &voterID);
    clearBuffer();
    int vIdx = findVoterByID(voterID);//call function if not registered give -1
    if (vIdx == -1) { printf(RED "You are not registered!\n" RESET); return; }
    if (voters[vIdx].hasVoted) { printf(RED "ERROR: You already voted! Double voting not allowed.\n" RESET); return; }

    printf(CYAN "Voter: %s | Constituency: %s\n" RESET, voters[vIdx].name, voters[vIdx].constituency);
    printf("\nCandidates in your constituency:\n");
    int any = 0;
    for (int i = 0; i < candidateCount; i++) {
        if (strcmp(candidates[i].constituency, voters[vIdx].constituency) == 0) {//compare both string if equal give 0
            printf("ID %d - %s (%s) Symbol: %s | Votes: %d\n", candidates[i].candidateID, candidates[i].name, candidates[i].party, candidates[i].symbol, candidates[i].votes);
            any = 1;
        }
    }
    if (any==0) { printf("No candidates in your constituency yet.\n"); return; }

    printf("Enter Candidate ID to vote for: "); scanf("%d", &candID);
    clearBuffer();
    int cIdx = findCandidateByID(candID);
    //check for candidate id 
    if (cIdx == -1) { printf(RED "Invalid Candidate ID!\n" RESET); return; }
    if (strcmp(candidates[cIdx].constituency, voters[vIdx].constituency) != 0) {//check for constituency if equal give zero else says different constituency 
        printf(RED "Cannot vote! Candidate is from different constituency.\n" RESET);
        return;
    }
    candidates[cIdx].votes++;//increment voter eg hamza has 6 vote now has 7
    voters[vIdx].hasVoted = 1;
    voters[vIdx].votedFor = candID;
    saveData();
    printf(GREEN "Vote Cast Successfully for %s! Thank you.\n" RESET, candidates[cIdx].name);
    printf("Press Enter to return to menu");
    getchar();
}

void showResults() {
    if (candidateCount == 0) {
        printf("%sNo candidates.\n%s", RED, RESET);
        printf("\n--------------------------------\n");
        printf("Press Enter to return to menu");
        getchar();
        return;
    }

    printf("%s\n========== ELECTION RESULTS ==========\n%s", YELLOW, RESET);
    printf("ID | Name | Party | Constituency | Symbol | Votes\n");
    printf("-----------------------------------------------\n");

    int totalVotes = 0;
    for (int i = 0; i < candidateCount; i++) {
        printf("%d | %s | %s | %s | %s | %d\n",
               candidates[i].candidateID, candidates[i].name,
               candidates[i].party, candidates[i].constituency,
               candidates[i].symbol, candidates[i].votes);
        totalVotes += candidates[i].votes;
    }

    printf("-----------------------------------------------\n");
    printf("Total Votes Cast: %d\n", totalVotes);
    printf("Total Voters: %d\n", voterCount);

    printf("\n--------------------------------\n");
    printf("Press Enter to return to menu");
    getchar();


    printf(CYAN "Total Votes Cast: %d / Total Voters: %d\n" RESET, totalVotes, voterCount);

}
