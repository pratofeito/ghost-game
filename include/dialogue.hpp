
#ifndef DIALOGUE_HPP
#define DIALOGUE_HPP

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cctype>
#include <map>


typedef struct
{	
	int id;
	std::string* content;
	int no_answers;
	int answer[3];
} dia_line;


class Dialogue
{
private:
public:
	char const* my_name;
	
	void init(char const* path, char const* name = "unnamed");
	bool initialized = false;
	
	int curr_id = 1;
	std::string* get_current();
	std::string* get_answer(int);
	int get_number_of_answers();
	void set_answer(int);
	
	FILE* f;
	std::map<int, dia_line*> lines;
	std::string contents[10000];
	int line_id[10000]; 
	int cur_line;

	void error_w_line(char const* s);
	void error(char const* s);
	int read_line(dia_line* d_line);
};


#endif
