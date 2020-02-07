#include <iostream>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <random>
#include <chrono>

#define timeNow() std::chrono::high_resolution_clock::now()

typedef float unit;

using namespace std; 

// Create a list of 'size' floating point numbers in the range [-bound, bound]
vector<float> generate_random_list(int size, float bound)
{
    vector<float> random_list(size);
    default_random_engine e;
    uniform_real_distribution<> dis(-bound, bound);

    for(int i=0; i<size;i++){
        random_list[i] = dis(e);
    }

    return random_list;
}

// Update position by velocity, one time-step
void update_coords(vector<float> &xs, vector<float> &ys, vector<float> &zs,
                   vector<float> const& vx, vector<float> const& vy, vector<float> const& vz)
{
    for(int i=0; i < xs.size();i++){
        xs[i] = xs[i] + vx[i];
        ys[i] = ys[i] + vy[i];
        zs[i] = zs[i] + vz[i];
    }
}

// Print vectors (HELPER)
void printvec(vector<float> vect)
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
        vector<unit> xs = generate_random_list(size, 1000.0);
        vector<unit> ys = generate_random_list(size, 1000.0);
        vector<unit> zs = generate_random_list(size, 1000.0);
        vector<unit> vx = generate_random_list(size, 1.0);
        vector<unit> vy = generate_random_list(size, 1.0);
        vector<unit> vz = generate_random_list(size, 1.0);

        auto t1 = timeNow();
        for(int i=0; i<iters; i++)
        {
            update_coords(xs,ys,zs,vx,vy,vz);
        }
        auto t2 = timeNow();
        double duration = chrono::duration_cast<chrono::microseconds>( t2 - t1 ).count();

        double checkSum = accumulate(xs.begin(),xs.end(),0.0) + accumulate(ys.begin(),ys.end(),0.0) 
                        + accumulate(zs.begin(),zs.end(),0.0);

        printf("Mean time per coordinate: %f us\n" ,(duration / (size * iters)));
        printf("Final checksum is: %f\n", checkSum);

        return 0;
    }
    
    else
    {
        cerr << "Invalid number entered" << endl;
    }    
}