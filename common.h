// common.h - Student 1 - Core Structures
#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VOTERS 200
#define MAX_CANDIDATES 100
#define VOTER_FILE "voters.dat"
#define CANDIDATE_FILE "candidates.dat"

typedef struct {
    int voterID;
    char name[100];
    char cnic[20];
    int age;
    char constituency[50];
    int hasVoted; // 0 = No, 1 = Yes
    int votedFor;
} Voter;

typedef struct {
    int candidateID;
    char name[100];
    char party[50];
    char constituency[50];
    char symbol[30];
    int votes;
} Candidate;

// Globals - defined in main.c
extern Voter voters[MAX_VOTERS];
extern int voterCount;
extern Candidate candidates[MAX_CANDIDATES];
extern int candidateCount;

// Prototypes - Student 1
void loadData();
void saveData();
void clearBuffer();
void showResults();
void showWinner();
void sortCandidatesByVotes();

// Prototypes - Student 2
int findVoterByID(int id);
int findVoterByCNIC(char *cnic);
void addVoter();
void displayVoters();
void searchVoter();
void updateVoter();
void deleteVoter();

// Prototypes - Student 3
int findCandidateByID(int id);
void addCandidate();
void displayCandidates();
void searchCandidate();
void updateCandidate();
void deleteCandidate();

// Prototypes - Student 4
void castVote();

#endif