#include <iostream>
#include <sstream>
#include <vector>
#include <random>
#include <time.h>

using namespace std; 

// Get random floating point number in the range [-bound, bound]

/*
float get_random(float bound)
{
    default_random_engine e;
    uniform_real_distribution<float> dis(-bound, bound);
    return dis(e);
}
*/

// Create a list of 'size' floating point numbers in the range [-bound, bound]
vector<float> generate_random_list(int size, float bound)
{
    default_random_engine e;
    uniform_real_distribution<> dis(-bound, bound);
    vector<float> random_list(size);

    for(int i=0; i<size;i++){
        int rand_int = dis(e);
        random_list[i] = rand_int;
    }

    return random_list;
}

// Update position by velocity, one time-step
void update_coords(vector<float> &xs, vector<float> &ys, vector<float> &zs,
                   vector<float> vx, vector<float> vy, vector<float> vz)
{
    for(int i=0; i < xs.size();i++){
        xs[i] = xs[i] + vx[i];
        ys[i] = ys[i] + vy[i];
        zs[i] = zs[i] + vz[i];
    }
}

// Print vectors
void printf(vector<float> vect)
{
    for(int i=0; i<vect.size();i++){
        cout << vect[i] << endl;
    }
}

// Main
int main(int argc, char **argv)
{
    if(argc != 3){
        cerr << "Required arguments: vector_length(N) and iterations_num(M)" << endl;
    }

    istringstream iss1(argv[1]);
    istringstream iss2(argv[2]);
    int size, iters;

    if(iss1 >> size && iss2 >> iters)
    {
        vector<float> xs = generate_random_list(size, 1000.0);
        vector<float> ys = generate_random_list(size, 1000.0);
        vector<float> zs = generate_random_list(size, 1000.0);
        vector<float> vx = generate_random_list(size, 1.0);
        vector<float> vy = generate_random_list(size, 1.0);
        vector<float> vz = generate_random_list(size, 1.0);

        printf(xs);

        struct timespec requestStart, requestEnd;
        clock_gettime(CLOCK_MONOTONIC, &requestStart);
        for(int i=0; i<iters; i++)
        {
            update_coords(xs,ys,zs,vx,vy,vz);
        }
        
        clock_gettime(CLOCK_MONOTONIC, &requestEnd);


        float t = ( requestEnd.tv_sec - requestStart.tv_sec
        + requestEnd.tv_nsec - requestStart.tv_nsec );

        int checkSum = accumulate(xs.begin(),xs.end(),0) + accumulate(ys.begin(),ys.end(),0) 
                        + accumulate(zs.begin(),zs.end(),0);


        cout << "Mean time per coordinate: " <<  t / (size * iters) <<  "us" << endl;
        cout << "Final checksum is: " << checkSum << endl;

        cout << "Check" << endl;

        return 0;
    }
    
    else
    {
        cerr << "Invalid number entered" << endl;
    }    
}