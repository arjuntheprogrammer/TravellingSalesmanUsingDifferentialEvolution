// Travelling Salesman using Differential Evoluation

#include<bits/stdc++.h>
using namespace std;

#define MaxDistanceBetweenNodes 1000.0
#define MaxNumberOfCities 1000
#define NumberOfCities 30

#define mutationFactor 0.8
#define crossoverRate 0.5

#define totalGenerations 1

#define populationSize 15

vector< pair<int, int> > position;
vector< double > pairwiseDistance[NumberOfCities+10];

int currentPopulation[populationSize+10][NumberOfCities+10];
int tempPopulation[NumberOfCities+10];


int mutantCurrentPopulation[populationSize+10][NumberOfCities+10];
int trialCurrentPopulation[populationSize+10][NumberOfCities+10];



double currentPopulationTotalDistance[populationSize+10];
double tempTotalDistance;
double tempMutPopulation[NumberOfCities+10];
double sorttempMutPopulation[NumberOfCities+10];

int visitOnFind[NumberOfCities+10];

int visitCR[NumberOfCities+10];



double calDistance(pair<int, int > a, pair<int , int> b){
    double dis = sqrt(pow((a.first - b.first), 2) + pow((a.second - b.second), 2));
    return dis;
}

void initPairwiseDistance(){
    for(int i=0; i<NumberOfCities; i++){
        for(int j= 0; j<NumberOfCities; j++){
            double dis;

            if(i==j){
                dis = MaxDistanceBetweenNodes;
            }
            else{
                dis = calDistance(position[i], position[j]);
            }

            pairwiseDistance[i].push_back(dis);
        }
    }
}
void printPairwiseDistance(){
    cout<<"\t\t\t";
    for(int i=0; i<NumberOfCities; i++){
        cout<<"City "<<i<<"\t";
    }
    
    cout<<endl;
    for(int i=0; i<NumberOfCities; i++){
        cout<<"City "<<i<<":|\t";
        for(int j= 0; j<NumberOfCities; j++){
            printf("%3.3f\t",pairwiseDistance[i][j] );
        }
        cout<<endl;
    }
}

void initVector(){
    int randomNumber = rand()%(NumberOfCities);
    int visit[NumberOfCities+10] = {0};
    int t = NumberOfCities;
    int source = randomNumber;
    int k=0;
    visit[source] = 1;
    tempPopulation[k++] = source;
    // cout<<"\nSource: "<<source<<" ";
    tempTotalDistance=0;
    while(t--){
        double minimumDis = MaxDistanceBetweenNodes;
        int node;
        int f=0;
        for(int i=0; i<NumberOfCities; i++){
            if(visit[i] == 0 && minimumDis >  pairwiseDistance[source][i]){
                node = i;
                minimumDis = pairwiseDistance[source][i];
                f=1;
            }
        }
        
        if(f==1){
            // cout<<"minimumDis:"<<minimumDis<<" tempTotalDistance:"<<tempTotalDistance<<endl;
            tempTotalDistance += minimumDis;
            tempPopulation[k++] = node;
            visit[node] = 1;
            source = node;
        }
    }

    tempTotalDistance += pairwiseDistance[source][randomNumber];
    
    // cout<<"Final Souce: "<<source<<" ->"<<randomNumber;
    // cout<<"minimumDis:"<<pairwiseDistance[source][randomNumber]<<" tempTotalDistance:"<<tempTotalDistance<<endl;    
    // cout<<"TempPopulation=\n";
    // for(int i=0; i<NumberOfCities; i++){
    //     cout<<tempPopulation[i]<<" ";
    // }
    // cout<<endl;


}

void initPopulation(){
    // for(int i= 0; i<1; i++){
    for(int i= 0; i<populationSize; i++){
        initVector();
        for(int j=0; j<NumberOfCities; j++){
            currentPopulation[i][j] = tempPopulation[j];
        }
        currentPopulationTotalDistance[i] = tempTotalDistance;

    }
}

void printCurrentPopulation(){  
    cout<<"Current Population: \n";

    for(int i= 0; i<populationSize; i++){
        for(int j=0; j<NumberOfCities; j++){
            cout<<currentPopulation[i][j]<<" ";
        }
        cout<<" TotalDistance:"<<currentPopulationTotalDistance[i];
        cout<<endl;
    }
}

bool checkConstraints(int member){
    
}

void repair(int member){
    
}

int findElementMut(double element){
    for(int j=0; j<NumberOfCities; j++){
        if(visitOnFind[j]==0 && sorttempMutPopulation[j]==element){
            visitOnFind[j]=1;
            return j;
        }
    }
    cout<<"\nNot found MUT\n";
    return -1;
}

void mutation(){
    //DE/rand/1 scheme
    int differenceVector1;
    int differenceVector2;
    int baseVector;
    int mutantVector;
    
    for(int i=0; i<populationSize; i++){
        mutantVector = i;
        while(1){
            baseVector = rand()%populationSize;
            if(baseVector != mutantVector){
                break;
            }
        }
        while(1){
            differenceVector1 = rand()%populationSize;
            if(differenceVector1 != baseVector && differenceVector1 != mutantVector){
                break;
            }
        }
        while(1){
            differenceVector2 = rand()%populationSize;
            if(differenceVector2 !=baseVector  && differenceVector2 != differenceVector1 && differenceVector2!= mutantVector){
                break;
            }
        }


        

        // cout<<"\n\nTemp Pop:\n";
        for(int j=0; j<NumberOfCities; j++){
            double mutantBit = currentPopulation[baseVector][j] + (mutationFactor) * ( currentPopulation[differenceVector1][j] - currentPopulation[differenceVector2][j] );
            // cout<<" mutantBit: "<<mutantBit;
            tempMutPopulation[j] = mutantBit;
            sorttempMutPopulation[j] = mutantBit;

            // cout<<tempMutPopulation[j]<<" ";
        }
        sort(sorttempMutPopulation+0, sorttempMutPopulation+NumberOfCities);
        
        // cout<<"\nSorted pop:\n";
        // for(int j=0; j<NumberOfCities; j++){
        //     cout<<sorttempMutPopulation[j]<<" ";
        // }

        
        // init visitOnFind
        for(int j=0; j<NumberOfCities; j++){
            visitOnFind[j]=0;
        }
        // cout<<"\nTrail Pop:\n";
        for(int j=0; j<NumberOfCities; j++){
            mutantCurrentPopulation[mutantVector][j] = findElementMut(tempMutPopulation[j]);    
            cout<<mutantCurrentPopulation[mutantVector][j]<<" ";
        }
        cout<<endl;

        
    }

}


void initVisitCR(){
    for(int j=0; j<NumberOfCities; j++){
        visitCR[j]=0;
    }
}

int findElementCR(int crVector, int element, int flag){
    if(flag==1){
        for(int j=0; j<NumberOfCities; j++){
            if(mutantCurrentPopulation[crVector][j]==element){
                return j;
            }
        }
        cout<<"\nNot found CR\n";
        return -1;
    }
    else if(flag==0){
        for(int j=0; j<NumberOfCities; j++){
            if(currentPopulation[crVector][j]==element){
                return j;
            }
        }
        cout<<"\nNot found CR\n";
        return -1;
    }
}

// currentPopulation
// mutantCurrentPopulation

//trialCurrentPopulation

// 1 4 2 5 3
// 4 5 1 2 3

int findNextCityIndex(int index){
    int nex;
    if(index+1 == NumberOfCities){
        nex = 0;
    }
    else{
        nex = index+1;
    }
    return nex;
}

void crossover(){
    int crVector;
    int ind, currCity1Ind, currCity2Ind, nextCity1Ind, nextCity2Ind;
    int currCity, nextCity1, nextCity2;

    for(int i=0; i<populationSize; i++){
        crVector = i;
        initVisitCR();
        
        int k=0;
        int j=0;
        currCity1Ind = j;
        nextCity1Ind = findNextCityIndex(currCity1Ind);
        currCity2Ind = findElementCR(crVector, currentPopulation[crVector][currCity1Ind], 1);
        nextCity2Ind = findNextCityIndex(currCity2Ind);
        
        currCity = currentPopulation[crVector][currCity1Ind];
        nextCity1 = currentPopulation[crVector][nextCity1Ind];
        nextCity2 = mutantCurrentPopulation[crVector][nextCity2Ind];

        trialCurrentPopulation[crVector][k++] = currCity;
        visitCR[currCity]=1;

        while(1){
            if( visitCR[nextCity1]==0 && visitCR[nextCity2]==0 ){
                
                double dis1 = pairwiseDistance[currCity ][nextCity1];
                double dis2 = pairwiseDistance[ currCity ][nextCity2];
                
                if(dis2 <= dis1){
                    trialCurrentPopulation[crVector][k++] = nextCity2;
                    visitCR[nextCity2]=1;
                    
                    currCity2Ind = nextCity2Ind;
                    nextCity2Ind = findNextCityIndex(currCity2Ind);
                    currCity1Ind = findElementCR(crVector, mutantCurrentPopulation[crVector][currCity2Ind], 0);
                    nextCity1Ind = findNextCityIndex(currCity1Ind);
                    
                    
                    currCity = nextCity2;
                    nextCity1 = currentPopulation[crVector][nextCity1Ind];
                    nextCity2 = mutantCurrentPopulation[crVector][nextCity2Ind];
            

                }
                else{
                    trialCurrentPopulation[crVector][k++] = nextCity1;
                    visitCR[nextCity1]=1;
                    
                    currCity1Ind = nextCity1Ind;
                    nextCity1Ind = findNextCityIndex(currCity1Ind);
                    currCity2Ind = findElementCR(crVector, currentPopulation[crVector][currCity1Ind], 1);
                    nextCity2Ind = findNextCityIndex(currCity2Ind);
                    
                    currCity = nextCity1;
                    nextCity1 = currentPopulation[crVector][nextCity1Ind];
                    nextCity2 = mutantCurrentPopulation[crVector][nextCity2Ind];
                }
            }
            
            else if(visitCR[nextCity1]==1 && visitCR[nextCity2]==0){
                trialCurrentPopulation[crVector][k++] = nextCity2;
                visitCR[nextCity2]=1;

                currCity2Ind = nextCity2Ind;
                nextCity2Ind = findNextCityIndex(currCity2Ind);
                currCity1Ind = findElementCR(crVector, mutantCurrentPopulation[crVector][currCity2Ind], 0);
                nextCity1Ind = findNextCityIndex(currCity1Ind);
                
                
                currCity = nextCity2;
                nextCity1 = currentPopulation[crVector][nextCity1Ind];
                nextCity2 = mutantCurrentPopulation[crVector][nextCity2Ind];

            }
            
            else if(visitCR[nextCity1]==0 && visitCR[nextCity2]==1){
                trialCurrentPopulation[crVector][k++] = nextCity1;
                visitCR[nextCity1]=1;

                currCity1Ind = nextCity1Ind;
                nextCity1Ind = findNextCityIndex(currCity1Ind);
                currCity2Ind = findElementCR(crVector, currentPopulation[crVector][currCity1Ind], 1);
                nextCity2Ind = findNextCityIndex(currCity2Ind);
                
                currCity = nextCity1;
                nextCity1 = currentPopulation[crVector][nextCity1Ind];
                nextCity2 = mutantCurrentPopulation[crVector][nextCity2Ind];
            }

            else{
                while(j<NumberOfCities &&  visitCR[j]==1){
                    j++;
                }
                if(j==NumberOfCities){
                    break;
                }
                else{
                    currCity1Ind = j;
                    nextCity1Ind = findNextCityIndex(currCity1Ind);
                    currCity2Ind = findElementCR(crVector, currentPopulation[crVector][currCity1Ind], 1);
                    nextCity2Ind = findNextCityIndex(currCity2Ind);
                    
                    currCity = currentPopulation[crVector][currCity1Ind];
                    nextCity1 = currentPopulation[crVector][nextCity1Ind];
                    nextCity2 = mutantCurrentPopulation[crVector][nextCity2Ind];
                }
            }


        }
        
        
    }
}

void selection(){
       
}

void calculateTotalFitness(){
   
}
void printAfterCRPopulation(){
    for(int i=0; i<populationSize; i++){
       for(int j=0; j<NumberOfCities; j++){
        cout<<trialCurrentPopulation[i][j]<<" ";
       }
       cout<<endl;
    }
}
int main(){

    FILE *fin1 = freopen("inputForDE.txt", "r", stdin);
    FILE *fin2 = freopen("ouputByDE.txt", "w", stdout);
    
    int x,y,nn;

    for(int i=0; i<NumberOfCities; i++){
        cin>>nn;
        cin>>x;
        cin>>y;
        position.push_back(make_pair(x,y));
    }
    
    initPairwiseDistance();
    // printPairwiseDistance();
    initPopulation();
    // cout<<"***************************************************************************************************\n";
    printCurrentPopulation();
    // cout<<"***************************************************************************************************\n";

    // cout<<"\nCurrent Population: \n";
    // printCurrentPopulation();
    // calculateTotalFitness();    

    int currentGeneration=0;
    
    // iterations for generations
    while(currentGeneration< totalGenerations){  
        cout<<"***************************************************************************************************\n";
        cout<<"Current Generation="<<currentGeneration<<"\n";    
        
        cout<<"\nAfter Mutation, Population: \n";
        mutation();
        crossover();
        cout<<"\nAfter Crossover, Population: \n";
        printAfterCRPopulation();

    //     printTrailCurrentPopulation();
        
    //     crossover();
    //     
    //     printTrailCurrentPopulation();
        
    //     selection();
    //     cout<<"\nAfter Selection, Population: \n";
    //     printCurrentPopulation();
        
    //     calculateTotalFitness();

        currentGeneration++;
    }

    cout<<"***************************************************************************************************\n";
    return 0;
}