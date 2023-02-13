#include <iostream>
#include <fstream>
#define SIZE 9
#define BOX 3
using namespace std;


class Grid{
    //private:
        //int x,y,z,i,j,k;

    public:

        int table[SIZE][SIZE][SIZE+1];
        Grid(){
            for(int i=0;i<SIZE;i++)
                for(int j=0;j<SIZE;j++)
                    for(int k=0;k<=SIZE;k++)
                        table[i][j][k]=0;

        }

        void ReadRare(){
            int x,y,z;
            ifstream f("Sudoku.in");
            while(f>>x>>y>>z)
                table[x][y][0]=z;

        }
        void ReadNormal(){
            int x,y,z;
            ifstream f("Sudoku2.in");
            for(int i=0;i<SIZE;i++)
                for(int j=0;j<SIZE;j++){
                    f>>table[i][j][0];
            }
        }
        void Show(){
            for(int i=0;i<SIZE;i++){
                if(i!=0&&i%BOX==0)
                    cout<<endl;
                for(int j=0;j<SIZE;j++){
                    if(j!=0&&j%BOX==0)
                        cout<<"  ";
                    cout<<table[i][j][0]<<" ";
                }

                cout<<endl;
            }
        }




        private:

        void InsertValue (int row, int col, int value){






                for(int i=1;i<SIZE+1;i++)
                    table[row][col][i]=0;
                table[row][col][0]=value;


                ///ROWS AND COLUMNS
                for(int i=0;i<SIZE;i++){
                    table[row][i][value]=0;
                    table[i][col][value]=0;

                }
                ///3X3 GRID
                for(int i=0;i<BOX;i++){
                    for(int j=0;j<BOX;j++)
                        table[row-row%BOX+i][col-col%BOX+j][value] =0;
                }










        }

        void Pencil (int row, int column){

            if(table[row][column][0]!=0){
                //cout<<"Value not empty\n";
                return;
            }

            for(int i=1;i<=SIZE;i++)
                table[row][column][i]=1;
            ///ROW
            for(int i=0;i<SIZE;i++)
                    table[row][column][table[row][i][0]]=0;
            ///COLUMN
            for(int i=0;i<SIZE;i++)
                    table[row][column][table[i][column][0]]=0;

            ///3X3 GRID
            for(int i=0;i<BOX;i++){
                for(int j=0;j<BOX;j++)
                    table[row][column][table[row-row%BOX+i][column-column%BOX+j][0] ]=0;
            }

            //cout<<row<<" "<<column<<endl;
            /*for(i=1;i<=9;i++)
                if(table[row][column][i]!=0)
                    cout<<i<<" ";*/




        }

        int UniquePen (int row, int column){
            int c=0;
            int value=0;
            for(int i=1;i<=SIZE;i++)
                if(table[row][column][i]==1){
                    c++;
                    value=i;

            }
            if(c==1)
                return value;
            else
                return -1;


        }

        int OnlyPlace (int row, int col){
            if(table[row][col][0]!=0)
                return -1;
            //int value=-1;
            int c;
            for(int i=1;i<=9;i++){
                ///ROW
                c=0;
                for(int j=0;j<SIZE;j++)
                {

                    if(table[row][j][i]==1&&table[row][col][i]==1)
                        c++;
                }
                if(c==1)
                    return i;


                ///COLUMN
                c=0;
                for(int j=0;j<SIZE;j++)
                {

                    if(table[j][col][i]==1&&table[row][col][i]==1)
                        c++;
                }
                if(c==1)
                    return i;

                ///BOX
                c=0;
                for(int j=0;j<BOX;j++){
                    for(int k=0;k<BOX;k++)
                        if(table[row-row%BOX+j][col-col%BOX+k][i] ==1&&table[row][col][i]==1)
                            c++;
                }
                if(c==1)
                    return i;

            }
            return -1;
        }


        /*

        bool SimpleTest(int row, int column){

            if(table[row][column][0]!=0)
                return false;

            //bool check[SIZE+1]={0};
            for(int i=1;i<=SIZE;i++)
                table[row][column][i]=0;
            ///ROW
            for(i=0;i<SIZE;i++)
                    table[row][column][table[row][i][0]]=1;
            ///COLUMN
            for(i=0;i<SIZE;i++)
                    table[row][column][table[i][column][0]]=1;

            ///3X3 GRID
            for(i=0;i<BOX;i++){
                for(int j=0;j<BOX;j++)
                    table[row][column][table[row-row%BOX+i][column-column%BOX+j][0] ]=1;
            }


            int c=0;
            int value=0;
            for(i=1;i<=SIZE;i++)
                if(table[row][column][i]==0){
                    c++;
                    value=i;

            }
            if(c==1){
                table[row][column][0]=value;
                return true;
            }
            else
                return false;


        }
        */



        public:
        /*bool SimpleSolve(){
            bool c=1;
            while(c){
                c=0;
                for(int i=0;i<SIZE;i++)
                    for(int j=0;j<SIZE;j++){
                        if(SimpleTest(i,j))
                            c=1;
                    }
            }
            for(int i=0;i<SIZE;i++)
                for(int j=0;j<SIZE;j++)
                    if (table[i][j][0]==0)
                        return false;
            return true;




        }

        bool BoxTest (int row, int column){

            for(i=row-row%BOX;i<row-row%BOX+3;i++)
                for(j=column-column%BOX;j<column-column%BOX;j++)
                        if((i!=row&&j!=column)&&table[i][j][0]==0)
                            for(k=1;k<=9;k++)
                                if(table[i][j][k]==1)
                                    table[row][column][k]=0;


            int c=0;
            int value=0;
            for(i=1;i<=SIZE;i++)
                if(table[row][column][i]==1){
                    c++;
                    value=i;

            }
            if(c==1){
                //table[row][column][0]=value;
                cout<<value;
                return true;
            }
            else
                return false;




        }*/



        bool Solve(){
            for(int ROW=0;ROW<SIZE;ROW++)
                for(int COL=0;COL<SIZE;COL++)
                    Pencil(ROW,COL);
            ///TESTING PENCIL FOR ENTIRE GRID



            ofstream g("Testing.txt");
            /*for(int ROW=0;ROW<SIZE;ROW++)
                for(int COL=0;COL<SIZE;COL++){
                    g<<ROW<<" "<<COL<<":  ";
                    //if(table[ROW][COL][0]!=0)
                       // g<<"Not empty. Value is "<<table[ROW][COL][0];
                    //else
                        for(int i=1;i<=9;i++)
                            if(table[ROW][COL][i]!=0)
                                g<<i<<" ";
                    g<<endl;
                }
            */



            bool c=1;



            while(c){
                c=0;
                for(int i=0;i<SIZE;i++)
                    for(int j=0;j<SIZE;j++){
                        //if(DelValue(i,j))
                            //c=1;
                        int value=UniquePen(i,j);
                        if (value!=-1){
                            c=1;
                            InsertValue(i,j,value);
                        }
                        else{
                            value=OnlyPlace(i,j);
                            if(value!=-1){
                                g<<i<<" "<<j<<" "<<value<<endl;
                                c=1;
                                InsertValue(i,j,value);
                            }

                        }


                    }
            }







            for(int i=0;i<SIZE;i++)
                for(int j=0;j<SIZE;j++)
                    if (table[i][j][0]==0)
                        return false;
            return true;













            //cout<<value;






        }
        int test(int r, int c){
            return OnlyPlace(r,c);
        }








}grid;






int main()
{
    grid.ReadNormal();
    grid.Solve();
    //cout<<grid.test(0,4)<<endl;
    grid.Show();
    return 0;
}
