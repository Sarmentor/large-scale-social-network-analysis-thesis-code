/*###############################################################################
#					Community Label Propagation Algorithm 						#
#						from Soman and Narang (2011).							#
#																				#
#					Implementation version with Green-Marl Language				#
#					by Rui Sarmento												#
#					for "Large Scale Social Network Analysis"					#
#					Master Thesis - 2013										#
#																				#
################################################################################*/
#include "communities-algo.h"         // header generated by gm_comp
#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <map>
#define WONT_OPEN 20

#include <sys/types.h>
#include <dirent.h>
using namespace std;

//todo - convert to hash_map as desired.
typedef map<long, string> NodeMap;
typedef map<string, long> NameMap;

void add_node(gm_graph *G, gm_graph *Gaux, NameMap *names, NodeMap *nodes, long id, string name) {
  G->add_node();
  Gaux->add_node();
  (*names)[name] = id;
  (*nodes)[id] = name;  
}

//void load_edge_list(gm_graph *G, gm_graph *Gaux, NameMap *names, NodeMap *nodes, string filename, char separator, string directed,string weighted) { 
void load_edge_list(gm_graph *G, gm_graph *Gaux, NameMap *names, NodeMap *nodes, string filename, char separator, string directed) { 
  ifstream file;
  file.open(filename, fstream::in);
  cout << "\nOpened File " << filename;
  if (!(file.is_open())) {
	cout << "\nFile is not open... ";
    throw WONT_OPEN;  
  }
  
  cout << "\nInitializing Variables... ";
  if(directed.compare("n")==0){
  cout << "\nGraph is undirected!";
  } else if(directed.compare("y")==0){
  cout << "\nGraph is directed!";
  }
  //TO DO - PREPARE CODE FOR WEIGHTED GRAPHS
  /*
  if(weighted.compare("n")==0){
  cout << "\nGraph is not weighted!";
  } else if(weighted.compare("y")==0){
  cout << "\nGraph is weighted!";
  }
  */
  string line;
  long int node_counter = 0;
  long int edge_counter = 0;
  cout << "\nBegining While Loop to read the edge list file... ";
  while(file.good()) {
	//cout << "\nRead Lines started..." ;
    //line = (char) file.get();
	getline(file, line);
	//std::stringstream(line);
	//cout << "\nRead Line: " << line;
    if (line.find('#') != std::string::npos) continue;
    if(file.eof()) break;
    size_t split = line.find(separator);
    string u = line.substr(0, split);
    string v = line.substr(split+1);
	//cout << "\nRead Line u: " << u << " - v: " << v;
    if(names->count(u) == 0) {
      add_node(G, Gaux,names, nodes, node_counter++, u);
	  //cout << "\nAdded Node: " << u ;
    } 
    if(names->count(v) == 0) {
      add_node(G, Gaux,names, nodes, node_counter++, v);
	  //cout << "\nAdded Node: " << v ;
    }
	if (directed.compare("n")==0){//graph is undirected
	G->add_edge((*names)[u], (*names)[v]);
	G->add_edge((*names)[v], (*names)[u]);
	//cout << "\nAdded Edge: " << u << " - " << v;
	//cout << "\nAdded Edge: " << v << " - " << u;
	edge_counter++;
	} else if (directed.compare("y")==0) {//graph is directed
	G->add_edge((*names)[u], (*names)[v]);
	//cout << "\nAdded Edge: " << u << " - " << v;
	edge_counter++;
	}
  }
  cout << "\nGraph has "<< node_counter << " Nodes!";
  cout << "\nGraph has "<< edge_counter << " Edges!";
  cout << "\nClosing Edge List file!";
  file.close();
}


//function to translate internal green-marl nodes Ids to edge list nodes
void compile_results(NameMap *names, NodeMap *nodes) {
  //for reading raw results file
  ifstream file;
  //for writing final results file
  ofstream resultsfile;
  resultsfile.open("results-communities.txt",fstream::in | fstream::out | fstream::app);
  
  //for writing final results file
  //resultsfile=fopen("results-communities.txt","a");
  
  //for reading raw results file
	long size;
	char *buf;
	char *ptr;
	size = pathconf(".", _PC_PATH_MAX);
	if ((buf = (char *)malloc((size_t)size)) != NULL)
	ptr = getcwd(buf, (size_t)size);
	file.open(string(buf).append("/results-raw.txt"), fstream::in);
	cout << "\nOpening Raw Results File ";
  if (!(file.is_open())) {
	cout << "\nFile is not open... ";
    throw WONT_OPEN;  
  }
  string line;
  long int node_counter = 0;
  long int edge_counter = 0;
  cout << "\nBegining While Loop to read the Raw file... ";
  while(file.good()) {
	//cout << "\nRead Lines started..." ;
    //line = (char) file.get();
	getline(file, line);
	//std::stringstream(line);
	//cout << "\nRead Line: " << line;
    if (line.find('#') != std::string::npos) continue;
    if(file.eof()) break;
    size_t split = line.find('\t');
    string u = line.substr(0, split);
    string v = line.substr(split+1);
	//for writing final results file
	char buffer[100];
	if (resultsfile !=NULL){
	string s_u = (*names).find((*nodes).find(stol(u))->second)->first;
	string s_v = (*names).find((*nodes).find(stol(v))->second)->first;
	//sprintf(buffer,"%s\t%s\r\n",s_u.c_str(),s_v.c_str());
	resultsfile << s_u.c_str() << "\t" << s_v.c_str() << "\r\n";
	//printf("%s\t%s\r\n",s_u.c_str(),s_v.c_str());
	//fputs(buffer,resultsfile);
	} else 
	{
	printf("Unable to open file results-communities.txt to write results");
	throw WONT_OPEN;
	} 
}
//fclose(resultsfile);
resultsfile.close();
}

int main(int argc, char** argv) {
gm_graph G, Gaux;
NameMap names;
NodeMap nodes;
//char directed[256];
//char file_name[256];
//char string[256];
string directed;
string weighted;
string file_name;
string calc_mod_aux;
time_t timer, timer_end;
struct tm * ptm_start;
struct tm * ptm_end;
float ptm_interval;
int calc_mod; 

 puts("\n############################################");
 puts("#####  Community Detection Algorithm   #####");
 puts("############################################\n");
 

if( remove( "results-raw.txt" ) != 0 )
    puts( "No need for cleaning tasks...continuing..." );
  else
    puts( "1st Cleaning Task Successfully Done" );
if( remove( "results-communities.txt" ) != 0 )
    puts( "No need for cleaning tasks...continuing..." );
  else
    puts( "2nd Cleaning Task Successfully Done" );

printf("Is the graph directed? Answer y (yes) or n (no): ");
//fgets(directed, sizeof(directed), stdin);
cin >> directed;
//printf("Is the graph weighted? Answer y (yes) or n (no): ");
//cin >> weighted;
printf("Input graph file name (only unweighted edge list is accepted!!): ");
//fgets(file_name, sizeof(file_name), stdin);
cin >> file_name;
printf("Do you want to calculate Modularity? It can make the algorithm slow! Answer y (yes) or n (no): ");
cin >> calc_mod_aux;
  //unsigned found_y = calc_mod.find('y');
  //unsigned found_n = calc_mod.find('n'); 
  if(calc_mod_aux.compare("n")==0){calc_mod=0;} else if(calc_mod_aux.compare("y")==0){calc_mod=1;}
time(&timer);  /* get current time; same as: timer = time(NULL)  */
ptm_start = gmtime(&timer);
cout << "Started Computation of Communities Algo at: " << ptm_start->tm_hour << ":" << ptm_start->tm_min << "\n";
cout << "Loading Edge List...";

//load_edge_list(&G, &Gaux ,&names, &nodes, file_name, '\t', directed, weighted);
load_edge_list(&G, &Gaux ,&names, &nodes, file_name, '\t', directed);
cout << "\nCalculating Communities Labels for every node...";

//cout << G.num_nodes();

//Variables for .gm procedures
// Create an array to hold the node property
int32_t* comm = new int32_t[G.num_nodes()]();//G.num_nodes()
// Create an array to hold the node property
float* ewn = new float[G.num_nodes()]();//G.num_nodes()
float* ew = new float[G.num_edges()]();

label_node_1(G, Gaux, ewn, comm, ew);//1rst Phase - Calculate Edge weights and store them in each node
//G.freeze();
Gaux.freeze();
label_node_2(G, Gaux, comm); //2Phase - Build auxiliary graph - calculate connected components on graph aux 

label_node_3(G, Gaux, calc_mod, ewn, comm, ew); //3rd Phase -  final labels for our original graph
//ncomm = label_node(G);
//cout << "\nDetected "<< ncomm <<" distinct Communities!";
time(&timer_end);  /* get current time; same as: timer_end = time(NULL)  */
ptm_end = gmtime(&timer_end);
cout << "\nEnded Computation of Communities Algorithm at: " << ptm_end->tm_hour << ":" << ptm_end->tm_min << "\n";
ptm_interval = difftime(timer_end,timer);
cout << "Processing Time - " << ptm_interval/3600 << " hours, " << ptm_interval/60  << " minutes OR "<< ptm_interval <<" seconds \n";
cout << "Compiling Results...";
compile_results(&names, &nodes);
cout << "\nFile results-communities.txt has the algorithm results! Enjoy!\n";

 puts("\n############################################");
 puts("#####  Community Detection Algorithm   #####");
 puts("############################################\n");

return 0;
} 

 