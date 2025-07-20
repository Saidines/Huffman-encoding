#include<bits/stdc++.h>
#include<fstream>
using namespace std;
struct Node{
	char ch;
	int freq;
	Node*left;
	Node*right;
	int v;
	Node(char ch,int f):ch(ch),freq(f),left(NULL),right(NULL){}
	};
	
	
struct compare{	
bool operator()(const Node*a,const Node*b){
	return a->freq>b->freq;
}};
	
void buildCodes(Node*root,string code,unordered_map<char,string>&codemap){
	if(root==NULL) return;
	
	if(root->left==NULL&&root->right==NULL){
	codemap[root->ch]=code;
	}
	buildCodes(root->left,code+"0",codemap);
	buildCodes(root->right,code+"1",codemap);
}
	
unordered_map<char,string> huffmancoding(const unordered_map<char,int>&freq){
	
	
	priority_queue<Node*,vector<Node*>,compare>pq;
	for(auto pair:freq){
		Node*x=new Node(pair.first,pair.second);
		pq.push(x);
	}
	
	while(pq.size()>1){
		Node*left=pq.top();
		pq.pop();
		Node*right=pq.top();
		pq.pop();
		Node*merged=new Node('\0',left->freq+right->freq);
		merged->left=left;
		merged->right=right;
		pq.push(merged);
	}
	
	Node*root=pq.top();
	unordered_map<char,string>codemap;
	buildCodes(root,"",codemap);
	return codemap;
	
	}
	
	int main(int argc,char**argv){
	
	unordered_map<char,int>freq;
	
	if(argc!=2){
		cout<<"incorrect number of arguments";
		return 1;
	}
	string s;
	s=argv[1];
	ifstream inFile(s);
	if(!inFile){
	cout<<"problem with reading the file";
	return 1;
	}
	string line;
	while(getline(inFile,line)){
		for(char c:line){
		freq[c]++;
		}
		freq['\n']++;
	
	}
	
	
	
		unordered_map<char,string>codemap;
		codemap=huffmancoding(freq);
		int total=0;
		int compressed=0;
		for(auto i:codemap){
		total+=freq[i.first]*8;
		compressed+=freq[i.first]*(i.second.size());
		cout<<i.first<<' '<<i.second<<endl;
		}
		cout<<total<<"   "<<compressed;
	
	}
	
	




	
	
