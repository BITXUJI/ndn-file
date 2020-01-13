// #include <iostream>
// //#include <QApplication>

// //#include "node_list.h"

// int main(int argc, char* argv[]){
//     // QApplication app(argc, argv);

//     // NodeList nl;
//     // nl.show();

//     // return app.exec();

// }
#include <iostream>
#include <boost/program_options.hpp>

#include "client.h"

void usage(const boost::program_options::options_description &options){
    std::cout << "Usage: sudo build/client [options] <prefix> \n";
    std::cout << options;
    exit(0);
}

int main(int argc, char * argv[]){
    
    // std::string prefix = "/localhost";
    // u_int64_t maxSegmentSize = 1024;
    // std::string filePath = "../../test/";
    std::string prefix="/ndnserver";
    std::string name="10Mfile.txt";
    std::string filePath="/home/pi/ndn-file-cxx/download/";
    u_int64_t maxSeq=10240;
    namespace po = boost::program_options;
    
    po::options_description visibleOptDesc("Allowed options");
    visibleOptDesc.add_options()("help,h", "print this message and exit")
                                ("prefix,p", po::value<std::string>(), "route name")
                                ("name,n", po::value<std::string>(), "file name needs to be downloaded")
                                ("maxSeq,m", po::value<u_int64_t>(), "maximum sequence number")
                                ("directory,d", po::value<std::string>(), "downloaded file directory");

    po::variables_map optVm;    
    store(parse_command_line(argc, argv, visibleOptDesc), optVm);

    if(optVm.count("help")){
        usage(visibleOptDesc);
    }

    if(optVm.count("prefix")){
        prefix = optVm["prefix"].as<std::string>();
    }

    if(optVm.count("name")){
        name = optVm["name"].as<std::string>();
    }

    if(optVm.count("maxSeq")){
        maxSeq = optVm["maxSeq"].as<u_int64_t>();
    }

    if(optVm.count("directory")){
        filePath = optVm["directory"].as<std::string>();
        if(filePath.back() != '/'){
            filePath.append("/");
        }
    }
    // Client(const std::string & prefix);

    // Client(const std::string & prefix, const std::string & name, const std::string & filePath, uint64_t maxSeq);
    Client client(prefix,name,filePath,maxSeq);
    client.requestFileList();
    client.requestFile();
    return 0;
}
