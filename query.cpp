#include "simplecanvas/simplecanvas.h"
#include "stdio.h"
#include "hashable.h"
#include "hashmap.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;



class DataBase{
    public:
        Map* m;

        DataBase(Map* m){
            this->m = m;
            for (int i = 0; i < 8; i++)
            {
                stringstream stream;
                stream << "Database/" << i << ".txt";
                string filename = stream.str();
                ifstream input_stream(filename);
                string line;

                int x = 0;
                ValueList songinfo;
                while (getline(input_stream, line))
                {
                    if (x == 0)
                    {
                        songinfo.push_back(line);
                    }
                    else if (x == 1)
                    {
                        songinfo.push_back(line);
                    }
                    else
                    {

                        string hashcode = line.substr(0, 7);
                        string time = line.substr(8);
                        songinfo.push_back(time);
                        HashableString code(hashcode);
                        this->m->put(&code, &songinfo);
                        songinfo.pop_back();
                    }
                    x++;
                }
            }
        }



        bool containsKey(Hashable* key){
            return m->containsKey(key);
        }
        Cloneable* get(Hashable* key){
            return m->get(key);
        }
};

void drawanchor(SimpleCanvas &image, int i, int j)
{

    int x = 3;
    int y = 2;
    while (i - x < 0)
    {
        x = x - 1;
    }
    while (i + x > image.height)
    {
        x = x - 1;
    }
    while (j - y < 0)
    {
        y = y - 1;
    }
    while (j + y > image.width)
    {
        y = y - 1;
    }

    for (int h = i - x; h < i + x; h++)
    {
        for (int k = j - y; k < j + y; k++)
        {
            image.data[h][k][0] = 214;
            image.data[h][k][1] = 57;
            image.data[h][k][2] = 225;
        }
    }
    image.data[i][j][0] = 255;
    image.data[i][j][1] = 0;
    image.data[i][j][2] = 0;
}

// dCenter = 86
// width = 50
// height = 21

vector<Fingerprint> fingerprints(vector<Anchor> vec, SimpleCanvas &image, DataBase database)
{
    vector<Fingerprint> prints;

    int count = 0;
    string holder;

    for (int i = 0; i < (int)vec.size(); i++)
    {

        int h = vec[i].getX();
        int k = vec[i].getY();
        for (int l = h - 21; l < h + 21; l++)
        {
            for (int m = k + 36; m < k + 86 + 50; m++)
            {
                if (l >= image.height - 1 || l <= 0 || m >= image.width - 1)
                {
                }
                else
                {
                    int hold1 = image.data[l][m][0];
                    if (hold1 == 255)
                    {
                        Anchor anchor(l, m);
                        Anchor anchor1(h, k);
                        Fingerprint print(&anchor1, &anchor);
                        prints.push_back(print);
                        stringstream ss;
                        ss << (int)print.getHash();
                        string str = ss.str();
                        HashableString hasher(str);
                        if (database.containsKey(&hasher) == true)
                        {

                            ValueList *test = (ValueList *)database.get(&hasher);
                            test->print();
                            // Unfinished portion
                            // Plan to locate key with matching time offset to corresponding song
                            // return/cout it
                        }
                    }
                }
            }
        }
    }

    return prints;
}

vector<Anchor> constellations(SimpleCanvas &image)
{
    vector<Anchor> vec;
    int h = 0;
    int k = 0;

    int i = 0;
    int j = 0;

    while (j + 18 < image.width)
    {
        while (i + 24 < image.height)
        {
            h = i;
            k = j;
            for (int xi = i; xi < i + 24; xi++)
            {
                for (int xj = j; xj < j + 18; xj++)
                {
                    int hold = image.data[xi][xj][0] + image.data[xi][xj][1] + image.data[xi][xj][2];
                    int hold1 = image.data[h][k][0] + image.data[h][k][1] + image.data[h][k][2];
                    if (hold >= hold1)
                    {
                        h = xi;
                        k = xj;
                    }
                }
            }

            Anchor anchor(h, k);
            vec.push_back(anchor);
            drawanchor(image, h, k);
            i = i + 24;
        }
        i = 0;
        j = j + 18;
    }

    return vec;
}

int main(int argc, char** argv) {
    SimpleCanvas image("spectrogram.png");

    //Load database of songs
    Map* m = new HashMap(10000);
    DataBase database(m);


    //Map anchors as constellations and store anchors in vector
    vector<Anchor> anchors = constellations(image);

    //With vector of anchors database image as param
    //return vector of all fingerprints from soundbyte
    //match fingerprint with song in database and cout song info
    vector<Fingerprint> prints = fingerprints(anchors, image, database);
    

    image.write("constellation.png");
    return 0;

}