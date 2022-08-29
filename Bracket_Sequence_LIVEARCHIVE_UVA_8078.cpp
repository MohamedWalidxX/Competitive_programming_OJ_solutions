/**
 * author : Mohamed Walid Mohamed
 * CF handle : XxMr_ErR0rxX
 * Email : Moh.Walid2002@gmail.com
 * ---------------------------------------
 *
 *
 * describe solution : The problem description is telling you that for each index in your input string count the longest
 *                      balanced bracket sequence (including your current index in it)
 *
 *         OBSERVATIONS and approach: 1- every balanced bracket must start with opened bracket
 *                                    2- for every closed bracket we will print it's answer by zero from the information given above
 *                                    3- every index  == opened bracket its answer depends only with  (idx + 1, idx + 2, idx + 3, ... , string.size())
 *                                    4- as a conclusion from last point the answer[string.size()] == ZERO (every time)
 *                                    5- from all the above we can calculate our answer using reversed string and stack saves the closed brackets
 *                                    till we find it's matched opened bracket
 *                                    6- assume that the substring of string[idx] to string[k]  is a balanced subsequence brackets
 *                                          therefore if there exist a nested substring in this substring it must be balanced too
 *                                              and its answer will be saved in answer[idx + 1]
 *                                              and answer[idx] will be equal to answer[idx] = answer[idx + 1] + 1 + some factor we will talk about it.
 *                                    7- after this implementation every answer[idx] will have the length of it's balanced bracket starting from string[idx]
 *                                          and end with string[k] and every and for every Z between ]idx, k[ (answer[idx] < answer[Z] > answer[k])
 *                                    8- notice that this approach does not consider every other blocks of balanced subsequence brackets in its answer
 *                                          and that is wrong !!
 *                                    9- to solve it you must peak to answer[k + 1] and if it has an answer we will add it to our answer[idx]
 *                                          example : [[]] [] [] [] 
 *                                          in buggy solution answer[0] == 4 (its bracket + the nested bracket)
 *                                          in accepted solution answer[0] == 10 (its bracket + the nested bracket + next neighbour.
 */

#include <bits/stdc++.h>

using namespace std;
vector<int>ans;
stack<int>st;
void clearSt(){
    while (!st.empty())
        st.pop();
}
int main() {
    int t,cnt = 0;
    string s;
    cin >> t;
    while (t--){
        cnt++;
        cin >> s;
        ans.clear();
        clearSt();
        ans = vector<int>(1e6,0);
        for (int i = s.size() - 1, sz = s.size(); i >= 0; i--){
            ans[i] = 0;
            if (s[i] == ')' || s[i] == ']' || s[i] == '}' || s[i] == '>'){
                ans[i] = 0;
                st.push(i);
            }
            else {
                if (!st.empty()){
                    int top = st.top(); st.pop();
                    // make use of ASCII TABLE 
                    if ((s[top] == s[i] + 1 || s[top] == s[i] + 2)){
                        if (top - 1 == i  && !((s[i] == ')' || s[i] == ']' || s[i] == '}' || s[i] == '>')) )
                            ans[i] = ans[i + 2];
                        else if (top - 1 != i)
                            ans[i] = ans[i + 1] + ans[top + 1];
                        ans[i] += 1;
                    }
                    else if (!st.empty())
                        clearSt();
                    ans[top] = 0;
                }

            }
        }
        cout << "Case " << cnt << ":\n";
        int i  =0, sz = s.size();
        for (; i < sz; i++){
            if (i == sz - 1){
                cout << ans[i];break;
            }
            cout << ans[i] * 2 << "\n";
        }
        // ERROR ???
        if (t) cout << "\n";
        else
            return 0;
    }
    return 0;
}

