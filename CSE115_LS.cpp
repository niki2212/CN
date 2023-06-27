#include <bits/stdc++.h>
using namespace std;

int main()
{
    cout<<"Enter the number of nodes or routers in the network: ";
    int num_of_nodes;  
    cin>>num_of_nodes;

    cout<<"Enter the weight or cost matrix: "<<endl;
    vector<vector<int>> weight_matrix(num_of_nodes, vector<int>(num_of_nodes));
    for (int i = 0; i < num_of_nodes; i++) 
    {
        for (int j = 0; j < num_of_nodes; j++) 
        {
            cin >> weight_matrix[i][j];
        }
    }
    int initial_router;
    weight_matrix[0][0] = initial_router;

    vector<vector<int>> linkstate(num_of_nodes,vector<int>(num_of_nodes));
    vector<bool> visited(num_of_nodes,false);
    linkstate[0] = weight_matrix[initial_router];
    visited[initial_router] = true;

    for(int i = 0; i<num_of_nodes-1; i++)
    {
        int minimum = INT_MAX;
        int minimumNode;
        for(int j = 0; j<num_of_nodes; j++)
        {

            if(visited[j] == false && linkstate[i][j] != -1 && linkstate[i][j]<minimum)
            {
                minimum = linkstate[i][j];
                minimumNode = j;
            }

        }
        visited[minimumNode] = true;

        for(int j = 0;j<num_of_nodes;j++)
        {    
            if(visited[j] == true)
            {
                linkstate[i+1][j] = linkstate[i][j];
                continue;
            }
            if(weight_matrix[minimumNode][j] == -1)
            {
                linkstate[i+1][j] = linkstate[i][j];
            }
            else if(linkstate[i][j] == -1)
            {
                linkstate[i+1][j] = linkstate[i][minimumNode]+weight_matrix[minimumNode][j];
            }
            else
            {
                linkstate[i+1][j] = min(linkstate[i][j], linkstate[i][minimumNode]+weight_matrix[minimumNode][j]);
            }
        }
    }


    for (int i = 0; i < num_of_nodes; i++)
    {
            cout << "Router " << i + 1 << " Distance " <<linkstate[num_of_nodes-1][i] << endl;     
    }

    return 0;
}