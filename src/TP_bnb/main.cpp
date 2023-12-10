#include "branchAndBound.hpp"
#include "utils.hpp"

int main(int argc, char** argv){
    if(argc < 2){
        exit(1);
    }

    int n;
    Map* m = readFile(argv[1], n); 

    double result = branchAndBound(n, m->getDistances());

    if(argc == 3 && strcmp(argv[2], "S") == 0){
        std::ofstream outputFile;
        outputFile.open("tests/branchAndBoundResults.txt", std::ios::app);

        if(result == __INT64_MAX__){
            outputFile << argv[1] << ";" << "nan" << std::endl;
        }else{
            outputFile << argv[1] << ";" << result << std::endl;
        }

        outputFile.close();
    } else {
        if(result == __INT64_MAX__){
            std::cout << argv[1] << "\t" << "nan" << std::endl;
        }else{
            std::cout << argv[1] << "\t" << result << std::endl;
        }
    }

    return 0;
}