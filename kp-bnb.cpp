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
struct Sub
{
	vector<int>x;
	int cp=0;
	int cw=0;
};
struct Record
{
	vector<char>x;
	int p=0;
	int rc=0;
};
class BnB_algo{
	vector<Knapsack>input;
	vector<Sub>sub;
	long int N, C;
	public:
	void ReadInput(char *file_name);
	int LowerBound(int i, int rc);
	int UpperBound(int p, int rc);
	void BnB_Solver();
	void PrintResult(int size);
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
		input.push_back(Knapsack());
		input[i].p = a;
		input[i].w = b;
		input[i].k = i;
		input[i].div = ((float)a)/((float)b);
	}
    g.close();
    sort(input.begin(), input.end(), compare);
}
int BnB_algo::LowerBound(int sp, int rc){
	int sum=0, i=sp;
	while(rc>=input[i].w){
		sum=input[i].p+sum;
		rc=rc-input[i].w;
		i++;
	}
	if(sp==0){
		Sub temp;
		temp.x.push_back(1);
		temp.cp=sum;
		temp.cw=rc;
	}
	return sum;
}
int BnB_algo::UpperBound(int i, int rc){
	double sum=0;
	while(rc>=input[i].w){
		sum=input[i].p+sum;
		rc=rc-input[i].w;
		i++;
	}
	//cout<<"\n---InUBLoop1---\n"<<sum<<"=="<<rc<<"+++"<<input[i].p<<","<<input[i].w;
	//cin.get();
	//if(sum>record)record=sum;
	if(rc>0)sum=sum+(((double)input[i].p/(double)input[i].w)*(double)rc);
	//cout<<"\n---InUBLoop1---\n"<<sum<<"=="<<rc;
	//cin.get();
	return floor(sum);
}
void BnB_algo::BnB_Solver(){
	int RC=C, LB, UB, SUM=0, W=0;
	Sub temp;
	//temp.x.push_back(1);
	temp.cp=0;
	temp.cw=C;
	sub.push_back(temp);
	//temp.reset();
	cout<<"x = "<<sub[0].x[0]<<"\n";
	cout<<"\n-----("<<sub[0].cp<<","<<sub[0].cw<<")-----\n";
	//cout<<"size = "<<sub[0].x.size()<<"\n";
	while(true){
		int i=0;
		 if(sub.size()>1){
		 	for(int j=0;i<sub[i-1].x.size();j++){
		 		SUM=SUM+(input.[j].p*sub[i-1].x[j]);
		 		W=W+(input.[j].w*sub[i-1].x[j]);
		 	}
		 }
		 for(int k=i; k<N; k++){
		 	
		 }

	}
	//LB=LowerBound(0, RC);
	//UB=UpperBound(0, RC);
	//Sub temp;
	//temp.x.push_back(1);
	//temp.cp=LB;
	//temp.cw=
	//cout<<"\n-----\n"<<LB;
	//cout<<"\n-----\n"<<UB;
	//cin.get();
	/*if(LowerBound(0, RC)>record){
		Sub[0].x='1';
		Sub[0].cp=input[0].p;
		Sub[0].cw=RC-input[0].w;
	}
	if(BnB(1, RC)>record)Sub[0].x='0';
	for(int i=1; i<N; i++){
		UB1=Sub[k].cp+BnB(i, RC);
		UB2=Sub[k].cp+BnB(i+1, RC);
	}*/
}
/*void BnB_algo::print(int size){


}*/
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
