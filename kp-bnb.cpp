#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<algorithm>
#include<vector>

using namespace std;

using itemtype = int;

struct Knapsack
{
    int p, w, k;
    float div;
};

struct Subproblem
{
    Subproblem(const vector<itemtype>& xn, int cpn, int rcn)
    	: x(xn), cp(cpn), rc(rcn)
    {
    }
    const vector<itemtype> x;
    const int cp = 0;
    const int rc = 0;
    int ub = 0;
};

struct Solution
{
    vector<itemtype> x;
    int p = 0;
};

class BnB
{
    vector<Knapsack>knp;
    vector<Subproblem>sub;
    Solution record;
    long int N, C;
public:
    void readInput(char *file_name);
    Subproblem bound(Subproblem &sub);
    void solver();
    friend ostream& operator<<(ostream& os, const Subproblem& sub);
    friend ostream& operator<<(ostream& os, const Solution& record);
};

ostream& operator<<(ostream& os, const Subproblem& sub)
{
    os << "Subproblem " << 1 << " = (cp=" << sub.cp << ", rc=" << sub.rc << ", ub=" << sub.ub << ") x = {";
    for (int j = 0; j < sub.x.size(); j++)
    {
        os << sub.x[j];
        if (j < sub.x.size() - 1)os << ", ";
    }
    os << "}\n";
    return os;
}

ostream& operator<<(ostream& os, const Solution& record)
{
	os << "Record = " << record.p << "  x = (";
    for (int i = 0; i < record.x.size(); i++)
    {
        os << record.x[i];
        if (i < record.x.size() - 1)os << ", ";
    }
    os << ")\n";
    return os;
}

bool sortInput(const Knapsack &a, const Knapsack &b)
{
    return a.div > b.div;
}

void BnB::readInput(char *file_name)
{
    ifstream g;
    int a, b, i = 0;
    g.open(file_name);
    if (!g.is_open()) {
        std::cerr << "Error: file could not be opened for <g>." << std::endl;
        exit(1);
    }
    g >> N;
    g >> C;
    for (i = 0; i < N; i++) {
        g >> a;
        g >> b;
        knp.push_back(Knapsack());
        knp[i].p = a;
        knp[i].w = b;
        knp[i].k = i;
        knp[i].div = ((float) a) / ((float) b);
    }
    g.close();
    sort(knp.begin(), knp.end(), sortInput);
}

Subproblem BnB::bound(Subproblem &sub) {
    int i = sub.x.size();
    int rc = sub.rc;
    int cp = sub.cp;
    vector<itemtype> x;
    while (knp[i].w <= rc) {
        cp += knp[i].p;
        rc -= knp[i].w;
        x.push_back(1);
        i++;
    }
    sub.ub = cp + (((double) knp[i].p / (double) knp[i].w)*(double) rc);
    if (cp > record.p) {
        record.p = cp;
        record.x.clear();
        
        record.x.insert(record.x.end(), sub.x.begin(), sub.x.end());
        record.x.insert(record.x.end(), x.begin(), x.end());
    }
    return sub;
}

void BnB::solver()
{
    int i, j;
    vector<itemtype> v1, v0;
    v0.push_back(0);
    v1.push_back(1);
    Subproblem s0(v0, 0, C);
    Subproblem s1(v1, knp[0].p, C - knp[0].w);
    
    sub.push_back(bound(s0));
    cout<<sub[0];
    cout<<record;
    sub.push_back(bound(s1));
    cout<<sub[1];
    cout<<record;
}

int main(int argc, char* argv[])
{
    time_t start, end;
    int size;
    char* str = NULL;
    if (argc >= 2) {
        str = argv[1];
    } else {
        fprintf(stderr, "usage: %s <input_file>\n", argv[0]);
        exit(-1);
    }
    BnB NA;
    NA.readInput(str);
    start = clock();
    NA.solver();
    end = clock();
    float diff((float) end - (float) start);
    float seconds = diff / CLOCKS_PER_SEC;
    //cout<<fixed<<"Runtime = "<<seconds<<"\t";
    return 0;
}
