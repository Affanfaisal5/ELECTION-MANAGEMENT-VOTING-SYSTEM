// voting.c - Student 4 - Voting Logic (Most Important)
#include "common.h"

void castVote() {
    int voterID, candID;
    printf("\n--- Cast Vote ---\n");
    printf("Enter Your Voter ID: "); scanf("%d", &voterID);
    int vIdx = findVoterByID(voterID);
    if (vIdx == -1) { printf("You are not registered!\n"); return; }
    if (voters[vIdx].hasVoted) { printf("ERROR: You already voted! Double voting not allowed.\n"); return; }

    printf("Voter: %s | Constituency: %s\n", voters[vIdx].name, voters[vIdx].constituency);
    printf("\nCandidates in your constituency:\n");
    int any = 0;
    for (int i = 0; i < candidateCount; i++) {
        if (strcmp(candidates[i].constituency, voters[vIdx].constituency) == 0) {
            printf("ID %d - %s (%s) Symbol: %s | Votes: %d\n", candidates[i].candidateID, candidates[i].name, candidates[i].party, candidates[i].symbol, candidates[i].votes);
            any = 1;
        }
    }
    if (!any) { printf("No candidates in your constituency yet.\n"); return; }

    printf("Enter Candidate ID to vote for: "); scanf("%d", &candID);
    int cIdx = findCandidateByID(candID); // FIX: Never use candidates[id-1]
    if (cIdx == -1) { printf("Invalid Candidate ID!\n"); return; }
    if (strcmp(candidates[cIdx].constituency, voters[vIdx].constituency) != 0) {
        printf("Cannot vote! Candidate is from different constituency.\n");
        return;
    }
    candidates[cIdx].votes++;
    voters[vIdx].hasVoted = 1;
    voters[vIdx].votedFor = candID;
    saveData();
    printf("Vote Cast Successfully for %s! Thank you.\n", candidates[cIdx].name);
}