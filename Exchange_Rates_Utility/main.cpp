#include <iostream>
#include <string>
#include "curl/curl.h"
#include "nlohmann/json.hpp"
#include <unistd.h>
#include <map>


using namespace std;
using json = nlohmann::json;
static char errorBuffer[CURL_ERROR_SIZE];

static string buffer;

struct path{
public:
    vector <double> sum;
    vector <string> name;
    int cur_num;
    vector <vector <double> > ve;
    vector <double> vec;
    map <double, int> mp;

    void new_round(){
        cur_num++;
    }

    void add_new_one(string s, double x){
        if (cur_num == 1){
            name.push_back(s);
            sum.push_back(x);
            vec.push_back(x);
            ve.push_back(vec);
            vec.clear();
        }
        else{
            int cnt = 0;

            while (name[cnt] != s || cnt < name.size()){
                cnt++;
            }

            if (name[cnt] == s){
                sum[cnt] += x;
                ve[cnt].push_back(x);
            }
            else{
                name.push_back(s);
                sum.push_back(x);
                vec.push_back(x);
                ve.push_back(vec);
                vec.clear();
            }
        }
    }

    double avarage_num(int i){
        return sum[i] / cur_num;
    }

    double median(int u){
        mp.clear();

        for (int i = 0; i < ve[u].size(); ++i){
            map<double,int>::iterator finder = mp.find(ve[u][i]);
            if (finder != mp.end()){
                mp.insert(make_pair(ve[u][i], 1));
            }
            else{
                mp[ve[u][i]]++;
            }
        }

        int val_max;
        double key_max;
        for (auto const& [key, val] : mp)
        {
            if (val > val_max){
                val_max = val;
                key_max = key;
            }
        }

        return key_max;
    }
};


int time ()
{
    clock_t start,end;
    start=clock();
    sleep(10);
    end=clock();
    return 0;
}


static void writer(char *data, size_t size, size_t nmemb, string *buffer)
{
    int result = 0;
    if (buffer != NULL)
    {
        buffer->append(data, size * nmemb);
        result = size * nmemb;
    }

    for (int i = 0; i < nmemb; ++i){
        buffer += data[i];
    }
}


void parcer(const string buffer, path &p){
    auto j1 = json::parse(buffer);

    auto j2 = j1.at("Valute");

    for (auto it = j2.begin(); it != j2.end(); ++it)
    {
        //cout << it.key() << " " << it.value().at("Value") << '\n';
        p.add_new_one(it.key(), it.value().at("Value"));
    }
}



int main(void)
{

    CURL *curl;
    CURLcode result;

    curl = curl_easy_init();

    path p;
    p.cur_num = 1;
    int Q = 0;

    if (curl)
    {
        while(1){
            curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
            curl_easy_setopt(curl, CURLOPT_URL, "https://www.cbr-xml-daily.ru/daily_json.js");

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);

            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

            result = curl_easy_perform(curl);

            if (result == CURLE_OK){
                //cout << buffer << "\n";
                parcer(buffer, p);}
            else
                cout << errorBuffer << endl;
            buffer.clear();

            for (int i = 0; i < p.ve.size(); ++i){
                cout << p.name[i] << " " << p.avarage_num(i) << " " << p.median(i) << endl;
            }

            time();
        }
    }

    curl_easy_cleanup(curl);

    return 0;
}