#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <iterator>
#include <list>
using namespace std;

template<typename T>
auto maybeConvert(T i,true_type){ return to_string(i);}

template<typename T>
auto maybeConvert(T i,false_type){
    static_assert(!is_floating_point<T>::value, "Floating point values are not allowed because the unprecise nature of these types would not allow a reliable check on symmetry");
    return i;
}

template<typename T>
bool isSymetric(T t){
  auto s = maybeConvert(t,is_integral<T>());
  return !equal(s.begin(), next(s.begin(),s.size()/2), s.rbegin());
}

template<class OutputIterator, typename Container>
OutputIterator symetricOnly(Container input,OutputIterator c){
    return remove_copy_if(input.begin(), input.end(),c, [](auto s) { //Why is this lambda needed?
        return isSymetric(s);
    });
}

//Y U no work?
template<class OutputIterator, typename Container>
OutputIterator symetricOnly2(Container input,OutputIterator c){
    return remove_copy_if(input.begin(), input.end(),c,isSymetric);
}

int main(){
    cout << "Strings With Vector" << endl;
    vector<string> v = {"abc", "aaa", "bbb", "bbcc"};
    vector<string> outvec;
    symetricOnly(v,back_inserter(outvec));
    for_each(outvec.begin(), outvec.end(), [](auto i) { cout << i << endl; });
    
    cout << "Strings reverse and change type" << endl;
    vector<string> input2 = { "YAY", "Hello", "World", "redivider", "wait", "cheap", "carriage", "demonic", "madam", "diligent" };
    deque<string> outvec2;
    symetricOnly(input2,front_inserter(outvec2)); 
    for_each(outvec2.begin(), outvec2.end(), [](auto i) { cout << i << endl; });
  
    
    cout << "Lists of int lists" << endl;
    list< list<int> > lists = { { 1 }, { 1, 2 }, { 5, 2, 1}, { 1, 1}, { 4, 0, 4}, {2, 0, 5}, {4, 3, 6, 3}, {2, 3, 4, 2, 5, 6}, {6, 4, 3, 4, 6}};
    auto end3 = symetricOnly(lists,lists.begin()); // Should return { {1}, {1, 1} }
    for_each(lists.begin(),end3, [](auto i) { 
        for(auto j:i){
            cout << j; 
        }
        cout << endl;
    });

    cout << "Ints in place using list" << endl;
    list< int > ints = { 1, 12, 521, 11, 404, 205, 4363, 234256, 64346 };
    auto end4 = symetricOnly(ints,ints.begin());
    for_each(ints.begin(), end4, [](auto i) { cout << i << endl; });

    // If you uncomment this it should not compile
    /*
    vector<float> input5 = {1,22,333,234,654};
    auto symVec5 = symetricOnly(input5);
    */

    return 0;
}