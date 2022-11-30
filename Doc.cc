#include "Doc.h"

using namespace std;

Doc::Doc(){
    emptyFile = true;
    lineCount = 0;
    doc_data data;
}

Doc::Doc(const Doc &rhs){
    emptyFile = rhs.emptyFile;
    lineCount = size();
    *this += rhs;
}

size_t Doc::indent(size_t indent) const{ //counts the indent of a specified line.
    size_t indentNum2 = 0;
    if(indent >= document.size()){
        string line = to_string(__LINE__);
        string s = "Error: Index our of range in line: " + line + ". ";
        string objectLines = to_string(lineCount);
        string s2 = "The object has " + objectLines + " lines.";
        throw out_of_range(s+s2);
    }
    if(document[indent].empty()){ //returns 0 if the vector elem is empty.
        return indentNum2;
    }
    string indentLine = document[indent]; //gets elem
    size_t x = indentLine.length();
    x++;
    char *str = new char[x];
    strcpy(str,indentLine.c_str());
    for(size_t i = 0; i<indentLine.length();i++){
        if(str[i] == ' '){
           indentNum2 ++;
        }
        if(str[i] != ' '){
            return indentNum2;
        }
    }
    delete [] str;
    return indentNum2;
}

size_t Doc::size() const{

    return document.size();
}

bool Doc::empty() const{
    return emptyFile;
}

string Doc::get_data(size_t a) const{
    if(a>= document.size()) {
        string line = to_string(__LINE__);
        string s = "Error: Index out of range in line: " + line + ".";
        string objectLines = to_string(lineCount);
        string s2 = "The object has " + objectLines + " lines.";
        throw out_of_range(s + s2);
    }
    string s = document[a];
    if(s.empty()){
        return "";
    }
    s = s.substr(indent(a));
    return s;
}

Doc& Doc::operator+=(const Doc &rhs){
    document.insert(document.end(), rhs.document.begin(),rhs.document.end());
    emptyFile = rhs.emptyFile;
    lineCount = lineCount + rhs.lineCount;
    return *this;
}

Doc& Doc::operator+=(const string &s){
    document.push_back(s);
    lineCount++;
    return *this;
}

Doc::doc_data Doc::operator[](size_t a) const{
    doc_data dd;
    dd.data = get_data(a);
    dd.indent = indent(a);
    return dd;
}

istream& operator>>(istream& in, Doc &d){
    d.read(in);
    return in;
}

ostream& operator<<(ostream& out, Doc &d){
    for(auto &word:d.document){
        out<<word<<"\n";
    }
    return out;
}

Doc::operator bool() const{
 if(emptyFile){
     return false;
 }
 return true;
}

Doc operator+(const Doc &lhs, const Doc &rhs){
    Doc temp;
    temp+=lhs;
    temp+=rhs;
    return temp;
}

Doc operator+(const Doc &lhs, const std::string &s){
    Doc temp;
    temp+=lhs;
    temp+=s;
    return temp;
}
void Doc::read(istream &path){
    string line;
    while(getline(path,line)){
        for(auto a: line){
            if(a == '\t'){
                throw runtime_error("Encountered '\\t' character.");
            }
        }
        while(!line.empty() && (line.back() == ' ' || line.back() == '\r')){
            line.pop_back();
        }
        if(!line.empty()){
            document.push_back(line);
            lineCount++;
        }
        if(lineCount != 0){
            emptyFile = false;
        }
    }
}

Doc& Doc::append(const Doc &arg){
    document.insert(document.end(), arg.document.begin(), arg.document.end());
    return *this;
}


Doc& Doc::insert(Doc &arg, size_t start){
    std::vector<string>::iterator it;
    it = document.begin() + start;
    document.insert(it , arg.document.begin(), arg.document.end());
    return *this;
}
Doc& Doc::erase(size_t start){
    return erase(start, 99999);
}

Doc& Doc::erase(size_t start, size_t count){
    if(start >= document.size() || (count >=  size() && count != 99999)){
        string line = to_string(__LINE__);
        string s = "Error: Index out of range in line: " + line + ".";
        string objectLines = to_string(lineCount);
        string s2 = "The object has " + objectLines + " lines.";
        throw out_of_range(s + s2);
    }
    else if(count == 99999) {
        std::vector<string>::iterator it;
        it = document.begin() + start;
        document.erase(it, document.end());
        return *this;
    }
    else{
        std::vector<string>::iterator it;
        it = document.begin() + start;
        document.erase(it, it+count);
        return *this;
    }
}

Doc& Doc::replace(Doc &arg, size_t start){
    return replace(arg, start, 99999);
}

Doc& Doc::replace(Doc &arg, size_t start, size_t count) {
    if(start >= document.size() || (count >=  size() && count != 99999)){
        string line = to_string(__LINE__);
        string s = "Error: Index out of range in line: " + line + ".";
        string objectLines = to_string(lineCount);
        string s2 = "The object has " + objectLines + " lines.";
        throw out_of_range(s + s2);
    }
    else if(count == 99999){
        while(document.back() != document[start-1]){
            document.pop_back();
        }
        append(arg);
        return *this;
    }
    else{
        vector<string> temp; //temp vector to not lose data.
        for (size_t i = start + count; i < document.size(); i++) { //save contents of vector.
            temp.push_back(document[i]);
        }
        this->erase(start);

        for (auto &j: arg.document) { //add the document
            document.push_back(j);
        }

        for (auto &val: temp) {
            document.push_back(val);
        }
        return *this;
    }
}









