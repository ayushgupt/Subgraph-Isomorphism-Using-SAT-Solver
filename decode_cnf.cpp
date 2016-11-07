#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <ctime>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <set>
#include <ctime>
#define max 10000
#define all(c) (c).begin(),(c).end() 
using namespace std;

char solvable[5];
bool is_solvable=false;
vector<int> answer;
int big_vertex_number=0;
int small_vertex_number=0;
vector<int> mappings;
vector<int> map_first_small;
vector<int> map_second_big;
int product;
string input_file="";
string graph_file="";
string output_file="";

void readfile()
{
	input_file+=".satoutput";
	// cout<<input_file<<endl;
	// cout<<input_file.length()<<endl;
	char input_file_array[input_file.length()+1];
	for(int i=0;i<input_file.length();i++)
	{
		input_file_array[i]=input_file.at(i);
	}
	input_file_array[input_file.length()]='\0';

	ifstream infile;
	infile.open(input_file_array);
	infile>> solvable;
	if(solvable[0]=='U')
	{
		is_solvable=false;
		return;
	}
	else
	{
		is_solvable=true;
	}
	int num;
	do
	{
		infile>>num;
		answer.push_back(num);
	}
	while(num!=0);
	answer.pop_back();
	infile.close();
}

void decode()
{
	product=int(answer.size());
	for(int i=0;i<product;i++)
	{
		if(answer[i]>0)
		{
			mappings.push_back(answer[i]);
		}
	}
	for(int i=0;i<int(mappings.size());i++)
	{
		
		if(mappings[i]%small_vertex_number==0)
		{
			map_first_small.push_back(small_vertex_number);
			map_second_big.push_back(  (mappings[i]/small_vertex_number)   );
		}
		else
		{
			map_second_big.push_back((mappings[i]/small_vertex_number)+1);
			map_first_small.push_back( (mappings[i]%small_vertex_number));	
		}
		
	}
}

void print_final_answer()
{
	output_file+=".mapping";
	char output_file_array[output_file.length()+1];
	for(int i=0;i<output_file.length();i++)
	{
		output_file_array[i]=output_file.at(i);
	}
	output_file_array[output_file.length()]='\0';

	ofstream outfile;
	outfile.open (output_file_array);
	for(int i=0;i<int(mappings.size());i++)
	{
		outfile<<map_first_small[i]<<" "<<map_second_big[i]<<endl;
	}
	outfile.close();
}
void find_vertex_numbers()
{
	graph_file+=".graphs";
	// cout<<input_file<<endl;
	// cout<<input_file.length()<<endl;
	char input_file_array[graph_file.length()+1];
	for(int i=0;i<graph_file.length();i++)
	{
		input_file_array[i]=graph_file.at(i);
	}
	input_file_array[graph_file.length()]='\0';
	// cout<<input_file_array;
	// return;
	ifstream infile;
	infile.open(input_file_array);
	int a,b,c;
	do
	{
		// cout<<"first"<<endl;
		infile>>a>>b;
		if(a>=b)
		{
			c=a;
		}
		else
		{
			c=b;
		}
		if(c>big_vertex_number)
		{
			big_vertex_number=c;
		}
	}
	while(a!=0 || b!=0);
	//Remove the last zeros from big each list
	do
	{
		// cout<<"second"<<endl;
		infile>>a>>b;
		if(a>=b)
		{
			c=a;
		}
		else
		{
			c=b;
		}
		if(c>small_vertex_number)
		{
			small_vertex_number=c;
		}
	}
	while(!infile.eof());
	// cout<<"Closed"<<endl;
	infile.close();
}

int main(int argc, char *argv[])
{
	string temp_str(argv[1]);
	input_file=temp_str;
	output_file=temp_str;
	graph_file=temp_str;
	readfile();
	find_vertex_numbers();
	if(!is_solvable)
	{
		// cout<<"not solvable"<<endl;
		output_file+=".mapping";
	char output_file_array[output_file.length()+1];
	for(int i=0;i<output_file.length();i++)
	{
		output_file_array[i]=output_file.at(i);
	}
	output_file_array[output_file.length()]='\0';

	ofstream outfile;
	outfile.open (output_file_array);		

		outfile<<0;
	outfile.close();
		return 0;
	}

	decode();

	print_final_answer();
	return 0;
}
