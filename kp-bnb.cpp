#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<algorithm>
#include<vector>
using namespace std;
struct Knapsack
{
	int p, w, k;
	float div;
};
struct Subproblems
{
	vector<int>x;
	int cp = 0;
	int rc = 0;
	int ub = 0;
};
struct Solution
{
	vector<int>x;
	int p=0;
};
class BnB_algo{
	vector<Knapsack>knp;
	vector<Subproblems>sub;
	Solution sol;
	long int N, C;
	public:
	void ReadInput(char *file_name);
	void Bound(int i);
	void BnB_Solver();
};
bool compare(const Knapsack &a, const Knapsack &b){
	return a.div > b.div;
}
void BnB_algo::ReadInput(char *file_name){
	ifstream g;
	int a, b, i=0;
	g.open(file_name);
	if(!g.is_open()){
      		std::cerr << "Error: file could not be opened for <g>." << std::endl;
      		exit(1);
       	}
	g >> N;
	g >> C;
	for(i = 0; i < N; i ++){
		g >> a;
		g >> b;
		knp.push_back(Knapsack());
		knp[i].p = a;
		knp[i].w = b;
		knp[i].k = i;
		knp[i].div = ((float)a)/((float)b);
	}
    g.close();
    sort(knp.begin(), knp.end(), compare);
}
void BnB_algo::Bound(int i){
	Subproblems temp;
	temp.cp=0;
	temp.rc=C;
	if(sub.size()==0){
	 	while(knp[i].w<=temp.rc){
	 		temp.cp += knp[i].p;
	 		temp.rc -= knp[i].w;
	 		temp.x.push_back(1);
	 		i++;
		}
		temp.ub=temp.cp+(((double)knp[i].p/(double)knp[i].w)*(double)temp.rc);
		sub.push_back(temp);
		sol.p=temp.cp;
		sol.x.clear();
	 	for(int m=0; m<temp.x.size(); m++)sol.x.push_back(temp.x[m]);
	 	temp.x.clear();
	}
	if(sub.size()>0){
		for(int j=0;i<sub[i-1].x.size();j++){
	 		temp.cp += knp[j].p * sub[i-1].x[j];
	 		temp.rc -= knp[j].w * sub[i-1].x[j];
	 		temp.x.push_back(sub[i-1].x[j]);
	 	}
	 	while(knp[i].w<=temp.rc){
	 		temp.cp += knp[i].p;
	 		temp.rc -= knp[i].w;
	 		temp.x.push_back(1);
	 		i++;
		}
		temp.ub=temp.cp+(((double)knp[i].p/(double)knp[i].w)*(double)temp.rc);
		sub.push_back(temp);
		if(temp.cp>sol.p){
			sol.p=temp.cp;
			sol.x.clear();
	 		for(int m=0; m<temp.x.size(); m++)sol.x.push_back(temp.x[m]);
		}
		temp.x.clear();
	}
}
void BnB_algo::BnB_Solver(){
	int RC=C, LB=0, UB=0, SUM=0, X1_p=0, X1_rc=0, X0_p=0, X0_rc=0, i=0, j=0, k=0, l=0;
	//temp.x.push_back(1);
	//temp_sub.cp=0;
	//temp_sub.rc=RC;
	//sub.push_back(temp_sub);
	//temp.reset();
	//cout<<"x = "<<sub[0].x[0]<<"\n";
	//cout<<"\n-----("<<sub[0].cp<<","<<sub[0].cw<<")-----\n";
	//cout<<"size = "<<sub[0].x.size()<<"\n";
	while(true){
		 if(sub.size()>1){
		 	for(j=0;i<sub[i-1].x.size();j++){
		 		SUM=SUM+(input[j].p*sub[i-1].x[j]);
		 		RC=RC-(input[j].w*sub[i-1].x[j]);
		 		temp_sub.x.push_back(sub[i-1].x[j]);
		 	}
		 }
		 k=i;
		 while(input[k].w<=RC){
		 	X1_p = X1_p+input[k].p;
		 	RC = RC-input[k].w;
		 	temp_sub.x.push_back(1);
		 	k++;
		 }
		 LB=SUM+X1_p;
		 UB=LB+(((double)input[k].p/(double)input[k].w)*(double)RC);
		 temp_sub.cp=UB;
		 temp_sub.rc=RC;
		 sub.push_back(temp_sub);
		 if(LB>record.p){
		 	record.p=LB;
		 	record.x.clear();
		 	for (int m=0; m<temp_sub.x.size(); m++) 
        		record.x.push_back(temp_sub.x[m]);
		 }
		 k=i+1;
		 for(int n=0;n<sub.size();n++){
		 	cout<<"\n("<<sub[n].cp<<","<<sub[n].rc<<")\nx = (";
		 	for(int o=0;o<sub[n].x.size();o++)cout<<sub[n].x[o]<<",";
		 	cout<<")\n";
		 }
		 cout<<"Record = "<<record.p<<"\nx = (";
		 for(int p=0;p<record.x.size();p++)cout<<record.x[p]<<",";
		 cout<<")\n";
		i++;
		 cin.get();
	}
}
int main(int argc, char* argv[]){
	time_t start, end;
	vector<Knapsack>input;
	vector<Sub>sub;
	int size;
	char* str = NULL;
    if(argc >= 2){
		str = argv[1];
   	}
    else{
    	fprintf(stderr, "usage: %s <input_file>\n", argv[0]);
    	exit(-1);
   	}
	BnB_algo NA;
	NA.ReadInput(str);
	start = clock();
	NA.BnB_Solver();
	end = clock();
	float diff((float)end-(float)start);
	float seconds = diff/CLOCKS_PER_SEC;
	cout<<fixed<<"Runtime = "<<seconds<<"\t";
	//NA.print(size);
	return 0;
}
