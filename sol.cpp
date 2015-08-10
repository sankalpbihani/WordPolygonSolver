#include <bits/stdc++.h>

using namespace std;

class trie
{
private:
    /**
        Vector of states(nodes).
        Each state contains:
        1. Vector to denote Links to other states depending on character.   :data.first
        2. Boolean to determine if this is end of a word.                   :data.second.first
        3. Integer to count the number of valid children the state has.     :data.second.second
    **/
    vector<pair<vector<int>,pair<bool,bool>>> data;

    int addToData()
    {
        data.push_back(make_pair(vector<int>(26,-1),make_pair(false,0)));
        return data.size()-1;
    }

public:
    trie()
    {
        assert(addToData() == 0);
    }

    /// Add a new string to trie.
    void add(string s)
    {
        int curr = 0;

        for(int i=0; i<s.size(); i++)
        {
            if(data[curr].first[s[i]-'A'] == -1)
            {
                data[curr].first[s[i]-'A'] = addToData();
                data[curr].second.second++;
            }

            curr = data[curr].first[s[i]-'A'];
        }

        data[curr].second.first = true;
    }

    /// Check whether the string is a word appearing in trie.
    bool checkWord(string s)
    {
        int curr = 0;
        for(int i=0; i<s.size(); i++)
        {
            curr = data[curr].first[s[i]-'A'];

            if(curr == -1)
                return false;
        }

        return data[curr].second.first;
    }

    /// Check whether string is a proper prefix of any word in trie.
    bool checkStrictPrefix(string s)
    {
        int curr = 0;
        for(int i=0; i<s.size(); i++)
        {
            curr = data[curr].first[s[i]-'A'];

            if(curr == -1)
                return false;
        }

        return data[curr].second.second;
    }

    /// Check whether string is a prefix of any word in trie.
    bool checkPrefix(string s)
    {
        return checkStrictPrefix(s) || checkWord(s);
    }

    /// Given current state and character, return the next state in trie.
    int nextState(int curr, char c)
    {
        if(curr < 0 || curr >= data.size())
            return -1;

        return data[curr].first[c - 'A'];
    }

    /// Check whether the current state is end of a word.
    bool checkWordState(int curr)
    {
        if(curr < 0 || curr >= data.size())
            return false;

        return data[curr].second.first;
    }

    /// Check whether the current state is proper prefix of some word.
    bool checkStrictPrefixState(int curr)
    {
        if(curr < 0 || curr >= data.size())
            return false;

        return data[curr].second.second;
    }

    /// Check whether the current state is prefix of some word.
    bool checkPrefixState(int curr)
    {
        return checkStrictPrefixState(curr) || checkWordState(curr);
    }
};

class solver
{
    /**
        grid - input grid of characters
        dict - input trie of allowed words
        seen - used in backtracking to see if character already visited
        ans - stores found words
        n, m - stores grid size (for convenience)
    **/
    vector<vector<char>> grid;
    trie dict;

    vector<vector<bool>> seen;
    set<string> ans;
    int n, m;

    void backtrack(int i, int j, string curr="", int state=0)
    {
        if(i < 0 || i >= n || j < 0 || j >= m || seen[i][j]) return;

        seen[i][j] = true;

        curr += grid[i][j];
        state = dict.nextState(state, grid[i][j]);

        if(dict.checkWordState(state))
            ans.insert(curr);

        if(dict.checkStrictPrefixState(state))
            for(int ii = i-1; ii <= i+1; ii++)
                for(int jj=j-1; jj <= j+1; jj++)
                    backtrack(ii, jj, curr, state);

        seen[i][j] = false;
    }

public:
    solver(vector<vector<char>> Grid, trie Dict)
    {
        grid = Grid;
        dict = Dict;
        n = grid.size();
        m = (n)?(grid[0].size()):0;
        seen.resize(n, vector<bool>(m, false));
    }

    set<string> solve()
    {
        ans.clear();
        seen.clear();

        if(!n || !m) return ans;

        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                backtrack(i, j);

        return ans;
    }
};

int main()
{
    ifstream dictionary("dict.txt");

    trie dict;
    string s;

    /// Create Trie from dictionary
    while(dictionary >> s)
        dict.add(s);

    /// Sanity Tests
    assert(dict.checkWord("ELEPHANT") == true);
    assert(dict.checkWord("ELEPHAAA") == false);
    assert(dict.checkWord("ELEPHA") == false);

    assert(dict.checkStrictPrefix("ELEPHANTS") == false);
    assert(dict.checkStrictPrefix("ELEPHANT") == true);
    assert(dict.checkStrictPrefix("ELEPHAAA") == false);
    assert(dict.checkStrictPrefix("ELEPHA") == true);

    assert(dict.checkPrefix("ELEPHAAA") == false);
    assert(dict.checkPrefix("ELEPHA") == true);
    assert(dict.checkPrefix("ELEPHANTS") == true);
    assert(dict.checkPrefix("ELEPHANT") == true);

    cout<<"Trie Prepared"<<endl;

    /// Input Loop
    while(true)
    {
        /**
            Input:
            n : rows in grid
            m : columns in grid
            followed by n*m characters given row wise
        **/
        int n, m;
        cin>>n>>m;

        if(!n || !m) break;

        vector<vector<char>> grid(n, vector<char>(m));

        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
            {
                cin>>grid[i][j];
                grid[i][j] = toupper(grid[i][j]);
            }

        solver sol(grid, dict);
        set<string> swords = sol.solve();
        vector<string> words(swords.begin(), swords.end());

        /**
            Output is given sorted according to following parameters
            - by length in decreasing order
            - lexicographically for words of same length
        **/

        sort(words.begin(), words.end(),
        [](const string &a, const string &b) -> bool
        {
            if(a.size() == b.size())
                return (a < b);
            else
                return a.size() > b.size();
        });

        for(string w: words) cout<<w<<endl;
        cout<<endl;
    }
}
