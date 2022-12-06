//
// Created by Jessica Halvorsen, Maggie Thompson, and Robert Noble on 12/01/22.
//
#include <iostream>
#include <algorithm>
#include <chrono>
#include "SongRec.h"
using namespace std;
using namespace std::chrono;

int main() {

    
    //1. read in csv file and create book struct
    SongRec songs;
    songs.readCSV("songs.csv");


    //2. welcome the user to the song recommender
    cout << "Welcome to the Song Recommender!" << endl;
    cout << "******************************************" << endl;

    // 3. ask the user to rank which criteria are most important to them
    //    danceability, energy, loudness, mode, acousticness, valence, tempo

    cout << "Which factors are most important to you? (rank in order ex: 231456)" << endl;
    cout << "1. Danceability \n2. Energy \n3. Mode \n4. Acousticness \n5. Valence \n6. Tempo\n";


    //4. based on their ranking, ask for their choices for each option
    //   and perform the associated method to add points to matching books
    //   maybe use a for loop here to iterate through their ranking in order
    //  start at 30, decrement by 5 with each iteration through loop

    string factorsRank, mode;
    int danceRank, energyRank, acousticRank, valenceRank, tempoRank;
    int numPoints = 30;

    cin >> factorsRank;
    for (int i = 0; i < 6; i++) {
        if (factorsRank[i] == '1') {
            cout << "On a scale of 1-10, how much would you like to be able to dance to your songs? (1-no dancing, 10-lots of dancing)" << endl;
            cin >> danceRank;
            songs.dancePoints(danceRank, numPoints);
        }
        if (factorsRank[i] == '2') {
            cout << "Energetic tracks typically feel fast, loud, and noisy. How much energy do you want in your songs on a scale of 1-10? (1-low energy, 10-high energy)"<< endl;
            cin >> energyRank;
            songs.energyPoints(energyRank, numPoints);
        }
        if (factorsRank[i] == '3') {
            cout << "Would you like your songs to be in the major or minor?" << endl;
            cin >> mode;
            songs.modePoints(mode, numPoints);
        }
        if (factorsRank[i] == '4') {
            cout << "How acoustic would you like your songs to be on a scale of 1-10?" << endl;
            cin >> acousticRank;
            songs.acousticPoints(acousticRank, numPoints);
        }
        if (factorsRank[i] == '5') {
            cout << "How positive would you like your songs to be on a scale of 1-10? (Ex: 1-sad, depressed, angry; 10-happy, cheerful, euphoric)" << endl;
            cin >> valenceRank;
            songs.valencePoints(valenceRank, numPoints);
        }
        if (factorsRank[i] == '6') {
            cout << "How fast would you like the tempo of your songs to be?\n"
                    "1. 0-70 BPM\n"
                    "2. 70-100 BPM\n"
                    "3. 100-130 BPM\n"
                    "4. 130-160 BPM\n"
                    "5. 160-190 BPM\n"
                    "6. 190+ BPM" << endl;
            cin >> tempoRank;
            songs.tempoPoints(tempoRank, numPoints);
        }
        numPoints = numPoints-5;
    }

    //time how long it takes to run merge or quick sort 
    //used geeks for geeks for clock method
    //https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
    auto start = high_resolution_clock::now();
    songs.mergeSort(0, songs.listLength() - 1);
    //songs.quickSort(0, songs.listLength() - 1);
    songs.printTopTen();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;

    //5. return a list of the top 10 books for the user
    songs.printTopTen(); 
    return 0;
}
