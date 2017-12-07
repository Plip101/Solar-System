#include "aitMesh.h"
#include <sstream>
#include <map>
#include <iostream>
#include <assert.h>
using namespace std;

bool aitMesh::loadFromObj(string path)
{
	
	string line;  
	vector<glm::vec3>v; //Vector for position
	vector<glm::vec3>vn; //Vector for normal
	ifstream myfile(path); //Ifstream (read) the filepath, IE monkey.obj
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (!line.find("v ")) //Checks if the "line" has a "v"...FOR SOME REASON IT DOES THE OPPOSITE SO I USED A ! to check if it doesnt
			{
				stringstream ss(line.substr(2)); //Puts the buffer 2 places in, So it skips the space and gets the number
				glm::vec3 pos;
				float x, y, z;
				ss >> x; //Write the current buffer to x, y and z
				ss >> y;
				ss >> z;
				pos = glm::vec3(x, y, z); //populate the vector(position) with normal
				v.push_back(pos); //Push the current vertex into the vector
				

			}
			else if (!line.find("vn")) // Repeat except checking for "vn" which is the normal, Again works the opposite of how it should
			{
				stringstream ss(line.substr(2));

				glm::vec3 normal;
				float x, y, z;
				ss >> x;
				ss >> y;
				ss >> z;
				normal = glm::vec3(x, y, z);
				vn.push_back(normal);
			}
			else if (!line.find("f")) // Repeat except for "f" which is the faces...
			{
				int pos;
				int normal;
				char slash; //Using a char, write the buffer to it and never use it
				stringstream ss(line.substr(2));
				for (int i = 0; i < 3; i++) //Each face has 3 points which make up the triangle so 3 loops
				{
					ss >> pos; // Write the buffer which is the first number, Position
					ss >> slash; //Write the buffer which is on the /
					ss >> slash; //Write the buffer which is on the /
					ss >> normal; //Write the buffer which is on the normal
					
					aitVertex vertex(v[pos-1],vn[normal-1]); //Populate the final vertex with the X,Y,Z of the position + normal aswell
															 //as putting the f pos + normal into the vertex, We use -1 as vectors start at 0
					vertices.push_back(vertex);	//Push the vertex to the final vector

				}
			}
			
		
			
		}
		myfile.close();
	}
	
	else cout << "Unable to open file";

	

	/*aitVertex v1(glm::vec3(0.000000, 1.000000, 0.000000), glm::vec3(0.000000, 0.000000, 1.000000));
	aitVertex v2(glm::vec3(-1.000000, -1.000000, 0.000000), glm::vec3(0.000000, 0.000000, 1.000000));
	aitVertex v3(glm::vec3(1.000000, -1.000000, 0.000000), glm::vec3(0.000000, 0.000000, 1.000000));
	
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);*/
	
	return true;
}