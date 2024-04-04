//fork is a system call can creates a child process called execv
using namespace std; 
#include <iostream>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <sys/wait.h>

//please use C++ 11 or higher
//first lets create a child process
//step one fork a normal child
//add an executable
int main(){
   
   
    while (true){
        string mystring;
        cout << "Comfy>  ";
        getline(cin, mystring);
        //pid_t pid = fork();

        if (mystring == "exit"){
            break;
        }
   

    //tokenizing process
    istringstream iss(mystring);
    vector<string> tokens((istream_iterator<string>(iss)), istream_iterator<string>());
    
    vector<char*> cmd_args;
    for(auto& token : tokens) {
        cmd_args.push_back(const_cast<char*>(token.c_str()));
    }
    
    cout << "aguments to execute: " << endl;
        for (size_t i = 0; i < cmd_args.size(); i++) { // printing executables, iteration  does not include & skips nullptr
            cout << "cmd_args[" << i << "] = \"" << cmd_args[i] << "\"" << endl;
        } 



    cmd_args.push_back(nullptr); // adding the null is always in cmd_args
    pid_t pid = fork();


    
    
    if (pid < 0){
        cerr << "UMM Failed :(" << endl;
        exit(EXIT_FAILURE);
        //ceerr means character error and is a cheat to dispaly errors (Geeks4Geeks)
    }

    // if child process tokenize input string
    else if (pid == 0) {
        execv(cmd_args[0], cmd_args.data());
        //data() a  function that returns a pointer directly to the memory array(Geeks4Geeks)
        
        cerr << "UMM Failed! with error code: " << errno << endl;
        exit(errno);
        /* cout << "Here is you're string tokenized!! : " << mystring << endl;
        stringstream ss(mystring);
        string token; 
        
        while (ss >> token) { 
            cout << "Token: " << token << endl;
        }
        
        char* args[] = { "/usr/bin/nano", NULL}; 
        if (execv("/usr/bin/nano", args) == -1){
            cerr << "Execv failed" << endl;
            exit(-1); 

        } */


    }
    else {
        int ss; //this is the WEXISTTATUS
        waitpid(pid, &ss, 0);
        if(WIFEXITED(ss) && WEXITSTATUS(ss) != 0){
            cerr << "Child process exited w/  a error" << WEXITSTATUS(ss) << endl;
        }
        
    }
}

return 0;


}


//if the executable is not found execv can handle thoses cases 