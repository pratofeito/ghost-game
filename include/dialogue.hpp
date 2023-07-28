
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cctype>
#include <map>



typedef struct{
	
	int id;
	std::vector<char>* content;
	int no_answers;
	int answer[3];
} dia_line;


class Dialogue{

public:
	FILE* f;
	std::map<int, dia_line*> lines;
	std::vector<char> contents[100000]; // assumindo que vamos ter menos de 100000 linhas lol
	int line_id[100000]; 
	int cur_line;

	void read_file();
	void error_w_line(char const* s);
	int read_line(dia_line* d_line);
	void print_myself();
	int seen[100000];
};

