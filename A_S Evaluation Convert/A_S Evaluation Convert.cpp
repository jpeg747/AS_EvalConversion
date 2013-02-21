/*
Jeremy Quinlan
ID: 000682613
Lawrence Technological University
A&S Deans Office
May 26 2011
Build: v0.6
*/
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <windows.h>
	using namespace std;

void read_file(string, int);  //read and extract data
void gotoxy(int, int);
void seperate();  //seperate data into 2-d array for calculation
void calc_mean();  //calculate mean
void find_minmax();  //find minimum
void calc_quart(int, int);  //calculate 25%, 50%, 75%
void print_headers();
void print_text_questions();  //print question descriptions
void find_std_dev(double, int);  //find standard deviation
double strtodou(string);  //convert string to double
bool response(string);

int min_response = 0; // minimum response requirement
int read = 0;  //counter for files read
const int MAXNUMS = 9999;  //maximum number of files that can be read
double sorted[20][MAXNUMS];  //sorted array for seperated data
double ave[MAXNUMS];
int ave_index = 0;
fstream myfile;  //input file
ofstream outfile;  //output file

//This program is for the A&S Department of Lawrence Technological University ONLY

int main()
{
	outfile.open("Eval_Results.txt");  //open output file
	outfile.clear();  //clear output file from last entry
	char yn = 'n';
	while(toupper(yn) != 'Y')
	{
			cout << "WARNING!: This program will mark each text file with '1'. Continue? (y/n): ";
			cin >> yn;
			if(toupper(yn) == 'N')
			{
				cout << "Exiting . . . ";
				system("PAUSE");
				return 0;
			}
			else
				continue;
	}

	int open = 0;  //counter for successfully opened files
	stringstream ss;  //stringstream for editing string name
	string fname;  //file name
	string str;  //store temp name
	for(int k = 0; k < 8999; k++)
	{
		myfile.clear();
		fname.clear();
		str.clear();
		ss.clear();
		ss << k;
		ss >> str;
		fname = str.append(".txt");  //add '.txt' to the end of the string
		myfile.open(fname.c_str());  //open file for editing
		myfile << "1";  //mark opened file with '1'
		myfile.close();
		myfile.open(fname.c_str()); //open file for reading
		if(!myfile.good())
			continue;
		else if(response(fname) == false)
			continue;
		else
		{
			open++;
			read_file(fname, k);
		}
	}
	if(read == 0)
	{
		cout << "Error: no files found! Exiting program . . ." << endl;
		system("PAUSE");
		return 0;
	}
	else
		;
	cout << "Done. " << open << " opened successfully. " << read << " read successfully with " << min_response << " reponses or more." << endl;
	print_headers();
	print_text_questions();
	seperate();
	find_minmax();
	calc_mean();
	gotoxy(0,44);  //go to bottom of command console
	cout << "Data exported to 'Eval_Results.txt' in current folder." << endl << endl;
	system("PAUSE");

	return 0;
}

void gotoxy(int h, int w)
{
	HANDLE hConsole = GetStdHandle (STD_OUTPUT_HANDLE);

	if (INVALID_HANDLE_VALUE != hConsole)
	{
		COORD pos = {h, w};
		SetConsoleCursorPosition (hConsole, pos);
	}

	return;
}

void print_headers()
{
	cout << endl << "Question" << setw(10) << "Minimum" << setw(6) << "25%" << setw(6) << "50%"
		<< setw(6) << "75%" << setw(11) << "Maximum" << setw(8) << "Mean" << setw(11) << "Std.Dev.";
	cout << endl;

	for(int i = 1; i < 21; i++)
		cout << i << "." << endl << endl;

	outfile << "Question" << setw(17) << "Minimum" << setw(6) << "25%" << setw(6) << "50%"
		<< setw(6) << "75%" << setw(11) << "Maximum" << setw(8) << "Mean" << setw(11) << "Std.Dev.";
	outfile << endl;

	return;
}

void read_file(string fname, int k)
{
	string line;
	if(myfile.is_open())
	{
		int i = 0;
		while(myfile.good() && i != 12) //read single line, overwrite until i = 12
		{
			getline(myfile,line);
			i++;
		}

		while(myfile.good() && i <= 24)
		{
			if(i%2 == 1)  //if i is odd, read line
			{
				getline(myfile,line); //read current line
				ave[ave_index] = strtodou(line);
				ave_index++;
				i++;
			}
			else
			{
				getline(myfile,line);
				i++;
			}
		}

		while(myfile.good() && i != 32)
		{
			getline(myfile,line);
			i++;
		}

		while(myfile.good() && i <= 60)
		{
			if(i%2 == 1)
			{
				getline(myfile,line);
				
				ave[ave_index] = strtodou(line);
				ave_index++;
				i++;
			}
			else
			{
				getline(myfile,line);
				i++;
			}
		}
		read++;
		myfile.close();
	}
	else  //close file
	{
		myfile.close();
	}
	return;
}

void seperate()
{
	int x;  //x index variable
	int y = 0;  //y index variable
	for(int a = 0; ave[a] != NULL;)
	{
		x = 0;
		while(x < 20)
		{
			sorted[x][y] = floor(ave[a]*100+0.5)/100.0;  //round average (X.XX)
			ave[a] = -1;  //mark for debug
			x++;
			a++;  //average index increase
		}
		y++;
	}
	return;
}

void calc_mean()
{
	double mean = 0;
	int n = 0;  //index
	for(int i = 0; i < 20; i++)
	{
		n = 0;
		mean = 0;
		while(sorted[i][n] != NULL)
		{
			mean += sorted[i][n];
			n++;
		}
		mean = mean / n;
		gotoxy(51, 4+2*i);
		cout << setprecision(3) << mean;

		if(i < 10)
			outfile.seekp(133+292*i);
		else
			outfile.seekp(3053+292*(i - 10));

		outfile << setprecision(3) << mean;
		calc_quart(n, i);
		find_std_dev(mean, i);
	}
	return;
}

void find_minmax()
{
	double MIN, MAX;
	double minmax[9999];
	int n = 0;
	for(int i = 0; i< 20; i++)
	{
		n = 0;
		while(sorted[i][n] != NULL)
		{
			minmax[n] = sorted[i][n];
			n++;
		}

		sort(minmax, minmax + n);  //sort array
		
		MIN = minmax[0];
		MAX = minmax[n - 1];

		gotoxy(11, 4+2*i);
		cout << setprecision(3) << MIN;

		if(i < 10)
			outfile.seekp(93+292*i);
		else
			outfile.seekp(3013+292*(i - 10));

		outfile << setprecision(3) << MIN;

		gotoxy(40, 4+2*i);
		cout << setprecision(3) << MAX;

		if(i < 10)
			outfile.seekp(122+292*i);
		else
			outfile.seekp(3042+292*(i - 10));

		outfile << setprecision(3) << MAX;
	}
	return;
}

void find_std_dev(double mean, int i)
{
	int n = 0;
	double sum = 0;
	double std_dev = 0;
	while(sorted[i][n] != NULL)
	{
		sorted[i][n] = sorted[i][n] - mean;
		sorted[i][n] = sorted[i][n] * sorted[i][n];
		sum += sorted[i][n];
		n++;
	}
	std_dev = sqrt(sum / (n - 1));
	gotoxy(58, 4+2*i);
	cout << setprecision(2) << std_dev;

	if(i < 10)
			outfile.seekp(140+292*i);
	else
			outfile.seekp(3060+292*(i - 10));

	outfile << setprecision(2) << std_dev;
	return;
}

void calc_quart(int n, int i)
{
	double quartiles[MAXNUMS];
	double quart_25 = 0;
	double quart_50 = 0;
	double quart_75 = 0;

	for(int a = 0; a < n; a++)
		quartiles[a] = sorted[i][a];

	sort(quartiles, quartiles + n);  //sort array
	quart_25 = quartiles[n/4 - 1];  //find %25
	quart_50 = quartiles[n/2 - 1];  //find median
	quart_75 = quartiles[(n*3)/4 - 1];  //find %75

	gotoxy(21, 4+2*i);
	cout << setprecision(3) << quart_25;

	if(i < 10)
		outfile.seekp(103+292*i);
	else
		outfile.seekp(3023+292*(i - 10));
	outfile << setprecision(3) << quart_25;

	gotoxy(27, 4+2*i);
	cout << setprecision(3) << quart_50;

	if(i < 10)
		outfile.seekp(109+292*i);
	else
		outfile.seekp(3029+292*(i - 10));
	outfile << setprecision(3) << quart_50;

	gotoxy(33, 4+2*i);
	cout << setprecision(3) << quart_75;

	if(i < 10)
		outfile.seekp(115+292*i);
	else
		outfile.seekp(3035+292*(i - 10));
	outfile << setprecision(3) << quart_75;

	return;
}

double strtodou(string line)
{
	double num;  //final result
	string line2;  //sub string line
	line2 = line.substr(76,4);  //extract string portion
	char* writable = new char[line2.size() + 1];  //convert string to double
	std::copy(line2.begin(), line2.end(), writable);
	writable[line2.size()] = '\0';
	num = atof(writable);

	return num;
}

void print_text_questions()
{
	outfile.seekp(75);
	outfile << "1.Usefulness of                                                         " 
		<< endl << "text, req'd                                                             " 
		<< endl << "reading, suppl.                                                         "
		<< endl << "                                                                    " << endl;
	outfile << "2.Adequacy of                                                           " 
		<< endl << "syllabus, grading                                                       " 
		<< endl << "policies                                                                "
		<< endl << "                                                                    " << endl;
	outfile << "3.Helpfulness of                                                        " 
		<< endl << "assignments, HW                                                         " 
		<< endl << "                                                                        "
		<< endl << "                                                                    " << endl;
	outfile << "4.Eff. feedback                                                         " 
		<< endl << "from graded                                                             " 
		<< endl << "material                                                                "
		<< endl << "                                                                    " << endl;
	outfile << "5.Suff. objective                                                       " 
		<< endl << "criteria for                                                            " 
		<< endl << "final grade                                                             "
		<< endl << "                                                                    " << endl;
	outfile << "6.Challenging                                                           " 
		<< endl << "coursework                                                              " 
		<< endl << "                                                                        "
		<< endl << "                                                                    " << endl;
	outfile << "7.Demonstrates                                                          " 
		<< endl << "knowledge of                                                            " 
		<< endl << "subject                                                                 "
		<< endl << "                                                                    " << endl;
	outfile << "8.Clear and thor-                                                       " 
		<< endl << "ough knowledge of                                                       " 
		<< endl << "subject                                                                 "
		<< endl << "                                                                    " << endl;
	outfile << "9.Uses examples                                                         " 
		<< endl << "effectively                                                             " 
		<< endl << "                                                                        "
		<< endl << "                                                                    " << endl;
	outfile << "10.Promotes                                                             " 
		<< endl << "critical thinking                                                       " 
		<< endl << "                                                                        "
		<< endl << "                                                                    " << endl;
	outfile << "11.Well prepared                                                        " 
		<< endl << "for class                                                               " 
		<< endl << "                                                                        "
		<< endl << "                                                                    " << endl;
	outfile << "12.Uses class                                                           " 
		<< endl << "time effectively                                                        " 
		<< endl << "                                                                        "
		<< endl << "                                                                    " << endl;
	outfile << "13.Explains                                                             " 
		<< endl << "requirements,                                                           " 
		<< endl << "grading policies                                                        "
		<< endl << "                                                                    " << endl;
	outfile << "14.Enthusiastic                                                         " 
		<< endl << "                                                                        " 
		<< endl << "                                                                        "
		<< endl << "                                                                    " << endl;
	outfile << "15.Exhibits good                                                        " 
		<< endl << "communication                                                           " 
		<< endl << "skills                                                                  "
		<< endl << "                                                                    " << endl;
	outfile << "16.Treats                                                               " 
		<< endl << "students with                                                           " 
		<< endl << "respect                                                                 "
		<< endl << "                                                                    " << endl;
	outfile << "17.Willing to                                                           " 
		<< endl << "help students                                                           " 
		<< endl << "                                                                        "
		<< endl << "                                                                    " << endl;
	outfile << "18.Available                                                            " 
		<< endl << "during scheduled                                                        " 
		<< endl << "office hours                                                            "
		<< endl << "                                                                    " << endl;
	outfile << "19.Fair and                                                             " 
		<< endl << "impartial in                                                            " 
		<< endl << "grading                                                                 "
		<< endl << "                                                                    " << endl;
	outfile << "20.Timely return                                                        " 
		<< endl << "of graded                                                               " 
		<< endl << "materials                                                               "
		<< endl << "                                                                    " << endl;

	return;
}

bool response(string fname)
{
	string line;
	int i = 0;
	while(myfile.good() && i != 14) //read single line, overwrite until i = 14
	{
		getline(myfile,line);
		i++;
	}

	double num;  //final result
	string line2;  //sub string line
	line2 = line.substr(71,2);  //extract string portion
	char* writable = new char[line2.size() + 1];  //convert string to double
	std::copy(line2.begin(), line2.end(), writable);
	writable[line2.size()] = '\0';
	num = atof(writable);
	myfile.close();
	myfile.open(fname.c_str());
	
	
	
	if(num < min_response)
		return false;
	else
		return true;
}