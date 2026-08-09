#include <iostream>
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
       User* user= new User (key.str(),(*info)["user"].as_string(),(*info)["email"].as_string());
          list.push_back(*user);
       };
        
    }

 return list;
}

int main (int argc,char ** argv){
    
    std::vector<User> result = parsefile(".userlist/profiles.toml");
    int indx =0;
    if (argc==0){
        int counter=1;
        for(auto user:  result){
            cout<<"["<<counter<<"] "<< result[counter-1].name<<endl;
        }
        int choice;
        cin>>choice;
   
       if(choice>0 && choice<result.size())
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


