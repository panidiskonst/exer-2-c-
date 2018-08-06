// basic file operations
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
typedef std::vector<char> char_vec;
typedef std::vector< vector<char> > char_2Dvec;

void print2dVec(char_2Dvec& vec ){

	for(unsigned int i=0; i<vec.size(); i++){			//print 2d vec
			   for(unsigned int j=0; j<vec[i].size(); j++)
			   	     std::cout <<vec[i][j] ;
			   cout<<endl;
		   }

}
struct cell
{
	int x,y,t;
	char force;
	 cell * next;
};
class list
{
	private:

	cell* head, *tail;

	public:
	list(){

		head=NULL;
		tail=NULL;
	}
	~list(){					//destructor
		cell *next=head;
		while(next){
			cell *deleteMe=next;
			next=next->next;
			delete deleteMe;

		}
	}

	void addCell(int xin,int yin,int tin, char forcein){
		cell *n=new cell;
		n->x=xin;
		n->y=yin;
		n->force=forcein;
		n->t=tin;
		n->next=NULL;
		if(head==NULL){
			//cout<<"first cell added"<<endl;
			head=n;
			tail=n;
			n=NULL;
		}
		else{
		//	cout<<"another cell added"<<endl;

			tail->next=n;
			tail=n;
		}
	}
	void displayList()
	{
		cell * temp=head;
		cout<<"[";
		while(temp!=NULL){
			cout<<"|("<<temp->x<<","<<temp->y<<") "<<"force:"<<temp->force<<"time:"<<temp->t<<"|<- ";
			temp=temp->next;
		}
		cout<<"]";
	}
	void deletehead(){
		cell *deleteme=head;
		head=head->next;
		delete deleteme;
	}

	int headx(){
		return head->x;
	}
	int heady(){
			return head->y;
		}
	int headt(){
			return head->t;
		}
	char headc(){
			return head->force;
		}
	bool headNull(){
		if (head==NULL) return true;
		else return false;
	}

};


int main(int argc, char *argv[]) {

   if (argc > 1) {


	   ifstream targetFile;
	   targetFile.open(argv[1]); //open txt given as argument

	   if(targetFile.fail()){			//give error message in case file doesnt open
		   cout<<"Error opening File"<<endl;
		   exit(1);
	   }

	   char_vec row;	   	//row vector
	   char_2Dvec matrix,new_matrix;	//vector of rows,or matrix(welcom neo)
	   char input;
	   int i=0,j=0,xmax=0,ymax=0,time=0;		//some debugging variables dont mind them
	   bool boomFlag=false;
	 //  cell *headptr;
	   list queue;

	   while(!targetFile.eof()){		//get each char till you reach eof

		   targetFile>>std::noskipws >>input;		//store temporarily the char


		   if(input=='\n'){				//if char is newline than start a new row, clear the row vector as we
		   			   	   	   	   	   	   	   	   // will fill it with a new row
		   			 j++; matrix.push_back(row); row.clear(); i=0;
		   }

		   		   else{						//if char not newline,just fill the damn row vector,
		   			   row.push_back(input);
		   			   if(input=='+'){
		   				   queue.addCell(i,j,time,'+'); //cout<<"entered here"<<endl;

		   			   }
		   			   if(input=='-'){
		   				   queue.addCell(i,j,time,'-');
		   			   }
		   			   i++;
		   		   }

	   }
	   ymax=matrix.size()-1;
	   xmax=matrix[0].size();

	  // print2dVec(matrix);

	  // cout<<matrix[1][9]<<endl;
	 //  cout<<"xmax:"<<xmax<<" ymax:"<<ymax<<endl;
	  // queue.displayList();cout<<endl;
	   time++;

	   //cout<<queue.headNull()<<endl;
	   while(!queue.headNull()){

		   //cout<<"time::"<<time<<endl;
		   if(queue.headt()==time){
			   if(boomFlag) break;
			   else time++;						//we covered all the cells of current time,move to next time unit,or break if explosion is about to go
		   }



		   if(queue.headx()+1<xmax){														//check east if there is east
			    if(matrix[queue.heady()][queue.headx()+1]=='.' ){							//check if space is available for move
			    	 matrix[queue.heady()][queue.headx()+1]=queue.headc(); 								//change matrix
			    	queue.addCell(queue.headx()+1,queue.heady(),time,queue.headc());		//add to list//check east
			    }

			    if(matrix[queue.heady()][queue.headx()+1]!='X' and queue.headc()!=matrix[queue.heady()][queue.headx()+1]){			//if we find not X and not same force,boom initialize
			    	matrix[queue.heady()][queue.headx()+1]='*'; boomFlag=true;														//set area to * and when time increases we break from loop

			    }

		   }

		   if(queue.headx()-1>=0){																		//check west if there is west
			   if(matrix[queue.heady()][queue.headx()-1]=='.'){											//check if space is available for move
				   matrix[queue.heady()][queue.headx()-1]=queue.headc(); 								//change matrix
				   queue.addCell(queue.headx()-1,queue.heady(),time,queue.headc());						//add to list
			   }

			    if(matrix[queue.heady()][queue.headx()-1]!='X' and queue.headc()!=matrix[queue.heady()][queue.headx()-1]){			//if we find not X and not same force,boom initialize
			    	matrix[queue.heady()][queue.headx()-1]='*'; boomFlag=true;														//set area to * and when time increases we break from loop

			    }
		   }

		   if(queue.heady()+1<ymax){																//check south if there is south
			   if(matrix[queue.heady()+1][queue.headx()]=='.' ){
				   matrix[queue.heady()+1][queue.headx()]=queue.headc(); 								//change matrix
				   queue.addCell(queue.headx(),queue.heady()+1,time,queue.headc());		//add to list
			   }

			    if(matrix[queue.heady()+1][queue.headx()]!='X' and queue.headc()!=matrix[queue.heady()+1][queue.headx()]){			//if we find not X and not same force,boom initialize
			    	matrix[queue.heady()+1][queue.headx()]='*'; boomFlag=true;														//set area to * and when time increases we break from loop

			    }


		   }

		   if(queue.heady()-1>=0){																//check north if there is north
			   if(matrix[queue.heady()-1][queue.headx()]=='.' ){							//check if space is available for move
		   		matrix[queue.heady()-1][queue.headx()]=queue.headc(); 								//change matrix
		   	    queue.addCell(queue.headx(),queue.heady()-1,time,queue.headc());		//add to list
			   }
			    if(matrix[queue.heady()-1][queue.headx()]!='X' and queue.headc()!=matrix[queue.heady()-1][queue.headx()]){			//if we find not X and not same force,boom initialize
			    	matrix[queue.heady()-1][queue.headx()]='*'; boomFlag=true;														//set area to * and when time increases we break from loop

			    }
		   }

		  // queue.displayList(); cout<<endl;
		   queue.deletehead();//cout<<endl;
		  // queue.displayList();cout<<endl;
	   }
if(!boomFlag){
	cout<<"the world is saved"<<endl;
	 print2dVec(matrix);
}
else{
	cout<<time<<endl;  print2dVec(matrix);
}

   }




	   return 1;
   }

