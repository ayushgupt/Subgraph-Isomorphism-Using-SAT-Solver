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

string int2str(int num)
{
	ostringstream ss;
	ss << num;
	return(ss.str());
}


vector< vector<short int> > small_adjacency_matrix;
vector< vector<short int> > big_adjacency_matrix;
vector< vector<short int> > variable_matrix;
vector<int> small_first_vertex_list;
vector<int> small_second_vertex_list;
vector<int> big_first_vertex_list;
vector<int> big_second_vertex_list;
vector<int> big_in_degree;
vector<int> big_out_degree;
vector<int> small_in_degree;
vector<int> small_out_degree;
int big_graph_vertex_number=0;
int small_graph_vertex_number=0;
int big_edges=0;
int small_edges=0;
string clause1="";
string clause2="";
string clause3="";
string clause4="";
string clause5="";
string clause6="";
string first_line="";
int count_clauses=0;
string end_line_str="\n";
string input_file="";
string output_file="";
ofstream outfile;

void readfile()
{
	input_file+=".graphs";
	// cout<<input_file<<endl;
	// cout<<input_file.length()<<endl;
	char input_file_array[input_file.length()+1];
	for(int i=0;i<input_file.length();i++)
	{
		input_file_array[i]=input_file.at(i);
	}
	input_file_array[input_file.length()]='\0';
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
		if(c>big_graph_vertex_number)
		{
			big_graph_vertex_number=c;
		}
		big_first_vertex_list.push_back(a);
		big_second_vertex_list.push_back(b);
	}
	while(a!=0 || b!=0);
	//Remove the last zeros from big each list
	big_first_vertex_list.pop_back();
	big_second_vertex_list.pop_back();
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
		if(c>small_graph_vertex_number)
		{
			small_graph_vertex_number=c;
		}
		small_first_vertex_list.push_back(a);
		small_second_vertex_list.push_back(b);
	}
	while(!infile.eof());
	small_first_vertex_list.pop_back();
	small_second_vertex_list.pop_back();
	// cout<<"Closed"<<endl;
	infile.close();
}

void make_adjacency_matrix()
{
	big_adjacency_matrix.clear();
	big_adjacency_matrix.resize( big_graph_vertex_number, vector<short int> (big_graph_vertex_number , 0 ) );
	small_adjacency_matrix.clear();
	small_adjacency_matrix.resize(small_graph_vertex_number, vector<short int> (small_graph_vertex_number , 0) );
	// cout<<"initialized"<<endl;
	big_edges = int(big_first_vertex_list.size() );
	small_edges = int(small_first_vertex_list.size());
	// cout<<"initialized 2"<<endl;
	for(int i=0;i<big_edges;i++)
	{
		big_adjacency_matrix[(big_first_vertex_list[i])-1][(big_second_vertex_list[i])-1]=1;
	}
	// cout<<"initialized 3"<<endl;
	// cout<<"Small Edges are "<<small_edges<<endl;
	// cout<<"big_graph_vertex_number"<<big_graph_vertex_number<<endl;
	// cout<<"small_graph_vertex_number"<<small_graph_vertex_number<<endl;
	for(int i=0;i<small_edges;i++)
	{
		// cout<<small_first_vertex_list[i]<<" "<<small_second_vertex_list[i]<<endl;
		small_adjacency_matrix[(small_first_vertex_list[i])-1][(small_second_vertex_list[i])-1]=1;
		// cout<<"assigned";
	}
	// cout<<"initialized 4"<<endl;
}

void print_both_adjacency_matrix()
{
	cout<<"Below is the Big Adjacency Matrix"<<endl;
	for(int i=0;i<big_graph_vertex_number;i++)
	{
		for(int j=0;j<big_graph_vertex_number;j++)
		{
			cout<<big_adjacency_matrix[i][j];
		}
		cout<<endl;
	}
	cout<<"Below is the small Adjacency Matrix"<<endl;
	for(int i=0;i<small_graph_vertex_number;i++)
	{
		for(int j=0;j<small_graph_vertex_number;j++)
		{
			cout<<small_adjacency_matrix[i][j];
		}
		cout<<endl;
	}
}

void make_indegree_outdegree_list()
{
	big_in_degree.clear();
	big_in_degree.resize(big_graph_vertex_number,0);
	big_out_degree.clear();
	big_out_degree.resize(big_graph_vertex_number,0);
	for(int i=0;i<big_edges;i++)
	{
		big_out_degree[(big_first_vertex_list[i])-1]+=1;
		big_in_degree[(big_second_vertex_list[i])-1]+=1;
	}
	small_in_degree.clear();
	small_in_degree.resize(small_graph_vertex_number,0);
	small_out_degree.clear();
	small_out_degree.resize(small_graph_vertex_number,0);
	for(int i=0; i<small_edges;i++)
	{
		small_out_degree[small_first_vertex_list[i]-1]+=1;
		small_in_degree[small_second_vertex_list[i]-1]+=1;
	}
}
void print_indegree_outdegree_list()
{
	cout<<"For Big Graph"<<endl;
	cout<<"Indegree List"<<endl;
	for(int i=0;i<big_graph_vertex_number;i++)
	{
		cout<<big_in_degree[i]<<" ";
	}
	cout<<endl;
	cout<<"Outdegree List"<<endl;
	for(int i=0;i<big_graph_vertex_number;i++)
	{
		cout<<big_out_degree[i]<<" ";
	}
	cout<<endl;

	cout<<"For Small Graph"<<endl;
	cout<<"Indegree List"<<endl;
	for(int i=0;i<small_graph_vertex_number;i++)
	{
		cout<<small_in_degree[i]<<" ";
	}
	cout<<endl;
	cout<<"Outdegree List"<<endl;
	for(int i=0;i<small_graph_vertex_number;i++)
	{
		cout<<small_out_degree[i]<<" ";
	}
	cout<<endl;
}
void make_variable_matrix()
{
	variable_matrix.clear();
	variable_matrix.resize(big_graph_vertex_number, vector<short int>(small_graph_vertex_number , 2));
	for(int i=0;i<small_graph_vertex_number;i++)
	{
		for(int j=0;j<big_graph_vertex_number;j++)
		{
			if(small_in_degree[i]>big_in_degree[j] || small_out_degree[i]>big_out_degree[j] || (small_in_degree[i]==0 && small_out_degree[i]==0) )
			{
				variable_matrix[j][i]=0;
			}
		}
	}


}
void print_variable_matrix()
{
	for(int i=0;i<big_graph_vertex_number;i++)
	{
		for(int j=0;j<small_graph_vertex_number;j++)
		{
			cout<<variable_matrix[i][j]<<" ";
		}
		cout<<endl;
	}
}
void make_clause_1()
{
	for(int i=0;i<small_graph_vertex_number;i++)
	{
		if(small_out_degree[i]!=0 || small_in_degree[i]!=0)
		{
			for(int j=0;j<big_graph_vertex_number;j++)
			{
				if(variable_matrix[j][i]==2)
				{
					outfile<< int2str((i+1)+j*small_graph_vertex_number)<<" ";
				}
			}
			outfile<<"0";
			outfile<<endl;
			// count_clauses+=1;
		}	
	}
}
void make_clause_2()
{
	for(int i=0;i<small_graph_vertex_number;i++)
	{
		for(int j=0;j<big_graph_vertex_number;j++)
		{
			if(variable_matrix[j][i]==0)
			{
				outfile<<int2str(((i+1)+j*small_graph_vertex_number)*(-1))<<" 0"<<endl;
				// count_clauses+=1;
			}
		}
	}	
}
void make_clause_3()
{
	vector<int> dummy;
	for(int i=0;i<small_graph_vertex_number;i++)
	{
		dummy.clear();
		for(int j=0;j<big_graph_vertex_number;j++)
		{
			if(variable_matrix[j][i]==2)
			{
				dummy.push_back(  ((i+1)+j*small_graph_vertex_number)  );
			}
		}

		for(int k=0;k<dummy.size();k++)
		{
			for(int l=k+1;l<dummy.size();l++)
			{
				clause3+=int2str( (-1)*dummy[k] )+" "+ int2str( (-1)*dummy[l] )+" 0"+end_line_str;
				count_clauses+=1;
			}
		}

	}	
}
void make_clause_4()
{
	vector<int> dummy;
	
	for(int i=0;i<big_graph_vertex_number;i++)
	{
		dummy.clear();
		for(int j=0;j<small_graph_vertex_number;j++)
		{
			if(variable_matrix[i][j]==2)
			{
				dummy.push_back(  ((j+1)+i*small_graph_vertex_number)  );
			}
		}

		for(int k=0;k<dummy.size();k++)
		{
			for(int l=k+1;l<dummy.size();l++)
			{
				clause4+=int2str( (-1)*dummy[k] )+" "+ int2str( (-1)*dummy[l] )+" 0"+end_line_str;
				count_clauses+=1;
			}
		}
	}	
}

void make_clause_6()
{
	int var_num;
	for(int i=0;i<small_graph_vertex_number;i++)
	{
		if(small_out_degree[i]==0 && small_in_degree[i]==0)
		{
			for(int j=0;j<big_graph_vertex_number;j++)
			{
				var_num=(  (i+1)+ ( j * small_graph_vertex_number  )   );
				outfile<<int2str(  (-1)* var_num )<<" 0"<<endl;
				// count_clauses += 1;

			}
		}
	}
}

void make_clause_5()
{
	vector<int> dummy;
	vector<int> row_number;
	vector<int> col_number;
	dummy.clear();
	for (int i = 0; i < small_graph_vertex_number; i++)
	{
		for (int j = 0; j < big_graph_vertex_number; j++)
		{
			if(variable_matrix[j][i]==2)
			{
				dummy.push_back( (i+1)+j*small_graph_vertex_number );
				row_number.push_back(j);
				col_number.push_back(i);
			}
		}
	}

	for(int k=0;k<dummy.size();k++)
	{
		for(int l=k+1;l<dummy.size();l++)
		{
			if(row_number[k]==row_number[l]||col_number[k]==col_number[l])
			{
				outfile<<int2str( (-1)*dummy[k] )+" "+ int2str( (-1)*dummy[l] )<<" 0"<<endl;
				// count_clauses+=1;
			}
			else
			{
				if(big_adjacency_matrix[row_number[k]][row_number[l]]!=small_adjacency_matrix[col_number[k]][col_number[l]] || big_adjacency_matrix[row_number[l]][row_number[k]]!=small_adjacency_matrix[col_number[l]][col_number[k]])
				{
					outfile<<int2str( (-1)*dummy[k] )<<" "<<int2str( (-1)*dummy[l] )<<" 0"<<endl;
					// count_clauses+=1;
				}
			}
			
		}
	}
}

void make_first_line()
{
	first_line+="p cnf ";
	first_line+=int2str(big_graph_vertex_number*small_graph_vertex_number)+" ";
	first_line+=int2str(count_clauses)+end_line_str;
}

void write_clause()
{
	
	
}

int main(int argc, char *argv[])
{
	string temp_str(argv[1]);
	// cout<<temp_str;
	input_file=temp_str;
	output_file=temp_str;
	readfile();
	// cout<<"Finished Reading";
	make_adjacency_matrix();
	// cout<<"Finished making Adjacency";
	// print_both_adjacency_matrix();
	// cout<<"Finished printing Adjacency list";
	make_indegree_outdegree_list();
	// print_indegree_outdegree_list();
	make_variable_matrix();
	// print_variable_matrix();
	
	// make_clause_3();
	// make_clause_4();
	
	// make_first_line();
	// write_clause();

	output_file+=".satinput";
	char output_file_array[output_file.length()+1];
	for(int i=0;i<output_file.length();i++)
	{
		output_file_array[i]=output_file.at(i);
	}
	output_file_array[output_file.length()]='\0';
	
	outfile.open(output_file_array);

	make_clause_1();
	make_clause_2();
	make_clause_5();
	make_clause_6();
	// outfile<<first_line;
	outfile.close();
	return 0;
}
