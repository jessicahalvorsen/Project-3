//
// Created by Jessica Halvorsen, Maggie Thompson, and Robert Noble on 12/01/22.
//
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include "SongRec.h"
#include <iostream>
using namespace std;

//reads in the CSV file and pushes back a new Song into songList for each line
void SongRec::readCSV(const string& filename) {
    //create file stream
    ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) throw runtime_error("Could not open file");

    // Extract the first line in the file
    string line;
    getline(myFile, line);

    int count = 0;
    //read in all the data line by line
    while(getline(myFile, line)) {

        //create string stream with the current line
        istringstream ss(line);

        //create string temps to read in each variable
        string track, artist, uri, danceability, energy, loudness, mode, speechiness, acousticness,
                valence, tempo, duration, target, decade;

        //read in each column using the | as the delimiter
        getline(ss, track, '|');
        getline(ss, artist, '|');
        getline(ss, uri, '|');
        getline(ss, danceability, '|');
        getline(ss, energy, '|');
        getline(ss, loudness, '|');
        getline(ss, mode, '|');
        getline(ss, speechiness, '|');
        getline(ss, acousticness, '|');
        getline(ss, valence, '|');
        getline(ss, tempo, '|');
        getline(ss, duration, '|');
        getline(ss, target, '|');
        getline(ss, decade, '|');

        //create a new song instance to store the current line's data
        Song newSong;

        //add the strings:
        newSong.track = track;
        newSong.artist = artist;
        newSong.uri = uri;

        //add the doubles:
        newSong.danceability = atof(danceability.c_str());
        newSong.energy = atof(energy.c_str());
        newSong.loudness = atof(loudness.c_str());
        newSong.speechiness = atof(speechiness.c_str());
        newSong.acousticness = atof(acousticness.c_str());
        newSong.valence = atof(valence.c_str());
        newSong.tempo = atof(tempo.c_str());

        //add the ints:
        newSong.mode = stoi(mode);
        newSong.duration = stoi(duration);
        newSong.target = stoi(target);
        newSong.decade = stoi(decade);

        //add the new book to the vector
        //newSong.points = 100000000 - count; //debugging for sorts
        songList.push_back(newSong);
        count++;
    }
}

//allocates points for any Songs that match the danceability choice of user
void SongRec::dancePoints(int choice, int numPoints) {
    //choice must be divided by 10 to match data
    double choiceDec = double(choice) / 10;
    for (Song& song : songList) {
        double diff = abs(choiceDec - song.danceability);
        double minus = diff * numPoints;
        song.points += numPoints - minus;
    }
}

void SongRec::energyPoints(int choice, int numPoints) {
    //choice must be divided by 10 to match data
    double choiceDec = double(choice) / 10;
    for (Song& song : songList) {
        double diff = abs(choiceDec - song.energy);
        double minus = diff * numPoints;
        song.points += numPoints - minus;
    }
}

void SongRec::modePoints(string choice, int numPoints) {
    int choiceInt;
    if (choice == "major")
        choiceInt = 1;
    if (choice == "minor")
        choiceInt = 0;
    for (Song& song : songList) {
        if (song.mode == choiceInt) {
            song.mode += numPoints;
        }
    }
}

void SongRec::acousticPoints(int choice, int numPoints) {
    //choice must be divided by 10 to match data
    double choiceDec = double(choice) / 10;
    for (Song& song : songList) {
        double diff = abs(choiceDec - song.acousticness);
        double minus = diff * numPoints;
        song.points += numPoints - minus;
    }
}

void SongRec::valencePoints(int choice, int numPoints) {
    //choice must be divided by 10 to match data
    double choiceDec = double(choice) / 10;
    for (Song& song : songList) {
        double diff = abs(choiceDec - song.valence);
        double minus = diff * numPoints;
        song.points += numPoints - minus;
    }
}

void SongRec::tempoPoints(int choice, int numPoints) {
    //choice must be multiplied by 20 to match data
    double choiceDec = double(choice) * 20;
    for (Song& song : songList) {
        double diff = abs(choiceDec - song.tempo);
        double minus = diff * numPoints;
        song.points += numPoints - minus;
    }
}

//returns the length of songList
int SongRec::listLength() {
    return songList.size();
}


//used mygreatlearning.com as a resource, link below
//https://www.mygreatlearning.com/blog/merge-sort/#:~:text=Pseudocode%20for%20MergeSort%201%20Declare%20left%20and%20right,we%20will%20call%20merge%20on%20the%202%20subproblems
//uses merge sort algorithm to sort songs by points in descending order
void SongRec::mergeSort(int start, int end) {
    if (start < end) {
        int mid = start + (end - start) / 2;
        mergeSort(start, mid);
        mergeSort(mid + 1, end);
        merge(start, mid, end);
    }
}

void SongRec::merge(int start, int mid, int end) {
    //get size of left and right portion to merge
    int size1 = mid - start + 1;
    int size2 = end - mid;

    //create containers for left and right sides;
    Song leftArr[size1], rightArr[size2];

    //load the left vector and right vector with corresponding points
    for (int i = 0; i < size1; i++) {
        leftArr[i] = songList.at(start + i);
    }
    for (int j = 0; j < size2; j++) {
        rightArr[j] = songList.at(mid + 1 + j);
    }

    //make new counter variables
    int i = 0, j = 0, k = start;

    //complete comparisons to put in descending order
    while (i < size1 && j < size2) {
        if (leftArr[i].points >= rightArr[j].points) {
            songList.at(k) = leftArr[i];
            i++;
        }
        else {
            songList.at(k) = rightArr[j];
            j++;
        }
        k++;
    }

    //put leftover indexes from the left side into songList
    while (i < size1) {
        songList.at(k) = leftArr[i];
        i++;
        k++;
    }

    //put leftover indexes from the right side into songList
    while (j < size2) {
        songList.at(k) = rightArr[j];
        j++;
        k++;
    }
}

//used as a resource for quick sort, link below
//https://www.geeksforgeeks.org/cpp-program-for-quicksort/
//uses quickSort algorithm to sort songs by points in descending order
int SongRec::quickSortHelp(int start, int end) {
    //pivot starts as the first element
    int pivot = songList.at(start).points;
    int count = 0;

    //find how many songs have points less than the pivot
    //this will be the starting position of the pivot
    for (int i = start + 1; i <= end; i++) {
        if (songList.at(i).points >= pivot) {
            count++;
        }
    }

    //move pivot to the new correct position
    int pivotIndex = start + count;
    swap(songList.at(pivotIndex), songList.at(start));

    //move 'up' and 'down' until they reach the pivot point
    int up = start, down = end;
    while (up < pivotIndex && down > pivotIndex) {
        //move up until it gets a value <= to the pivot value
        while(songList.at(up).points >= pivot) {
            up++;
        }
        //move down until it gets a value > the pivot
        while(songList.at(down).points < pivot) {
            down--;
        }
        //if up and down have not reached the pivot yet, swap up and down values
        if (up < pivotIndex && down > pivotIndex) {
            swap(songList.at(up), songList.at(down));
            up++;
            down--;
        }
    }
    return pivotIndex;
}

void SongRec::quickSort(int start, int end) {
    //if start passes end, sorting is done
    if (start >= end) {
        return;
    }

    //get the first pivot index and sort around it
    int pivot = quickSortHelp(start, end);
    //sort the left side of pivot
    quickSort(start, pivot - 1);
    //sort the right side of pivot
    quickSort(pivot + 1, end);
}

//prints the top 10 song recommendations
void SongRec::printTopTen() {
    for (int i = 0; i < 20; i++) {
        cout << i+1 << ". " << songList.at(i).track << " by " << songList.at(i).artist << endl;
    }
}

