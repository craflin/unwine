
#include <string>
#include <algorithm>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

int main(int argc, char* argv[])
{
    if (argc == 0)
        return EXIT_FAILURE;

    // get user name
    std::string user;
    {
        char _[MAX_PATH] = {0};
        GetEnvironmentVariable("USERNAME", _, sizeof(_));
        user = _;
    }

    // get command and args to be launched
    std::string exeName(argv[0]);
    std::string args;
    {
        int firstArg = 1;
        size_t n = exeName.find_last_of("/\\");
        if (n != std::string::npos)
            exeName = exeName.substr(n + 1);
        if(exeName == "unwine.exe")
        {
            if (argc == 1)
                return EXIT_FAILURE;
            exeName = argv[1];
            ++firstArg;
        }
        else
        {
            if (exeName.length() >= 4 && exeName.substr(exeName.length() - 4) == ".exe")
                exeName.resize(exeName.length() - 4);
        }
        for (int i = firstArg; i < argc; ++i)
        {
            std::string arg = argv[i];
            if (arg.length() >= 2 && arg[1] == ':' && isalpha(arg[0]))
            {
                std::replace(arg.begin(), arg.end(), '\\', '/');
                arg[0] = tolower(arg[0]);
                arg = "/home/" + user + "/.wine/dosdevices/" + arg;
            }
            if (i != firstArg)
                args += " ";
            args += "\\\"";
            args += arg;
            args += "\\\"";
        }
    }

    // get current dir
    std::string currentDir;
    {
        char _[MAX_PATH] = {0};
        GetCurrentDirectory(sizeof(_), _);
        _[0] = tolower(_[0]);
        currentDir = _;
        std::replace(currentDir.begin(), currentDir.end(), '\\', '/');
        currentDir = "/home/" + user + "/.wine/dosdevices/" + currentDir;
    }

    // get path to key file
    std::string keyFile;
    {
        char _[MAX_PATH] = {0};
        GetModuleFileName(NULL, _, sizeof(_));
        keyFile = _;
        size_t n = keyFile.find_last_of("/\\");
        if (n != std::string::npos)
            keyFile = keyFile.substr(0, n + 1);
        keyFile += "key.ppk";
    }

    // launch the command
    std::string command = "plink -batch -i \"" + keyFile + "\" -ssh " + user + "@127.0.0.1 \"cd \\\"" + currentDir + "\\\" && \\\"" +  exeName + "\\\" " + args + "\"";
    return system(command.c_str());
}
