#include <fstream>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#include "SportsLayout.h"

    SportsLayout::SportsLayout(string inputfilename)
    {
        readInInputFile(inputfilename);
		cost_bound = INT_MIN;
		count = INT_MAX;
		map_sz = INT_MIN;
    }

    bool SportsLayout::check_output_format()
    {

        vector<bool> visited(l,false);
        for(int i=0;i<z;i++)
        {
            if((mapping[i]>=1 && mapping[i]<=l))
            {
                if(!visited[mapping[i]-1])
                visited[mapping[i]-1]=true;
                else
                {
                    cout<<"Repeated locations, check format\n";
                    return false;
                }
            }
            else
            {
                cout<<"Invalid location, check format\n";
                return false;
            }
        }

        return true;

    }

    // void SportsLayout::readOutputFile(string output_filename)
    // {
    //         fstream ipfile;
	//         ipfile.open(output_filename, ios::in);
    //         if (!ipfile) {
    //             cout << "No such file\n";
    //             exit( 0 );
    //         }
    //         else {
                
    //             vector<int> ip;

    //             while (1) {
    //                 int t;
    //                 ipfile >> t;
    //                 ip.push_back(t);
    //                 if (ipfile.eof())
    //                     break;
                    
    //             }
            
    //         if(ip.size()!=z)
    //         {
    //             cout<<"number of values not equal to number of zones, check output format\n";
    //             exit(0);
    //         }
    //         for(int i=0;i<z;i++)
    //         mapping[i]=ip[i];
    //     ipfile.close();

    //     if(!check_output_format())
    //         exit(0);
    //     cout<<"Read output file, format OK"<<endl;

    //         }
        
    // }


    long long SportsLayout::cost_fn(vector<int> &x){


        long long cost=0;

        for(int i=0; i < (int)x.size(); i++)
        {
           for(int j=0; j < (int)x.size(); j++) 
           {
                cost+=(long long)N[i][j]*(long long)T[x[i]-1][x[j]-1];
           }
        }

        return cost;
    }

    void SportsLayout::readInInputFile(string inputfilename)
    {
            fstream ipfile;
	        ipfile.open(inputfilename, ios::in);
            if (!ipfile) {
                cout << "No such file\n";
                exit( 0 );
            }
            else {
                

                ipfile>> time;
                ipfile >> z;
                ipfile >> l;

                if(z>l)
                {
                    cout<<"Number of zones more than locations, check format of input file\n";
                    exit(0);
                }


            

            int **tempT;
            int **tempN;

          tempT = new int*[l];
         for (int i = 0; i < l; ++i)
            tempT[i] = new int[l];
        
        tempN = new int*[z];
        for (int i = 0; i < z; ++i)
            tempN[i] = new int[z];

        for(int i=0;i<z;i++)
        {
            for(int j=0;j<z;j++)
            ipfile>>tempN[i][j];
        }

        for(int i=0;i<l;i++)
        {
            for(int j=0;j<l;j++)
            ipfile>>tempT[i][j];
        }

        ipfile.close();

        T= tempT;
        N= tempN;
            }

    }

    void SportsLayout::write_to_file(string outputfilename){

         // Open the file for writing
    ofstream outputFile(outputfilename);

    // Check if the file is opened successfully
    if (!outputFile.is_open()) {
        cerr << "Failed to open the file for writing." << std::endl;
        exit(0);
    }

    for(int i=0;i<z;i++)
    outputFile<<mapping[i]<<" ";

    // Close the file
    outputFile.close();

    cout << "Allocation written to the file successfully." << endl;

    }

	long long SportsLayout::get_map()
	{
		return cost_fn(mapping);
	}

	vector<vector<int>> SportsLayout::expd(vector<int> x)
	{
		map<int,bool> mp;
		for(auto &u: x) mp[u] = true;
		vector<vector<int>> succ;
		for(int i = 1; i <= l; i++)
		{
			if(mp[i]) continue;
			x.push_back(i);
			succ.push_back(x);
			x.pop_back();
		}
		return succ;
	}	

	long long SportsLayout::g(vector<int> &x)
	{
		return cost_fn(x);
	}

	long long SportsLayout::h(vector<int> &x)
	{
		if((int)x.size() == z) return 0;
		long long est_cost = INT_MAX;
		for(int i = 1; i <= l; i++)
		{
			long long summ = 0;
			x.push_back(i);
			for(int j = 0; j < x.size()-1; j++)
			{
				summ += ((long long)N[j][(int)x.size()-1] + (long long)N[(int)x.size()-1][j])*(long long)T[j][(int)x.size()-1];
				summ *= (long long)(z - x.size());
			}
			est_cost = min(est_cost, summ);
			x.pop_back();
		}
		return est_cost;
	}	

	long long SportsLayout::f(vector<int> &x)
	{
		return g(x)+h(x);
	}

	void SportsLayout::dfs(vector<int> &x)
	{
		if(map_sz == z) return;
		if(f(x) > cost_bound) 
		{
			count = min(count,f(x));
			return;
		}
		map_sz = max(map_sz, (int)x.size());
		if(map_sz == z) ans = x;
		for(auto &u: expd(x)) dfs(u);	
	}

    void SportsLayout::compute_allocation()
    {
		while(map_sz != z)
		{
			dfs(mapping);
			cost_bound = count;
			count = INT_MAX;
		}

		mapping = ans;
		for(int i = 0; i < z; i++) cout<< mapping[i] <<" ";
		cout<<endl;
    }


