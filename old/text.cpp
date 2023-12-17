#include<iostream>
#include<fstream>
#include<string>
#include<map>
using namespace std;

map<string,int>mp;
int count;

void error(int count)
{
	cout<<"错误发生在第"<<count<<"行"<<endl; 
}

void checkReservedWord(string str2)
{
	if(mp[str2]==1){
		cout<<"保留字："<<str2<<endl; 
	}
	else {
		cout<<"标识符："<<str2<<endl;
	}
} 

int checkIdentifier(string str,int i)
{
	string str2;
	for(int j=i;j<str.length();j++){
		if((str[j]>='a'&&str[j]<='z')||(str[j]>='A'&&str[j]<='Z')||(str[j]>='0'&&str[j]<='9')){
			str2+=str[j];
		}
		else {
			checkReservedWord(str2);
			return j-1;
		}
	}
	cout<<endl;
}

int checkZeroDigit(string str,int i)
{
	for(int j=i+1;j<str.length();j++){
		if(str[j]!=' '||str[j]!='<'||
		str[j]!='>'||str[j]!='='||str[j]!='/'||
		str[j]!='!'||str[j]!='('||str[j]!=')'||
		str[j]!=';'||str[j]!='{'||str[j]!='}'){
			error(count);
			return j-1;
		}
	}
	cout<<"数字："<<str[i]<<endl;
}

int checkNotZeroDigit(string str,int i)
{
	string str2;
	for(int j=i;j<str.length();j++){
		if(str[j]>='0'&&str[j]<='9'){
			str2+=str[j];
		}
		else if(str[j]==' '||str[j]=='<'||
		str[j]=='>'||str[j]=='='||str[j]=='/'||
		str[j]=='!'||str[j]=='('||str[j]==')'||
		str[j]==';'||str[j]=='{'||str[j]=='}'){
			cout<<"数字："<<str2<<endl;
			return j-1;
		}
		else {
			error(count);
			return j-1;
		}
	}
}

void checkSeparator(char x)
{
	cout<<"分隔符："<<x<<endl; 
}

void checkExegesis(string str,int i)
{
	cout<<"注释：";
	for(int j=i;j<str.length();j++){
		cout<<str[j];
	} 
	cout<<endl;
}

void checkArithmeticOperator(char x)
{
	cout<<"运算符："<<x<<endl; 
}

int checkComparisonOperator(string str,int i)
{
	if(str[i+1]=='='){
		cout<<"运算符："<<str[i]<<str[i+1]<<endl;
		return i+1;
	}
	else{
		cout<<"运算符："<<str[i]<<endl;
		return i;
	}
}

int checkNotEqualOperator(string str,int i)
{
	if(str[i+1]=='='){
		cout<<"运算符："<<str[i]<<str[i+1]<<endl;
		return i+1;
	}
}

void reservedWord(){
	mp["if"]=1;
	mp["else"]=1;
	mp["for"]=1;
	mp["while"]=1;
	mp["do"]=1;
	mp["int"]=1;
	mp["write"]=1;
	mp["read"]=1;
}

int main(){
	reservedWord();
    ifstream file;
    file.open("./lex.txt"); 
    string str;
    count = 0;
    while (getline(file, str)) {
        count++;
		for(int i=0;i<str.length();i++){
			char x = str[i];
			if(x=='0'){
				i = checkZeroDigit(str,i); //识别数字零 
			}
			else if(x>='1'&&x<='9'){
				i = checkNotZeroDigit(str,i);	//识别非零数字 

			} 
			else if(x=='('||x==')'||x==';'||x=='{'||x=='}'){
				checkSeparator(x); //识别分隔符 
			}
			else if(x=='/'){
				if(str[i+1]=='/'){
					checkExegesis(str,i); //识别注释 
					break;
				}
				else {
					checkArithmeticOperator(x); //识别算数运算符 
				}
			}
			else if(x=='+'||x=='-'||x=='*') {
				checkArithmeticOperator(x); 	//识别算数运算符 
			}
			else if(x=='<'||x=='>'||x=='=') {
				i = checkComparisonOperator(str,i);	//识别比较运算符 
			} 
			else if(x=='!') {
				i = checkNotEqualOperator(str,i);	//识别不等于运算符 
			}
			else if(x>='a'&&x<='z'||x>='A'&&x<='Z'){
				i = checkIdentifier(str,i);		//识别标识符 
			}
			else if(x==' '){
				continue;
			}
			else{
				error(count);
			}
		}
    }
    return 0;
}
