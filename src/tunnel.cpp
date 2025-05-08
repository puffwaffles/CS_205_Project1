#include <iostream>
#include <cmath>
#include "../header/tunnel.hpp"

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
int Tunnel::getloc(vector<int> coordinates) {
    int loc = 0;
    //size * y coordinate gives the first soldier on the row the actual soldier is on
    //x coordinate gives the offset of the actual position from the first soldier of that row
    loc = coordinates.at(0) + size * coordinates.at(1);
    return loc;
}

//We convert the coordinates into a vector location to extract the value from the vector
int Tunnel::getnum(vector<int> coordinates) {
    int loc = 0;
    int num = 0;
    //Use getloc to retrieve vector location from coordinates
    loc = getloc(coordinates);
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
    int swappable = 0;
    //cout << "Before getblankcoor for " << blank << endl;//
    //Getting x and y coordinates 
    //cout << "blank: " << blank << endl;
    //cout << "blanks size is " << blanks.size() << endl;
    //cout << "size: " << size << endl;
    
    int bloc = blanks.at(blank);
    //cout << "blank value: " << bloc << endl;
    /*if (location == 4) {
        //cout << "blank: " << blank << endl;
        //cout << "blank value: " << bloc << endl;
    }*/
    int y = bloc / size;
    int x = bloc % size;
    //cout << "After getblankcoor" << endl;//
    //Using a coordinate vector of x and y so we can use it to extract adjacent values
    vector<int> coor;
    coor.resize(2);
    coor.at(0) = x;
    coor.at(1) = y;
    int val = 0;
    int slides = 1;
    //cout << "x: " << x << endl;
    //cout << "y: " << y << endl;/**/

    /*if (location == 3) {
        //cout << "x: " << x << endl;
        //cout << "y: " << y << endl;
    }*/

    while (swappable != -1 && swappable != 1) {
        //cout << "slides: " << slides << endl;
        //Uses designated location to determine viability for a given direction
        switch (location) {
            case 1:
                coor.at(1) = y - 1;
                //cout << "up coor y " << coor.at(1) << endl;
                //Two criteria for swapping up: y is on the second row and there is a soldier above (has values from 1 to size). 
                if (coor.at(1) == 0) {
                    val = getnum(coor);
                    if (val > 0 && val <= size) {
                        //cout << "swappable! " << endl;
                        swappable = 1;
                    }
                    if (val <= 0) {
                        swappable = -1;
                    }
                }
                else {
                    swappable = -1;
                }
                //cout << "Up Swappable is " << swappable << endl;
                break;

            case 2:
                coor.at(1) = y + 1;
                //cout << "down coor y " << coor.at(1) << endl;
                //cout << blank << "has y down at " << coor.at(1) << endl;
                //Two criteria for swapping up: y is on the first row and there is a soldier below (has values from 1 to size). 
                if (coor.at(1) == 1) {
                    val = getnum(coor);
                    if (val > 0 && val <= size) {
                        swappable = 1;
                    }
                    if (val <= 0) {
                        swappable = -1;
                    }
                }
                else {
                    swappable = -1;
                }
                //cout << "Down Swappable is " << swappable << endl;
                break;
            
            case 3:
                coor.at(0) = x - (1 * slides);
                //cout << "left coor x " << coor.at(0) << endl;
                //Two criteria for swapping left: y is not on the first column and there is a soldier to the left (has values from 1 to size). 
                if (coor.at(0) >= 0 && coor.at(0) < size) {
                    val = getnum(coor);
                    //cout << "val is " << val << endl;
                    if (val > 0 && val < size) {
                        //cout << "Swappable!" << endl;
                        swappable = 1;
                    }
                    if (val < 0) {
                        swappable = -1;
                    }
                }
                else {
                    swappable = -1;
                }
                break;

            case 4:
                //cout << "slides: " << slides << endl;
                coor.at(0) = x + (1 * slides);
                //cout << "coor x: " << coor.at(0) << endl;
                //Two criteria for swapping right: y is not on the last column and there is a soldier to the right (has values from 1 to size). 
                if (coor.at(0) < size && coor.at(0) > 0) {
                    val = getnum(coor);
                    //cout << "val: " << getnum(coor) << endl;
                    //cout << "Ex val: " << tunnelvect.at(y * size + x + slides) << endl;
                    if (val > 0 && val <= size) {
                        swappable = 1;
                        //cout << "Is swappable" << endl;
                    }
                    if (val < 0) {
                        //cout << "Not swappable" << endl;
                        swappable = -1;
                    }
                }
                else {
                    //cout << "Not swappable" << endl;
                    swappable = -1;
                }
                break;
            default: 
                swappable = -1;
                break; 
        }
        if (swappable == 0) {
            slides++;
        }
    }
    //cout << "Swappable before if " << swappable << endl;
    if (swappable != -1) {
        swappable = slides;
    }
    //cout << "Swappable is " << swappable << endl;
    return swappable;
}

//blankval is index of blank in blank vector
void Tunnel::swap(int blankval, int x, int y) {
    //cout << "In swapper!" << endl;
    //cout << "In swap" << endl;
    int temp = 0;
    //cout << "new x " << x << endl;
    //cout << "new y " << y << endl;
    int bloc = blanks.at(blankval);
    //Calculate coordinates of soldier to be swapped with blank soldier
    int tempx = (bloc % size) + x;
    int tempy = (bloc / size) + y;
    //cout << "tempx " << tempx << endl;
    //cout << "tempy " << tempy << endl;


    //Use coordinates to store these temp coordinates
    vector<int> coordinates;
    coordinates.push_back(tempx);
    coordinates.push_back(tempy);

    //Get soldier value 
    temp = getnum(coordinates);
    //cout << "soldier value is " << temp << endl;

    //Get the soldier's location in the vector
    int loc = getnumloc(temp);
    //cout << "loc1 " << loc << endl;
    //Get the blank's location in the vector
    
    //Set blank's original location to temp's value
    tunnelvect.at(bloc) = temp;
    //cout << "Value at " << bloc << " is " << tunnelvect.at(bloc) << endl;
    //Set temp's original location to blank's value
    tunnelvect.at(loc) = 0;
    //cout << "Value at loc " << loc << " is " << tunnelvect.at(loc) << endl;
    setblankval(loc, blankval);
    //cout << "Blank " << blankval << " is " << blanks.at(blankval) << " expecting " << loc << endl;
    //cout << "Finished swap" << endl;
}

void Tunnel::swapsoldier(int blank, int location) {
    //cout << "in swapsoldier" << endl;
    int swappable = canswap(blank, location);
    //cout << "after can swap" << endl;
    /*cout << "swappable: " << swappable << endl;
    //cout << "location: " << location << endl; */
    if (swappable > 0) {
        //cout << " We can swap!" << endl;
        //cout << "Swappable!" << endl;
        switch (location) {
            //Swap blank with soldier above
            case 1:
                swap(blank, 0, -1);
                break;
            //Swap blank with soldier below
            case 2:
                swap(blank, 0, 1);
                break;
            //Swap blank with soldier to the left
            case 3:
                swap(blank, swappable * -1, 0);
                break;
            //Swap blank with soldier to the right
            case 4:
                //cout << "Swap made" << endl;
                swap(blank, swappable, 0);
                //cout << "After right swap" << endl;
                break;
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
    //cout << "tunnelvect set" << endl;
    //Update blank coordinates to blank's position in the vector
    setblank();
}

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
