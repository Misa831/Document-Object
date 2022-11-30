#ifndef DOC_DOC_H
#define DOC_DOC_H

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

class Doc {
public:
        struct doc_data{
            size_t indent;
            std::string data;
        };

        Doc();
        Doc(const Doc&);
        ~Doc() = default;

        [[nodiscard]] size_t indent(size_t num) const;
        [[nodiscard]] size_t size() const;
        [[nodiscard]]bool empty() const;

        Doc& operator+=(const Doc&);
        Doc& operator+=(const std::string &s);
        explicit operator bool() const;
        doc_data operator[](size_t) const;

        Doc& append(const Doc& arg);

        template <typename Iter> //iter, iter
        Doc& append(Iter begin, Iter end){
            while(*begin != *end){
                document.push_back(*begin);
                begin++;
            }
            return *this;
        }

        Doc& erase(size_t start);
        Doc& erase(size_t start, size_t count);
        Doc& insert(Doc&, size_t start);

        template <typename X>
        Doc& insert(X arg, X arg2,size_t start ){
            document.insert(document.begin() + start, arg, arg2);
            return *this;
        }
        Doc& replace(Doc&, size_t start);
        Doc& replace(Doc&, size_t start, size_t count); //review this one

        template<typename V>
        Doc& replace(V arg, V arg2, size_t start){
            return replace(arg, arg2, start, 99999);
        }

        template <typename V>
        Doc& replace(V arg, V arg2, size_t start, size_t count){
            if(start >= document.size() || (count >=  size() && count != 99999)){
                std::string line = std::to_string(__LINE__);
                std::string s = "Error: Index out of range in line: " + line + ".";
                std::string objectLines = std::to_string(lineCount);
                std::string s2 = "The object has " + objectLines + " lines.";
                throw std::out_of_range(s + s2);
            }
            else if(count == 99999){
           while(document.back() != document[start-1]){
               document.pop_back();
           }
           while(arg != arg2){
               document.push_back(*arg);
               arg++;
           }
            return *this;
            }
            else{
                std::vector<std::string> temp;
                for(size_t i = start + count; i<document.size();i++){
                    temp.push_back(document[i]);
                }
                this->erase(start);
                while(arg != arg2){
                    document.push_back(*arg);
                    arg++;
                }
                return *this;
            }
        } //iter, iter, start

        void read(std::istream& path);
        [[nodiscard]] std::string get_data(size_t a) const;

        friend std::ostream& operator<<(std::ostream &out, Doc& d);
        friend std::istream& operator>>(std::istream &in, Doc &d);
private:
        std::vector<std::string> document;
        std::string dataString;
        size_t lineCount;
        std::string filepath;
        bool emptyFile;
};

#endif //DOC_DOC_H
