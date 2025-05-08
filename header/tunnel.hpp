#ifndef TUNNEL_HPP
#define TUNNEL_HPP
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class Tunnel {
    private:
        //Represents the size of the tunnel
        int size;
        //Represents the number of soldiers in the tunnel
        int numsoldiers;
        //Represents tunnel of size m x 2. cubes = m x 2 
        vector<int> tunnelvect;
        //Represents the number of blanks on the side of the tunnel
        int numblanks;
        //Represents the list of coordinates of the blanks. Coordinates are (x, y)
        vector<int> blanks;

    public:
        Tunnel();
        //Choose between inputting a size (m + 1) x 2 tunnel with n recesses or using default tunnel
        Tunnel(int size, int soldiers, int blanks);
        //Get the size of the tunnel
        int getsize();
        //Get the number of soldiers in the tunnel
        int getsoldiers();
        //set the size the tunnel
        void setsize(int num);
        //set the number of soldiers in the tunnel
        void setsoldiers(int num);
        //Get tunnel vector location for a given soldier. Blanks are m + 1, ..., m + 1 + #blanks and solid barriers are -1
        //Get the number of blanks in the tunnel including original front blank
        int getblanks();
        //Get the blanks vector
        vector<int> getblanksvec();
        //set the number of blanks in the tunnel including original front blank
        void setblanks(int num);
        int getnumloc(int num);
        //Get coodinates of given number. 
        vector<int> getnumcoor(int num);
        //Get coodinates of a designated Blank. The coordinates should have 0
        int getblankloc(int num);
        //Get tunnel location for given coordinates. 
        int getloc(int x, int y);
        //Get number for given coordinates. Blanks are 0 and solid barriers are -1
        int getnum(int x, int y);
        //Get tunnel with numbers in order
        vector<int> gettunnelvect();
        //Preset blank values
        void setblank();
        //Set blank value for given blank
        void setblankval(int val, int index);
        //Checks if the swap can be made for a given tile. Location is denoted by 1 (up), 2 (down), 3 (left), 4 (right)
        int canswap(int blank, int location);
        void swap(int blankval, int x, int y);
        //Swap a given blank value with another space on the tunnel. Location is denoted by 1 (up), 2 (down), 3 (left), 4 (right)
        void swapsoldier(int blank, int location);
        //Set values in the tunnel to an existing tunnel
        void copytunnel(vector<int> tunnel);
        //Copy blank vector
        void copyblank(vector<int> blanks);
        //Show tunnel
        void displaytunnel();
        //Show location of inputted number.
        void displayloc(int num);
};

#endif 