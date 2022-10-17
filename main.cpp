#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <vector>
#include <map>

class solvent{
    
public:
    
    std::string name;
    long double dielectric;
    
    
    void write_name(solvent obj){
        
        std::cout<<"Solvent name?\n";
        std::cin>>obj.name;
    }
    
    void write_dielectric(solvent obj){
        std::cout<<"Solvent dielectric?\n";
        std::cin>>obj.dielectric;
    }
    
};

class ion{
    
public:
    
    std::string name;
    long double radius;
    long double charge;
    
    
    void write_name(ion obj){
        
        std::cout<<"Ion name?\n";
        std::cin>>obj.name;
    }
    
    void write_radius(ion obj){
        
        std::cout<<"Ion radius?\n";
        std::cin>>obj.radius;
    }
    
    void write_charge(ion obj){
        
        std::cout<<"Ion charge?\n";
        std::cin>>obj.charge;
    }
    
};


std::map <std::string, long double> solvent_list(){
    
    std::string p;
    std::ifstream myfile;
    std::map<std::string, long double> out;
    out ["empty"] = 0;
    
    std::cout<<"List of solvent address:\n";
    std::cin>>p;
    
      myfile.open (p, std::ifstream::in);
    
    if(!myfile.is_open()){std::cout<<"Error in file\n"; return out;}
    
    std::string line;
    solvent obj;
    
   
        while (getline(myfile, line)){
            
            std::istringstream iss(line);
            std::string name, dielectric;
            
            if (getline(iss, name, ',') &&
                getline(iss, dielectric))
                
                        {
                            char *endp = nullptr;
                            if (name.c_str() != endp)
                            {
                                std::transform(name.begin(), name.end(), name.begin(),
                                    [](unsigned char c){return std::tolower(c); });
                                obj.name=name;
                                obj.dielectric=stof(dielectric);
                                out [obj.name] = obj.dielectric;
                            }
                        }
        }
    
    return out;
    }



std::map <std::string, std::vector<long double>> ion_list(){
    
    std::string p;
    std::ifstream myfile;
    std::map<std::string, std::vector<long double>> out;
    std::vector <long double> dummy;
    out ["empty"] = dummy;
    
    std::cout<<"List of ion address:\n";
    std::cin>>p;
    
      myfile.open (p, std::ifstream::in);
    
    if(!myfile.is_open()){std::cout<<"Error in file\n"; return out;}
    
    std::string line;
    ion obj;
    
   
        while (getline(myfile, line)){
            
            std::istringstream iss(line);
            std::string name, radius, charge;
            
            if (getline(iss, name, ' ') &&
                getline(iss, radius, ' ') && getline(iss, charge))
                
                        {
                            char *endp = nullptr;
                            if (name.c_str() != endp)
                            {
                                std::transform(name.begin(), name.end(), name.begin(),
                                    [](unsigned char c){ return std::tolower(c); });
                                obj.name=name;
                                obj.radius=stof(radius);
                                obj.charge=stof(charge);
                                dummy.push_back(obj.radius);
                                dummy.push_back(obj.charge);
  
                                out [obj.name] = dummy;
                                dummy.clear();
                            }
                        }
        }
    
    return out;
    }

long double g_el(){
    
    std::map<std::string, long double> solv=solvent_list();
    std::string p;
    long double e, z, r;
    
    std::cout<<"Enter the name of the solvent, lowercase\n";
    std::cin>>p;
    e=solv[p];
    
    std::map<std::string, std::vector <long double>> ionrad =ion_list();
    
    std::cout<<"Enter the name of the ion, lowercase\n";
    std::cin>>p;
    
   std::vector <long double> values;
    
    values=ionrad[p];
    
    z=values[0];
    r=values[1];
    
    
    long double res=-1*pow(1.602176634E-19, 2)*pow(z,2)*6.02214076E+23*(1-1/e)/(1000*4.184*8*3.14*8.85418781762039E-12*r);
    
    std::cout<<"The G_el is "<<res<<" ccal"<<std::endl;
    
    return res;
}

int main(){
    
    g_el();
    
    return 0;
}
