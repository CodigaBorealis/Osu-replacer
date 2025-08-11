#include <filesystem>
#include <iostream>
#include <string>
#include <typeinfo>



namespace fs = std::filesystem;
void replace(fs::path path,fs::path replacementPath);
fs::path getOsuPath();



int main(){
    fs::path osuPath=getOsuPath();
    fs::path replacementPath;
    if(osuPath!=fs::path{}){//could find the osu path

    std::string option="";
    std::string inputReplacement="";//idk, the user inputs his replacement as a string
    
    std::cout<<"This is a tool made to either replace or delete the background of every map in your osu! folder \n";

    while(option!="del" && option!="rep"){//loop while the option is invalid
        std::cout<<"Input del to delete all backgrounds, input rep to replace all backgrounds, input 0 to close the program\n";
        std::cout<<"be adviced that all backgrounds are deleted after replacing them\n";
        std::cout<<"some maps may not show the backround correctly due to how osu beatmap files work, for those the background will just be deleted \n";
        std::getline(std::cin,option);
        if(option=="0"){
        std::exit(0);
        }

    }
    if(option=="del"){//the user wants to delete everything
        replace(osuPath,fs::path{});//sends only the osu path
    }

    if(option=="rep"){//the user wants to replace
        std::cout<<"paste your replacement path here: \n";
        std::getline(std::cin>>std::ws,inputReplacement);//avoids the replacement path from cutting off after the first space
        replacementPath=fs::path(inputReplacement);//i have the path now, yay
        if(fs::exists(replacementPath)){//the path does exist
            replace(osuPath,replacementPath);//sends both paths

        }else{
            std::cout<<"Your replacement file doesnt exist \n";
        }
    

    }
    }
    std::cout << "press enter to exit";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    return 0;}





void replace(fs::path path,fs::path replacementPath){
    if(replacementPath==fs::path{}){//DELETION DONT FORGET WHICH IS WHICH YOU DUMMY!
        std::cout<<"all backgrounds in: "<<path<<" will be deleted \n";
        for(const auto& rootPath: fs::directory_iterator(path)){
            if(fs::is_directory(rootPath)){
                fs::path folder=rootPath.path();
                for(const auto& dirEntry: fs::directory_iterator(folder)){//loops trough every folder in songs
                    if(fs::is_regular_file(dirEntry)){//ignores anything that is not a regular file
                        fs::path currFile=dirEntry.path();//stores the current file its checking
                        std::string currExtension=currFile.extension().string();//obtains the extension of the current file its checking
                        if(currExtension==".png" || currExtension==".jpg" || currExtension==".JPG"|| currExtension==".PNG"|| currExtension=="jpeg"||currExtension=="JPEG"){
                            fs::remove(currFile);
                           std::cout<<"background from "<<currFile<<" has been deleted \n";
                            
                    
                                                        }

                                                    }
                                                }
                                            }

                                        }

    }else{//REPLACEMENT DONT FORGET WHICH IS WHICH DUMMY!
        std::string extension=replacementPath.extension().string();//the extension
        std::cout<<"the specified file is a: "<<extension<<"\n";
        if(extension==".png" || extension==".jpg"){
        std::cout<<"all backgrounds in: "<<path<<" will be replaced with "<<replacementPath<<"\n";
        for(const auto& rootPath: fs::directory_iterator(path)){
            if(fs::is_directory(rootPath)){
                fs::path folder=rootPath.path();
                for(const auto& dirEntry: fs::directory_iterator(folder)){//loops trough every folder in songs
                    if(fs::is_regular_file(dirEntry)){//ignores anything that is not a regular file
                        fs::path currFile=dirEntry.path();//stores the current file its checking
                        std::string currExtension=currFile.extension().string();//obtains the extension of the current file its checking
                        if(currExtension==".png" || currExtension==".jpg" || currExtension==".JPG"|| currExtension==".PNG" || currExtension=="jpeg" || currExtension=="JPEG"){
                            std::string backgroundName=currFile.stem().string();
                            fs::remove(currFile);
                           std::cout<<"background from "<<currFile<<" has been deleted \n";
                            try{
                                fs::path beatmapFolder=currFile.parent_path()/(backgroundName+replacementPath.extension().string());
                                fs::copy_file(replacementPath,beatmapFolder,fs::copy_options::overwrite_existing);
                            std::cout<<"background from "<<currFile<<" has been replaced with "<<replacementPath;
                            }catch(fs::filesystem_error& e){
                                std::cout<<"an error has ocurred while trying to copy: "<<e.what()<<"\n";
                            }
                            
                    
                                                        }

                                                    }
                                                }
                                            }

                                        }





        }else{
            std::cout<<"The image must be a png or jpg \n";
        }
        
    }


    
}

fs::path getOsuPath(){
    const char* user=std::getenv("USERPROFILE");//gets the user profile via pointer
    if(user==nullptr){//if the pointer is null, idk fix your windows or something
        std::cout<<"Couldnt find the user path \n";
        return fs::path{};
    }
    fs::path path=fs::path(user)/"AppData"/"Local"/"osu!"/"Songs";//the path
    if(fs::exists(path)){//osu is where it should be, yay
        return path;
    }else{//not my fault tbh
        std::cout<<"Couldnt find the osu! folder \n";
        return fs::path{};
    }
} 