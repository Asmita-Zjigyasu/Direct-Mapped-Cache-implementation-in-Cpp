#include <bits/stdc++.h>

using namespace std;
typedef unsigned long long int ull;

//34ef0008->34ef000(1000)->address becomes 11 bits long
string funct(unordered_map<char, string> hexa_to_binary, string hexa_address)
{
    string comparable_address = hexa_address.substr(0, 7) + hexa_to_binary[hexa_address.at(7)];
    return comparable_address;
}


pair<ull, ull>cache_hit_miss(vector<string> addresses_from_file)
{
    unordered_map<string, string> DM_cache_64_8;//64 KB cache size and 8 bytes cache line size
    string addr, tag, index, byte_offset;
    ull hits = 0, misses = 0;
    for(ull i = 0; i < addresses_from_file.size(); i++)
    {
        addr = addresses_from_file.at(i);//Pick an address from the addresses vector
        
        //For a 64 KB cache and 8 bytes Cache line size, 
        //tag = 16 binary bits(4 hexadecimal bits)
        //index = 13 binary bits(3 hexadecimal bits + 1 binary bit)
        //byte_offset = 3 binary bits(3 binary bits)
        
        tag = addr.substr(0, 4);//4 characters after 0th position
        index = addr.substr(4, 4);//5 characters after 4th position
        byte_offset = addr.substr(8, 3);//3 characters after 8th position
        
        if(DM_cache_64_8.find(index) == DM_cache_64_8.end())// if the valid bit of index is 0, then in our map, 
                                                            // the index won't be found. Hence it is a Cache miss.
        {
            misses++;//increment the number of misses
            DM_cache_64_8.insert({index, tag});//store the index with the tag in the cache(map)
        }
        
        else// if the valid bit of the index is 1, then the index is found in our map
        {
            unordered_map<string, string> :: iterator IT = DM_cache_64_8.find(index);//initialise an iterator of the type unordered_map
            // in an unordered_map iterator-> key = first, value = second
            
            if(IT->second == tag)
                hits++;//there is a tag match
            else//the index matched, but the tag did not match, hence a cache misses
            {
                misses++;
                DM_cache_64_8[index] = tag;//update the tag corresponding to that index
            }
        }
    }
    pair<ull, ull> hits_and_misses = make_pair(hits, misses);
    return hits_and_misses;
}


int main()
{
    unordered_map<char, string> hexa_to_binary;
    hexa_to_binary.insert({'0', "0000"});
    hexa_to_binary.insert({'1', "0001"});
    hexa_to_binary.insert({'2', "0010"});
    hexa_to_binary.insert({'3', "0011"});
    hexa_to_binary.insert({'4', "0100"});
    hexa_to_binary.insert({'5', "0101"});
    hexa_to_binary.insert({'6', "0110"});
    hexa_to_binary.insert({'7', "0111"});
    hexa_to_binary.insert({'8', "1000"});
    hexa_to_binary.insert({'9', "1001"});
    hexa_to_binary.insert({'a', "1010"});//10
    hexa_to_binary.insert({'b', "1011"});//11
    hexa_to_binary.insert({'c', "1100"});//12
    hexa_to_binary.insert({'d', "1101"});//13
    hexa_to_binary.insert({'e', "1110"});//14
    hexa_to_binary.insert({'f', "1111"});//15
    
    vector<string> addresses_from_file;
    ifstream traces;
    string line;//To read a line from the input trace file
    
    traces.open("gcc.trace");
    if(traces.is_open())
        while(getline(traces, line))//Run the loop of reading lines from file till the end of file is reached
            addresses_from_file.push_back(funct(hexa_to_binary, line.substr(4, 8)));//store the address to be compred in the addresses map
    traces.close();//close the trace file after reading it and storing the addresses to the map
    pair<ull, ull> GCC = cache_hit_miss(addresses_from_file);
    addresses_from_file.clear();//Clear the vector to reuse it for the next files
    
    
    traces.open("gzip.trace");
    if(traces.is_open())
        while(getline(traces, line))//Run the loop of reading lines from file till the end of file is reached
            addresses_from_file.push_back(funct(hexa_to_binary, line.substr(4, 8)));//store the address to be compred in the addresses map
    traces.close();//close the trace file after reading it and storing the addresses to the map
    pair<ull, ull> GZIP = cache_hit_miss(addresses_from_file);
    addresses_from_file.clear();//Clear the vector to reuse it for the next files
    
    
    traces.open("swim.trace");
    if(traces.is_open())
        while(getline(traces, line))//Run the loop of reading lines from file till the end of file is reached
            addresses_from_file.push_back(funct(hexa_to_binary, line.substr(4, 8)));//store the address to be compred in the addresses map
    traces.close();//close the trace file after reading it and storing the addresses to the map
    pair<ull, ull> SWIM = cache_hit_miss(addresses_from_file);
    addresses_from_file.clear();//Clear the vector to reuse it for the next files
    
    
    traces.open("mcf.trace");
    if(traces.is_open())
        while(getline(traces, line))//Run the loop of reading lines from file till the end of file is reached
            addresses_from_file.push_back(funct(hexa_to_binary, line.substr(4, 8)));//store the address to be compred in the addresses map
    traces.close();//close the trace file after reading it and storing the addresses to the map
    pair<ull, ull> MCF = cache_hit_miss(addresses_from_file);
    addresses_from_file.clear();//Clear the vector to reuse it for the next files
    
    
    traces.open("twolf.trace");
    if(traces.is_open())
        while(getline(traces, line))//Run the loop of reading lines from file till the end of file is reached
            addresses_from_file.push_back(funct(hexa_to_binary, line.substr(4, 8)));//store the address to be compred in the addresses map
    traces.close();//close the trace file after reading it and storing the addresses to the map
    pair<ull, ull> TWOLF = cache_hit_miss(addresses_from_file);
    addresses_from_file.clear();//Clear the vector to reuse it for the next files
    
    //cout << fixed;
    cout << "GCC:      " << "Hits: " << GCC.first << "     " << "Misses: " << GCC.second << "       " << "Hit Ratio: " << ((long double) (GCC.first)) / (GCC.first + GCC.second) << "      " << "Miss Ratio: " <<((long double) (GCC.second)) / (GCC.first + GCC.second) << "      " << "Hit/Miss Rate: " << ((long double) (GCC.first)) / GCC.second << endl;
    cout << "GZIP:     " << "Hits: " << GZIP.first << "     " << "Misses: " << GZIP.second << "       " << "Hit Ratio: " << ((long double) (GZIP.first)) / (GZIP.first + GZIP.second) << "      " << "Miss Ratio: " <<((long double) (GZIP.second)) / (GZIP.first + GZIP.second) << "      " << "Hit/Miss Rate: " << ((long double) (GZIP.first)) / GZIP.second << endl;
    cout << "SWIM:     " << "Hits: " << SWIM.first << "     " << "Misses: " << SWIM.second << "       " << "Hit Ratio: " << ((long double) (SWIM.first)) / (SWIM.first + SWIM.second) << "      " << "Miss Ratio: " <<((long double) (SWIM.second)) / (SWIM.first + SWIM.second) << "      " << "Hit/Miss Rate: " << ((long double) (SWIM.first)) /SWIM.second << endl;
    cout << "MCF:      " << "Hits: " << MCF.first << "     " << "Misses: " << MCF.second << "       " << "Hit Ratio: " << ((long double) (MCF.first)) / (MCF.first + MCF.second) << "      " << "Miss Ratio: " <<((long double) (MCF.second)) / (MCF.first + MCF.second) << "      " << "Hit/Miss Rate: " << ((long double) (MCF.first)) /MCF.second << endl;
    cout << "TWOLF:    " << "Hits: " << TWOLF.first << "     " << "Misses: " << TWOLF.second << "       " << "Hit Ratio: " << ((long double) (TWOLF.first)) / (TWOLF.first + TWOLF.second) << "      " << "Miss Ratio: " <<((long double) (TWOLF.second)) / (TWOLF.first + TWOLF.second) << "      " << "Hit/Miss Rate: " << ((long double) (TWOLF.first)) /TWOLF.second << endl;
    return 0;
    
}