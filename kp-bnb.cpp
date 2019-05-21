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
struct Subproblem
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
	vector<Subproblem>sub;
	Solution record;
	long int N, C;
	public:
	void ReadInput(char *file_name);
	Subproblem Bound(Subproblem &sub);
	//void Bounds(int i);
	void BnB_Solver();
};
bool comp_sort(const Knapsack &a, const Knapsack &b){
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
    sort(knp.begin(), knp.end(), comp_sort);
}
Subproblem BnB_algo::Bound(Subproblem &sub){
	int i;
	sub.rc=C;
	for(i=0;i<sub.x.size();i++){
	 	sub.cp += knp[i].p * sub.x[i];
	 	sub.rc -= knp[i].w * sub.x[i];
	}
	while(knp[i].w<=sub.rc){
	 	sub.cp += knp[i].p;
	 	sub.rc -= knp[i].w;
	 	sub.x.push_back(1);
	 	i++;
	}
	sub.ub = sub.cp+(((double)knp[i].p/(double)knp[i].w)*(double)sub.rc);
	if(sub.cp>record.p){
	 		record.p=sub.cp;
			record.x.clear();
	 		for(int m=0; m<sub.x.size(); m++)record.x.push_back(sub.x[m]);
	 	}
	return sub;
}
/*	Subproblem temp_x1, temp_x0;
	int k=i+1;
	temp_x1.cp=0;
	temp_x1.rc=C;
	temp_x0.cp=0;
	temp_x0.rc=C;
	if(sub.size()==0){
	 	while(knp[i].w<=temp_x1.rc){
	 		temp_x1.cp += knp[i].p;
	 		temp_x1.rc -= knp[i].w;
	 		temp_x1.x.push_back(1);
	 		i++;
		}
		while(knp[k].w<=temp_x0.rc){
			temp_x0.cp += knp[k].p;
	 		temp_x0.rc -= knp[k].w;
	 		temp_x0.x.push_back(1);
	 		k++;
		}
		temp_x1.ub=temp_x1.cp+(((double)knp[i].p/(double)knp[i].w)*(double)temp_x1.rc);
		temp_x0.ub=temp_x0.cp+(((double)knp[k].p/(double)knp[k].w)*(double)temp_x0.rc);
		sub.push_back(temp_x1);
		sub.push_back(temp_x0);
		sol.p=temp_x1.cp;
		sol.x.clear();
	 	for(int m=0; m<temp_x1.x.size(); m++)sol.x.push_back(temp_x1.x[m]);
	 	if(temp_x0.cp>sol.p){
	 		sol.p=temp_x0.cp;
			sol.x.clear();
	 		for(int m=0; m<temp_x0.x.size(); m++)sol.x.push_back(temp_x0.x[m]);
	 	}
	 	temp_x1.x.clear();
	 	temp_x0.x.clear();
	}
	if(sub.size()>0){
		for(int j=0;i<sub[i-1].x.size();j++){
	 		temp_x1.cp += knp[j].p * sub[i-1].x[j];
	 		temp_x0.cp = temp_x1.cp;
	 		temp_x1.rc -= knp[j].w * sub[i-1].x[j];
	 		temp_x0.rc = temp_x1.rc;
	 		temp_x1.x.push_back(sub[i-1].x[j]);
	 		temp_x0.x.push_back(sub[i-1].x[j]);
	 	}
	 	while(knp[i].w<=temp_x1.rc){
	 		temp_x1.cp += knp[i].p;
	 		temp_x1.rc -= knp[i].w;
	 		temp_x1.x.push_back(1);
	 		i++;
		}
		while(knp[k].w<=temp_x0.rc){
			temp_x0.cp += knp[k].p;
	 		temp_x0.rc -= knp[k].w;
	 		temp_x0.x.push_back(1);
	 		k++;
		}
		temp_x1.ub=temp_x1.cp+(((double)knp[i].p/(double)knp[i].w)*(double)temp_x1.rc);
		temp_x0.ub=temp_x0.cp+(((double)knp[k].p/(double)knp[k].w)*(double)temp_x0.rc);
		sub.push_back(temp_x1);
		sub.push_back(temp_x0);
		if(temp_x1.cp>sol.p){
			sol.p=temp_x1.cp;
			sol.x.clear();
	 		for(int m=0; m<temp_x1.x.size(); m++)sol.x.push_back(temp_x1.x[m]);
		}
		if(temp_x0.cp>sol.p){
			sol.p=temp_x0.cp;
			sol.x.clear();
	 		for(int m=0; m<temp_x0.x.size(); m++)sol.x.push_back(temp_x0.x[m]);
		}
		temp_x1.x.clear();
		temp_x0.x.clear();
	}
}*/
void BnB_algo::BnB_Solver(){
	int i, j;
	Subproblem temp_x1, temp_x0;
	temp_x1.x.push_back(1);
	sub.push_back(Bound(temp_x1));
	temp_x0.x.push_back(0);
	sub.push_back(Bound(temp_x0));
	for(i=0; i<sub.size(); i++){
		cout<<"\n sub "<<i+1<<" = (cp="<<sub[i].cp<<", rc="<<sub[i].rc<<", ub="<<sub[i].ub<<") {";
		for(j=0; j<sub[i].x.size(); j++){
			cout<<sub[i].x[j];
			if(j<sub[i].x.size()-1)cout<<", ";
		}
		cout<<"}\n\n";
	}
	cout<<" Record = "<<record.p<<"\n\n";
	//temp.x.push_back(1);
	//temp_sub.cp=0;
	//temp_sub.rc=RC;
	//sub.push_back(temp_sub);
	//temp.reset();
	//cout<<"x = "<<sub[0].x[0]<<"\n";
	//cout<<"\n-----("<<sub[0].cp<<","<<sub[0].cw<<")-----\n";
	//cout<<"size = "<<sub[0].x.size()<<"\n";

	/*while(true){
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
	}*/
}
int main(int argc, char* argv[]){
	time_t start, end;
	//vector<Knapsack>input;
	//vector<Sub>sub;
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
	//cout<<fixed<<"Runtime = "<<seconds<<"\t";
	//NA.print(size);
	return 0;
}
