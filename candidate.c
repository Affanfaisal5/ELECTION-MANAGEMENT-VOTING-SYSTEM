// candidate.c - Student 3 - Candidate Management
#include "common.h"

int findCandidateByID(int id) {
    Candidate *ptr = candidates;
    for (int i = 0; i < candidateCount; i++) {
        if ((ptr + i)->candidateID == id) return i;
    }
    return -1;
}

void addCandidate() {
    if (candidateCount >= MAX_CANDIDATES) { printf("Candidate list full!\n"); return; }
    Candidate c;
    printf("\n--- Add New Candidate ---\n");
    printf("Enter Candidate ID: "); scanf("%d", &c.candidateID); clearBuffer();
    if (c.candidateID <= 0) { printf("Invalid ID!\n"); return; }
    if (findCandidateByID(c.candidateID) != -1) { printf("ID already exists!\n"); return; }
    printf("Enter Candidate Name: "); fgets(c.name, sizeof(c.name), stdin); c.name[strcspn(c.name, "\n")] = 0;
    printf("Enter Party (PTI / PML-N / PPP / Independent): "); fgets(c.party, sizeof(c.party), stdin); c.party[strcspn(c.party, "\n")] = 0;
    printf("Enter Constituency (e.g. NA-247): "); fgets(c.constituency, sizeof(c.constituency), stdin); c.constituency[strcspn(c.constituency, "\n")] = 0;
    printf("Enter Election Symbol (Bat / Arrow / Lion): "); fgets(c.symbol, sizeof(c.symbol), stdin); c.symbol[strcspn(c.symbol, "\n")] = 0;
    c.votes = 0;
    candidates[candidateCount++] = c;
    saveData(); printf("Candidate added!\n");
}

void displayCandidates() {
    if (candidateCount == 0) { printf("No candidates found.\n"); return; }
    printf("\n%-8s %-25s %-15s %-12s %-12s %-6s\n", "ID", "Name", "Party", "Constituency", "Symbol", "Votes");
    printf("------------------------------------------------------------------------------------\n");
    for (int i = 0; i < candidateCount; i++) {
        printf("%-8d %-25s %-15s %-12s %-12s %-6d\n", candidates[i].candidateID, candidates[i].name, candidates[i].party, candidates[i].constituency, candidates[i].symbol, candidates[i].votes);
    }
}

void searchCandidate() {
    int opt; printf("Search by: 1. ID  2. Party\nEnter: "); scanf("%d", &opt); clearBuffer();
    if (opt == 1) {
        int id; printf("Enter Candidate ID: "); scanf("%d", &id);
        int idx = findCandidateByID(id);
        if (idx == -1) printf("Not found!\n");
        else printf("Found: %s | %s | %s | Symbol: %s | Votes: %d\n", candidates[idx].name, candidates[idx].party, candidates[idx].constituency, candidates[idx].symbol, candidates[idx].votes);
    } else {
        char party[50]; printf("Enter Party: "); fgets(party, sizeof(party), stdin); party[strcspn(party, "\n")] = 0;
        int found = 0;
        for (int i = 0; i < candidateCount; i++) {
            if (strstr(candidates[i].party, party) != NULL) {
                printf("Found: ID %d - %s | %s | Votes %d\n", candidates[i].candidateID, candidates[i].name, candidates[i].constituency, candidates[i].votes);
                found = 1;
            }
        }
        if (!found) printf("No candidate of that party.\n");
    }
}

void updateCandidate() {
    int id; printf("Enter Candidate ID to update: "); scanf("%d", &id); clearBuffer();
    int idx = findCandidateByID(id);
    if (idx == -1) { printf("Not found!\n"); return; }
    printf("Enter New Party: "); fgets(candidates[idx].party, sizeof(candidates[idx].party), stdin); candidates[idx].party[strcspn(candidates[idx].party, "\n")] = 0;
    printf("Enter New Symbol: "); fgets(candidates[idx].symbol, sizeof(candidates[idx].symbol), stdin); candidates[idx].symbol[strcspn(candidates[idx].symbol, "\n")] = 0;
    saveData(); printf("Candidate updated!\n");
}

void deleteCandidate() {
    int id; printf("Enter Candidate ID to delete: "); scanf("%d", &id);
    int idx = findCandidateByID(id);
    if (idx == -1) { printf("Not found!\n"); return; }
    for (int i = idx; i < candidateCount - 1; i++) candidates[i] = candidates[i + 1];
    candidateCount--; saveData(); printf("Candidate deleted!\n");
}