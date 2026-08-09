#include <iostream>
#include <vector>
#include "toml++/toml.hpp"
#include <string>
using namespace std;
class User{
    public:
        std::string name;
        toml::v3::value<std::string> user;
        toml::v3::value<std::string> email;
        User(std::string_view nam, toml::v3::value<std::string> * usr, toml::v3::value<std::string> * eml){
            name=nam;
            user=*usr;
            email=*eml;
        }
        void activate(){
           std::string exec = "git config --global user.name "+this->user.get()+" && git config --global user.email "+this->email.get();
            system(exec.c_str());
        }

};
std::vector<User> parsefile(std::string path){
 std::vector<User> list;
   
    toml::table tbl = toml::parse_file(path);
    
    for(auto&& [key,value]: tbl){
       if(toml::table* info = value.as_table()) {
          list.emplace_back(key.str(), (*info)["user"].as_string(), (*info)["email"].as_string());
       };
        
    }

 return list;
}

int main (int argc,char ** argv){
    
    std::vector<User> result = parsefile(".userlist/profiles.toml");
    int indx =0;
    if (argc==1){
        
        for(int ix=0; ix<result.size();ix++){
            cout<<"["<<ix+1<<"] "<< result[ix].name<<endl;
      
        }
        int choice;
       cin>>choice;
   
       if(choice>0 && choice<= static_cast<int>(result.size()))
        {
            indx = choice-1;
        }
        else{
            cerr<<"invalid choice"<<endl;
        }
    }else{

        indx=atoi(argv[1]);
    }
    std::cout<<"\033[92m ... switching into \033[00m"<<result[indx].name <<std::endl;
    result[indx].activate();
  
    return 0;
}


