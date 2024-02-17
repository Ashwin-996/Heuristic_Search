
#ifndef SPORTSLAYOUT_H
#define	SPORTSLAYOUT_H

#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class SportsLayout{

    private:
    int z,l;
    int** T;
    int **N;
    int time;
	long long cost_bound;
    vector<int> mapping;
	int map_sz;
	long long count;
	vector<int> ans;

    public:
    SportsLayout(string inputfilename);

    bool check_output_format();

    // void readOutputFile(string output_filename);
    
    long long cost_fn(vector<int> &x);

    void write_to_file(string outputfilename);

    void readInInputFile(string inputfilename);

    void compute_allocation();

	vector<vector<int>> expd(vector<int> x);
	
	long long g(vector<int> &x);

	long long h(vector<int> &x);

	long long f(vector<int> &x);

	void dfs(vector<int> &x);

	long long get_map();
};


#endif
