#include "dialogue.hpp"




std::string* Dialogue::get_current()
{
	return lines[curr_id]->content;
}

int Dialogue::get_number_of_answers()
{
	return lines[curr_id]->no_answers;
}

std::string* Dialogue::get_answer(int i)
{
    if(i>=get_number_of_answers())
    {
	    std::cout << "invalid answer\n";
	    std::exit(1);
	}
	return lines[lines[curr_id]->answer[i]]->content;
}

void Dialogue::set_answer(int i)
{
    if(i>=get_number_of_answers())
    {
        std::cout << "invalid answer\n";
        std::exit(1);
    }
    int answer_id = lines[curr_id]->answer[i];
    if(lines[answer_id]->no_answers!=1)
    {
        char s[60];
        std::sprintf(s, "id %d: npc has multiple or no replies to player", answer_id);
        error(s);
    }
    int reply = lines[answer_id]->answer[0];
    curr_id = reply;
}

void Dialogue::init(char const* path, char const* name)
{
	my_name = name;

	f = std::fopen(path, "r");
	cur_line = 1;
	int log_line = 0;
	while(!feof(f))
	{
		dia_line* dp = (dia_line*) std::malloc(sizeof(dia_line));
		dp->content = &contents[log_line++];
		if(read_line(dp)) break;
		if(lines.find(dp->id)!=lines.end()) error_w_line("duplicate line id");
		lines[dp->id] = dp;
		line_id[cur_line++] = dp->id;
	}
	
	// consistency checks:
	
	for(int i=1;i<cur_line;i++)
	{
		if(line_id[i]==-1) continue;
		int id = line_id[i];
		dia_line* dp = lines[id];
		for(int j=0;j<dp->no_answers;j++)
		{
			int answer = dp->answer[j];
			if(lines.find(answer)==lines.end())
			{
				cur_line = i;
				error_w_line("invalid answer id");
			}
		}
	}
	
	if(lines.find(1)==lines.end()) error("there must be an initial line with id 1");
	int size = lines.size();
	int* marc = (int*) std::calloc(size, sizeof(int));
	
	
	initialized = true;
}

void Dialogue::error_w_line(char const* s)
{

	std::printf("%s dialogue: line %d: %s\n", my_name, cur_line, s);
	std::exit(1);
}

void Dialogue::error(char const* s)
{
	std::printf("%s dialogue: %s\n", my_name, s);
	std::exit(1);
}

int Dialogue::read_line(dia_line* d_line)
{
	
    int c;
    c = std::fgetc(f);
    while((c==' ')||(c=='\t')||(c=='\n')||(c==EOF))
    {
        if(c=='\n')
            line_id[cur_line++] = -1;
        if(c==EOF)
            return -1;
        c = std::fgetc(f);
    }
    if(!isdigit(c))
        error_w_line("line must begin with id");
    std::ungetc(c, f);
	
    if(std::fscanf(f, "%d", &d_line->id)!=1)
        error_w_line("unexpected error");
	
    c = std::fgetc(f);
    while((c==' ')||(c=='\t')) 
        c = std::fgetc(f);
    if(c!='"') error_w_line("content must start with \"");
	
    c = std::fgetc(f);
    while(c!='"')
    {
        if((c=='\n')||(c==EOF))
            error_w_line("content must end with \"");
        d_line->content->push_back(c);
        c = std::fgetc(f);
    }
    d_line->no_answers = 0;
    while(1)
    {
        c = std::fgetc(f);
        while((c==' ')||(c=='\t')) 
            c = std::fgetc(f);
        if(!isdigit(c))
        {
            if((c=='\n')||(c==EOF)) 
                return 0;
            else 
                error_w_line("after content must come answer id's");
        }
        if((d_line->no_answers)>=3) 
            error_w_line("too many answer options");
        ungetc(c, f);
        if(std::fscanf(f, "%d", &(d_line->answer[(d_line->no_answers)++]))!=1)
            error_w_line("unexpected error\n");
    }
}

