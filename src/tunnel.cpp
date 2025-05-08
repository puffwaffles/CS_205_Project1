#include <iostream>
#include <cmath>
#include "../header/tunnel.hpp"
#include <fstream>

using namespace std;

Tunnel::Tunnel() {
    size = 10;
    numsoldiers = 9;
    //We have two rows. The first row will be barriers and recesses. The second will have soldiers
    //But we can flatten this into a 1D array to make things simple 
    int length = size * 2;
    //Preset the tunnel to be of size length
    tunnelvect.resize(length);
    blanks.clear();
    //By default we have three holes on the side. There are actually four holes in total. We will use blank to store hole locations in vector
    numblanks = 4;
    blanks.resize(numblanks);
    int j = 0;
    int sideblanks = numblanks - 1;
    //Prefill blank with coordinates (k,0) where k starts at 3 and increments by 2 and ends with 7 
    for (int i = 3; i < 9; i = i + 2) {
        if (j < sideblanks) {
            blanks.at(j) = i;
            j++;
        }
    }
    //Last blank is on the second row (0, 1). This is the space where soldier 1 should end up at
    blanks.at(sideblanks) = 0;
}

Tunnel::Tunnel(int sizes, int soldiers, int blank) {
    size = sizes;
    numsoldiers = soldiers;
    int length = size * 2;
    //Preset the tunnel to be of size length
    tunnelvect.resize(length);
    blanks.clear();
    numblanks = blank;
    //Set blank to size blanks.
    blanks.resize(numblanks);
    int sideblanks = numblanks - 1;
    //Prefill blank with coordinates (k,0) where k starts at 3 and increments by 2 and ends with 7 
    int i = 0;
    for (int j = 3; j < 4 + (2 * (blank - 1)); j += 2) {
        if (i < sideblanks) {
            blanks.at(i) = j;
            i++;
        }
    }
    //Last blank is on the second row (0, 1). This is the space where soldier 1 should end up at
    blanks.at(sideblanks) = size;
}

//Returns the size of the tunnel
int Tunnel::getsize() {
    return size;
}

//Returns the number of soldiers in the tunnel
int Tunnel::getsoldiers() {
    return numsoldiers;
}

//Returns the number of blanks in the tunnel including original front blank
int Tunnel::getblanks() {
    return numblanks;
}

//Sets the size of the tunnel
void Tunnel::setsize(int s) {
    size = s;
}

//Sets the number of soldiers in the tunnel
void Tunnel::setsoldiers(int s) {
    numsoldiers = s;
}

//Sets the number of blanks in the tunnel including original front blank
void Tunnel::setblanks(int n) {
    numblanks = n;
}


//Gets location of the value in terms of 1D view
int Tunnel::getnumloc(int num) {
    int loc = 0;
    int i = 0;
    //Iterate through array until number is found
    while (i < tunnelvect.size()) {
        if (tunnelvect.at(i) == num) {
            loc = i;
            break;
        }
        i++;
    }
    return loc;
}

//Get coordinates of given soldier in 2D point of view. We need this to switch between tunnel recesses and regular
vector<int> Tunnel::getnumcoor(int num) {
    vector<int> coor;
    coor.resize(2);
    //Get the location of the number in the vector by index
    int loc = getnumloc(num);
    int x = 0;
    int y = 0;
    //Each row starts on location k * size, where k is the row index
    //Gives column using the offset from first location on the row
    x = loc % size;
    //Gives the row by determining the nearest k * size
    y = loc / size;
    coor.at(0) = x;
    coor.at(1) = y;
    return coor;
}

//Returns blanks
int Tunnel::getblankloc(int num) {
    //Retrieve which blank based on num (0 - numblanks - 1)
    int loc = blanks.at(num);
    return loc;
}

//Returns blanks
vector<int> Tunnel::getblanksvec() {
    return blanks;
}

//Convert the coordinates to a location on the vector
int Tunnel::getloc(int x, int y) {
    int loc = 0;
    //size * y coordinate gives the first soldier on the row the actual soldier is on
    //x coordinate gives the offset of the actual position from the first soldier of that row
    loc = x + size * y;
    return loc;
}

//We convert the coordinates into a vector location to extract the value from the vector
int Tunnel::getnum(int x, int y) {
    int loc = 0;
    int num = 0;
    //Use getloc to retrieve vector location from coordinates
    loc = getloc(x, y);
    //Access value from vector
    num = tunnelvect.at(loc);
    return num;
}

//Returns the vector for the tunnel
vector<int> Tunnel::gettunnelvect() {
    return tunnelvect;
}

//Update blank locations
void Tunnel::setblank() {
    int blank = 0;
    for (int i = 0; i < tunnelvect.size(); i++) {
        if (tunnelvect.at(i) == 0) {
            blanks.at(blank) = i;
            blank++;
        }
    }
}

//Val is location in tunnel vector and index is location in index
void Tunnel::setblankval(int val, int index) {
    blanks.at(index) = val;
}

//Uses a given blank space. The blank refers to the blank's index in blank vector
int Tunnel::canswap(int blank, int location) {
    //Record location of blank
    int swappable = 0;
    int bloc = blanks.at(blank);
    int y = bloc / size;
    int x = bloc % size;
    //cout << "After getblankcoor" << endl;//
    
    int val = 0;
    //Record how many spaces to slide blank
    int slides = 1;

    //Keep iterating until we hit a barrier or a soldier
    while (swappable != -1 && swappable != 1) {
        //Uses designated location to determine viability for a given direction
        switch (location) {
            //Swapping up
            case 1:
                y = y - 1;
                //Two criteria for swapping up: y is on the second row and there is a soldier above (has values from 1 to size). 
                if (y == 0) {
                    val = getnum(x, y);
                    if (val > 0 && val <= size) {
                        swappable = 1;
                    }
                    //Barrier found
                    if (val < 0) {
                        swappable = -1;
                    }
                }
                //Going out of bounds
                else {
                    swappable = -1;
                }
                break;
            //Swapping down
            case 2:
                y = y + 1;
                //Two criteria for swapping up: y is on the first row and there is a soldier below (has values from 1 to size). 
                if (y == 1) {
                    val = getnum(x, y);
                    if (val > 0 && val <= size) {
                        swappable = 1;
                    }
                    //Barrier found
                    if (val < 0) {
                        swappable = -1;
                    }
                }
                //Going out of bounds
                else {
                    swappable = -1;
                }
                break;
            //Swapping left
            case 3:
                x = x - 1;
                //Two criteria for swapping left: y is not on the first column and there is a soldier to the left (has values from 1 to size). 
                if (x >= 0 && x < size) {
                    val = getnum(x, y);
                    if (val > 0 && val < size) {
                        swappable = 1;
                    }
                    //Found barrier
                    if (val < 0) {
                        swappable = -1;
                    }
                }
                //Going out of bounds
                else {
                    swappable = -1;
                }
                break;
            //Swapping right
            case 4:
                x = x + 1;
                //Two criteria for swapping right: y is not on the last column and there is a soldier to the right (has values from 1 to size). 
                if (x < size && x > 0) {
                    val = getnum(x, y);
                    if (val > 0 && val <= size) {
                        swappable = 1;
                    }
                    //Found barrier
                    if (val < 0) {
                        swappable = -1;
                    }
                }
                //Going out of bounds
                else {
                    swappable = -1;
                }
                break;
            //Default for strange values
            default: 
                swappable = -1;
                break; 
        }
        //If we find a blank, just update slides so we can slide past it
        if (swappable == 0) {
            slides++;
        }
    }
    //If we didn't encounter a barrier or go out of bounds, we return the amount of slides we need to make
    if (swappable != -1) {
        swappable = slides;
    }
    return swappable;
}

//blankval is index of blank in blank vector. Swap blank with soldier value at (x, y)
void Tunnel::swap(int blankval, int x, int y) {
    //Retrieve location of blank in tunnel vector
    int temp = 0;
    int bloc = blanks.at(blankval);

    //Get soldier value 
    temp = getnum(x, y);
    //cout << "soldier value is " << temp << endl;

    //Get the soldier's location in the vector
    int loc = getnumloc(temp);
    
    //Set blank's original location to temp's value
    tunnelvect.at(bloc) = temp;
    //Set temp's original location to blank's value
    tunnelvect.at(loc) = 0;
    //Update blank's new location in blank vector
    setblankval(loc, blankval);
}

//Swaps soldier in a given location in one direction (Does not account for direction switches). Does nothing if blank can't be swapped
void Tunnel::swapsoldier(int blank, int location) {
    //Check if blank can be swapped for a given location and retrieve distance to slide blank if it can
    int swappable = canswap(blank, location);
    //Acquire location of blank and coordinates
    int bloc = blanks.at(blank);
    int y = bloc / size;
    int x = bloc % size;

    //Swap blank if it is swappable in that direction
    if (swappable > 0) {
        switch (location) {
            //Swap blank with soldier above
            case 1:
                swap(blank, x, y - 1);
                break;
            //Swap blank with soldier below
            case 2:
                swap(blank, x, y + 1);
                break;
            //Swap blank with soldier to the left
            case 3:
                swap(blank, x + swappable * -1, y);
                break;
            //Swap blank with soldier to the right
            case 4:
                swap(blank, x + swappable, y);
                break;
            //Default for strange values
            default: 
                break; 
        }
    }
    else {
        string locations[] = {"up", "down", "left", "right"};
        //cout << "Blank soldier can not be swapped " << locations[location - 1] << endl;
    }
}

void Tunnel::copytunnel(vector<int> tunnel) {
    //Change tunnel contents to vector contents
    tunnelvect = tunnel;
    //Set up blanks vector
    setblank();
}

void Tunnel::copyblank(vector<int> blank) {
    //Copy contents of blank vector
    blanks = blank;
}

//Prints out layout of tunnel with soldiers, holes and barriers
void Tunnel::displaytunnel() {
    int place = 0;
    
    //Print row by row
    for (int j = 0; j < 2; j++) {
        // Print each value in the row separated by a space
        for (int k = 0; k < size; k++) {
            //Blanks are 0
            if (tunnelvect.at(place) == 0) {
                cout << "  ";
            }
            //Barriers have value -1
            else if (tunnelvect.at(place) < 0) {
                cout << "X" << " ";
            } 
            //For the 0 value, we just print a space to represent a blank soldier
            else {
                cout << tunnelvect.at(place) << " ";
            }
            place++;
        }
        cout << endl;
    }  
}
