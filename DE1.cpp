// Travelling Salesman using Differential Evoluation

#include<bits/stdc++.h>
using namespace std;

#define MaxDistanceBetweenNodes 1000.0
#define MaxNumberOfCities 1000
#define NumberOfCities 30

#define mutationFactor 0.8
#define crossoverRate 0.8

#define totalGenerations 100

#define populationSize 20

vector< pair<int, int> > position;
vector< double > pairwiseDistance[NumberOfCities+10];

int tempPopulation[NumberOfCities+10];

int currentPopulation[populationSize+10][NumberOfCities+10];
int mutantCurrentPopulation[populationSize+10][NumberOfCities+10];
int sortedCurrentPopulation[populationSize+10][NumberOfCities+10];
int trialCurrentPopulation[populationSize+10][NumberOfCities+10];



double currentPopulationTotalDistance[populationSize+10];
double mutantPopulationTotalDistance[populationSize+10];
double sortedPopulationTotalDistance[populationSize+10];
double trialPopulationTotalDistance[populationSize+10];

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
    double totalDis =0;
    double minimumVal = DBL_MAX;
    for(int i= 0; i<populationSize; i++){
        for(int j=0; j<NumberOfCities; j++){
            // cout<<currentPopulation[i][j]<<" ";
        }
        totalDis += currentPopulationTotalDistance[i];
        if(currentPopulationTotalDistance[i] < minimumVal){
            minimumVal = currentPopulationTotalDistance[i];
        }
        // cout<<" Distance:"<<currentPopulationTotalDistance[i];
        // cout<<endl;
    }
    cout<<"\n============================================================================> minimumVal: "<<minimumVal<<endl;
    cout<<"\n====================================================================> Total of Distances: "<<totalDis<<endl;
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
        for(int j=0; j<NumberOfCities; j++){
            mutantCurrentPopulation[mutantVector][j] = findElementMut(tempMutPopulation[j]);    
            //cout<<mutantCurrentPopulation[mutantVector][j]<<" ";
        }
        // cout<<endl;

        
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
    return -1;
}

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

// mutantCurrentPopulation[populationSize+10][NumberOfCities+10];
// sortedCurrentPopulation[populationSize+10][NumberOfCities+10];

// currentPopulationTotalDistance
// trialPopulationTotalDistance

bool compare(pair<int , int >a, pair<int , int >b){
    return (a.second < b.second);
}

void crossover(){
    vector< pair<int , int > > dimensionDistancePair;
    
    //calculating mutantPopulationTotalDistance
    for(int i=0; i<populationSize; i++){
        double dis = 0;
        int source = mutantCurrentPopulation[i][0];
        int j;
        for(j=0; j<NumberOfCities-1; j++){
            dis += pairwiseDistance[mutantCurrentPopulation[i][j]][mutantCurrentPopulation[i][j+1]]; 
        }
        dis += pairwiseDistance[mutantCurrentPopulation[i][j]][source];
        mutantPopulationTotalDistance[i] = dis;
        dimensionDistancePair.push_back(make_pair(i, dis));
    }


    sort(dimensionDistancePair.begin(), dimensionDistancePair.end(), compare);
    for(int i=0; i<populationSize; i++){
        int index = dimensionDistancePair[i].first;
        for(int j=0; j<NumberOfCities; j++){
            sortedCurrentPopulation[i][j] = mutantCurrentPopulation[index][j];   
        }
        sortedPopulationTotalDistance[i] = mutantPopulationTotalDistance[index];
    }

    // cout<<"\nSorted population for crossover\n";
    // for(int i=0; i<populationSize; i++){
    //     for(int j=0; j<NumberOfCities; j++){
    //         cout<<sortedCurrentPopulation[i][j]<<" ";   
    //     }
    //     cout<<"Distance: "<<sortedPopulationTotalDistance[i];
    //     cout<<endl;
    // }

    int pairs = populationSize*crossoverRate;
    int mid = NumberOfCities/2;
    int i;
    for(i=0; i<pairs; i+=2){
        for(int j=0; j<NumberOfCities; j++){
            visitCR[j]=0;
        }
        int k=0;
        for(int j=0; j<mid; j++){
            trialCurrentPopulation[i][k++] = sortedCurrentPopulation[i][j]; 
            visitCR[sortedCurrentPopulation[i][j]] = 1;
        }
        for(int j=0; j<NumberOfCities; j++){
            if(visitCR[sortedCurrentPopulation[i+1][j]] ==0){
                trialCurrentPopulation[i][k++] = sortedCurrentPopulation[i+1][j]; 
                visitCR[sortedCurrentPopulation[i+1][j]] = 1;
            }
        }

        for(int j=0; j<NumberOfCities; j++){
            visitCR[j]=0;
        }
        k=0;
        for(int j=0; j<mid; j++){
            trialCurrentPopulation[i+1][k++] = sortedCurrentPopulation[i+1][j]; 
            visitCR[sortedCurrentPopulation[i+1][j]] = 1;
        }
        for(int j=0; j<NumberOfCities; j++){
            if(visitCR[sortedCurrentPopulation[i][j]] ==0){
                trialCurrentPopulation[i+1][k++] = sortedCurrentPopulation[i][j]; 
                visitCR[sortedCurrentPopulation[i][j]] = 1;
            }
        }

    }
    for(int ii=i; ii<populationSize; ii++){
        for(int j=0; j<NumberOfCities; j++){
            trialCurrentPopulation[ii][j] = sortedCurrentPopulation[ii][j];
        }
    }

    // trial distance calualation
    for(int i=0; i<populationSize; i++){
        double dis = 0;
        int source = trialCurrentPopulation[i][0];
        int j;
        for(j= 0; j<NumberOfCities-1; j++){
            dis += pairwiseDistance[trialCurrentPopulation[i][j]][trialCurrentPopulation[i][j+1]]; 
        }
        dis += pairwiseDistance[trialCurrentPopulation[i][j]][source];
        trialPopulationTotalDistance[i] = dis;
    }

    

}

//currentPopulation
//trialCurrentPopulation

// currentPopulationTotalDistance
// trialPopulationTotalDistance

void selection(){ 
    

    for(int i=0; i<populationSize; i++){
        if(trialPopulationTotalDistance[i] < currentPopulationTotalDistance[i]){
            for(int j= 0; j<NumberOfCities; j++){
                currentPopulation[i][j] = trialCurrentPopulation[i][j];
            }
            currentPopulationTotalDistance[i] = trialPopulationTotalDistance[i];
        }
    }

}

void printAfterCRPopulation(){
    for(int i=0; i<populationSize; i++){
        for(int j=0; j<NumberOfCities; j++){
            cout<<trialCurrentPopulation[i][j]<<" ";   
        }
        cout<<" Distance:"<<trialPopulationTotalDistance[i];
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
    cout<<"***************************************************************************************************\n";
    cout<<"Current Population: \n";
    printCurrentPopulation();
    cout<<"***************************************************************************************************\n";

    int currentGeneration=0;
    
    // iterations for generations
    while(currentGeneration< totalGenerations){  
        // cout<<"***************************************************************************************************\n";
        // cout<<"Current Generation="<<currentGeneration<<"\n";    
        
        // cout<<"\nAfter Mutation, Population: \n";
        mutation();
        crossover();
        // cout<<"\nAfter Crossover, Population: \n";
        // printAfterCRPopulation();
        selection();
        // cout<<"\nAfter Selection, Population: \n";
        printCurrentPopulation();
    
        currentGeneration++;
    }

    cout<<"***************************************************************************************************\n";
    return 0;
}