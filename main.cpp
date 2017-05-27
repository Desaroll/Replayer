#include <fstream>
#include <string>
#include <windows.h>

#ifdef DEBUG 
#include <ctime>
#endif

using namespace std;

int main(int argc, char** argv) {
	
	#ifdef DEBUG 
	// Debug file.
	string filename = "Replayer";
	filename.append(to_string(time(0)));
	filename.append(".txt");
	ofstream f(filename.c_str(),ios::out);
	#endif
	
	//////////////////////////////////////
	// Prepare path
	//////////////////////////////////////
	
	// We save the path to ourselves.
	string path(argv[0]);
	path = path.substr(0,path.find_last_of("/\\"));
		
	string versionsFile = path + "/RADS/solutions/lol_game_client_sln/releases/releaselisting_LA2";
	
	#ifdef DEBUG 
	// Log paths.
	f << path << endl;
	f << versionsFile << endl;
	#endif
	
	/////////////////////////////////////
	// Lookup last version
	/////////////////////////////////////
	string lastVersion = "";
	ifstream versions(versionsFile.c_str());
	if(!versions.good()) return -1;
	while(!versions.eof()) versions >> lastVersion;
	
	//printf("test%stest",loadedVersions.c_str());
	string exePath = path + "/RADS/solutions/lol_game_client_sln/releases/" + lastVersion + "/deploy";
	string exe = exePath + "/League of Legends.exe";
	
	#ifdef DEBUG 
	// Log last version and resulting paths
	f << lastVersion << endl;
	f << exePath << endl;
	f << exe << endl;
	#endif
	
	/////////////////////////////////////
	// Collect arguments in a string.
	/////////////////////////////////////
	string arguments("");

	// We prepend the exe path as the first argument.
	
	//Some arguments have space, so we wrap them in " to prevent the client from parsing them as different arguments.
	arguments.append("\"");
	arguments.append(exe);	
	arguments.append("\"");
	
	// Parse Arguments, from the second one (The first one is the program itself, we don't care for it)
	for(int i=1; i<argc; i++) {
			arguments.append(" ");
			//Some arguments have space, so we wrap them in " to prevent the client from parsing them as different arguments.
			arguments.append("\"");
			arguments.append(argv[i]);
			arguments.append("\"");
		//}
    }
	
	#ifdef DEBUG 
	// Log arguments.
	f << arguments << endl;
	#endif
	
	/////////////////////////////////////
	// Prepare to execute the client
	/////////////////////////////////////
	
	char * writable = new char[arguments.size() + 1];
	std::copy(arguments.begin(), arguments.end(), writable);
	writable[arguments.size()] = '\0';
	
	STARTUPINFO si;
    PROCESS_INFORMATION pi;
		
    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );	
	
	
	BOOL result = CreateProcess(exe.c_str(),writable,NULL,NULL,true,0,NULL,exePath.c_str(),&si,&pi);
	#ifdef DEBUG
	f << result << endl;
	#endif

}