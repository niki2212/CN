#include <bits/stdc++.h>
using namespace std;

int main()
{
    cout<<"Enter the number of nodes or routers in the network:";
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

    vector<vector<int>> routing_path(num_of_nodes, vector<int>(num_of_nodes));
    
    for(int i=0; i<num_of_nodes; i++)
    {
        for(int j=0; j<num_of_nodes; j++)
        {
            routing_path[i][j] = weight_matrix[i][j];
        }
    }

    int flag = 0;
    do 
    {
        flag = 0;
        for (int i = 0; i < num_of_nodes; i++) 
        {
            for (int j = 0; j < num_of_nodes; j++) 
            {
                if (i == j) 
                {
                    continue;
                }
                if (weight_matrix[i][j] != -1) 
                {
                  for(int k = 0; k<num_of_nodes; k++)
                  {
                        if(routing_path[i][k] == -1 && routing_path[j][k] != -1)
                        {
                            routing_path[i][k] = routing_path[i][j]+routing_path[j][k];
                            flag++;
                        }
                        else if(routing_path[i][k]!=-1 && routing_path[j][k]!=-1)
                        {
                            if(min(routing_path[i][k],routing_path[i][j]+routing_path[j][k]) != routing_path[i][k])
                            {
                                flag++;
                            }
                            routing_path[i][k] = min(routing_path[i][k],routing_path[i][j]+routing_path[j][k]);
                        }
                    }
                }
            }
        }
    } while (flag != 0);

    for (int i = 0; i < num_of_nodes; i++)
    {
    cout<<endl;
    cout << "Final routing path for router " << i + 1 << ":" << endl;
        for (int j = 0; j < num_of_nodes; j++) 
        {
            cout << "via " << j + 1 << " Distance " << routing_path[i][j] << endl;
        }
    }
    return 0;
}