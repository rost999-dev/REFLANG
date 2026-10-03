#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#define TEXT_LEN 2048
#define FUNC_COUNTER 32
    int skip=0;
    int eval=0;
    long int code;
	long int now;
	long int new_now;
	long int now_command;
	typedef struct{
		long int start;
		long int end;
		long int num;
		long int step;
		long int end_num;
	}new_loop;
	new_loop loop;
	
	typedef struct{
		int start;
		int end;
		int els;
		
	}new_if;
	new_if nif;
typedef struct{
	char *buf[5];
	char *command[TEXT_LEN];
	long int command_counter;
	long int var_counter;
	long int text_len;
	char *input;
	char *file_name;
	long int import;
}REFLANG_console;
REFLANG_console RFL;

typedef struct{
	void (*func)(char *,char *,char *,char *,char *);
	char *temp;
	long int args;
	char *com;
	long int var_work;
}new_func;
new_func *func;
typedef struct{
	char *name;
	char *info;
}new_var;
new_var *var;

void cmd_strout(char *text,char *non2, char *non3, char *non4,char* non5){
	printf("%s",text);
	fflush(stdout);
};

void cmd_endl(char *counter,char *non2, char *non3, char *non4,char *non5){
	long int index;
	for(index=0;index<atol(counter);index+=1){
	printf("\n");
	}
}
void cmd_sleep(char *counter,char *non2, char *non3, char *non4,char *non5){
	long int new_time=time(NULL)+atol(counter);
	while(time(NULL)<new_time){
		;
	}
}
void cmd_open(char *name,char *non2, char *non3, char *non4,char *non5){
	free(RFL.file_name);
	RFL.file_name=(char*)malloc((strlen(name)+1)*sizeof(char));
	strcpy(RFL.file_name,name);
}
void cmd_exit(char *name,char *non2, char *non3, char *non4,char *non5){
	exit(atol(name));
}
void cmd_read(char *name,char *non2, char *non3, char *non4,char *non5){
	if(strcmp(RFL.file_name,"")!=0){
		FILE *f=fopen(RFL.file_name,"r");
		if(f!=NULL){
		    long int var_each;
		    for(var_each=0;var_each<RFL.var_counter;var_each+=1){
		    	if(strcmp(var[var_each].name,name)==0){
		    		while(fgets(RFL.buf[4],RFL.text_len,f)){
		    			strcat(var[var_each].info,RFL.buf[4]);
		    		}
		    	}
		    }
		    fclose(f);
		}
		
		
	}
}
void cmd_remove(char *name,char *non2, char *non3, char *non4,char *non5){
	remove(name);
}

void cmd_write(char *name,char *non2, char *non3, char *non4,char *non5){
	if(strcmp(RFL.file_name,"")!=0){
		FILE *f=fopen(RFL.file_name,"w+");
		if(f!=NULL){
			fprintf(f,"%s",name);
			fclose(f);
		}
	}
}
void cmd_time(char *name,char *non2, char *non3, char *non4,char *non5){
	long int var_each;
	for(var_each=0;var_each<RFL.var_counter;var_each+=1){
		if(strcmp(var[var_each].name,name)==0){
			sprintf(var[var_each].info,"%ld",time(NULL));
		}
	}
}
void cmd_struct(char *name,char *non2, char *non3, char *non4,char *non5){
	if(strcmp(name,"list")==0 || strcmp(name,"arr")==0){
		char *save_name=(char*)malloc(RFL.text_len *sizeof(char));
		long int counter=0;
		for(counter=0;counter<atol(non2);counter+=1){
			sprintf(save_name,"%s[%ld]",non3,counter);
			var[RFL.var_counter].name=(char*)malloc(TEXT_LEN*sizeof(char));
	var[RFL.var_counter].info=(char*)malloc(TEXT_LEN*sizeof(char));
	strcpy(var[RFL.var_counter].name,save_name);
	strcpy(var[RFL.var_counter].info,"");
	RFL.var_counter+=1;
		}
		free(save_name);
	}
	if(strcmp(name,"dict")==0){
		char *save_name=(char*)malloc(RFL.text_len *sizeof(char));
		sprintf(save_name,"%s[%s]",non3,non2);
		var[RFL.var_counter].name=(char*)malloc(TEXT_LEN*sizeof(char));
	var[RFL.var_counter].info=(char*)malloc(TEXT_LEN*sizeof(char));
	strcpy(var[RFL.var_counter].name,save_name);
	strcpy(var[RFL.var_counter].info,"");
	RFL.var_counter+=1;
		free(save_name);
	}
}
void cmd_set(char *name,char *non2, char *non3, char *non4,char *non5){
	long int var_each;
	for(var_each=0;var_each<RFL.var_counter;var_each+=1){
		if(strcmp(var[var_each].name,non2)==0){
			sprintf(non2,"%s",var[var_each].info);
		}
	}
	for(var_each=0;var_each<RFL.var_counter;var_each+=1){
		if(strcmp(var[var_each].name,non3)==0){
			sprintf(non3,"%s",var[var_each].info);
		}
	}
	sprintf(name,"%s[%s]",name,non2);
	for(var_each=0;var_each<RFL.var_counter;var_each+=1){
		if(strcmp(var[var_each].name,name)==0){
			sprintf(var[var_each].info,"%s",non3);
		}
	}
}
void cmd_rand(char *name,char *non2, char *non3, char *non4,char *non5){
	long int var_each;
	for(var_each=0;var_each<RFL.var_counter;var_each+=1){
		if(strcmp(var[var_each].name,non2)==0){
			sprintf(non2,"%s",var[var_each].info);
		}
		if(strcmp(var[var_each].name,non3)==0){
			sprintf(non3,"%s",var[var_each].info);
		}
	}
	for(var_each=0;var_each<RFL.var_counter;var_each+=1){
		if(strcmp(var[var_each].name,name)==0){
			sprintf(var[var_each].info,"%ld",(rand() % ((atol(non3)+1)-atol(non2)))+atol(non2));
		}
	}
}
void cmd_rng(char *name,char *non2, char *non3, char *non4,char *non5){
	long int var_each;
	for(var_each=0;var_each<RFL.var_counter;var_each+=1){
		if(strcmp(var[var_each].name,non2)==0){
			sprintf(non2,"%s",var[var_each].info);
		}
		if(strcmp(var[var_each].name,non3)==0){
			sprintf(non3,"%s",var[var_each].info);
		}
	}
	for(var_each=0;var_each<RFL.var_counter;var_each+=1){
		if(strcmp(var[var_each].name,name)==0){
			sprintf(var[var_each].info,"%ld",((time(NULL)/atol(non4)) % ((atol(non3)+1)-atol(non2)))+atol(non2));
		}
	}
}
void cmd_cmd(char *name,char *non2, char *non3, char *non4,char *non5){
	system(name);
}

void cmd_append(char *name,char *non2, char *non3, char *non4,char *non5){
	if(strcmp(RFL.file_name,"")!=0){
		FILE *f=fopen(RFL.file_name,"a");
		if(f!=NULL){
			fprintf(f,"%s",name);
			fclose(f);
		}
	}
}
void cmd_debug(char *name,char *ascii, char *info, char *non4,char *non5){
	if(strcmp(name,"var")==0){
		long int var_each=0;
		for(var_each=0;var_each<RFL.var_counter;var_each+=1){
			printf("%s - %s\n",var[var_each].name,var[var_each].info);
		}
	}else if(strcmp(name,"command")==0){
		printf("%ld\n",RFL.command_counter);
	}
	else if(strcmp(name,"memory")==0){
		printf("%ld\n",RFL.text_len);
	}
}
void cmd_var(char *name,char *ascii, char *info, char *non4,char *non5){
	long int found=0;
	long int var_each;
	if(strcmp(info,"NONE")==0){
		strcpy(info,"");
	}
	if(strcmp(ascii,"=")==0){
	for(var_each=0;var_each<RFL.var_counter;var_each+=1){
		if(strcmp(var[var_each].name,name)==0){
			strcpy(var[var_each].info,info);
			found=1;
		}
	}
	
	if(found!=1){
	var[RFL.var_counter].name=(char*)malloc(TEXT_LEN*sizeof(char));
	var[RFL.var_counter].info=(char*)malloc(TEXT_LEN*sizeof(char));
	strcpy(var[RFL.var_counter].name,name);
	strcpy(var[RFL.var_counter].info,info);
	RFL.var_counter+=1;
	}
	}else{
		for(var_each=0;var_each<RFL.var_counter;var_each+=1){
			if(strcmp(info,var[var_each].name)==0){
				strcpy(info,var[var_each].info);
				break;
			}
		}
		for(var_each=0;var_each<RFL.var_counter;var_each+=1){
			if(strcmp(name,var[var_each].name)==0){
				if(strcmp(ascii,"+")==0){
					sprintf(var[var_each].info,"%ld",(atol(var[var_each].info)+atol(info)));
				}
				else if(strcmp(ascii,"-")==0){
					sprintf(var[var_each].info,"%ld",(atol(var[var_each].info)-atol(info)));
				}
				else if(strcmp(ascii,"/")==0){
					sprintf(var[var_each].info,"%ld",(atol(var[var_each].info)/atol(info)));
				}
				else if(strcmp(ascii,"*")==0){
					sprintf(var[var_each].info,"%ld",(atol(var[var_each].info)*atol(info)));
				}
				else if(strcmp(ascii,"%")==0){
					sprintf(var[var_each].info,"%ld",(atol(var[var_each].info)%atol(info)));
				}
				else if(strcmp(ascii,"<-")==0){
					strcat(var[var_each].info,info);
				}
				else if(strcmp(ascii,"{-")==0){
					strcat(var[var_each].info," ");
					strcat(var[var_each].info,info);
				}
				else if(strcmp(ascii,"[-")==0){
					strcat(var[var_each].info,"\n");
					strcat(var[var_each].info,info);
				}
				else if(strcmp(ascii,"#-")==0){
					strcat(var[var_each].info,";");
					strcat(var[var_each].info,info);
				}
				else if(strcmp(ascii,"n-")==0){
					strcat(var[var_each].info,"NONE");
				}
				else if(strcmp(ascii,"b-")==0){
					long int counter;
					for(counter=0;counter<strlen(var[var_each].info);counter+=1){
						if(counter>atol(info)){
							var[var_each].info[counter]=0;
						}
					}
				}
				else if(strcmp(ascii,"f-")==0){
					free(var[var_each].info);
					free(var[var_each].name);
					var[var_each].name=(char*)malloc(strlen(name)+1);
					var[var_each].info=(char*)malloc(strlen(info)+1);
					strcpy(var[var_each].name,name);
					strcpy(var[var_each].info,info);
				}
			}
		}
	}
}

void cmd_strin(char *name,char *non2, char *non3, char *non4,char *non5){
	long int var_each;
	for(var_each=0;var_each<RFL.var_counter;var_each+=1){
			if(strcmp(name,var[var_each].name)==0){
				fgets(var[var_each].info,RFL.text_len,stdin);
				var[var_each].info[strcspn(var[var_each].info,"\n")]=0;
			}
	}
}
void cmd_jump(char *name,char *non2, char *non3, char *non4,char *non5){
	if(atol(name)<RFL.command_counter){
	now=atol(name)-1;
	skip=1;
	}
}
void cmd_print(char *name,char *non2, char *non3, char *non4,char *non5){
	FILE *f = fopen(name,"r");
	if(f!=NULL){
		while(fgets(non2,RFL.text_len,f)){
			printf("%s",non2);
		}
	fclose(f);
	}
}
void cmd_error(char *name,char *non2, char *non3, char *non4,char *non5){
	fprintf(stderr,"ERROR:%s\n",name);
	exit(1);
	
}
void cmd_goto(char *name,char *non2, char *non3, char *non4,char *non5){
	sprintf(name,"%s:",name);
	for(new_now=0;new_now<RFL.command_counter;new_now+=1){
		if(strcmp(RFL.command[new_now],name)==0){
			now=new_now-1;
			skip=1;
			return;
		}
	}
}
void cmd_guide(char *name,char *non2, char *non3, char *non4,char *non5){
	long int func_each;
	for(func_each=0;func_each<FUNC_COUNTER;func_each+=1){
		
		if(strstr(func[func_each].temp,name)!=NULL || strcmp(name,"NONE")==0){
			printf("%ld)[ %s ] - %s",func_each,func[func_each].temp,func[func_each].com);
		}
		}
	
}
void cmd_var_out(char *name,char *info, char *non3, char *non4,char *non5){
	long int var_each=0;
	for(var_each=0;var_each<RFL.var_counter;var_each+=1){
		
	}
}
void cmd_len(char *name,char *info, char *non3, char *non4,char *non5){
	long int var_each;
	char *save;
	save=NULL;
	for(var_each=0;var_each<RFL.var_counter;var_each+=1){
		if(strcmp(name,var[var_each].name)==0){
			save=(char*)malloc(strlen(var[var_each].info)+1);
			strcpy(save,var[var_each].info);
			break;
		}
	}
	for(var_each=0;var_each<RFL.var_counter;var_each+=1){
		if(strcmp(info,var[var_each].name)==0){
			if(save!=NULL){
			sprintf(var[var_each].info,"%ld",strlen(save));
			}
		}
	}
	if(save!=NULL){
	free(save);
	}
}
void cmd_memory(char *name,char *non2, char *non3, char *non4,char *non5){
	RFL.text_len=atol(name);
	if(!(var=(new_var*)realloc(var,RFL.text_len*sizeof(new_var)))){
		printf("ERROR:var_memory broken\n");
	}
	if(!((RFL.buf[0]=(char*)realloc(RFL.buf[0],RFL.text_len*sizeof(char))))||(RFL.buf[1]=(char*)realloc(RFL.buf[1],RFL.text_len*sizeof(char)))||(RFL.buf[2]=(char*)realloc(RFL.buf[2],RFL.text_len*sizeof(char)))||(RFL.buf[3]=(char*)realloc(RFL.buf[3],RFL.text_len*sizeof(char)))||(RFL.buf[4]=(char*)realloc(RFL.buf[4],RFL.text_len*sizeof(char)))){
		printf("ERROR:buf_memory broken\n");
	}
	if(!((RFL.input=(char*)realloc(RFL.input,RFL.text_len*sizeof(char))))){
		printf("ERROR:input_memory broken\n");
	}
	
}


void cmd_repeat(char *name,char *info, char *num, char *non4,char *non5){
	loop.start=now;
	loop.step=atol(num);
	loop.num=atol(name)+loop.step;
	loop.end_num=atol(info);
	for(new_now=0;new_now<RFL.command_counter;new_now+=1){
		if(strcmp(RFL.command[new_now],"repeat.end")==0){
			loop.end=new_now;
			break;
		}
	}
}
void cmd_if(char *name,char *ascii, char *info, char *non4,char *non5){
	code=0;
	nif.start=now;
	nif.end=-1;
	nif.els=-1;
	for(new_now=now;new_now<RFL.command_counter;new_now+=1){
		if(strcmp(RFL.command[new_now],"if.else")==0){
			nif.els=new_now;
		}
		if(strcmp(RFL.command[new_now],"if.end")==0){
			nif.end=new_now;
			break;
		}
	}
	
	if(strcmp(name,info)==0 && strcmp(ascii,"=")==0){
		code=1;
	}
	else if((atol(name)<atol(info)) && strcmp(ascii,"<")==0){
		code=1;
	}
		else if((atol(name)<=atol(info)) && strcmp(ascii,"<=")==0){
		code=1;
	}
		else if((atol(name)>atol(info)) && strcmp(ascii,">")==0){
		code=1;
	}
		else if((atol(name)>=atol(info)) && strcmp(ascii,">=")==0){
		code=1;
	}
		else if((atol(name)!=atol(info)) && strcmp(ascii,"!")==0){
		code=1;
	}
		else if((atol(name) && atol(info)) && strcmp(ascii,"&")==0){
		code=1;
	}
		else if((atol(name)||atol(info)) && strcmp(ascii,"||")==0){
		code=1;
	}
	else if((strstr(info,name)) && strcmp(ascii,"in")==0){
		code=1;
	}
	if(code==0 && nif.els!=-1){
		now=nif.els;
	}else if(code==0){
		now=nif.end;
	}
}
void cmd_owner(char *name,char *info, char *non3, char *non4,char *non5){
	long int var_each;
	for(var_each=0;var_each<RFL.var_counter;var_each+=1){
		if(strcmp(var[var_each].name,name)==0){
			sprintf(var[var_each].name,"%s.%s",info,name);
		}
	}
}
void cmd_make(char *name,char *info, char *non3, char *non4,char *non5){
	/* name - c compiler , info - REFLANG origenal file , non3 - new file , non4-name of import file, non5-name of program */
	char *save_buf=(char*)malloc(RFL.text_len*sizeof(char));
	sprintf(name,"%s %s -o %s",name,non3,non5);
	FILE *f=fopen(info,"r");
	FILE *f2=fopen(non3,"w+");
	fprintf(f2,"");
	fclose(f2);
	f2=fopen(non3,"a");
	while(fgets(save_buf,RFL.text_len,f)){
		if(strstr(save_buf,"/* mark for make */")!=NULL && strstr(save_buf,"strstr")==NULL){
			fprintf(f2,"strcpy(RFL.input,\"console.import:%s\");if( hide == 0 ){hide=1;}",non4);
		}else{
			if(strstr(save_buf,"REFLANG by rost999dev")!=NULL){
				;
			}else{
			fprintf(f2,"%s",save_buf);
			}
		}
	}
	fclose(f2);
	fclose(f);
	free(save_buf);
	system(name);
}
void cmd_get(char *name,char *info, char *non3, char *non4,char *non5){
	
	long int var_each;
	for(var_each=0;var_each<RFL.var_counter;var_each+=1){
		if(strcmp(info,var[var_each].name)==0){
			sprintf(info,"%s",var[var_each].info);
		}
	}
	sprintf(name,"%s[%s]",name,info);
	for(var_each=0;var_each<RFL.var_counter;var_each+=1){
		if(strcmp(var[var_each].name,name)==0){
			sprintf(info,"%s",var[var_each].info);
			break;
		}
	}
	for(var_each=0;var_each<RFL.var_counter;var_each+=1){
		if(strcmp(var[var_each].name,non3)==0){
			sprintf(var[var_each].info,"%s",info);
			break;
		}
	}
}

void cmd_import(char *name,char *non2, char *non3, char *non4,char *non5){
		strcpy(RFL.input,"");
		FILE *f=fopen(name,"r");
			if(f!=NULL){
				while(fgets(RFL.buf[2],RFL.text_len,f)){
					RFL.buf[2][strcspn(RFL.buf[2],"\n")]=0;
					strcat(RFL.buf[2],";");
					strcat(RFL.input,RFL.buf[2]);
				}
				fclose(f);
			}
			
			RFL.import=1;
			RFL.command_counter=0;
}
int main(int argc, char *argv[]){
	/*init*/
	int hide=0;
	RFL.import=0;
	long int args;
	loop.num=0;
	loop.end_num=0;
	long int var_each;
	RFL.text_len=TEXT_LEN;
RFL.var_counter=0;
srand(time(NULL));
RFL.command_counter=0;
    var=(new_var*)malloc(RFL.text_len*sizeof(new_var));
	
	
	RFL.buf[0]=(char*)malloc((4*RFL.text_len)*sizeof(char));
	RFL.buf[1]=(char*)malloc((4*RFL.text_len)*sizeof(char));
	RFL.buf[2]=(char*)malloc((4*RFL.text_len)*sizeof(char));
	RFL.buf[3]=(char*)malloc((4*RFL.text_len)*sizeof(char));
	RFL.buf[4]=(char*)malloc((4*RFL.text_len)*sizeof(char));
	strcpy(RFL.buf[0],"");
	strcpy(RFL.buf[1],"");
	strcpy(RFL.buf[2],"");
	strcpy(RFL.buf[3],"");
	strcpy(RFL.buf[4],"");
	/*init func*/
	func=(new_func *)malloc(FUNC_COUNTER*sizeof(new_func));
	/* init func part 2 */
	func[0].func=cmd_strout;
	func[0].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[0].temp,"str.out:%s");
	func[0].args=1;
	func[0].var_work=1;
	func[0].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[0].com,"print the text\n");
	/*end func */
	func[1].func=cmd_endl;
	func[1].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[1].temp,"line.end:%s");
	func[1].args=1;
	func[1].var_work=1;
	func[1].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[1].com,"print the end of line \n");
	/*end func */
	func[2].func=cmd_var;
	func[2].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[2].temp,"var.%s %s %s");
	func[2].args=3;
	func[2].var_work=0;
	func[2].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[2].com,"set the varible \n");
	/*end func */
	func[3].func=cmd_strin;
	func[3].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[3].temp,"str.in:%s");
	func[3].args=1;
	func[3].var_work=0;
	func[3].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[3].com,"get the input to var\n");
	/*end func */
	func[4].func=cmd_jump;
	func[4].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[4].temp,"jump:%s");
	func[4].args=1;
	func[4].var_work=1;
	func[4].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[4].com,"jump to number command\n");
	/*end func */
	func[5].func=cmd_if;
	func[5].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[5].temp,"if( %s %s %s )");
	func[5].args=3;
	func[5].var_work=1;
	func[5].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[5].com,"if( var or num <,>,&,=,||,<=,>=,!,in var or num) code if.else code if.end\n");
	/*end func */
	func[6].func=cmd_open;
	func[6].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[6].temp,"file.open:%s");
	func[6].args=1;
	func[6].var_work=1;
	func[6].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[6].com,"open file\n");
	/*end func */
	func[7].func=cmd_read;
	func[7].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[7].temp,"file.read:%s");
	func[7].args=1;
	func[7].var_work=0;
	func[7].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[7].com,"get data from opened file\n");
	/*end func */
	func[8].func=cmd_write;
	func[8].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[8].temp,"file.write:%s");
	func[8].args=1;
	func[8].var_work=1;
	func[8].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[8].com,"write in file\n");
	/*end func */
	func[9].func=cmd_append;
	func[9].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[9].temp,"file.append:%s");
	func[9].args=1;
	func[9].var_work=1;
	func[9].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[9].com,"append text into file\n");
	/*end func */
	func[10].func=cmd_goto;
	func[10].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[10].temp,"goto -> %s");
	func[10].args=1;
	func[10].var_work=0;
	func[10].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[10].com,"teleport to mark: \n");
	/*end func */
	func[11].func=cmd_repeat;
	func[11].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[11].temp,"repeat( %s to %s ) -> %s");
	func[11].args=3;
	func[11].var_work=1;
	func[11].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[11].com,"repeat( .... ) -> ...  code repeat.end\n");
	/*end func */
	func[12].func=cmd_len;
	func[12].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[12].temp,"len.%s -> %s");
	func[12].args=2;
	func[12].var_work=0;
	func[12].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[12].com,"save len of one var to another var\n");
	/*end func */
	func[13].func=cmd_memory;
	func[13].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[13].temp,"console.memory:%s");
	func[13].args=1;
	func[13].var_work=1;
	func[13].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[13].com,"set max memory for console\n");
	/*end func */
	func[14].func=cmd_guide;
	func[14].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[14].temp,"guide.%s");
	func[14].args=1;
	func[14].var_work=0;
	func[14].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[14].com,"print all info of func \n");
	/*end func */
	func[15].func=cmd_remove;
	func[15].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[15].temp,"remove.file:%s");
	func[15].args=1;
	func[15].var_work=0;
	func[15].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[15].com,"delite file\n");
	/*end func */
	func[16].func=cmd_time;
	func[16].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[16].temp,"console.time.%s");
	func[16].args=1;
	func[16].var_work=0;
	func[16].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[16].com,"save time in var\n");
	/*end func */
	func[17].func=cmd_cmd;
	func[17].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[17].temp,"system.cmd:%s");
	func[17].args=1;
	func[17].var_work=1;
	func[17].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[17].com,"run shell command\n");
	/*end func */
	func[18].func=cmd_rand;
	func[18].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[18].temp,"random.%s %s to %s");
	func[18].args=3;
	func[18].var_work=0;
	func[18].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[18].com,"get random num\n");
	/*end func */
	func[19].func=cmd_sleep;
	func[19].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[19].temp,"sleep:%s");
	func[19].args=1;
	func[19].var_work=1;
	func[19].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[19].com,"sleep n seconds\n");
	/*end func */
	func[20].func=cmd_strout;
	func[20].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[20].temp,"console.log:%s");
	func[20].args=1;
	func[20].var_work=0;
	func[20].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[20].com,"print only  text\n");
	/*end func */
	func[21].func=cmd_owner;
	func[21].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[21].temp,"owner.%s -> %s");
	func[21].args=2;
	func[21].var_work=0;
	func[21].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[21].com,"create name prefix\n");
	/*end func */
	func[22].func=cmd_error;
	func[22].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[22].temp,"console.error:%s");
	func[22].args=1;
	func[22].var_work=1;
	func[22].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[22].com,"create error\n");
	/*end func */
	func[23].func=cmd_import;
	func[23].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[23].temp,"console.import:%s");
	func[23].args=1;
	func[23].var_work=1;
	func[23].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[23].com,"import and run file\n");
	/*end func */
	func[24].func=cmd_exit;
	func[24].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[24].temp,"console.exit:%s");
	func[24].args=1;
	func[24].var_work=1;
	func[24].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[24].com,"exit the program\n");
	/*end func */
	func[25].func=cmd_struct;
	func[25].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[25].temp,"struct.%s ->  %s %s");
	func[25].args=3;
	func[25].var_work=0;
	func[25].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[25].com,"create a struct like array,dict\n");
	/*end func */
	func[26].func=cmd_debug;
	func[26].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[26].temp,"debug.%s");
	func[26].args=1;
	func[26].var_work=0;
	func[26].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[26].com,"debbuging a var , memory \n");
	/*end func */
	func[27].func=cmd_print;
	func[27].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[27].temp,"print:%s");
	func[27].args=1;
	func[27].var_work=0;
	func[27].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[27].com,"print file\n");
	/*end func */
	func[28].func=cmd_get;
	func[28].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[28].temp,"get.%s %s -> %s");
	func[28].args=3;
	func[28].var_work=0;
	func[28].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[28].com,"get part of array\n");
	/*end func */
	func[29].func=cmd_set;
	func[29].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[29].temp,"set.%s %s -> %s");
	func[29].args=3;
	func[29].var_work=0;
	func[29].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[29].com,"set part of array\n");
	/*end func */
	func[30].func=cmd_make;
	func[30].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[30].temp,"program.make:%s %s -> %s %s %s");
	func[30].args=5;
	func[30].var_work=0;
	func[30].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[30].com,"make program real 1- C compiler 2-original REFLANG file 3-new c code file 4-file with REFLANG code 5-name of app\n");
	/*end func */
	func[31].func=cmd_rng;
	func[31].temp=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[31].temp,"rng.%s %s to %s %s");
	func[31].args=4;
	func[31].var_work=0;
	func[31].com=(char*)malloc(RFL.text_len*sizeof(char));
	strcpy(func[31].com,"get random but custom sleep times\n");
	/*end init func */
	FILE *f;
	RFL.input=(char*)malloc(RFL.text_len*sizeof(char));
	if(argc<2){
	printf("REFLANG by rost999dev\n");
	}
	while(1){
	RFL.command_counter=0;
	if(argc<2){
	/* mark for make */
	if(hide==0 || hide==-1){
	printf("REFLANG>>");
	fgets(RFL.input,RFL.text_len,stdin);
	RFL.input[strcspn(RFL.input,"\n")]=0;
	if(strcspn(RFL.input,"\r")!=0){
		RFL.input[strcspn(RFL.input,"\r")]=0;
	}
	}else{
	hide=-1;
	}
	
	}else{
		strcpy(RFL.input,"");
		for(args=1;args<argc;args+=1){
			f=fopen(argv[args],"r");
			
			if(f!=NULL){
				while(fgets(RFL.buf[0],RFL.text_len,f)){
					RFL.buf[0][strcspn(RFL.buf[0],"\n")]=0;
					strcat(RFL.buf[0],";");
					strcat(RFL.input,RFL.buf[0]);
				}
			}
			fclose(f);
		}
	}
	if(strcmp(RFL.input,"\0")!=0){
		parse:
		RFL.command[RFL.command_counter]=strtok(RFL.input,";");
		RFL.command_counter+=1;
		while(RFL.command[RFL.command_counter]=strtok(NULL,";")){
			RFL.command_counter+=1;
		}
		for( now=0;now<RFL.command_counter;now+=1){
			if(loop.end==now){
					if(loop.num!=loop.end_num){
					now=loop.start+1;
					loop.num+=loop.step;
					}
				}
			for( now_command=0;now_command<FUNC_COUNTER;now_command+=1){
				
				if(sscanf(RFL.command[now],func[now_command].temp,RFL.buf[0],RFL.buf[1],RFL.buf[2],RFL.buf[3],RFL.buf[4])==func[now_command].args){
					if(func[now_command].var_work==1){
					
					for(var_each=0;var_each<RFL.var_counter;var_each+=1){
							if(strcmp(var[var_each].name,RFL.buf[0])==0){
			strcpy(RFL.buf[0],var[var_each].info);
			
		}
		if(strcmp(var[var_each].name,RFL.buf[1])==0){
			strcpy(RFL.buf[1],var[var_each].info);
			
		}
		if(strcmp(var[var_each].name,RFL.buf[2])==0){
			strcpy(RFL.buf[2],var[var_each].info);
			
		}
		if(strcmp(var[var_each].name,RFL.buf[3])==0){
			strcpy(RFL.buf[3],var[var_each].info);
			
		}
		if(strcmp(var[var_each].name,RFL.buf[4])==0){
			strcpy(RFL.buf[4],var[var_each].info);
			
		}
					}
					}
					
					
				func[now_command].func(RFL.buf[0],RFL.buf[1],RFL.buf[2],RFL.buf[3],RFL.buf[4]);
				
					
				if(skip==1){
					skip=0;
					continue;
					
					}
				if(RFL.import==1){
					RFL.import=0;
					goto parse;
				}
				if(now==nif.els && code ==1){
					now=nif.end;
				}
					if(RFL.var_counter>RFL.text_len){
						RFL.text_len+=(RFL.var_counter-RFL.text_len);
						var=(new_var*)realloc(var,RFL.text_len*sizeof(new_var));
						}
						break;	
				}
			}
		}
	}
	if(argc>=2){
		exit(0);
	}
	}
}
