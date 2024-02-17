#include <fstream>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#include "SportsLayout.h"

    SportsLayout::SportsLayout(string inputfilename)
	{
        readInInputFile(inputfilename);
		min_cost = INT_MAX;
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


    long long SportsLayout::cost_fn(vector<int> x){

        long long cost=0;

        for(int i=0;i<z;i++)
        {
           for(int j=0;j<z;j++) 
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
                

                ipfile >> time;
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

	vector<vector<int>> SportsLayout::expd(vector<int> x)
	{
		vector<vector<int>> res;

		for(int i = 0; i<z; i++)
		{
			for(int j = i+1; j<z; j++)
			{
				vector<int> temp = x;
				int temp1 = x[i];
				x[i] = x[j];
				x[j] = temp1;
				res.push_back(x);
				x = temp;
			}
		}
		return res;
	}
	
	vector<int> SportsLayout::get_map()
	{
		return ans;
	}	

	vector<int> SportsLayout::func()
	{
		int count = 0;
		int shoulder = 0;
		while(true)
		{
			vector<vector<int>> x = expd(mapping);
			bool check = false;
			for(int i = 0; i < z*(z-1)/2; i++)
			{
				if(cost_fn(x[i]) == cost_fn(mapping) && shoulder < 100)
				{
					mapping = x[i];
					shoulder++;
					check = true;
				}
				else if(cost_fn(x[i]) < cost_fn(mapping)) 
				{
					mapping = x[i];
					check = true;
				}
			}
			if(count > 100) return mapping;    
			if(!check) 
			{
				random_shuffle(mapping.begin(), mapping.end()); 
				count++;
			}
		}
	}

	void SportsLayout::generate(int num)
	{
		if(num > l+1) return;
		if(mapping.size() == z) 
		{
			vector<int> temp = mapping;
			if(cost_fn(func()) <= min_cost) 
			{
				ans = func();
				min_cost = cost_fn(func());
			}
			mapping = temp;
			return;
		}
		mapping.push_back(num);
		generate(num+1);
		mapping.pop_back();
		generate(num+1);
	}

    void SportsLayout::compute_allocation()
    {
		generate(1);
		for(int i = 0; i<z; i++) cout<< ans[i] <<" ";
		cout<<endl; 
    }


