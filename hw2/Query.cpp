#include "Query.h"
#include "TextQuery.h"
#include <memory>
#include <set>
#include <algorithm>
#include <iostream>
#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <regex>
using namespace std;

pair<string, string> split_(const string &l) {
    vector<string> v;
    istringstream iss(l);
    for (string s; iss >> s;)
        v.push_back(s);
    
    if (v.size() > 2)
        return make_pair(v.at(1), v.at(2));
    else throw invalid_argument("Unrecognized search\n");
}

shared_ptr<QueryBase> QueryBase::factory(const string& l)
{
    pair<string, string> split_(const string &l);
    regex word{R"(\w+)"};
    regex and_words{R"(\s*AND\s*\w+\s*\w+\s*)"};
    regex or_words{R"(\s*OR\s*\w+\s*\w+\s*)"};
    regex ad_words{R"(\s*AD\s*\w+\s*\w+\s*)"};
    
    if (regex_match(l, word))
        return shared_ptr<QueryBase>(new WordQuery(l));
    
    else if (regex_match(l, or_words)) {
        pair<string, string> words = split_(l);
        return shared_ptr<QueryBase>(new OrQuery(words.first, words.second));
    }
    
    else if (regex_match(l, and_words)) {
        pair<string, string> words = split_(l);
        return shared_ptr<QueryBase>(new AndQuery(words.first, words.second));
    }
    
    else if (regex_match(l, ad_words)) {
        pair<string, string> words = split_(l);
        return shared_ptr<QueryBase>(new AdjacentQuery(words.first, words.second));
    }
    
    else throw invalid_argument("Unrecognized search\n");
}
QueryResult AndQuery::eval (const TextQuery& text) const
{
    QueryResult left_result = text.query(left_query);
    QueryResult right_result = text.query(right_query);
    auto ret_lines = make_shared<set<line_no>>();
    set_intersection(left_result.begin(), left_result.end(),
                     right_result.begin(), right_result.end(),
                     inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(rep(), ret_lines, left_result.get_file());
}

QueryResult OrQuery::eval(const TextQuery &text) const
{
    QueryResult left_result = text.query(left_query);
    QueryResult right_result = text.query(right_query);
    auto ret_lines = make_shared<set<line_no>>(left_result.begin(), left_result.end());
    ret_lines->insert(right_result.begin(), right_result.end());
    return QueryResult(rep(), ret_lines, left_result.get_file());
    
}

QueryResult AdjacentQuery::eval(const TextQuery &text) const {
    QueryResult left_result = text.query(left_query);
    QueryResult right_result = text.query(right_query);
    auto ret_lines = make_shared<set<line_no>>();
    auto n = left_result.begin();
    auto r = right_result.begin();
    for (n = left_result.begin(); n != left_result.end(); n++) {
        for (r = right_result.begin(); r != right_result.end(); r++) {
            if(*r - *n == 1) {
                ret_lines->insert(*n);
            }
            if(*n - *r == 1) {
                ret_lines->insert(*r);
            }
        }
    }
    return QueryResult(rep(), ret_lines, left_result.get_file());
}

/////////////////////////////////////////////////////////
std::ostream &print(std::ostream &os, const QueryResult &qr)
{
    if(qr.sought.at(1) != 'D'){;
        os << "\"" << qr.sought << "\"" << " occurs " <<
        qr.lines->size() << " times:" <<std::endl;
        for (auto num : *qr.lines){
            os << "\t(line " << num + 1 << ") "
            << *(qr.file->begin() + num) << std::endl;
        }
    }
    
    else{
        os << "\"" << qr.sought << "\"" << " occurs " <<
        qr.lines->size() << " times:" <<std::endl;
       // cout << qr.lines->size() <<std::endl;
        int count = 0;
        for (auto num : *qr.lines){
           count++;
            os << "\t(line " << num + 1 << ") "
            << *(qr.file->begin() + num) << std::endl;
            os << "\t(line " << num + 2 << ") "
            << *(qr.file->begin() + num + 1) << std::endl;
            if(count != qr.lines->size()){
            os <<" " << std::endl;
            }
        }
    }
    return os;
}

